(defmodule MAIN (export ?ALL))
;;------------------------
(deftemplate item (slot id) (slot name) (slot instructor) (slot duration) (multislot groups))
(deftemplate instructor (slot name) (multislot intervals))
(deftemplate orarone (slot tip) (slot id) (slot day) (multislot interval) (slot room) (multislot groups) (slot instructor) )
(deftemplate slt (slot id) (slot room))
(deftemplate onedaysc (slot slt) (slot interval) )
(deftemplate orar (slot day) (slot onedaysc))


(deffacts facts (orar) (schedule) (interv 8 11 ) (ranroom eg206) (days Mon Tue Wed Thu Fri) (randay Mon))
(deffacts facts1 (score 0))
(deffacts facts2 (scor 0))
(deffacts fasda (iterations))
(deffacts facturi (vector))
(deffunction randomintervalrest  (?duration ?rest1 ?rest2)
	
	(bind ?x1 (random 8 (- 20 ?duration) ))
	(bind ?x2  (+ ?x1 ?duration))
	
	(while (and (and (not (> ?x2 ?rest1)) (not (<= ?x2 ?rest2))) (and (not (>= ?x1 ?rest1)) (not (< ?x1 ?rest2)))) 
	(bind ?x1 (random 8 (- 20 ?duration) ))
	(bind ?x2  (+ ?x1 ?duration))
	)
	  
	(assert (interv ?x1 ?x2))	
)

(defrule init
  =>
  	(focus MAKE COPIE ITERATII)
	(set-fact-duplication TRUE)
	(load-facts "input.txt") 
	(set-fact-duplication FALSE)
	)
	


;===========
(defmodule ITERATII (import MAIN ?ALL))
;=========================


(defrule iteratii 
	
	?s <- (iterations ?it&:(> ?it 0) )
	
=>	
	
	(retract ?s )
	
	(assert (iterations (- ?it 1))) 
	(focus MP MI MS MG FITNESSVECHI FITNESSNOU  KEEP RESTART COPIE ITERATII)
	
	
	)

(defrule afisfis 
	(orarone (tip vechi) (id ?id) (day ?d) (interval ?i1 ?i2) (room ?room) (groups $?grp)(instructor ?instructor))
	(not (vector $? ?id $?))
	(vector $?x)
	
=>
	(assert (vector $?x ?id))
	(open "out" out "a")
	(printout out ?id "  " ?d "  [" ?i1 "  " ?i2 "]   " ?room "  " crlf)
	(close)
	)


;----------------------------------
(defmodule RESTART (import MAIN ?ALL))
;----------------------------------
(deffacts rest (ok 0 ))

	
(defrule restart 
;	?a <- (vector1 $?aa)
;	?b <- (vector2 $?ba)
;	?c <- (vector3 $?ca)
;	?d <- (vector $?da)
	?e <- (score ?ea)
;	?f <- (vect1 $?aaa)
;	?g <- (vect2 $?baa)
;	?h <- (vect3 $?caa)
;	?i <- (vect $?daa)
	?j <- (scor ?eaa)
	(ok 0)
	?ok <- (ok ?x)
	
=>
	
	;;(retract ?a ?b ?c ?d ?e ?f ?g ?h ?i ?j)
	(retract ?e ?j ?ok)
;	(modify ?a (vector1 nil))
;	(modify ?b (vector2 nil))
;	(modify ?c (vector3 nil))
;	(modify ?d (vector nil))
;	(modify ?e (score 0))
;	(modify ?f (vect1 nil))
;	(modify ?g (vect2 nil))
;	(modify ?h (vect3 nil))
;	(modify ?i (vect nil))
;	(modify ?j (scor 0))
;	(modify ?ok (ok 1))
	(assert (ok 1))
	(assert (scor 0))
	(assert (score 0))

	)
;----------------------------------
(defmodule KEEP (import MAIN ?ALL))
;----------------------------------
;score fitness vechi
;scor fitness nou
(defrule afis 


=>
	(printout t "din KEEP de aici"  crlf)
	)

