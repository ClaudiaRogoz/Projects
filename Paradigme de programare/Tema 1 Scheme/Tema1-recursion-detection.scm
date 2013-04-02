(include "Reflection.scm")



; transforma lista de liste L in o lista simpla
(define (deep-length  L )
  (dl-helper L '()))

(define (dl-helper L result )
  (cond
    ((null? L ) (reverse result))
    ((list? (car L) ) (dl-helper (append (car L ) (cdr L) ) result ))
    (else (dl-helper (cdr L)  (cons (car L) result)  ))))






; verifica daca s se afla in lista L
(define (contains? s L)
  (let search((list (deep-length L)))
    
    (if (null? list)
        #f
    (if (equal? s (car list))
        #t
    (search (cdr list))))))

(define (containsa? isa L)
  (let search((list (deep-length L)))
    
    (if (null? list)
        #f
    (if (isa (car list))
        #t
    (search (cdr list))))))

; afiseaza tot ce se afla in body-ul functiei dupa primul apel al functiei
(define (rec2 s L)
  (let searchrec ((list (deep-length L)) (after '()) (tf #f))
     (if (null? list) 
         (reverse after)
     (if (and (equal? s (car list)) (equal? tf #f)) 
          (searchrec (cdr list) (cons (car list) after) #t)
     (if (equal? tf #t) 
         (searchrec (cdr list) (cons (car list) after) tf)
      (searchrec (cdr list) after tf)))))) 



 



; intoarce o prima chestie inainte de apelul de functie
(define (before  s L)
  (let before ( (list L) (b null))
    (if (or  (null? list) (equal? s (car list)))
        b
      (before (cdr list) (car list)))))


; returneaza lista de elemente dupa primul element inainte de primul apel de functie
(define (getallbefore2 f)
  (let apel ( (list (get-function-lambda f)) (name (get-function-name f)) (apelat '()) (b (before (get-function-name f) (deep-length (get-function-lambda f))))  )
    (cond 
      ((null? list)  null)
      ( (list? (car list) )  (apel (append (car list) (cdr list)) name apelat b ))
      ((and (equal? (car list) b) (list? (cadr list)) ) 
           (if (equal? (car (cadr list)) name)  list
               (apel (cdr list) name apelat b)
               ))
      
      (else  (apel (cdr list) name apelat b)))))


; returneaza lista de elemente dupa primul element inainte de primul apel de functie
(define (allin f)
  (let apel ( (list (get-function-lambda f)) (name (get-function-name f)) (apelat '()) (b (before (get-function-name f) (deep-length (get-function-lambda f))))  )
    (cond 
      ((null? list)  null)
      ( (list? (car list) )  (apel (append (car list) (cdr list)) name apelat b ))
      ((and (equal? (car list) b) (list? (cadr list)) ) 
           (if (equal? (car (cadr list)) name)  (cadr list)
               (apel (cdr list) name apelat b)
               ))
      
      (else  (apel (cdr list) name apelat b)))))

;returneze apelul functiei  
(define (getapel f)
  (let apel ( (list (get-function-lambda f)) (name (get-function-name f)) (apelat '()) )
    (cond 
      ((null? list) apelat)
      ( (list? (car list) )  (apel (append (car list) (cdr list)) name apelat  ) )
      ((equal? (car list) name)   (append (cdr list) apelat))
      (else (apel (cdr list) name apelat )))))
 






 ; verifica daca ceva este operator
(define operators '('+ '- '/ '* 'quotient 'modulo '% 'car 'cdr  'append))

(define (operator? x)
  (contains? x operators)
  )




;numarul de parametrii ai functiei
(define (paramn f)
  (let x((list (cadr (get-function-lambda f))) (nr 0))
    ( if (null? list)
         nr
      (x (cdr list) (+ nr 1))
      )))


; contains more intoarce daca exista de mai mult de 2 ori name in lista
(define (contmore l name)
  (let cont((list (deep-length l) ) (nr 0))
  (if (null? list)
      #f
  (if (> nr 1)
      #t
  (if (equal? name (car list)) 
      (cont (cdr list) (+ nr 1))
   ( cont (cdr list) nr))))))




;; afiseaza ce este ianinte de s si x
(define (beforex  s x L )
  (let before ( (list L) (b null))
    (if (null? list) null
       (if (and (equal? x (car list)) (equal? s (car (cdr list))))
        b
      (before (cdr list) (car list))))))



;; functie mai ciudata :))
(define (getbeforebefore  f)
  (let apel ( (list (get-function-lambda f)) (name (get-function-name f)) (apelat '()) (b (before (get-function-name f) (deep-length (get-function-lambda f)))) (bef null) )
    (cond 
      ((null? list)  null)
      ( (list? (car list) )  (apel (append (car list) (cdr list)) name apelat b  list))
      ((and (equal? (car list) b) (list? (cadr list)) ) 
           (if (equal? (car (cadr list)) name)  bef
               (apel (cdr list) name apelat b  list )
               ))
      
      (else  (apel (cdr list) name apelat b list)))))



; ia apelul functiei :)
(define (getapelok f)
  (let xx ( (list (getapel f)) (nr (paramn f)) (acum '()) )   
   ( if (= nr 0)
      (reverse acum) 
    ( xx (cdr list) (- nr 1) (cons (car list) acum)))))




(define tails '(cons + ))


  (define (acum? x)
  (contains? x tails)
    )







(define (detect-recursion f)
   (let ((list (deep-length (get-function-lambda f))) (name (get-function-name f)))
      (if (not (contains? name list)) 
          'NON-RECURSIVE
     (if  (contmore (allin f) name)  
         'TREE-RECURSIVE
     (if  (and (or (operator? (car (getallbefore2 f))) (operator? (beforex name (before name list) list)) ) (not (containsa? acum? (getapelok f))))
           'STACK-RECURSIVE
      'TAIL-RECURSIVE)))))

(define-r (fibo n)
  (cond
    ((zero? n) 0)
    ((= n 1) 1)
    (else (+ (fibo (- n 1)) (fibo (- n 2))))))

(detect-recursion fibo)
