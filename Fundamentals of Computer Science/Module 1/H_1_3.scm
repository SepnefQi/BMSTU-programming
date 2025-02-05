(define (my-gcd a b)
  (if (= b 0)
      (if (> a 0)
          a
          (* a -1))
      (my-gcd b (modulo a b))))

(define (my-lcm a b)
  (* (/ a (my-gcd a b)) b))

(define (prime? n)
  (define (squareRoot start x)
        (if (> (* start start) x)
                start
                (squareRoot (+ start 1) x)
        ))
  (let loop ((i 2) (n n) (k (squareRoot 1 n)))
    (if (< i k)
        (cond
          ((= (modulo n i) 0)
           #f)
          (else (loop (+ 1 i) n k)))
        #t)))