;#1
(define-syntax trace
  (syntax-rules ()
    ((_ x)
     (let ((res x))
       (write 'x)
       (display " => ")
       (write res)
       (newline)
       res))))

(define (zip . xss)
  (if (or (null? xss)
          (null? (trace (car xss))))
      '()
      (cons (map car xss)
            (apply zip (map cdr (trace xss))))))

;#2
(define-syntax test
  (syntax-rules ()
    ((test expression var)
     (list 'expression var))))

(define (run-test t)
  (begin
    (display (car t))
    (let ((te (eval (car t) (interaction-environment))))
      (if (equal? te (cadr t))
          (begin (display " ok\n") #t)
          (begin (display "FAIL\n Expected: ")
                 (write (cadr t))
                 (display "\n Returned: ")
                 (write te) (newline) #f)))))

(define (and-fold x . xs)
  (if (null? xs)
      x
      (and x (apply and-fold xs))))

(define (run-tests ts)
  (if (null? ts)
      #t
      (apply and-fold (list (run-test (car ts))
                            (run-tests (cdr ts))))))

(define (signum x)
  (cond
    ((< x 0) -1)
    ((= x 0) 1) ; Ошибка здесь!
    (else    1)))

(define the-tests
  (list (test (signum -2) -1)
        (test (signum  0)  0)
        (test (signum  2)  1)))

(run-tests the-tests)

;#3
(define ufill (lambda (a b)
                (define (uget x k) (cond
                                     ((list? x) (list-ref x k))
                                     ((vector? x) (vector-ref x k))
                                     ((string? x) (string-ref x k))))
                (define (uset! x k v) (cond
                                        ((list? x) (set-car! (list-tail x k) v))
                                        ((vector? x) (vector-set! x k v))
                                        ((string? x) (string-set! x k v))))
                (define (ulen x) (cond
                                   ((list? x) (length x))
                                   ((vector? x) (vector-length x))
                                   ((string? x) (string-length x))))
                (define loop (lambda (i) (begin
                                           (uset! b i (uget a i))
                                           (if (not (= i 0)) (loop (- i 1))))))
                (loop (- (ulen a) 1))))
            



(define (reverse! seq . xs)
  (cond
    ((null? xs)
     (cond
       ((list? seq) (ufill (reverse seq) seq))
       ((vector? seq) (ufill (list->vector (reverse (vector->list seq))) seq))
       ((string? seq) (ufill (list->string (reverse (string->list seq))) seq))
       ));If only one argument
    ((not(null? xs))
     (cond
       ((list? (car xs))
        (cond
          ((list? seq) (ufill (reverse seq) (car xs)))
          ((vector? seq) (ufill (reverse (vector->list seq)) (car xs)))
          ((string? seq) (ufill (reverse (string->list seq)) (car xs)))
          )
        )
       ((vector? (car xs))
        (cond
          ((list? seq) (ufill (list->vector (reverse seq)) (car xs)))
          ((vector? seq) (ufill (list->vector (reverse (vector->list seq))) (car xs)))
          ((string? seq) (ufill (list->vector (reverse (string->list seq))) (car xs)))
          )
        )
       ((string? (car xs))
        (cond
          ((list? seq) (ufill (list->string (reverse seq)) (car xs)))
          ((vector? seq) (ufill (list->string (reverse (vector->list seq))) (car xs)))
          ((string? seq) (ufill (list->string (reverse (string->list seq))) (car xs)))
          )
        (values seq xs)
        )
       ))))

(define xs '(a b c d e))
(define ys (vector 1 2 3 4 5))
(define zs (string #\h #\e #\l #\l #\o))
(define as '(a b c))
(define bs (append '(x y z) as))
(set-car! as 1)
(define the-tests
  (list (test (let ((xs xs))
                (reverse! xs)
                (list xs))
              '((e d c b a)))
        (test (let ((ys ys))
                (reverse! ys)
                (list ys))
              '(#(5 4 3 2 1)))
        (test (let ((zs zs))
                (reverse! zs)
                (list zs))
              '("olleh"))
        (test (let ((bs bs))
                (reverse! bs)
                (list bs))
              '((c b 1 z y x)))))

(run-tests the-tests)

(define xs (list 'a 'b 'c 'd 'e))
(define ys (vector 1 2 3 4 5))
(define zs (string #\h #\e #\l #\l #\o))
(define the-tests
  (list (test (let ((xs xs)
                (ys ys))
                (reverse! xs ys)
                (list xs ys))
              '((a b c d e) #(e d c b a)))
        (test (let ((zs zs)
                (xs xs))
                (reverse! zs xs)
                (list zs xs))
              '("hello" (#\o #\l #\l #\e #\h)))))

(run-tests the-tests)

;#4
(define (factorize xy)
  (define x (list-ref (list-ref xy 1) 1))
  (define y (list-ref (list-ref xy 2) 1))
  (define pow (list-ref (list-ref xy 1) 2))
  (if (eq? pow 2)
      (if (eq? (car xy) '-)
          `(* (- ,x ,y) (+ ,x ,y))
          #f
          )
      (if (eq? (car xy) '-)
          `(* (- ,x ,y) (+ (+ (expt ,x 2) (expt ,y 2)) (* ,x ,y)))
          `(* (+ ,x ,y) (- (+ (expt ,x 2) (expt ,y 2)) (* ,x ,y)))
          )))

(define the-tests
  (list (test (factorize '(- (expt x 2) (expt y 2))) '(* (- x y) (+ x y)))
        (test (factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2)))
              '(* (- (+ first 1) (- second 1))
                  (+ (+ first 1) (- second 1))))
        (test (eval (list (list 'lambda 
                                '(x y) 
                                (factorize '(- (expt x 2) (expt y 2))))
                          1 2)
                    (interaction-environment)) -3)
        (test (factorize '(- (expt a 3) (expt b 3)))
              '(* (- a b) (+ (+ (expt a 2) (expt b 2)) (* a b))))
        (test (factorize '(+ (expt a 3) (expt b 3)))
              '(* (+ a b) (- (+ (expt a 2) (expt b 2)) (* a b))))
        ))

(run-tests the-tests)

;tests for #1
(define counter
  (let ((n 0))
    (lambda ()
      (set! n (+ n 1))
      n)))

(+ (trace (counter))
   (trace (counter)))

(define counter-tests
  (list (test (counter) 3)
        (test (counter) 77) ; ошибка
        (test (counter) 5)))

(run-tests counter-tests)