(defrule keep
	(score ?score)
	(scor ?scor)
	?f <- (orarone (tip nou) (id ?id) (day ?d) (interval ?i1 ?i2) (room ?room) (groups $?grp)(instructor ?instructor))
	?g <- (orarone (tip vechi) (id ?id) (day ?d1) (interval ?o1 ?o2) (room ?rm) (groups $?grup)(instructor ?instr))
	
	
=>
	;(printout t "scor vechi  " ?score    "  scor nou  " ?scor)
	(if (> ?score ?scor) 
		then ; alegem orarul nou copiem nou peste vechi si stergem nou 
			(retract ?g)
			(assert (orarone (tip vechi) (id ?id) (day ?d) (interval ?i1 ?i2) (room ?room) (groups $?grp) (instructor ?instructor)))
			(retract ?f)
			)
	(if (<= ?score ?scor) 	
		then ; alegem orarul vechi doar stergem orarul nou
			(retract ?f))

	
	)



;;------------------------------
(defmodule MAKE (import MAIN ?ALL))
;;------------------------------

(deffunction randominterval  (?duration)
	(bind ?x1 (random 8 (- 20 ?duration) ))
	(bind ?x2  (+ ?x1 ?duration))
	(assert (interv ?x1 ?x2))
	
)

(deffunction randomsala ( $?rooms )
	(bind ?x1 (random 1 (length $?rooms)))
	(assert (ranroom (nth$ ?x1 $?rooms)))
	
)

(deffunction randomday ($?days )
	(bind ?x (random 1 5))
	(assert (randay (nth$ ?x $?days)))
)



(defrule makeorarrandom
	(declare (salience 10))
	?f <- (item (id ?id1) (name ?name) (instructor ?instructor) (duration ?duration) (groups $?grp) )
	?g <- (instructor (name ?instructor) (intervals $? ?p1 ?day $?x ?p2 $? ))
	(rooms $?room )
	?f1 <- (ranroom ?rom)
	?f3 <- (interv ?x1 ?x2)
	(days $?days)
	?f2 <- (randay ?d)
	(test (eq ?p1 [))	
	(test (eq ?p2 ]))
	(test (eq (length $?x) 2))
	(not (orarone  (id ?id1)))
	
	
 =>	
	(retract ?f1 ?f2 ?f3)
	(randomsala $?room)
	(randominterval ?duration)
	(randomday $?days)
 	(assert (orarone (tip vechi) (id ?id1) (day ?d) (interval ?x1 ?x2) (room ?rom) (groups $?grp) (instructor ?instructor) ))
	)


(defrule makeorarrandom1
	(declare (salience 5))
	?f <- (item (id ?id1) (name ?name) (instructor ?instructor) (duration ?duration) (groups $?grp))
	(rooms $?room )
	?f2 <- (ranroom ?rom)
	?f3 <- (interv ?x1 ?x2)
	(days $?days)
	?f1 <- (randay ?d)
	(not (instructor (name ?instructor) ))
	(not (orarone  (id ?id1)))
 =>	
 	(retract ?f1 ?f2 ?f3)
	(randominterval ?duration)
	(randomsala $?room)
	(randomday $?days)
 	(assert (orarone (tip vechi) (id ?id1) (day ?d) (interval ?x1 ?x2) (room ?rom) (groups $?grp) (instructor ?instructor)))
		)


;;------------------------------
(defmodule COPIE (import MAIN ?ALL))
;;------------------------------

	


(defrule copie
	?f <- (orarone (tip vechi) (id ?id) (day ?d) (interval ?i1 ?i2) (room ?room) (groups $?grp)(instructor ?instructor))
	
=>
	(assert (orarone (tip nou) (id ?id) (day ?d) (interval ?i1 ?i2) (room ?room) (groups $?grp)(instructor ?instructor)))
	
	)

(defrule fa 
	(declare (salience -1000))
=>
	(printout t "din copie" crlf)
	
	)
;;------------------------------
(defmodule MI (import MAIN ?ALL))
;;------------------------------

(deffacts fa (control 0))

(deffunction randomint (?i1 ?i2 ?dur)
	(bind ?x1 (random ?i1 ?i2))
	(bind ?x2 (+ ?x1 ?dur))
	(assert (interv ?x1 ?x2))
)

	
(defrule afis 
	(declare (salience 10))
	(control ?x)
=>
	(printout t "din mutatie de aici" ?x crlf)
	) 

