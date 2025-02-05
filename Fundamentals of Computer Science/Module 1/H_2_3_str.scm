(define (string-trim-left s) ;O(n^2)
  (if (char-whitespace? (string-ref s 0))
      (string-trim-left (substring s 1))
      s))

(define (string-trim-right s) ;O(n^2)
  (if (char-whitespace? (string-ref s (- (string-length s) 1)))
      (string-trim-right (substring s 0 (- (string-length s) 1)))
      s))

(define (string-trim s) ;O(n)
  (string-trim-left (string-trim-right s)))

(define (string-prefix? a b) ;O(n)
  (and (not (> (string-length a) (string-length b)))
      (equal? (substring b 0 (string-length a)) a)))

(define (string-suffix? a b) ;O(n)
  (cond
    ((> (string-length a) (string-length b)) #f)
    ((equal? (substring b (- (string-length b) (string-length a))) a) #t)
    (else #f)))

(define (string-infix? a b) ;O(n^2)
  (cond
    ((> (string-length a) (string-length b)) #f)
    ((string-prefix? a b) #t)
    (else (string-infix? a (substring b 1)))))

(define (add-elem s sep) ;O(n)
  (cond
    ((= (string-length s) 0) (string))
    ((string-prefix? sep s) (string))
    (else (string-append (make-string 1 (string-ref s 0)) (add-elem (substring s 1) sep)))))

(define (string-split s sep) ;O(n^2)
  (cond
    ((= (string-length s) 0) (list))
    ((> (string-length sep) (string-length s)) (list s))
    ((string-prefix? sep s) (string-split (substring s (string-length sep)) sep))
    (else (cons (add-elem s sep) (string-split (substring s (string-length (add-elem s sep))) sep)))))
;По поводу O в некоторых случаях O(2n) или O(c*n), а c отбрасывается