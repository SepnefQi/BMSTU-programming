;start unit-tests
(define-syntax test
  (syntax-rules ()
    ((_ fx res)
     (let ((q 'fx) (ans res))
       (list q res)))))


(define (run-test x)
  (display (car x))
  (let ((returned (eval (car x) (interaction-environment))) (expected (cadr x)))
    (if (equal? returned expected)
        (begin
          (display " ok\n")
          #t)
        (begin
          (display " fail\n")
          (display "  Expected:")
          (display expected)
          (display "\n  Returned:")
          (display returned)
          (newline)
          #f))))


(define (run-tests l)
  (define (loop b a)
    (if (null? a)
        b
        (loop (and (run-test (car a)) b) (cdr a))))
  (loop #t l))
;end unit-tests

(define (elem-index elem program index)
  (if (< index (vector-length program))
      (if (equal? (vector-ref program index) elem)
          index
          (elem-index elem program (+ index 1)))
      #f))

(define (interpret program stack)
  (let loop ((stac stack) (i 0) (define-elems '()) (return '()))
    (if (= (vector-length program) i)
        stac
        (let ((elem (vector-ref program i)))
          (cond
            ((number? elem) (loop (cons elem stac) (+ i 1) define-elems return))
            ((equal? elem '+) (loop (cons (+ (cadr stac) (car stac)) (cddr stac)) 
            (+ i 1) define-elems return))
            ((equal? elem '-) (loop (cons (- (cadr stac) (car stac)) (cddr stac)) 
            (+ i 1) define-elems return))
            ((equal? elem '*) (loop (cons (* (cadr stac) (car stac)) (cddr stac)) 
            (+ i 1) define-elems return))
            ((equal? elem '/) (loop (cons (/ (cadr stac) (car stac)) (cddr stac)) 
            (+ i 1) define-elems return))
            ((equal? elem 'mod) (loop (cons (remainder (cadr stac) (car stac)) 
            (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem 'neg) (loop (cons (* (car stac) -1) (cdr stac)) 
            (+ i 1) define-elems return))
            ((equal? elem '=) (loop (cons (if (= (cadr stac) (car stac)) -1 0) 
            (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem '>) (loop (cons (if (> (cadr stac) (car stac)) -1 0) 
            (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem '<) (loop (cons (if (< (cadr stac) (car stac)) -1 0) 
            (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem 'not) (loop (cons (if (= elem 0) -1 0) (cdr stac)) 
            (+ i 1) define-elems return))
            ((equal? elem 'and) (loop (cons (if (and (not(= (car stac) 0)) 
            (not(= (cadr stac) 0))) -1 0) (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem 'or) (loop (cons (if (or (not(= (car stac) 0)) 
            (not(= (cadr stac) 0))) -1 0) (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem 'drop) (loop (cdr stac) (+ i 1) define-elems return))
            ((equal? elem 'swap) (loop (append (list (cadr stac) (car stac)) 
            (cddr stac)) (+ i 1) define-elems return))
            ((equal? elem 'dup) (loop (cons (car stac) stac) (+ i 1) 
            define-elems return))
            ((equal? elem 'over) (loop (cons (cadr stac) stac) (+ i 1) 
            define-elems return))
            ((equal? elem 'rot) (loop (append (list (caddr stac) (cadr stac) 
            (car stac)) (cdddr stac)) (+ i 1) define-elems return))
            ((equal? elem 'depth) (loop (cons (length stac) stac) (+ i 1) 
            define-elems return))
            ((equal? elem 'define) (loop stac (+ (elem-index 'end program i) 1) 
            (cons (list (vector-ref program (+ i 1)) (+ i 2)) define-elems) return))
            ((or (equal? elem 'end) (equal? elem 'exit)) (loop stac (car return) 
            define-elems (cdr return)))
            ((equal? elem 'if) (if (zero? (car stac))
                                   (loop (cdr stac) (+ (elem-index 'endif program i) 1)
                                         define-elems return)
                                   (loop (cdr stac) (+ i 1) define-elems return)))
            ((equal? elem 'endif) (loop stac (+ i 1) define-elems return))
            (else (loop stac (cadr (assq elem define-elems)) define-elems 
            (cons (+ i 1) return)))
            ;Если никакое слово из раннее введённых не подошло, то значит, 
            мы его определили в define
            ;define-elems  у нас словарь (слово его-значение), 
            ;assq - ищет в нём подходящую пару и возвращает её
            ;Пример: (assq 5 '((2 3) (5 7) (11 13))) -> (5 7)
            )))))

;Как должно быть: (interpret #(10 5 -) '()) -> (5)
;                 (interpret #(3 2 mod) '()) -> (1)
            
(define the-tests
  (list (test (interpret #(   define abs
                               dup 0 <
                               if neg endif
                               end
                               9 abs
                               -9 abs      )(quote ()))
              '(9 9))
        (test (interpret #(   define =0? dup 0 = end
                               define <0? dup 0 < end
                               define signum
                               =0? if exit endif
                               <0? if drop -1 exit endif
                               drop
                               1
                               end
                               0 signum
                               -5 signum
                               10 signum       ) (quote ()))
              '(1 -1 0))
        (test (interpret #(   define -- 1 - end
                               define =0? dup 0 = end
                               define =1? dup 1 = end
                               define factorial
                               =0? if drop 1 exit endif
                               =1? if drop 1 exit endif
                               dup --
                               factorial
                               *
                               end
                               0 factorial
                               1 factorial
                               2 factorial
                               3 factorial
                               4 factorial     ) (quote ()))
              '(24 6 2 1 1))
        (test (interpret #(   define =0? dup 0 = end
                               define =1? dup 1 = end
                               define -- 1 - end
                               define fib
                               =0? if drop 0 exit endif
                               =1? if drop 1 exit endif
                               -- dup
                               -- fib
                               swap fib
                               +
                               end
                               define make-fib
                               dup 0 < if drop exit endif
                               dup fib
                               swap --
                               make-fib
                               end
                               10 make-fib     ) (quote ()))
              '(0 1 1 2 3 5 8 13 21 34 55))
        (test (interpret #(   define =0? dup 0 = end
                               define gcd
                               =0? if drop exit endif
                               swap over mod
                               gcd
                               end
                               90 99 gcd
                               234 8100 gcd    ) '())
              '(18 9))
        ))
(run-tests the-tests)