(defrule mutatieinterval
	(declare (salience 9))
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2))
	(item (id ?id) (instructor ?ins) (duration ?dur))
	(instructor (name ?ins) (intervals $? ?p1 ?day ?x1 ?x2 ?p2 $? ) )
	(test (eq ?p1 [))	
	(test (eq ?p2 ]))
	(or (not (test (<= ?x1 ?i1))) (not (test (>= ?x2 ?i2))))
	?int <- (interv ?n1 ?n2)
	(not (control 1))
	?cont <- (control ?x)
	
=>	
	(retract ?int ?cont)
	(printout t "ANA are mere" crlf)
	(randomint ?x1 ?x2 ?dur)
	(modify ?f (interval ?n1 ?n2 ))
	(assert (control 1 ))
	
	)
	


;;------------------------------
(defmodule MS (import MAIN ?ALL))
;;------------------------------

(deffacts fa (control 0))


(defrule mutatiesala
	
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2) (room ?room))
	?g <- (orarone (tip nou) (id ?id1) (day ?day) (interval ?o1 ?o2) (room ?room))
	(test (neq ?id ?id1))
	(item (id ?id) (duration ?dur1))
	(item (id ?id1) (duration ?dur2))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	?int <- (interv ?n1 ?n2)
	(not (control 1))
	?cont <- (control ?x)
=>
	(retract ?int ?cont)
	(printout t "ANA are mere" ?id ?id1 crlf)
	
	(bind ?rand (random 1 2)) 
	(if (eq ?rand 1) 
		then
		(printout  t "de aici " ?rand crlf)
		  (randomintervalrest ?dur1 ?i1 ?i2)
		  (modify ?g (interval ?n1 ?n2 ))
	)
	
	(if (eq ?rand 2)
		then
		(printout  t "de aici " ?rand crlf)
		  (randomintervalrest ?dur2 ?o1 ?o2)
		  (modify ?f (interval ?n1 ?n2 ))	  
	)
	
	(assert (control 1 ))
	)
	
(defrule restart 
	?f <- (control ?x)
=>
	(modify ?f (control 0))
	)

;;------------------------------
(defmodule MG (import MAIN ?ALL))
;;------------------------------
(deffacts fa (control 0))
(defrule mutatiegrupe 
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2))
	(item (id ?id) (duration ?dur1) (groups $? ?grp $?))
	?g <- (orarone (tip nou) (id ?id1) (day ?day) (interval ?o1 ?o2))
	(item (id ?id1) (duration ?dur2) (groups $? ?grp $?))
	(test (neq ?id ?id1))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	?int <- (interv ?n1 ?n2)
	(not (control 1))		
	?cont <- (control ?x)
	
=>	
	(retract ?int ?cont)
	(printout t "ANA are grupe" ?id ?id1 crlf)
	
	(bind ?rand (random 1 2)) 
	(if (eq ?rand 1) 
		then
		(printout  t "de aici " ?rand crlf)
		  (randomintervalrest ?dur1 ?i1 ?i2)
		  (modify ?g (interval ?n1 ?n2 ))
	)
	
	(if (eq ?rand 2)
		then
		(printout  t "de aici " ?rand crlf)
		  (randomintervalrest ?dur2 ?o1 ?o2)
		  (modify ?f (interval ?n1 ?n2 ))	  
	)
	
	(assert (control 1 ))
	)
	
	
(defrule restart 
	?f <- (control ?x)
=>
	(modify ?f (control 0))
	)
;;------------------------------
(defmodule MP (import MAIN ?ALL))
;;------------------------------
(deffacts fa (control 0))



(defrule mutatieprof
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2))
	?g <- (orarone (tip nou) (id ?id1) (day ?day) (interval ?o1 ?o2))
	(item (id ?id) (instructor ?name) (duration ?dur1))
	(item (id ?id1) (instructor ?name) (duration ?dur2))
	(test (neq ?id ?id1))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	?int <- (interv ?n1 ?n2)
	(not (control 1))
	?cont <- (control ?x)
	
