(define pi (* 4 (atan 1))) 
(define (my-abs x) ((if (> x 0) + -) x)) 
(define (my-odd? x) (if (> (remainder x 2) 0) #t #f)) 
(define (power b e) (if(> e 0) (* b (power b (- e 1))) 1)) 