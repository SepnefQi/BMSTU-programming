(define (my-element? x xs);O(len(xs))
  (cond
    ((equal? xs '()) #f)
    ((equal? x (car xs)) #t)
    (else (my-element? x (cdr xs)))))

(define (list->set xs);O(len(xs))
  (if (null? xs) '()
      (if (my-element? (car xs) (cdr xs))
          (list->set (cdr xs))
          (cons (car xs) (list->set (cdr xs))))))

(define (set? xs);O(len(xs)*len(xs)/2)
  (cond
    ((null? xs) #t)
    ((my-element? (car xs) (cdr xs)) #f)
    (else (set? (cdr xs)))))

(define (union xs ys);O(len(xs)*len(ys))
  (cond
    ((null? xs) ys)
    ((my-element? (car xs) ys) (union (cdr xs) ys))
    (else (cons (car xs) (union (cdr xs) ys)))))

(define (intersection xs ys);O(len(xs)*len(ys))
  (cond
    ((or (null? xs) (null? ys)) '())
    ((my-element? (car xs) ys) (cons (car xs) (intersection (cdr xs) ys)))
    (else (intersection (cdr xs) ys))))
  

(define (difference xs ys);O(len(xs)*len(ys))
  (cond
    ((or (null? ys) (null? xs)) xs)
    ((my-element? (car xs) ys) (difference (cdr xs) ys))
    (else (cons (car xs) (difference (cdr xs) ys)))))

(define (symmetric-difference xs ys);O(2*len(xs)^2*len(ys)^2)
  (union (difference xs ys) (difference ys xs)))

(define (set-eq? xs ys);O((len(xs)+len(ys))^2)
  (and (set? xs) (set? ys) (equal? (symmetric-difference xs ys) '())))