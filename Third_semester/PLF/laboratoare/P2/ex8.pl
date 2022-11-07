%domains
%   el = integer
%   list = el*
%predicates
%   adaugaSf(el,list,list)  (i,i,o)
%   invers(list,list)   (i,o)
%   sum(list,integer,list)  (i,i,o)
%   succesor(list,list)     (i,o)
%   tipar(list)
%clauses

adaugaSf(E,[],[E]).
adaugaSf(E,[H|T],[H|L]):-adaugaSf(E,T,L).
invers([], []).
invers([H|T], L):-invers(T,L1),
                  adaugaSf(H,L1,L).

sum([],Tr,[_]):-Tr=\=0,!.
sum([],Tr,[]):-!.
sum([H|T],Tr,[S|L1]):-
                    S1=H+Tr,
                    S=S1 mod 10,
                    Tr1 = S1 div 10,
                    sum(T,Tr1,L1).

succesor(L,LS):-invers(L,LI),
                sum(LI,1,LA),
                invers(LA,LS),
                write("L="),
                tipar(LS),
                write("]").

tipar([]).
tipar([H|T]):-write(H),
              write(","),
              tipar(T).