=>	
	(retract ?int ?cont)
	(printout t "ANA are profi" ?id ?id1 crlf)
	
	(bind ?rand (random 1 2)) 
	(if (eq ?rand 1) 
		then
		(printout  t "de aici " ?rand crlf)
		  (randomintervalrest ?dur1 ?i1 ?i2)
		  (modify ?g (interval ?n1 ?n2 ))
	)
	
	(if (eq ?rand 2)
		then
		(printout  t "de aici " ?rand crlf)
		  (randomintervalrest ?dur2 ?o1 ?o2)
		  (modify ?f (interval ?n1 ?n2 ))	  
	)
	
	(assert (control 1 ))
	)

(defrule restart 
	?f <- (control ?x)
=>
	(modify ?f (control 0))
	)


;;------------------------------
(defmodule FITNESSVECHI (import MAIN ?ALL))
;;------------------------------

(deffacts facts1 (vector) (vector1 ) (vector2 ) (vector3 ))



	
(defrule fitnessala
	(declare (salience 10))
	?f <- (orarone (tip vechi) (id ?id) (day ?day) (interval ?i1 ?i2) (room ?room))
	?g <- (orarone (tip vechi) (id ?id1) (day ?day) (interval ?o1 ?o2) (room ?room))
	(test (neq ?id ?id1))
	(not (vector $? [ ?id ?id1 ] $?)) 
	(not (vector $? [ ?id1 ?id ] $?))
	?v <- (vector $?abc)
	(item (id ?id) (duration ?dur1))
	(item (id ?id1) (duration ?dur2))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	?s <- (score ?x)
=>
	(retract ?s)
	(assert (score (+ ?x 1)))
	(assert (vector $?abc [ ?id ?id1 ] ))
	(printout t "fitnesssala vechi:  " ?x ?id "  " ?id1 crlf)
	
	)


	
(defrule fitnesprof
	(declare (salience 8))
	?f <- (orarone (tip vechi) (id ?id) (day ?day) (interval ?i1 ?i2))
	?g <- (orarone (tip vechi) (id ?id1) (day ?day) (interval ?o1 ?o2))
	(item (id ?id) (instructor ?name) (duration ?dur1))
	(item (id ?id1) (instructor ?name) (duration ?dur2))
	(test (neq ?id ?id1))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	(not (vector1 $? [ ?id ?id1 ] $?)) 
	(not (vector1 $? [ ?id1 ?id ] $?))
	?v <- (vector1 $?abc)
	?s <- (score ?x)
	
=>
	(retract ?s)
	(assert (score (+ ?x 1)))
	(assert (vector1 $?abc [ ?id ?id1 ]))
	(printout t "fitnesprof vechi:  " ?x "  " ?id "  " ?id1 crlf)
	
	)
	
(defrule fitnesgrupa
	(declare (salience 7))
	?f <- (orarone (tip vechi) (id ?id) (day ?day) (interval ?i1 ?i2))
	(item (id ?id)  (groups $? ?grp $?))
	?g <- (orarone (tip vechi) (id ?id1) (day ?day) (interval ?o1 ?o2))
	(item (id ?id1)  (groups $? ?grp $?))
	(test (neq ?id ?id1))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	(not (vector2 $? [ ?id ?id1 ] $?)) 
	(not (vector2 $? [ ?id1 ?id ] $?))
	?v <- (vector2 $?abc)
	?s <- (score ?x)
=>
	(retract ?s)
	(assert (score (+ ?x 1)))
	(assert (vector2 $?abc [ ?id ?id1 ]))
	(printout t "fitnesgrupe vechi:  " ?x "  " ?id "  " ?id1 crlf)
	
	)

(defrule fitnesdole 
	(declare (salience 6))
	?f <- (orarone (tip vechi) (id ?id) (day ?day) (interval ?i1 ?i2))
	(item (id ?id) (instructor ?ins) (duration ?dur))
	(instructor (name ?ins) (intervals $? ?p1 ?day ?x1 ?x2 ?p2 $? ) )
	(test (eq ?p1 [))	
	(test (eq ?p2 ]))
	(or (not (test (<= ?x1 ?i1))) (not (test (>= ?x2 ?i2))) (not (test (>= ?x1 ?i2))) (not (test (<= ?i2 ?x1))) )
	(not (vector3 $? ?id  $?)) 
	?v <- (vector3 $?abc)
	?s <- (score ?x)
=>
	(retract ?s)
	(assert (score (+ ?x 1)))
	(assert (vector3 $?abc ?id))
	(printout t "fitnesdoleante vechi:  " ?x "  " ?id  crlf)
	)

