;valid-frac? valid-many-fracs? valid? Parser

(define eop (integer->char 0))
(define (make-stream items . eos)
  (if (null? eos)
      (make-stream items #f)
      (list items (car eos))))
(define (peek stream)
  (if (null? (car stream))
      (cadr stream)
      (caar stream)))
(define (next stream)
  (let ((n (peek stream)))
    (if (not (null? (car stream)))
        (set-car! stream (cdr (car stream))))
    n))
(define (expect stream term error)
  (if (equal? (peek stream) term)
      (next stream)
      (error #f)))
(define (word? token)
  (and (symbol? token)
       (not (member token '(if end endif define while do wend)))))
(define (my-flatten xs)
  (define (loop xs ans)
    (if (null? xs)
        ans
        (if (null? (car xs))
            (loop (cdr xs) ans)
            (if (list? (car xs))
                (loop (cons (caar xs) (cons (cdar xs) (cdr xs))) ans)
                (loop (cdr xs) (append  ans (list (car xs))))))))
  (loop xs '()))


#|
<str> ::= <space><word><space>
<word> ::= <woel> | <word><space><woel>
<woel> ::= <sign><elem>"/"<elem>
<elem> ::= <digit> | <digit><elem>
<digit> ::= "0"|...|"9"
<space> ::= " "<space> | "" | "\t"<space> | "\n"<space>
<sign> ::= "+" | "-" | ""
|#
#|
<str> ::= <space><word>"/"<elem><space> | <space><word>"/"<elem><str>
<word> ::= <sign><woel>
<elem> ::= <digit> | <digit><elem> | <empty>
<digit> ::= "0"|...|"9"
<space> ::= " "<space> | "" | "\t"<space> | "\n"<space>
<sign> ::= "+" | "-" | ""
<empty> ::= 
|#
#|
<strs> ::= <spaces><str><spaces> | <spaces><str><spaces><strs> | <empty>
<spaces> ::= " "<space>
<space> ::= " "<space> | <empty>

<str> ::= <word>"/"<elems>
<word> ::= <sign><elems>
<elems> ::= <digit><elem>
<elem> ::= <digit><elem> | <empty>
<sign> ::= "+" | "-" | <empty>
<digit> := "1"|"2"|...|"9"|"0"
<empty> ::= 
|#
;valid-frac?
(define (valid-frac? string)
  (define stream (make-stream (string->list string) eop))
  (call-with-current-continuation
   (lambda (error)
     (check-decimal stream error)
     (equal? (peek stream) EOP))))

;<str> ::= <word>"/"<elems>
(define (check-decimal stream error)
  (check-decimal-with-sign stream error)
  (expect stream #\/ error)
  (check-digits stream error))
;<word> ::= <sign><elems>
;<sign> ::= "+" | "-" | <empty>
;<empty> ::= 
(define (check-decimal-with-sign stream error)
  (cond ((member (peek stream) '(#\+ #\-))
         (next stream)
         (check-digits stream error))
        (else (check-digits stream error))))
;<elems> ::= <digit><elem>
(define (check-digits stream error)
  (cond ((num? (peek stream))
         (next stream)
         (check-tail-digits stream error))
        (else (error #f))))
;<elem> ::= <digit><elem> | <empty>
(define (check-tail-digits stream error)
  (cond ((num? (peek stream))
         (next stream)
         (check-tail-digits stream error))
        (else #t)))
;<digit> := "1"|"2"|...|"9"|"0"
(define (num? char)
  (< 47 (char->integer char) 58))
  
      


;valid-many-fracs?
(define (valid-many-fracs? string)
  (define stream (make-stream (string->list string) eop))
  (call-with-current-continuation
   (lambda (error)
     (check-decimals stream error)
     (equal? (peek stream) EOP))))

(define (check-decimals stream error)
  (cond ((or (member (peek stream) '(#\+ #\-)) (num? (peek stream)))
         (check-decimal stream error)
         (check-decimals stream error))
        ((char-whitespace? (peek stream))
         (check-spaces stream error)
         (check-decimals stream error))
        ((equal? (peek stream) eop)
         #t)
        (else (error #f))))

(define (check-spaces stream error)
  (cond ((char-whitespace? (peek stream))
         (next stream)
         (check-tail-spaces stream error))
        (else (error #f))))

(define (check-tail-spaces stream error)
  (cond ((char-whitespace? (peek stream))
         (next stream)
         (check-tail-spaces stream error))
        (else #t)))
;valid?
;<Program>  ::= <Articles> <Body> .
;<Articles> ::= <Article> <Articles> | .
;<Article>  ::= define word <Body> end .
;<Body>     ::= if <Body> endif <Body>
;             | while <Body> do <Body> wend <Body>
;             | integer <Body> | word <Body> | .
(define (valid? tokens)
  (define stream (make-stream (vector->list tokens) eop))
  (call-with-current-continuation
   (lambda (error)
     (check-program stream error)
     (equal? (peek stream) EOP))))
  
;<Program>  ::= <Articles> <Body> .
(define (check-program stream error)
  (check-articles stream error)
  (check-body stream error))

;<Articles> ::= <Article> <Articles> | .
(define (check-articles stream error)
  (cond ((equal? (peek stream) 'define);FIRST(<Article>) = {define}
         (check-article stream error)
         (check-articles stream error))
        (else #t)))

;<Article>  ::= define word <Body> end .
(define (check-article stream error)
  (expect stream 'define error)
  (if (word? (peek stream))
      (next stream)
      (error #f))
  (check-body stream error)
  (expect stream 'end error))

;<Body>     ::= if <Body> endif <Body>
;             | while <Body> do <Body> wend <Body>
;             | integer <Body> | word <Body> | .
(define (check-body stream error)
  (cond ((equal? (peek stream) 'if)
         (expect stream 'if error)
         (check-body stream error)
         (expect stream 'endif error)
         (check-body stream error))
        ((equal? (peek stream) 'while)
         (expect stream 'while error)
         (check-body stream error)
         (expect stream 'do error)
         (check-body stream error)
         (expect stream 'wend error)
         (check-body stream error))
        ((number? (peek stream))
         (next stream)
         (check-body stream error))
        ((word? (peek stream))
         (next stream)
         (check-body stream error))))




;parse
(define (parse vector)
  (define stream (make-stream (vector->list vector)))
  (call-with-current-continuation
   (lambda (error)
     (program stream error))))

(define (program stream error)
  (list (articles stream error)
        (body stream error)))

(define (articles stream error)
  (let ((art (article stream error)))
    (if art
        (cons art (articles stream error))
        '())))

(define (article stream error)
  (and (equal? (peek stream) 'define)
       (begin
         (next stream)
         (and (not (word? (peek stream))) (error #f))
         (let ((bod (list (next stream)
                          (body stream error))))
           (if (equal? (next stream) 'end)
               bod
               (error #f))))))

(define (body stream error)
  (let ((symb (peek stream)))
    (cond
      ((number? symb)
       (begin
         (next stream)
         (cons symb (body stream error))))

      ((word? symb)
       (begin
         (next stream)
         (cons symb (body stream error))))

      ((equal? symb 'if)
       (begin
         (next stream)
         (let ((bod (list 'if (body stream error))))
           (if (equal? 'endif (peek stream))
               (begin
                 (next stream)
                 (cons bod (body stream error)))
               (error #f)))))

      ((equal? symb 'while)
       (begin
         (next stream)
         (let ((condition (body stream error)))
           (if (equal? 'do (peek stream))
               (begin
                 (next stream)
                 (let ((actions (body stream error)))
                   (if (equal? 'wend (peek stream))
                       (begin
                         (next stream)
                         (cons (list 'while condition actions) 
                               (body stream error)))
                       (error #f))))
               (error #f)))))

      (else '()))))

(valid-frac? "110/111"); ⇒ #t
(valid-frac? "-4/3");    ⇒ #t
(valid-frac? "+5/10");   ⇒ #t
(valid-frac? "5.0/10");  ⇒ #f
(valid-frac? "FF/10");   ⇒ #f
(newline)
(valid-many-fracs? "\t1/2 1/3\n\n10/8");   ⇒ #t
(valid-many-fracs? "\t1/2 1/3\n\n2/-5");   ⇒ #f
(valid-many-fracs? "+1/2-3/4");            ⇒ #t
(newline)
#|(scan-frac "110/111");   ⇒ 110/111
(scan-frac "-4/3");      ⇒ -4/3
(scan-frac "+5/10");     ⇒ 1/2
(scan-frac "5.0/10");    ⇒ #f
(scan-frac "FF/10");     ⇒ #f
(newline)
(scan-many-fracs "\t1/2 1/3\n\n10/8");   ⇒ (1/2 1/3 5/4)
(scan-many-fracs "\t1/2 1/3\n\n2/-5");   ⇒ #f
(scan-many-fracs "+1/2 3/4");            ⇒ (1/2 3/4)
(newline)|#
(valid? #(1 2 +)); ⇒ #t
(valid? #(define 1 2 end)); ⇒ #f
(valid? #(define x if end endif)); ⇒ #f
(newline)
(parse #(1 2 +)); ⇒ (() (1 2 +))
(parse #(x dup 0 swap if drop -1 endif))
; ⇒ (() (x dup 0 swap (if (drop -1))))
(parse #(x dup while dup 0 > do 1 - swap over * swap))
; ⇒ (() (1 x (while (dup 0 >) (1 - swap over * swap)))) 
;-> #f (т.к. после while отсутствует wend)
(parse #(1 x while dup 0 > do 1 - swap over * swap wend)) ;!

(parse #( define -- 1 - end
          define =0? dup 0 = end
          define =1? dup 1 = end
          define factorial
              =0? if drop 1 exit endif
              =1? if drop 1 exit endif
              1 swap
              while dup 0 > do
                  1 - swap over * swap
              wend
              drop
          end
          0 factorial
          1 factorial
          2 factorial
          3 factorial
          4 factorial ))
; ⇒
; (((-- (1 -))
;   (=0? (dup 0 =))
;   (=1? (dup 1 =))
;   (factorial
;    (=0? (if (drop 1 exit)) =1? (if (drop 1 exit))
;    1 swap (while (dup 0 >) (1 - swap over * swap)) drop))
;  (0 factorial 1 factorial 2 factorial 3 factorial 4 factorial))

(parse #(define word w1 w2 w3)); ⇒ #f

;scan-frac  scan-many-fracs

;for scan
(define finish-symbol (integer->char 0))
;<expression> := <content> FINISH-SYMBOL
(define (make-streams str)
  (append (string->list str) (list finish-symbol)))


(define (peeks stream)
  (if (null? stream)
      #f
      (car stream)))

(define (nexts stream)
  (if (null? stream)
      #f
      (cdr stream)))

(define (next-col x stream)
  (letrec ((loop (lambda (xs x)
                   (if (or (= x 0) (null? xs))
                       xs
                       (loop (cdr xs) (- x 1))))))
    (loop stream x)))

;<sign> := - | +
(define (Sign? symb)
  (or (equal? symb #\-) (equal? symb #\+)))
(define (peak-sign char)
  (cond ((equal? char #\-) -1)
        (else 1)))
;<digit> := 0|1|2|3|4|5|6|7|8|9
(define (Digit? char)
  (or (equal? char #\0) (equal? char #\1) (equal? char #\2) 
      (equal? char #\3) (equal? char #\4)
      (equal? char #\5) (equal? char #\6) (equal? char #\7) 
      (equal? char #\8) (equal? char #\9)))
      
(define (scan-digit char)
  (cond ((equal? char #\0) 0) ((equal? char #\1) 1) 
        ((equal? char #\2) 2) ((equal? char #\3) 3)
        ((equal? char #\4) 4) ((equal? char #\5) 5) 
        ((equal? char #\6) 6) ((equal? char #\7) 7)
        ((equal? char #\8) 8) ((equal? char #\9) 9) (else #f)))
        
;<number> := <digit> | <number> <digit>
(define (Num? stream)
  (if (null? stream) 
      #f
      (letrec ((loop (lambda (xs)
                       (if (null? xs)
                           #t
                           (and (Digit? (peeks xs)) (loop (cdr xs)))))))
        (loop stream))))

(define (Num stream)
  (letrec ((loop (lambda (xs res)
                   (if (null? xs)
                       res
                       (loop (cdr xs) (+ (* res 10) (scan-digit (car xs))))))))
    (loop stream 0)))
    
;<fraction> := <sign> <number> SLASH <number>
(define (frac stream) 
  (letrec ((stream-numerator '())
           (stream-denominator '())
           (sign 1)
           (make-stream-loop (lambda (xs1 xs2 finish)
                               (if (or (equal? (peeks xs1) finish) 
                                       (equal? (peeks xs1) finish-symbol) 
                                       (null? xs1))
                                   xs2
                                   (make-stream-loop (cdr xs1) 
                                                     (append xs2 
                                                             (list (peeks xs1))) 
                                                     finish)))))
    ;sign
    (if (Sign? (peeks stream))
        (begin (set! sign (peak-sign (peeks stream))) (set! stream 
                                                            (nexts stream))))
    ;numerator
    (set! stream-numerator (make-stream-loop stream '() #\/))
    (set! stream (next-col (length stream-numerator) stream))

    ;SLASH
    (if (eq? (peeks stream) #\/)
        (begin
          (set! stream (nexts stream))
          ;denominator
          (set! stream-denominator (make-stream-loop stream '() finish-symbol))
          (set! stream (next-col (length stream-denominator) stream))
          
          (if (and (Num? stream-numerator) (Num? stream-denominator))
              (list (* sign (Num stream-numerator)) (Num stream-denominator))
              #f))
        #f)))
;<content> := <fraction> | <other-symbols> | <content> <fraction> | <content> <other-symbols>
(define (fracs stream)
  (letrec ((x #f)
           (list-fracs '())
           (loop (lambda (xs fracs)
                   (if (equal? (peeks xs) finish-symbol)
                       fracs
                       (if (or (Digit? (peeks xs)) (Sign? (peeks xs)))
                           (begin (set! x (try-frac xs))
                                  (if (null? x)
                                      ;(loop (cdr xs) fracs)
                                      #f
                                      (loop (next-col (length x) xs) 
                                            (append fracs (frac x)))))
                           (if (null? xs)
                               fracs
                               (loop (cdr xs) fracs))))))
           (try-frac (lambda (xs)
                       (letrec ((loop2 (lambda (xs1 xs2 res)
                                         (if (null? xs1)
                                             res
                                             (begin (set! xs2 
                                                         (append xs2 
                                                                 (list (car xs1)
                                                                       )))
                                                    (if (frac xs2)
                                                        (set! res xs2))
                                                    (loop2 (cdr xs1) xs2 res)
                                                    )))))
                         (loop2 xs '() '()))))
           (complete-fracs (lambda (xs1 xs2) ;(1 2 3 4) -> (1/2 3/4)
                             (if (null? xs1)
                                 xs2
                                 (complete-fracs (cdr (cdr xs1)) 
                                                 (append xs2 
                                                         (list (/ (car xs1) 
                                                                  (car (cdr xs1)
                                                                       )))))))))
    
    (set! list-fracs (loop stream '()))
    (if (eq? list-fracs #f)
        #f
        (complete-fracs list-fracs '()))))                                     
                                   
(define (check-frac str)
  (if (frac (make-streams str))
      #t
      #f))

(define (scan-frac str)
  (if (check-frac str)
      (/ (car (frac (make-streams str))) (car (cdr (frac (make-streams str)))))
      #f))

(define (scan-many-fracs str)
  (fracs (make-streams str)))

(scan-frac "110/111");   ⇒ 110/111
(scan-frac "-4/3");      ⇒ -4/3
(scan-frac "+5/10");     ⇒ 1/2
(scan-frac "5.0/10");    ⇒ #f
(scan-frac "FF/10");     ⇒ #f
(newline)
(scan-many-fracs "\t1/2 1/3\n\n10/8");   ⇒ (1/2 1/3 5/4)
(scan-many-fracs "\t1/2 1/3\n\n2/-5");   ⇒ #f
(scan-many-fracs "+1/2-3/4");            ⇒ (1/2 -3/4)

;Вывод - Писать парсер очень тяжело. Самая сложная лабораторная работа из всех
;Комментарий преподавателя: Сдано не в срок (3 балла) + вывод оценил (1 балл) = 4 балла.