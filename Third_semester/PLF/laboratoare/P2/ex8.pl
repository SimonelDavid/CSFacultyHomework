%8. a)
%list-integer*
%adaugare la sfarsitul unei liste
%adaugare(E:integer, L:list, LRez:list)
%(i,i,o),(i,i,i)
adaugare([],E,[E]).
adaugare([H|T],E,[H|L]):-adaugare(T,E,L).

%inversa unei liste
%inversare(L:list, LRez:list)
%(i,o),(i,i)
inversare([],[]).
inversare([H|T],LRez):-inversare(T,L), adaugare(L,H,LRez).

%adaugare cu transport
%sum(L:list, Tr:integer, LRez:list)
%(i,o),(i,i)
sum([],Tr,[Tr]):-Tr>0.
sum([],Tr,[]):-Tr=0.
sum([H|T],Tr,[R|LRez]) :- R1 is H+Tr, R is R1 mod 10, Tr1 is R1 div 10, sum(T,Tr1,LRez).

%succesor(L:list, LS:list)
%(i,o),(i,i)
succesor(L,LS):- inversare(L,LI), sum(LI,1,LA), inversare(LA,LS).


%8. b).
%sublist(L:lista eterogena, R:lista eterogena)
%(i,o),(i,i)
sublist([],[]).
sublist([H|T],[H|L]):-not(is_list(H)), sublist(T,L).
sublist([H|T],[L1|L]):-is_list(H), succesor(H,L1), sublist(T,L), write(L).

