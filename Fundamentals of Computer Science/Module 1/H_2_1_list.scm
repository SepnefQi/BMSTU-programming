(define (my-range a b d) ;O((b-a)/d) (O(b-a))
  (if (< a b)
      (cons a (my-range (+ a d) b d))
      '()))

(define (my-flatten xs)
  (reverse (flatrec xs '()))) ;O(n^2)

(define (flatrec xs res)
    (cond ((null? xs) res)
        ((list? xs)(flatrec (cdr xs) (flatrec (car xs) res)))
           (else (cons xs res))))

(define (my-element? x xs) ;O(len(xs))
  (cond
    ((equal? xs '()) #f)
    ((equal? x (car xs)) #t)
    (else (my-element? x (cdr xs)))))

(define (my-filter pred? xs) ; O(len(xs))
  (cond
    ((null? xs) '())
    ((pred? (car xs)) (cons (car xs) (my-filter pred? (cdr xs))))
    (else (my-filter pred? (cdr xs)))))

(define (my-fold-left op xs) ;O(len(xs))
  (if (null? (cdr xs))
      (car xs)
      (my-fold-left op (cons (op (car xs) (cadr xs)) (cddr xs)))))

(define (my-fold-right op xs) ;O(len(xs))
  (if (null? (cdr xs))
      (car xs)
      (op (car xs) (my-fold-right op (cdr xs)))))

(define (reverse! xs) ; O(n^2)
  (cond
    ((null? xs) '())
    ((null? (cdr xs)) (list (car xs)))
    (else (append! (reverse! (cdr xs)) (list (car xs))))))

(define (append! . lst) ; O(n)
  (define (loop lst res)
    (if (null? lst)
        res
        (if (null? res)
            (if (null? (car lst))
                
                (loop (cdr lst) res)
                (loop (cdr lst) (car lst)))
            (begin
              (set-cdr! (list-tail res (- (length res) 1)) (car lst))
              (loop (cdr lst) res)))))
  (if (null? lst)
      '()
      (loop (cdr lst) (car lst))))