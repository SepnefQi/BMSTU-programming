(define (uniq xs)
  (cond
    ((null? xs) '())
    ((null? (cdr xs)) xs)
    ((equal? (car xs) (cadr xs)) (uniq (cdr xs)))
    (else (cons (car xs) (uniq (cdr xs)))) 
  )
  )

(define (delete pred? xs)
  (cond
    ((null? xs) '())
    ((pred? (car xs)) (delete pred? (cdr xs)))
    (else (cons (car xs) (delete pred? (cdr xs))))
  )
  )

(define (polynom xs x)
  (cond
    ((null? xs) 0)
    (else (+ (* (car xs) (expt x (- (length xs) 1))) (polynom (cdr xs) x))))
  )

(define (intersperse e xs)
  (cond
    ((null? xs) '())
    ((null? (cdr xs)) xs)
    (else (cons (car xs)
                (cons e
                      (intersperse e (cdr xs)))))))

(define (all? pred? xs)
  (or (null? xs) (and (pred? (car xs)) (all? pred? (cdr xs))))
  )

(define (f x) (+ x 2))
(define (g x) (* x 3))
(define (h x) (- x))

(define (o . xs)
  (lambda (x)
    (if (null? xs)
        x
        ((car xs) ((apply o (cdr xs)) x)))))(define (hello name)
  (display "Привет, ")
  (display name)
  (display "!\n"))