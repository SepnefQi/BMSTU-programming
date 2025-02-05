(define (make-multi-vector sizes . fill)
  (cons sizes (list (if (= (length fill) 1)
                        (make-vector (apply * sizes) (car fill))
                        (make-vector (apply * sizes))))))

(define (multi-vector? m)
  (and (list? m) (list? (car m)) (vector? (cadr m))))

(define (multi-vector-ref m indices)
  (vector-ref (cadr m) (let loop ((m (car m)) (ind indices))
                         (if (null? (cdr m))
                             (car m)
                             (+ (* (car ind) (apply * (cdr m)))
                                (loop (cdr m) (cdr ind)))))))

(define (multi-vector-set! m indices x)
  (vector-set! (cadr m) (let loop ((m (car m)) (ind indices))
                          (if (null? (cdr m))
                              (car m)
                              (+ (* (car ind) (apply * (cdr m)))
                                 (loop (cdr m) (cdr ind)))))
               x))
(define m (make-multi-vector '(11 12 9 16)))
(multi-vector? m);#t
(multi-vector-set! m '(10 7 6 12) 'test)
(multi-vector-ref m '(10 7 6 12));test
(multi-vector-set! m '(1 2 1 1) 'X)
(multi-vector-set! m '(2 1 1 1) 'Y)
(multi-vector-ref m '(1 2 1 1));x
(multi-vector-ref m '(2 1 1 1));y
(define m (make-multi-vector '(3 5 7) -1))
(multi-vector-ref m '(0 0 0));-1