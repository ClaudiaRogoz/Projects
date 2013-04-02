% tema 4 PP
	
% functie care citeste din fisierul de intrare X
init(X) :- 
	see(X),
	citit.

citit :-
	read(X),
	assert(X),
	not(X = end_of_file),
	citit.


citit :- 
	read(X),
	assert(X),
	(X = end_of_file),
	seen.
	


% functie principala 
start_agent :-
	write('Ce tara doriti sa vizitati?'),nl,
	read(Tara),
	concat(Tara,'.txt',Read),
	init(Read),
	write('Ce buget aveti?'),nl,
	read(Buget),
	preference(Buget,Read).
	
preference(Buget,Read) :-
	write('Cum doriti sa fie urmatoarea destinatie de vacanta?'),nl,
	read(Listp),
	optiuni(Listp,Read),
	initmedie(Listp,Medie),
	preference1(Medie,Read,Buget).
	
	
preference1(Medie,Read,Buget) :-
	bestfittown(Medie,BT,Buget),
	townattr(BT,List),
	write('Destinatie recomandata: '), write(BT),write(' - '), write(List),nl,
	cost(BT,Cost),
	(Cost > Buget
	->
	write('Fonduri Insuficiente'),!;
	write('Costul este '), 
	write(Cost), 
	write('   Doriti sa mergeti ? '),nl,
	read(Ans),
	(Ans = yes
	->
	Buget1 is Buget - Cost,
	write('Bun venit in '), write(BT),write(' !'),retract(destinatie(BT)),
	write('Feedback?  '), read(FeedBack),
	addfeed(FeedBack,BT,Read),
	preference(Buget1,Read);
	retract(destinatie(BT)),
	preference1(Medie,Read,Buget))
	).
	
	 

addfeed([],Town,Read).
addfeed([Head|Feedback],Town,Read):-
	Pred =.. [Head,Town],
	assert(Pred),
	append(Read),
	write(Pred), write('.'),nl,nl,
	told,
	addfeed(Feedback,Town,Read).
	
	

townattr(Town,List) :-
	findall(A,semnificatie(A,_),L),
	getTown(Town,L,List).
	
	
optiuni([],Read).
optiuni([Optiune|Tail],Read) :-
	(semnificatie(Optiune,_)
	-> 
	Pred =.. [Optiune,X];
	write('Ce inseamna '),
	write(Optiune),
	write('?'),nl,
	write('Sablon : [temperatura/26,  densitate/8000, dimensiune/50, popularitate/40, urbanizare/76] '),
	read(ListNou),
	assert(semnificatie(Optiune,ListNou)),
	dynamic(Optiune/1),
	append(Read),
	write('semnificatie(') ,write(Optiune),write(','),write(ListNou),write(').'),nl,nl,nl,
	write(':- dynamic '), write(Optiune), write('/1.'),nl, listing(Optiune/1),nl,nl,
	told
	),
	optiuni(Tail,Read).
	

permite(Town,Buget) :- cost(Town,X), X =< Buget.


bestfittown(MedCerere,Rez,Buget) :-	
	findall(Town,destinatie(Town),Towns),
	findall(Attr,semnificatie(Attr,_),Attrbs),
	getTownAttr(Towns,Attrbs,MedCerere,M,Rez,Buget).

	

getTownAttr([Town],Attrbs,MaxV,MaxS,Town,Buget) :-
	getTown(Town,Attrbs,ListAttr),
	initmedie(ListAttr,Med),
	comparatie(Med,MaxV,MaxS).
	
	
getTownAttr([Head|Tail],Attrbs, MaxV,MaxS,BTown,Buget) :-
	getTownAttr(Tail,Attrbs,MaxV,MaxS1,BTown1,Buget),
	getTown(Head,Attrbs,ListAttr),
	initmedie(ListAttr,Med),
	comparatie(Med,MaxV,Comp),
	(Comp =< MaxS1 , cost(Head,Cost), Cost < Buget
	->
	MaxS is Comp,
	BTown = Head;
	MaxS is MaxS1,
	BTown = BTown1,!
	).
	


% functie care imi calculeaza toate atributele pe care le are orasul Town in List
getTown(Town,[],[]).
getTown(Town,[AtH|AtT],[AtH|List]) :-
	Pred =.. [AtH,Town],
	Pred,
	getTown(Town,AtT,List).


getTown(Town,[AtH|AtT],List) :-
	Pred =.. [AtH,Town],
	not(Pred),
	getTown(Town,AtT,List).
	


	
% compara 2 liste de atribute
comparatie([temperatura/A,  densitate/B, dimensiune/C, popularitate/D, urbanizare/E],[temperatura/F,  densitate/G, dimensiune/H, popularitate/I, urbanizare/J],Rez) :-
	scadere(A ,F,A1),
	scadere(B ,G,A2),
	scadere(C ,H,A3),
	scadere(D ,I,A4),
	scadere(E ,J,A5),
	X is A1 + A2 + A3 + A4 + A5,
	absol(X,Rez).


% modulul unui numar
absol(X,Rez) :-
	(X >= 0
	->
	Rez is X;
	Rez is -1 * X).

% scadere dintre 2 valori de atribute
scadere(nimic,nimic,0).
scadere(nimic,A,A).
scadere(A,nimic,A).
scadere(A,B,Rez) :- 
	not(A = nimic),not(B = nimic),
	Rez is A - B.
		

medie([],X,Rez).
medie([Head],X,Rez) :- 
	semnificatie(Head,Y),
	media1(Y,X,Rez),
	medie([],Rez,K).


	
medie([Head|Tail],X,Rez) :-
	semnificatie(Head,Y),
	media1(Y,X,K),
	medie(Tail,K,Rez).
		
% functie care calculeaza media dintre o lista de semnificatii
initmedie([],Rez).
initmedie([Head],Rez) :-
	semnificatie(Head,Rez). 
initmedie([Head|Tail],Rez):-
	semnificatie(Head,X),
	medie(Tail,X,Rez).

	

media1([temperatura/A,  densitate/B, dimensiune/C, popularitate/D, urbanizare/E],[temperatura/F,  densitate/G, dimensiune/H, popularitate/I, urbanizare/J],Rez) :-
	media2(A,F,M1),
	media2(B,G,M2),
	media2(C,H,M3),
	media2(D,I,M4),
	media2(E,J,M5),
	Rez = [temperatura/M1,  densitate/M2, dimensiune/M3, popularitate/M4, urbanizare/M5].


media2(nimic,nimic,nimic).
media2(nimic,A,X) :-
	not(A = nimic),
	X is A.
media2(A,nimic,X) :-
	not(A = nimic),
	X is A.
media2(A,B,M) :-
	not(A = nimic),not(B = nimic),
	M is (A + B)/2.

