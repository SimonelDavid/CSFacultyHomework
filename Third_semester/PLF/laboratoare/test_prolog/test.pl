%test
% sterge(L:lista, E:Integer, X:Integer, R:lista)
% Modele de flux (i, i, i, o),(i,i,i,i)
%L:lista inițială din care vrem sa stergem
%E:pozitia elementului pe care il vrem sters
%X: pozitia actuala
%R:lista fără elementul pe care dorim sa îl ștergem

sterge([], E, X, []).
sterge([H|T], E, X, R) :- 
    X =:= E, 
    X1 is X+1,
    E1 is E*2, 
    E2 is E1+1,
    sterge(T, E2, X1, R).
sterge([H|T], E, X, [H|R]) :- 
    X =\= E,
    X1 is X+1,
    sterge(T, E, X1, R).
