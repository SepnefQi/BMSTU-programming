(define call/cc call-with-current-continuation)
(define false #f)

;#1
(define-syntax use-assertions
  (syntax-rules ()
    ((use-assertions) (call/cc (lambda (f) (set! false f))))))

(define-syntax assert
  (syntax-rules ()
    ((assert exp)
     (if (not exp)
         (begin
           (display "FAILED: ")
           (write (quote exp))
           (newline)
           (false))))))

(use-assertions)

(define (1/x x)
  (assert (not (zero? x))) ; Утверждение: x ДОЛЖЕН БЫТЬ ≠ 0
  (/ 1 x))

(map 1/x '(1 2 3 4 5)); ВЕРНЕТ список значений в программу

(map 1/x '(-2 -1 0 1 2)); ВЫВЕДЕТ в консоль сообщение и завершит работу программы

;#2
(define (proc-desugar source dest)
  (letrec(
          (in (open-input-file source))
          (out (open-output-file dest))
          (loop (lambda ()
                  (let ((cur (read in)))
                    (if (eof-object? cur)
                        (begin
                          (close-output-port out)
                          (close-input-port in))
                        (begin
                          (if (and (list? cur)
                                   (equal? (car cur) 'define)
                                   (list? (cadr cur)))
                              (write '(define ,(caadr cur)
                                        (lambda ,(cdadr cur) ,(cddr cur))) out))
                          (write cur out)
                          (write #\newline out)
                          (loop)))))))
    (loop)))
;ТЕСТ
;(proc-desugar "./lab 4.rkt" "./test1.rkt")
                                                              
  

(define (file-notvoid-lines-count file)
  (with-input-from-file  file (lambda ()
                                (let loop ((k 0))
                                  (let ((cur (read-char)))
                                    (cond ((eof-object? cur)
                                           k)
                                          ((and (not (equal? cur #\newline))
                                                (or (eof-object? (peek-char))
                                                    (equal? (peek-char) #\newline)))
                                           (loop (+ k 1)))
                                          (else (loop k))))))))

;eof-object? - предикат, проверяющий, является ли текущий объект
;объектом конца файла
;with-input-from-file - процедура, временно меняющая текущий входной
;порт на результат открытия файла во время применения какой-то процедуры
;call-with-input-file - создаёт новый входной порт для файла и передаёт процедуре
(newline)
(display (file-notvoid-lines-count "./lab 4.rkt"))
(newline)

;#3
(define (tribonacci n)
  (cond
    ((<= n 1) 0)
    ((= n 2) 1)
    (else (+ (tribonacci (- n 1)) (tribonacci (- n 2)) (tribonacci (- n 3))))))

(define (tribonacci-mem n)
  (let ((memo (make-vector (+ n 1))))
    (let loop ((n n))
      (cond
        ((<= n 1) 0)
        ((= n 2) 1)
        (else (if (zero? (vector-ref memo n))
                  (vector-set! memo n (+ (loop (- n 1))
                                         (loop (- n 2))
                                         (loop (- n 3)))))
              (vector-ref memo n))))))
(newline)
(tribonacci-mem 28)
(tribonacci 28)
(newline)

;#4
(define-syntax lazy-cons
  (syntax-rules ()
    ((_ a b) (cons a (delay b)))))

(define (lazy-car p)
  (car p))
;(define lazy-car car)

(define (lazy-cdr p)
  (force (cdr p)))

(define (lazy-head xs k)
  (if (<= k 0)
      '()
      (cons (lazy-car xs) (lazy-head (lazy-cdr xs) (- k 1)))))

(define (lazy-ref xs k)
  (if (= k 0)
      (lazy-car xs)
      (lazy-ref (lazy-cdr xs) (- k 1))))

;(define (lazy-map proc xs)
;  (if (null? xs)
;      '()
;      (lazy-cons (proc (lazy-car xs)) (lazy-map proc (lazy-cdr xs)))))
(define (lazy-map proc . xs)
  (if (memq '() xs)
      '()
      (lazy-cons (apply proc (map lazy-car xs))
                 (apply lazy-map proc (map lazy-cdr xs)))))

(define (lazy-zip xs ys)
  (if (or (null? xs) (null? ys))
      '()
      (lazy-cons (list (lazy-car xs) (lazy-car ys))
                 (lazy-zip (lazy-cdr xs) (lazy-cdr ys)))))

(define ones (lazy-cons 1 ones))
(write (lazy-head ones 5))
(newline)
(define fibonacci (lazy-cons 1 (lazy-cons 1 (lazy-map + fibonacci (lazy-cdr fibonacci)))))
(newline)
(write (lazy-ref fibonacci 100))
(newline)
(write (lazy-head fibonacci 10))
(newline)


;#5
(define-syntax when
  (syntax-rules ()
    ((_ cond? body ...)
     (and cond? (begin body ...)))))

(define-syntax for
  (syntax-rules (in as)
    ((_ i in xs body ...)
     (let loop ((xss xs))
       (if (not (null? xss))
           (let ((i (car xss)))
             body ...
             (loop (cdr xss))))))
    ((_ xs as i body ...)
     (for i in xs body ...))))

(newline)
(define x 1)
(when (> x 0) (display "x > 0")  (newline))
(define x -1)
(when (> x 0) (display "x > 0")  (newline))
(newline)

(for i in '(1 2 3)
  (for j in '(4 5 6)
    (display (list i j))
    (newline)))

(newline)

(for '(1 2 3) as i
  (for '(4 5 6) as j
    (display (list i j))
    (newline)))

(define-syntax repeat
  (syntax-rules (until)
    ((repeat (body ...) until cond?)
     (let loop ()
       body ...
       (if (not cond?) (loop))))))

(newline)
(let ((i 0)
      (j 0))
  (repeat ((set! j 0)
           (repeat ((display (list i j))
                    (set! j (+ j 1)))
                   until (= j 3))
           (set! i (+ i 1))
           (newline))
          until (= i 3)))