;;------------------------------
(defmodule FITNESSNOU (import MAIN ?ALL))
;;------------------------------

(deffacts facts2 (vect) (vect1 ) (vect2 ) (vect3) )



(defrule fitnessala
	(declare (salience 10))
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2) (room ?room))
	?g <- (orarone (tip nou) (id ?id1) (day ?day) (interval ?o1 ?o2) (room ?room))
	(test (neq ?id ?id1))
	(not (vect $? [ ?id ?id1 ] $?)) 
	(not (vect $? [ ?id1 ?id ] $?))
	?v <- (vect $?abc)
	(item (id ?id) (duration ?dur1))
	(item (id ?id1) (duration ?dur2))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	?s <- (scor ?x)
=>
	(retract ?s)
	(assert (scor (+ ?x 1)))
	(assert (vect $?abc [ ?id ?id1 ]))
	(printout t "fitnesssala nou:  " ?x ?id "  " ?id1 crlf)
	
	)


	
(defrule fitnesprof
	(declare (salience 8))
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2))
	?g <- (orarone (tip nou) (id ?id1) (day ?day) (interval ?o1 ?o2))
	(item (id ?id) (instructor ?name) (duration ?dur1))
	(item (id ?id1) (instructor ?name) (duration ?dur2))
	(test (neq ?id ?id1))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	(not (vect1 $? [ ?id ?id1 ] $?)) 
	(not (vect1 $? [ ?id1 ?id ] $?))
	?v <- (vect1 $?abc)
	?s <- (scor ?x)
	
=>
	(retract ?s)
	(assert (scor (+ ?x 1)))
	(assert (vect1 $?abc [ ?id ?id1 ]))
	(printout t "fitnesprof nou:  " ?x "  " ?id "  " ?id1 crlf)
	
	)
	
(defrule fitnesgrupa
	(declare (salience 7))
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2))
	(item (id ?id)  (groups $? ?grp $?))
	?g <- (orarone (tip nou) (id ?id1) (day ?day) (interval ?o1 ?o2))
	(item (id ?id1)  (groups $? ?grp $?))
	(test (neq ?id ?id1))
	(test (or (and (>= ?i1 ?o1) (<= ?i1 ?o2) )  (and (>= ?i2 ?o1) (<= ?i2 ?o2) )))
	(not (vect2 $? [ ?id ?id1 ] $?)) 
	(not (vect2 $? [ ?id1 ?id ] $?))
	
	?v <- (vect2 $?abc)
	?s <- (scor ?x)
=>
	(retract ?s)
	(assert (scor (+ ?x 1)))
	(assert (vect2 $?abc [ ?id ?id1 ]))
	(printout t "fitnesgrupe nou:  " ?x "  " ?id "  " ?id1 crlf)
	
	)

(defrule fitnesdole 
	(declare (salience 6))
	?f <- (orarone (tip nou) (id ?id) (day ?day) (interval ?i1 ?i2))
	(item (id ?id) (instructor ?ins) (duration ?dur))
	(instructor (name ?ins) (intervals $? ?p1 ?day ?x1 ?x2 ?p2 $? ) )
	(test (eq ?p1 [))	
	(test (eq ?p2 ]))
	(or (not (test (<= ?x1 ?i1))) (not (test (>= ?x2 ?i2))) (not (test (>= ?x1 ?i2))) (not (test (<= ?i2 ?x1))) )
	(not (vect3 $? ?id  $?)) 
	?v <- (vect3 $?abc)
	?s <- (scor ?x)
=>
	(retract ?s)
	(assert (scor (+ ?x 1)))
	(assert (vect3 $?abc ?id))
	(printout t "fitnesdoleante nou:  " ?x "  " ?id  crlf)
	)

