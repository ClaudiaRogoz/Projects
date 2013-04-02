(include "Reflection.scm")


; transforma lista de liste L in o lista simpla
(define (deep-length  L )
  (dl-helper L '()))

(define (dl-helper L result )
  (cond
    ((null? L ) (reverse result))
    ((list? (car L) ) (dl-helper (append (car L ) (cdr L) ) result ))
    (else (dl-helper (cdr L)  (cons (car L) result)  ))))


;; Misc

;; Testeaza daca un simbol incepe cu un anumit caracter
;; Ex (symbol-starts-with? #\? '?variable) => #t
(define (symbol-starts-with? first-char x)
    (and (symbol? x)
         (let ((s (symbol->string x)))
           (and (>= (string-length s) 1)
                (equal? first-char (string-ref s 0))))))


;; Testeaza ca argumentul este o entitate primitiva (care nu mai poate fi descompusa)
(define (atom? x)
  (or (symbol? x)
      (number? x)
      (char? x)
      (string? x)
      (boolean? x)))

(define constant-folding-rule
  '((WHEN ((:conditional ?operator (lambda (op) (member op ‘(+ - *))))
           (:conditional ?x number?)
           (:conditional ?y number?)))
    (THEN (:evaluate (?operator ?x ?y)))))

       

(define rewrite-as-map
  '((WHEN (lambda (?L) (if (null? ?L) '() (cons (:abstraction ?f ((car ?L) x)) (?this (cdr ?L))))))
    (THEN (lambda (?L) (map ?f ?L)))))

(define rewrite-as-foldl
  '((WHEN (lambda (?acum ?L) (if (null? ?L) ?acum (?this (:abstraction ?f ((car ?L) x) (?acum acum)) (cdr ?L)))))
    (THEN (lambda (init ?L) (foldl ?f init ?L)))))
        
(define remove-redundant-lambda
  '((WHEN (lambda (?arg) (?f ?arg)))
    (THEN ?f)))

(define use-add1
  '((WHEN (+ ?x 1))
    (THEN (add1 ?x))))
