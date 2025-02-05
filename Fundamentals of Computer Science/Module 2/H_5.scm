'feature-if-else
'feature-nested-if
'feature-while-loop
'feature-repeat-loop
'feature-for-loop
'feature-break-continue
'feature-switch-case
;'feature-hi-level
'feature-tail-call
'feature-global

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

(define (set1 elem x xs) ;(count 0) 5 ((count 1) (six 64) (space 1957))
  (if (null? xs)
      '()
      (if (equal? (car elem) (caar xs))
          (cons (list (car elem) x) (set1 elem x (cdr xs)))
          (cons (car xs) (set1 elem x (cdr xs))))))

(define (findpare a1 a2 program i)
  (if (not (= (vector-length program) i))
      (if (= (+ (elem-index a1 program i) 1) (elem-index a2 program i))
          (elem-index a2 program i)
          (findpare a1 a2 program (+ i 1)))
      #f))
          

(define (elem-index elem program index)
  (if (< index (vector-length program))
      (if (equal? (vector-ref program index) elem)
          index
          (elem-index elem program (+ index 1)))
      #f))

(define (interpret program stack)
  (define (find-else start)
    (define (loopif index cif celse cend)
      (cond ((and (equal? (vector-ref program index) 'else)
                  (= (+ 1 celse) cif))
             (+ 1 index))
            ((equal? (vector-ref program index) 'else)
             (loopif (+ 1 index) cif (+ 1 celse) cend))
            ((and (equal? (vector-ref program index) 'endif)
                  (= (+ 1 cend) cif))
             (+ 1 index))
            ((equal? (vector-ref program index) 'endif)
             (loopif (+ 1 index) cif celse (+ 1 cend)))
            ((equal? (vector-ref program index) 'if)
             (loopif (+ 1 index) (+ 1 cif) celse cend))
            (else
             (loopif (+ 1 index) cif celse cend))))
    (loopif start 0 0 0))
  (define (find-wend start)
    (define (loop index cntw cntend)
      (cond ((and (equal? (vector-ref program index) 'wend)
                  (= (+ 1 cntend) cntw))
             (+ 1 index))
            ((equal? (vector-ref program index) 'wend)
             (loop (+ 1 index) cntw (+ 1 cntend)))
            ((equal? (vector-ref program index) 'while)
             (loop (+ 1 index) (+ 1 cntw) cntend))
            (else
             (loop (+ 1 index) cntw cntend))))
    (loop start 0 0))
  (let loop ((stac stack) (i 0) (define-elems '()) (return '()) (vlog 0) (constants '()))
    (if (= (vector-length program) i)
        stac
        (let ((elem (vector-ref program i)))
          (cond
            ((equal? elem 'if)
             (if (zero? (car stac))
                 (loop (cdr stac) (find-else i) define-elems return vlog constants)
                 (loop (cdr stac) (+ i 1) define-elems return vlog constants)))
                     
            ;if --------
            ((number? elem) (loop (cons elem stac) (+ i 1) define-elems return vlog constants))
            ((equal? elem '+) (loop (cons (+ (cadr stac) (car stac)) (cddr stac)) 
                                    (+ i 1) define-elems return vlog constants))
            ((equal? elem '-) (loop (cons (- (cadr stac) (car stac)) (cddr stac)) 
                                    (+ i 1) define-elems return vlog constants))
            ((equal? elem '*) (loop (cons (* (cadr stac) (car stac)) (cddr stac)) 
                                    (+ i 1) define-elems return vlog constants))
            ((equal? elem '/) (loop (cons (quotient (cadr stac) (car stac)) (cddr stac)) 
                                    (+ i 1) define-elems return vlog constants))
            ((equal? elem 'mod)
             (loop (cons (remainder (cadr stac) (car stac))
                         (cddr stac)) (+ i 1) define-elems return vlog constants))
            ((equal? elem 'neg) (loop (cons (* (car stac) -1) (cdr stac)) 
                                      (+ i 1) define-elems return vlog constants))
            ((equal? elem '=) (loop (cons (if (= (cadr stac) (car stac)) -1 0) 
                                          (cddr stac)) (+ i 1) define-elems return vlog constants))
            ((equal? elem '>) (loop (cons (if (> (cadr stac) (car stac)) -1 0) 
                                          (cddr stac)) (+ i 1) define-elems return vlog constants))
            ((equal? elem '<) (loop (cons (if (< (cadr stac) (car stac)) -1 0) 
                                          (cddr stac)) (+ i 1) define-elems return vlog constants))
            ((equal? elem 'not) (loop (cons (if (= (car stac) 0) -1 0) (cdr stac)) 
                                      (+ i 1) define-elems return vlog constants))
            ((equal? elem 'and) (loop (cons (if (and (not(= (car stac) 0)) 
                                                     (not(= (cadr stac) 0))) -1 0) (cddr stac))
                                      (+ i 1) define-elems return vlog constants))
            ((equal? elem 'or) (loop (cons (if (or (not(= (car stac) 0)) 
                                                   (not(= (cadr stac) 0))) -1 0) (cddr stac))
                                     (+ i 1) define-elems return vlog constants))
            ((equal? elem 'drop) (loop (cdr stac) (+ i 1) define-elems return vlog constants))
            ((equal? elem 'swap) (loop (append (list (cadr stac) (car stac)) 
                                               (cddr stac)) (+ i 1) define-elems return vlog constants))
            ((equal? elem 'dup) (loop (cons (car stac) stac) (+ i 1) 
                                      define-elems return vlog constants))
            ((equal? elem 'over) (loop (cons (cadr stac) stac) (+ i 1) 
                                       define-elems return vlog constants))
            ((equal? elem 'rot) (loop (append (list (caddr stac) (cadr stac) 
                                                    (car stac)) (cdddr stac))
                                      (+ i 1) define-elems return vlog constants))
            ((equal? elem 'depth) (loop (cons (length stac) stac) (+ i 1) 
                                        define-elems return vlog constants))
            ((equal? elem 'while)
             (if (zero? (car stac))
                 (loop (cdr stac) (find-wend i) define-elems return vlog constants)
                 (loop (cdr stac) (+ i 1) define-elems (cons i return) vlog constants)))
            ((equal? elem 'repeat) (loop stac (+ i 1) define-elems (cons i return) vlog constants))
            ((equal? elem 'until)
             (if (not (zero? (car stac)))
                 (loop (cdr stac) (+ i 1) define-elems (cdr return) vlog constants)
                 (loop (cdr stac) (car return) define-elems (cdr return) vlog constants)))
            ((equal? elem 'switch)
             (if (and (elem-index 'case program i)
                      (< (elem-index 'case program i) (elem-index 'endswitch program i)))
                 (loop stac (elem-index 'case program i) define-elems return vlog constants)
                 (loop (cdr stac) (elem-index 'endswitch i) define-elems return vlog constants)))
            ((and (equal? elem 'case) (not (equal? (vector-ref program (- i 1)) 'exitcase))
                  (not (equal? (vector-ref program (- i 1)) 'switch)) (= vlog 1))
             (loop stac (+ i 2) define-elems return vlog constants))
            ((equal? elem 'case)
             (if (equal? (car stac) (vector-ref program (+ i 1)))
                 (loop (cdr stac) (+ i 2) define-elems return (+ vlog 1) constants)
                 (if (and (elem-index 'case program (+ i 1))
                          (< (elem-index 'case program (+ i 1)) (elem-index 'endswitch program i)))
                     (loop stac (elem-index 'case program (+ i 1)) define-elems return vlog
                           constants)
                     (loop (cdr stac) (elem-index 'endswitch program i) define-elems return vlog
                           constants)
                     )))
            ((equal? elem 'exitcase)
             (loop stac (elem-index 'endswitch program i) define-elems return (- vlog 1)
                   constants))
            ((and (equal? elem 'endswitch) (= vlog 0))
             (loop stac (+ i 1) define-elems return vlog constants))
            ((equal? elem 'endswitch)
             (loop stac (+ i 1) define-elems return (- vlog 1) constants))
            
            ((equal? elem 'for) (loop (cddr stac) (+ i 1) define-elems
                                      (append (list (cadr stac) (car stac) (+ i 1)) return)
                                      vlog constants))
            ((equal? elem 'i) (loop (cons (car return) stac) (+ i 1) define-elems
                                    return vlog constants))
            ((equal? elem 'next) (if (>= (car return) (cadr return))
                                     (loop stac (+ i 1) define-elems
                                           (cdddr return) vlog constants)
                                     (loop stac (caddr return) define-elems
                                           (cons (+ (car return) 1) (cdr return))
                                           vlog constants)))
            ((equal? elem '&) (loop  (cons (cadr (assq (vector-ref program (+ i 1)) define-elems))
                                                  stac) (+ i 2)
                                    define-elems return vlog constants))
            ((equal? elem 'lam) (loop (cons (+ i 1) stac) (+ (elem-index 'endlam program i) 1)
                                      define-elems return vlog constants))
            ((equal? elem 'endlam) (loop stac (car return) define-elems
                                         (cdr return) vlog constants))
            ((equal? elem 'apply) (loop (cdr stac) (+ (car stac) 1) define-elems
                                        (cons (+ i 1) return) vlog constants))
            ((equal? elem 'break)
             (cond
               ((and (< (car return) (vector-length program))
                     (equal? (vector-ref program (car return)) 'while))
                (loop stac (+ (elem-index 'wend program i) 1)
                      define-elems (cdr return) vlog constants))
               ((and (< (car return) (vector-length program))
                     (equal? (vector-ref program (car return)) 'repeat))
                (loop stac (+ (elem-index 'until program i) 1)
                      define-elems (cdr return) vlog constants))
               (else (loop stac (+ (elem-index 'next program i) 1)
                           define-elems (cdddr return) vlog constants))
               ))
            ((equal? elem 'continue)
             (cond
               ((and (< (car return) (vector-length program))
                     (equal? (vector-ref program (car return)) 'while))
                (loop stac (car return) define-elems (cdr return) vlog constants))
               ((and (< (car return) (vector-length program))
                     (equal? (vector-ref program (car return)) 'repeat))
                (loop stac (elem-index 'until program i) define-elems
                      return vlog constants))
               ((>= (car return) (cadr return))
                (loop stac (+ i 1)
                      define-elems (cdddr return) vlog constants))
               (else (loop stac (caddr return) define-elems
                           (cons (+ 1 (car return)) (cdr return)) vlog constants))
               ))
               
            ((equal? elem 'define) (loop stac (+ (elem-index 'end program i) 1) 
                                         (cons (list (vector-ref program (+ i 1)) (+ i 2))
                                               define-elems) return vlog constants))
            ((equal? elem 'defvar) (loop stac (+ i 3) define-elems return vlog 
                                         (cons (list (vector-ref program (+ i 1))
                                                     (vector-ref program (+ i 2)))
                                               constants)))
            ((equal? elem 'set) (loop (cdr stac) (+ i 2) define-elems return vlog
                                     (set1 (assq (vector-ref program (+ i 1)) constants)
                                           (car stac) constants)))
            ((equal? elem 'tail) (loop stac (+ (findpare 'define
                                                            (vector-ref program (+ i 1))
                                                            program 0) 1)
                                       define-elems return vlog constants))
            ((or (equal? elem 'end)
                 (equal? elem 'exit)
                 (equal? elem 'wend)) (loop stac (car return)
                                            define-elems (cdr return) vlog constants))
            ((equal? elem 'endif) (loop stac (+ i 1) define-elems return vlog constants))
            ((equal? elem 'else) (loop stac (+ (elem-index 'endif program i) 1)
                                       define-elems return vlog constants))
            ((assq elem define-elems)
             (loop stac (cadr (assq elem define-elems)) define-elems 
                        (cons (+ i 1) return) vlog constants))
            (else (loop (cons (cadr (assq elem constants)) stac) (+ i 1) define-elems return vlog
                       constants))
            ;Если никакое слово из раннее введённых не подошло, то значит, 
            ;мы его определили в define
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
        (test (interpret #(1 if 100 else 200 endif) '()) '(100))
        (test (interpret #(0 if 100 else 200 endif) '()) '(200))
        (test (interpret #(0 if 1 if 2 endif 3 endif 4) '()) '(4))
        (test (interpret #(1 if 2 if 3 endif 4 endif 5) '()) '(5 4 3))
        (test (interpret #(1 if 0 if 2 endif 3 endif 4) '()) '(4 3))
        (test (interpret #(while wend) '(3 7 4 0 5 9)) '(5 9))
        (test (interpret #(define sum
                            dup
                            while + swap dup wend
                            drop
                            end
                            1 2 3 0 4 5 6 sum)
                         '()) '(15 3 2 1))
        (test (interpret #(define power2
                            1 swap dup
                            while
                            swap 2 * swap 1 - dup
                            wend
                            drop
                            end
                            5 power2 3 power2 power2) '()) '(256 32))
        (test (interpret #(1 switch case 0 0 exitcase case 1 1
                             exitcase case 2 2
                             exitcase endswitch 5) '()) '(5 1))
        (test (interpret #(1 switch case 0 0 exitcase
                             case 2 2 exitcase
                             endswitch 5) '()) '(5))
        (test (interpret #(define factorize 2 repeat over over =
              if drop break endif over over mod if 1 + 0 continue
              endif dup rot swap / over 0 until end 12 factorize) (quote ())) '(3 2 2))
        (test (interpret #(define factorize
                             2
                             repeat     ; ... n d
                               over over = if drop break endif
                               over over mod if 1 + 0 continue endif
                               dup      ; ... n d d
                               rot      ; ... d d n
                               swap     ; ... d n d
                               /        ; ... d n/d
                               over     ; ... d n/d d
                             0 until
                           end
                           20 factorize)
                         '())
              '(5 2 2))
        (test (interpret #(define factorize
                             2
                             repeat     ; ... n d
                               over over = if drop break endif
                               over over mod if 1 + 0 continue endif
                               dup      ; ... n d d
                               rot      ; ... d d n
                               swap     ; ... d n d
                               /        ; ... d n/d
                               over     ; ... d n/d d
                             0 until
                           end
                           16 factorize)
                         '())
              '(2 2 2 2))
        (test (interpret #(define factorize
                             2
                             repeat     ; ... n d
                               over over = if drop break endif
                               over over mod if 1 + 0 continue endif
                               dup      ; ... n d d
                               rot      ; ... d d n
                               swap     ; ... d n d
                               /        ; ... d n/d
                               over     ; ... d n/d d
                             0 until
                           end
                           120 factorize)
                         '())
              '(5 3 2 2 2))
        (test (interpret #(define factorize
                             2
                             repeat     ; ... n d
                               over over = if drop break endif
                               over over mod if 1 + 0 continue endif
                               dup      ; ... n d d
                               rot      ; ... d d n
                               swap     ; ... d n d
                               /        ; ... d n/d
                               over     ; ... d n/d d
                             0 until
                           end
                           49 factorize)
                         '())
              '(7 7))
        (test (interpret #(defvar counter 0
             define nextnum
               counter dup 1 + set counter
             end
             nextnum nextnum
             nextnum nextnum +
             nextnum nextnum *)
           '())  '(20 5 1 0))
        (test (interpret #(define F 11 22 33 tail G 44 55 end
             define G 77 88 99 end
             F)
           '()) '(99 88 77 33 22 11))
        (test (interpret #(define =0? dup 0 = end
             define gcd
                 =0? if drop exit endif
                 swap over mod
                 tail gcd
             end
             90 99 gcd
             234 8100 gcd) '()) '(18 9))
        (test (interpret #(define fact
               1 1 rot for i * next
             end
             6 fact 10 fact)
           '()) '(3628800 720))
        (test (interpret #(1 40 for
                               i 3 mod 0 = if continue endif
                               i 22 > if break endif
                               i
                           next)
                         '())
              '(22 20 19 17 16 14 13 11 10 8 7 5 4 2 1))))
(run-tests the-tests)