;O(n^2) ( O(len(xs)^2) )
(define (list-trim-right str)   
  (define (loop xs space new)
    (if (null? new)
        xs
        (if (or (equal? (car new) #\newline) (equal? (car new) #\space)
                (equal? (car new) #\tab) (equal? (car new) #\return))
            (loop xs (append space (list (car new))) (cdr new))
            (if (null? space)
                (loop (append xs (list (car new))) space (cdr new))
                (loop (append xs space (list (car new))) '() (cdr new))
                ))
        ))
  (loop '() '() str))