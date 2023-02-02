; model matematic
;                           vid                     , n = 0
; sterg(l1 l2 ... ln) =     sterg_par(l1)+sterg(l)           , daca l1 nr
;                           l1 + sterg(l2 ... ln)   , altfel
; ver_par(e, l1 l2 ... ln, j) =    j+1     , daca l1 = e
;                                   j      , altfel
;
; sterg_par(e, l) =    e  , daca j este par
;                      nil,altfel

(defun sterg_par(el)
    (cond
        (() )

    )
)

(defun sterg(l)
    (cond 
        ((null l) nil)
        ((numberp (car l))(cons (sterg_par (car l)) sterg(cdr l)))
        (T(cons (car l) (sterg(cdr l))))
    )    
)

(print (sterg '(1 g (1 h 8 e (2)))))