;; vede daca un simbol este ?variable
(define (isvariable? symbol)
  (and (symbol? symbol)
       (eqv? (string-ref (symbol->string symbol) 0)
               #\?)))

(define (iscomand? symbol)
  (and (symbol? symbol)
       (eqv? (string-ref (symbol->string symbol) 0)
               #\:)))

(define (containsVar? list)
   (> ( length (filter isvariable? list)) 0))

(containsVar? '(:when :then 1 2 3 when I talk))
       
      
      


(define optimization-pack
  (list constant-folding-rule
        rewrite-as-map
        rewrite-as-foldl
        remove-redundant-lambda
 use-add1))




  
 (cdr (car rewrite-as-map))

 
(define (getallbefore1 f something)
  (let apel ( (list (get-function-lambda f)) (name (get-function-name f)) (apelat '()) (b something)  )
    (cond 
      ((null? list)  null)
      ( (list? (car list) )  (apel (append (car list) (cdr list)) name apelat b ))
      ((and (equal? (car list) b) (list? (cadr list)) ) 
           (if (equal? (car (cadr list)) name)  list
               (apel (cdr list) name apelat b)
               ))
      
      (else  (apel (cdr list) name apelat b)))))
 
 

 ;; verifica daca o variabila nu a fost deja adaugata in lista de variabile care este o lista de perechi (?var var)
 (define (notalreadyput? listvar var)
   (if (null? listvar)
       #t
   (if (equal? (car (car listvar)) var)
       #f
   (notalreadyput? (cdr listvar) var))))
 
 
(define (take-var var)
   (let getvar((lst var) (rez '()))
   (if (null? lst) 
       rez
   (getvar (cdr lst) (append (cdr (car lst)) rez)))))

 ; intoarce variabila asignata pentru variable 
(define (takevarassigned variables variable)
  (let iter ( (list variables) (rez '()))
    (if (null? list)
        rez
     (if (equal? (car ( car list)) variable)
         (cadar list)
     (iter (cdr list) rez )))))



                                        
; inlocuieste in lista variabilele care au o asociere in cealalta lista                                        
(define replacecoresp
(lambda (ls a-list)
    (map (lambda (x)
           (let ((lookup (assq x a-list)))
             (if lookup
                 (cadr lookup)
                 x)))
         ls))) 

;reface un singur pattern
(define (repat pattern var)
  (let it ( (list   pattern) (rez '()))
    (if (null? list)
       (reverse rez)
    (if (list? (cadr (reverse list)))
    (it '() (append rez (cons (car (reverse list))  (cons (replacecoresp (cadr (reverse list)) var) '() ) )))
    (it '() (append rez (cons (car (reverse list))  (cons (car (replacecoresp (cons (car  list) '()) var)) '() ) )))))))


; reface patternul unui when adica inlocuieste din lista de variabile cu cele corespunzatoare intorcand noul pattern de cautat
(define (maprepat patterns var)
  (let it ( (lst patterns) (rez '()))
    (if (null? lst)
      rez
    (it (cdr lst) (append rez (cons (repat (car lst) var) '()))))))


;; verifica daca o lista contine patternul respectiv de ex in lista (+ (car L) 1)  cauta patternul (car L)
(define (haspattern lst pattern)
  (let find ( (list lst) )
  (if (null? list)
      #f
  (if (and (list? (car list) ) (list? pattern))
      (if (equal? (car list) pattern)
          #t
      (find (append  (car list) (cdr list)) ))
  (if (and (not (list? (car list))) (not (list? pattern)))
      (if (equal? (car list) pattern)
          #t
      (find (cdr list)))
  (find (cdr list)))))))


;verifica daca intr-o lista se gasesc toate patternurile '(+ (car L) (cons  p) (- 2 1)) '((car L) (cons q p))
(define (hasallpat list patterns)
  (let find ((patterns patterns) (rez #t))
    (if (null? patterns)
        rez
    (if (haspattern list (caar patterns))
        (find (cdr patterns) (and rez #t))
    (find (cdr patterns) #f)))))



; inlocuieste intr-o lista un element care are o asociere intr-o lista de asocieri
(define replacecorespandlists
(lambda (ls a-list)
    (map (lambda (x)
           (let ((lookup (assoc x a-list)))
             (if lookup
                 (cadr lookup)
                 x)))
         ls)))    
    
    
 (define (replacedeep ls a-list)
  (cond 
    ((null? ls) '() )
    ((assoc ls a-list)
         (let ((lookup (assoc ls a-list)))
           (if lookup
               (cadr lookup)
               ls)))
    ((not (list? ls))
     (let ((lookup (assoc ls a-list)))
           (if lookup
               (cadr lookup)
               ls)))
    (else (cons (replacedeep (car ls) a-list)
                (replacedeep (cdr ls) a-list)))))     
 
; aceasta functie primeste o lista care reprezinta corpul viitoarei functii
; when reprezinta un pattern abstraction var lista de variabile name numele functiei 
; si returneaza functia rezultata in urma inlocuirilor

(define (abstraction list when var name)
(if (hasallpat list (maprepat (cddr when) var))
   (let abstr((lst list) (w (maprepat (cddr when) var)) (var var) (funct (reverse (cons (take-var var) '(lambda) ))) )
     (if (or (null? lst) (null? w))
         funct
     (abstr lst (cdr w) var  (append funct (cons  (replacecorespandlists lst w) '()) ) )))
   #f))
     
         
         
     
;remembers the list o pais of variables value ?x x
(define (remvar list w)
  (let it( (list list) (when w) (rez '()) (ok #f))
  (if (or (null? list) (null? when))
      rez
  (if (equal? (car list) (car when))
     ; (if (isvariable? (car when))
      ;    (it (cdr list) (cdr when) (cons (cons (car when) (car list)) rez) #t)
      (it (cdr list) (cdr when) rez #t)
  (if (list? (car list))
      (if (equal? ok #t) 
          (if (and (isvariable? (car when)) (notalreadyput? rez (car when)))
              (it (cdr list) (cdr when) (cons (cons (car when) (cons (car list) '())) rez) #t)
          (if (list? (car when))
              (it (append (car list) (cdr list)) (append (car when) (cdr when)) rez ok)
          (it (append (car list) (cdr list)) w rez #f)))
      (it (append (car list) (cdr list)) when rez #f))
  (if (and (isvariable? (car when)) (notalreadyput? rez (car when)))
      (if (equal? ok #t)
          (it (cdr list) (cdr when) (cons (cons (car when) (cons (car list) '())) rez) #t)
      )
  (it (cdr list) when rez #f)))))))   
         
         
;(define (getfromabs abstraction)
 ; (let iter ( (list (cddr abstraction)) (perechi '()))
  ;  (if (null? list)
   ;     perechi
   ; (iter 
  ;
  
  
 

  
;(define (refactor-code fun refactoring-pack)
 ; (let repattern((pattern refactoring-pack)) 
  ;  (let seek ( (list (get-function-lambda fun)) (name (get-function-name fun)) (ok #f) (listbef '()) (variabile '())  (whenbef '()) (when (cdr (car (car pattern)))) (then (cadr (cadr (car pattern)))))
   ;  (if (null? pattern)
    ;      result
     ; (if (or ( null? list) (null? when))
      ;    (repattern (cdr pattern)) 
      ;(if (and (list? (car list) ) (list? (car when)))
       ;   (if (equal? (car list) (car when))
        ;      (seek (cdr list) name #t (car list) variabile (car when) (cdr when) then)
         ; (seek (append (car list) (cdr list)) name ok (car list) variabile (car when) (append (car when ) (cdr when)) then))  
      ;(if (and (not (list? (car list))) (not (list? (car when))))
       ;   (cond 
        ;  ((equal? (car list) (car when) )
         ;    (seek (cdr list) name #t listbef variabile whenbef (cdr when) then))
          ;((and (isvariable? (car when)) (notalreadyput? variabile (car when)))
           ;  (seek (cdr list) name #t listbef (cons (cons (car when) (char list)) variabile) whenbef (cdr when) then))
          ;((iscomand? (car when))
           ;    (cond 
            ;     
             ;  ((equal? (car when) ':abstraction)
              ;     (abstraction listbef    ))
               ;((equal? (car when) ':conditional)
                ;   (conditional ))
               ;(else (repattern (cdr pattern )))))
           
               
                   ;; prelucreaza cu then functia si chestii :)  
               
               
        ;  ((and (equal? ok #t) (not (null? when)))
         ;     (repattern (cdr pattern)))
          ;(else (seek (cdr list) name #f '() '() '() '() when then))))))))))

(define (refactor-code fun refactoring-pack)
  (let repattern((pattern refactoring-pack) (result (get-function-lambda fun)))  
    (let seek ( (list result) (name (get-function-name fun)) (ok #f) (listbef '()) (variabile (remvar fun (cdr (car (car pattern)))) )  (whenbef '()) (when (cdr (car (car pattern)))) (then (cadr (cadr (car pattern)))))
     (if (null? pattern)
          result
    (if (or ( null? list) (null? when))
          (repattern (cdr pattern) list) 
     (if (and (list? (car list) ) (list? (car when)))
         (if (equal? (car list) (car when))
              (seek (cdr list) name #t (car list) variabile (car when) (cdr when) then)
         (seek (append (car list) (cdr list)) name ok (car list) variabile (car when) (append (car when ) (cdr when)) then)))  )))))
;
 
(define-r (add1-to-all L)
  (if (null? L)
      '()
      (cons (+ (car L) (- 2 1)) (add1-to-all (cdr L)))))



(define (makethen var then)
  (replacedeep then var))

(define (getin f something)
  (let apel ((list f) (rez '()))
    (cond 
      ( (null? list) null)
      ((list? (car list)) (apel (append (car list) (cdr list)) (car list)))
      ((equal? (car list) something)
            rez)
      (else (apel (cdr list) rez)))))
(define (getallaftersomething f something)
  (let apel ( (list f) (rez '()))
    (cond 
      ( (null? list) null)
      ((list? (car list)) (apel (append (car list) (cdr list)) (cons (car list) rez ))
                           )
      ((and (equal? (car list) something) (list? (cadr list))) 
          rez
          )
      (else (apel (cdr list) rez)))))

(define (getin f something)
  (let apel ((list f) (rez '()))
    (cond 
      ( (null? list) null)
      ((list? (car list)) (apel (append (car list) (cdr list)) (car list)))
      ((equal? (car list) something)
            rez)
      (else (apel (cdr list) rez)))))


       
   
(define (makethen var then)
  (replacedeep then var))            

(define (replacedeep ls a-list)
  (cond 
    ((null? ls) '() )
    ((assoc ls a-list)
         (let ((lookup (assoc ls a-list)))
           (if lookup
               (cadr lookup)
               ls)))
    ((not (list? ls))
     (let ((lookup (assoc ls a-list)))
           (if lookup
               (cadr lookup)
               ls)))
    (else (cons (replacedeep (car ls) a-list)
                (replacedeep (cdr ls) a-list)))))


          
        
     
    

  
  
  
  

