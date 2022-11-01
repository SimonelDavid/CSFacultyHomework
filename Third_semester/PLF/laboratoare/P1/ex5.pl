%Pb5

%a)
%sl(sir_a: lista, el: element ce trebuie sters, Rez_a: lista rezultat)
%(i,i,o) model de flux

sl([], _, []).
sl([H | T], H, Rez_a) :-
    sl(T, H, Rez_a).

sl([H | T], E, [H | Y]) :-
    sl(T, E, Y).

%b)
%add(sir_b: lista data, E: elemnt ce trebuie adaugat, Rez_b:lista rezultat
%gasit: flag ce indica gasirea)
%(i, i, o, i) model de flux

add([], _, [], 1).
add([], E, [[E,1]], 0).
add([ [ H | T ] | U], E,[[H , T1] | Rez_b], _) :- E == H, add(U, E, Rez_b, 1),
    T1 is T+1 .
add([ [ H | T ] | U], E,[[H | T ] | Rez_b], G) :- E \= H, add(U, E, Rez_b, G). 

%copy(sir1_b: primul sir de copiat, sir2_b: sirul2 de copiat)
%(i,o) model de flux
copy([],[]).
copy([T | H], [T | H1]) :- copy(H, H1).

%fr(sir_b: sirul dat, Rez_b: sir intermediar, Rezf_b: rezultat final)
%(i,i,o) determinist
fr([], Rez_b, Rezf_b) :- copy(Rezf_b,Rez_b).
fr([H | T], Rez_b, Rezf_b) :- add(Rez_b, H, Rez1_b, 0),fr(T, Rez1_b, Rezf_b).