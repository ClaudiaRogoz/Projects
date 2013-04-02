#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "helpers.h"
#include <queue>
using namespace std;

#define DRUMAX 10000

void vecini (int topologie[10][10] , int i, int * vec){
	int k;
	
	for (k = 0; k < 10; k++)
		if(topologie[i][k] != -1) {
			vec[k] = topologie[i][k];
			
		}	


}
int digits(int i){
	int k = 0;
	if(i == 0) return 1;
	while(i){
	i = i /10;
	k++;
	}
	return k;
	
}
int minselect(int d[KIDS], int s[KIDS]){
	int i;
	int min = 100000;
	int ind = -1;
	for(i = 0 ; i < KIDS; i++){
		if(min > d[i] && s[i] == 0){
			min = d[i];
			ind = i;
		}
	}
	return ind;
}

void dijkstra (int sursa, int topologie[KIDS][KIDS], int tab_rutare[KIDS][2]) {
	int i,j;
	for(i=0;i<KIDS;i++)
	topologie[i][i] =0;
	for(i=0;i<KIDS;i++){
		for(j=0;j<KIDS;j++){
			if(topologie[i][j] == -1)
			topologie[i][j] = 10000;
		}
	}
	int selectat[KIDS]; 
	int d[KIDS];
	int v[KIDS];
	for(i = 0; i < KIDS; i++) {
		selectat[i] = 0;
		d[i] = topologie[sursa][i];
		if (d[i] != 10000)
			v[i] =  i;
		else v[i] = 0;
	}
	
	selectat[sursa] = 1;
	d[sursa] = 0;
	for(i = 0; i < KIDS; i++) {
		int k = minselect(d, selectat);
		int j;
		selectat[k] = 1;
		for(j = 0; j < KIDS; j++)
			if ( (selectat[j] == 0) && (d[k] + topologie[k][j] < d[j]) ) {
				d[j] = d[k] + topologie[k][j];
				v[j] = v[k];
			}
	}
	
	for(i=0;i<KIDS;i++){
		tab_rutare[i][0] = d[i];
		tab_rutare[i][1] = v[i];
	}
	for(i=0;i<KIDS;i++)
	topologie[i][i] =-1;
	for(i=0;i<KIDS;i++){
		for(j=0;j<KIDS;j++){
			if(topologie[i][j] == 10000)
			topologie[i][j] = -1;
		}
	}
	
}

int newmsg(msg lsadb[], msg x, int index,int *put){
	int i =0;
	int ok = 0;
	for (i =0; i < index;i++){
		if(x.creator == lsadb[i].creator ){
		
					ok =1;
			if(x.timp > lsadb[i].timp ){
						ok =2;
						*put = i;
						break;
			}
		} 
		 
	}
	return ok;	
}

void printtopo(int topo[KIDS][KIDS]){
	int i,j;
	for(i=0;i<KIDS;i++){
		printf("\n");
		for(j=0;j<KIDS;j++){
			printf(" %i ",topo[i][j]);
		}
	}
	printf("\n");

}
int main (int argc, char ** argv)
{			

	int pipeout = atoi(argv[1]);
	int pipein = atoi(argv[2]);
	int nod_id = atoi(argv[3]); //procesul curent participa la simulare numai dupa ce nodul cu id-ul lui este adaugat in topologie 
	int timp =-1 ;
	int gata = FALSE;
	msg mesaj;
	int cit, k;
	int topologie[10][10];
	int j = 0,i =0;
	int nr_secv = 0;
	for(j = 0; j < 10; j++)
		for(i = 0; i < 10; i++)
			topologie[i][j] = -1;
	
	msg LSADatabase[KIDS];
	for(j = 0; j < KIDS;j++)
		LSADatabase[j].timp = -100;
	
	int indexdb = 0;
	queue<msg> curentq;
		
	//nu modificati numele, modalitatea de alocare si initializare a tabelei de rutare - se foloseste la mesajele de tip 8/10, deja implementate si la logare
	int tab_rutare [KIDS][2]; //tab_rutare[k][0] reprezinta costul drumului minim de la ruterul curent (nod_id) la ruterul k 
								//tab_rutare[k][1] reprezinta next_hop pe drumul minim de la ruterul curent (nod_id) la ruterul k 
								
	for (k = 0; k < KIDS; k++) {
		tab_rutare[k][0] = 10000;  // drum =DRUMAX daca ruterul k nu e in retea sau informatiile despre el nu au ajuns la ruterul curent
		tab_rutare[k][1] = -1; //in cadrul protocolului(pe care il veti implementa), next_hop =-1 inseamna ca ruterul k nu e (inca) cunoscut de ruterul nod_id (vezi mai sus)
	}
																
	printf ("Nod %d, pid %u alive & kicking\n", nod_id, getpid());

	if (nod_id == 0) { //sunt deja in topologie
		timp = -1; //la momentul 0 are loc primul eveniment
		mesaj.type = 5; //finish procesare mesaje timp -1
		mesaj.sender = nod_id;
		write (pipeout, &mesaj, sizeof(msg)); 
		printf ("TRIMIS Timp %d, Nod %d, msg tip 5 - terminare procesare mesaje vechi din coada\n", timp, nod_id);
	
	}

	while (!gata) {
		cit = read(pipein, &mesaj, sizeof(msg));
		
		if (cit <= 0) {
			printf ("Adio, lume cruda. Timp %d, Nod %d, msg tip %d cit %d\n", timp, nod_id, mesaj.type, cit);
			exit (-1);
		}
		
		switch (mesaj.type) {
			
			//1,2,3,4 sunt mesaje din protocolul link state; 
			//actiunea imediata corecta la primirea unui pachet de tip 1,2,3,4 este buffer-area (punerea in coada /coada new daca sunt 2 cozi - vezi enunt)
			//mesajele din coada new se vor procesa atunci cand ea devine coada old (cand am intrat in urmatorul pas de timp)
			case 1:
				{
				//printf ("Timp %d, Nod %d, msg tip 1 - LSA\n", timp, nod_id);
				curentq.push(mesaj);
				
				
				}
				break;
				
			case 2:
				{
				//printf ("Timp %d, Nod %d, msg tip 2 - Database Request\n", timp, nod_id);
				
				curentq.push(mesaj);
				
				
				}
				
				break;
				
			case 3:
				{
				//printf ("Timp %d, Nod %d, msg tip 3 - Database Reply\n", timp, nod_id);
				
				
				curentq.push(mesaj);
				}
				break;
				
			case 4: 
				{ 
				//printf ("Timp %d, Nod %d, msg tip 4 - pachet de date (de rutat)\n", timp, nod_id);
				curentq.push(mesaj);
				
				}
				break; 
			
			case 6://complet in ceea ce priveste partea cu mesajele de control 
					//puteti inlocui conditia de coada goala, ca sa corespunda cu implementarea personala
				  //aveti de implementat procesarea mesajelor ce tin de protocolul de rutare
				{
				timp++;
				//printf ("Timp %d, Nod %d, msg tip 6 - incepe procesarea mesajelor puse din coada la timpul anterior (%d)\n", timp, nod_id, timp-1);
				queue<msg> oldq = curentq;
				while(!curentq.empty())
					curentq.pop();
				
				
				//veti modifica ce e mai jos -> in scheletul de cod nu exista nicio coada
				//int coada_old_goala = TRUE;
				
				//daca NU mai am de procesat mesaje venite la timpul anterior
				//(dar mai pot fi mesaje venite in acest moment de timp, pe care le procesez la t+1) 
				//trimit mesaj terminare procesare pentru acest pas (tip 5)
				//altfel, procesez mesajele venite la timpul anterior si apoi trimit mesaj de tip 5
				while (!oldq.empty()) {
					//	procesez tote mesajele din coada old 
					//	(sau toate mesajele primite inainte de inceperea timpului curent - marcata de mesaj de tip 6)
					//	la acest pas/timp NU se vor procesa mesaje venite DUPA inceperea timpului curent
//cand trimiteti mesaje de tip 4 nu uitati sa setati (inclusiv) campurile, necesare pt logare:  mesaj.timp, mesaj.creator, mesaj.nr_secv, mesaj.sender, mesaj.next_hop
					//la tip 4 - creator este sursa initiala a pachetului rutat
				msg mesajq = oldq.front();
				oldq.pop();
				switch(mesajq.type){
				
					case 1 : {	//printf ("Timp %d, Nod %d, msg tip 1 - LSA %s \n====================", timp, nod_id,mesajq.payload);
					
							int put = 0;
							int ok = newmsg(LSADatabase,mesajq,indexdb,&put);
							// exista creator si este mai nou decat in db
							if(ok == 2 ){
							
								LSADatabase[put] = mesajq;
								char *p;
								int com[100]; 
								int i =0 ;
								char payload[1400] ;
								strcpy(payload,mesajq.payload);
								p = strtok (payload, " ");
								while (p != NULL)
								{
									com[i] = atoi(p);					
									i++;
									p = strtok (NULL, " ");
								}
								int len = i;
								// actualizare topologie 
							
								for(i = 0; i < len - 1 ; i+=2){
									topologie[com[i]][mesajq.creator] = com[i+1];
									topologie[mesajq.creator][com[i]] = com[i+1];
								
								}
								if(len > 1 ){
									// forwardam mesajul primit tuturor vecinilor mai putin senderului
									int sender = mesajq.sender;
									int vec[10];
									for(i = 0; i < KIDS; i++)
										vec[i] = -1;
									vecini(topologie,nod_id,vec);	
									for(i = 0;i < KIDS; i++){
										if(vec[i] !=-1 && i != sender){
											
											mesajq.sender = nod_id;
											mesajq.next_hop = i;
											write (pipeout, &mesajq, sizeof(msg)); 
										}
									}		
								
								}
								
								
							}else if(ok ==0 ){
								// nu exista creator in Db 
							
								LSADatabase[indexdb] = mesajq;
								indexdb++;
								char *p;
								int com[100]; 
								int i =0 ;
								char payload[1400];
								strcpy(payload,mesajq.payload);
								p = strtok (payload, " ");
								while (p != NULL)
								{
									com[i] = atoi(p);					
									i++;
									p = strtok (NULL, " ");
								}
								int len = i;
								// actualizare topologie
								for(i = 0; i < len - 1 ; i+=2){
									topologie[com[i]][mesajq.creator] = com[i+1];
									topologie[mesajq.creator][com[i]] = com[i+1];
								}
								if(len > 1 ){
									// forwardam mesajul primit tuturor vecinilor mai putin senderului

									int sender = mesajq.sender;
									int vec[10];
									for(i = 0; i < KIDS; i++)
										vec[i] = -1;
									vecini(topologie,nod_id,vec);	
									for(i = 0;i < KIDS; i++){
										if(vec[i] !=-1 && i != sender){
											
											mesajq.sender = nod_id;
											mesajq.next_hop = i;
											write (pipeout, &mesajq, sizeof(msg)); 
										}
									}		
								
								}	
							}
							
							
							} break;
					case 2: {
						// trimitem mesaje de tip database reply cu toata LSADatabase noului router pentru a fi 						//updatat
						
						
						//update topologie 
						topologie[nod_id][mesajq.sender] = mesajq.len;
						topologie[mesajq.sender][nod_id] = mesajq.len;
						
						
						// routerul raspunde lui newR cu toate mesajele din database;
						for(j = 0; j < indexdb ; j++){
							
							msg tip3 = LSADatabase[j];
							
							tip3.type = 3;
							tip3.sender = nod_id;
							tip3.next_hop = mesajq.sender;	
							tip3.timp = timp;
							write (pipeout, &tip3, sizeof(msg)); 
						}
						
						msg tip1;
						tip1.type = 1;
						tip1.sender = nod_id;
						tip1.timp = timp;
						tip1.creator = nod_id;
						tip1.nr_secv = nr_secv ;
						nr_secv++;
						
						int vec[10];
						for(i = 0; i < KIDS; i++)
							vec[i] = -1;
						vecini(topologie,nod_id,vec);
						
				
						
						
						char payload[1400] ;
						int k = 0;
						for(i = 0;i < KIDS; i++){
							if(vec[i] !=-1){
								int x = digits(i) + 2 + digits(vec[i]);
								sprintf(payload+k,"%i%c%i%c",i,' ',vec[i],' ');
								k +=x;
							}
						}
						
						sprintf(payload+k,"%c",'\0');
						
						memcpy(tip1.payload, payload,strlen(payload));
						
						
						
						for(i = 0;i < KIDS; i++){
							if(vec[i] != -1){
								tip1.next_hop = i;
								
								
								write (pipeout, &tip1, sizeof(msg)); 
							}
						}
						
					} break;
					
					case 3 : {	int put = 0;
							int ok = newmsg(LSADatabase,mesajq,indexdb,&put);
							
							// exista creator si este mai nou decat in db
							if(ok == 2 ){
							
								LSADatabase[put] = mesajq;
								char *p;
								int com[100]; 
								char payload[1400];
								strcpy(payload,mesajq.payload);
								int i =0 ;
								p = strtok (payload, " ");
								while (p != NULL)
								{
									com[i] = atoi(p);					
									i++;
									p = strtok (NULL, " ");
								}
								int len = i;
								// actualizare topologie 
								for(i = 0; i < len - 1 ; i+=2){
									topologie[com[i]][mesajq.creator] = com[i+1];
									topologie[mesajq.creator][com[i]] = com[i+1];
								
						
								}	
							}else if(ok ==0 ){
							
								// nu exista creator in Db 
								LSADatabase[indexdb] = mesajq;
								indexdb++;
								char *p;
								char payload[1400] ;
								strcpy(payload,mesajq.payload);
								int com[100]; 
								int i =0 ;
								p = strtok (payload, " ");
								while (p != NULL)
								{
									com[i] = atoi(p);					
									i++;
									p = strtok (NULL, " ");
								}
								int len = i;
								// actualizare topologie
								for(i = 0; i < len - 1 ; i+=2){
									topologie[com[i]][mesajq.creator] = com[i+1];
									topologie[mesajq.creator][com[i]] = com[i+1];
								
								}
								
							}
						} break;
						// primesc pachet de tip 4 il retrimit 
					case 4 : {
							
							if(mesajq.len == nod_id){
								printf("!!!!!!!@@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!am ajuns acasa\n");
							}
							else
							{
								mesajq.sender = nod_id;
								mesajq.next_hop = tab_rutare[mesajq.len][1];
								mesajq.timp = timp;
								write (pipeout, &mesajq, sizeof(msg)); 
								
							}
						
							} break;
				
				
				}
				
				
				
				
				
				
				}
				dijkstra(nod_id,topologie,tab_rutare);
				
				FILE * f = fopen("log","at");
				
				fprintf(f,"\nNodul %i la timpul %i \n", nod_id, timp-1);
				
				for(i=0;i<KIDS;i++){
					fprintf(f,"\n");
					for(j=0;j<KIDS;j++){
					 fprintf(f," %i ",topologie[i][j]);
					}
				}
				fprintf(f,"\n");
				
				for(i=0;i<KIDS;i++){
					fprintf(f,"\n");
					fprintf(f,"%i   %i ", tab_rutare[i][1],tab_rutare[i][0]);
					
				}
				fprintf(f,"\n");
				
				fclose(f);
				
				//acum coada_old e goala, trimit mesaj de tip 5
					mesaj.type = 5; 
					mesaj.sender = nod_id;
					write (pipeout, &mesaj, sizeof(msg)); 
				}
				break;
			
			case 7: //complet in ceea ce priveste partea cu mesajele de control
					//aveti de implementat tratarea evenimentelor si trimiterea mesajelor ce tin de protocolul de rutare
					//in campul payload al mesajului de tip 7 e linia de fisier (%s) corespunzatoare respectivului eveniment
					//vezi multiproc.c, liniile 88-115 (trimitere mes tip 7) si liniile 184-194 (parsare fisiere evenimente)
					 
					//rutere direct implicate in evenimente, care vor primi mesaje de tip 7 de la simulatorul central:
					//eveniment tip 1: ruterul nou adaugat la retea  (ev.d1  - vezi liniile indicate)
					//eveniment tip 2: capetele noului link (ev.d1 si ev.d2)
					//eveniment tip 3: capetele linkului suprimat (ev.d1 si ev.d2)
					//evenimet tip 4:  ruterul sursa al pachetului (ev.d1)
				{
				
		
		
				if (mesaj.join == TRUE) {
					timp = mesaj.timp;
					printf ("Nod %d, msg tip eveniment - voi adera la topologie la pasul %d\n", nod_id, timp+1); 
				}
				else
					printf ("Timp %d, Nod %d, msg tip 7 - eveniment\n", timp+1, nod_id);
				//acest tip de mesaj (7) se proceseaza imediat - nu se pune in nicio coada (vezi enunt)
				// parsare mesaj
				char *p;
				int com[100]; 
				int i =0 ;
				char payload[1400] ; strcpy(payload,mesaj.payload);
				p = strtok (payload, " ");
				while (p != NULL)
				{
					com[i] = atoi(p);					
					
					i++;
					p = strtok (NULL, " ");
				}
				int len = i;
				switch (com[0]) {
					case 1 :  // eveniment de tip 1 
						 {
							
							msg tip2;
							tip2.type = 2;
							tip2.sender = nod_id;
							tip2.timp = timp ;
							tip2.creator = nod_id;
							
							// actualizam topologia cu datele primite din mesaj
							// si trimitem mesajele la vecini
							for( i = 3; i < len-1 ; i+=2){
								
								topologie[com[1]][com[i]] = com[i+1]; 
								topologie[com[i]][com[1]] = com[i+1]; 
								
								tip2.next_hop = com[i];
								tip2.len = com[i+1];
								tip2.nr_secv = nr_secv;
								nr_secv++;
								write (pipeout, &tip2, sizeof(msg));	
							}

							
							int vec[10];
							for(i = 0; i < 10; i++)
								vec[i] = -1;
							vecini(topologie,nod_id,vec);
							
							
								



							} break;
					case 2 :  // eveniment de tip 2 adaugare de link 
						 {
						 	// creeaza si isi trimit unul altora mesaje de tip Database request
						 	topologie[com[1]][com[2]] = com[3];
						 	topologie[com[2]][com[1]] = com[3];
						 	
						 	msg tip2;
						 	tip2.type = 2;
						 	tip2.sender = nod_id;
						 	tip2.next_hop = com[1] == nod_id ? com[2] : com[1];
						 	tip2.timp = timp;
						 	tip2.creator = nod_id;
						 	tip2.nr_secv = nr_secv;
						 	nr_secv++;
						 	tip2.len = com[3];
						 	write (pipeout, &tip2, sizeof(msg));
						 	// trimit lsa la vecini 
						 	int vec[10];
							for(i = 0; i < 10; i++)
								vec[i] = -1;
							vecini(topologie,nod_id,vec);
							
							msg lsa;
							lsa.type = 1;
							lsa.sender = nod_id;
							lsa.creator = nod_id;
							lsa.timp = timp;
							lsa.nr_secv = nr_secv;
							nr_secv ++;
							
							char payload[1400] ;
							int k = 0;
							for(i = 0;i < KIDS; i++){
								if(vec[i] !=-1){
									int x = digits(i) + 2 + digits(vec[i]);
									sprintf(payload+k,"%i%c%i%c",i,' ',vec[i],' ');
									k +=x;
								}
							}
						
							sprintf(payload+k,"%c",'\0');
						
							memcpy(lsa.payload, payload,strlen(payload));
							
							for(i = 0 ; i < KIDS; i++)
								if(vec[i] != -1){
									lsa.next_hop = i;
									write (pipeout, &lsa, sizeof(msg)); 
								}	
						 
							} break;					
					case 3 :  // eveniment de tip 3 suprimarea unui link 
						 {
						 	//printf("am primit eveniment 3 in %i \n",nod_id);
						 	// creeaza si isi trimit unul altora mesaje de tip Database request
						 	
						 	//printf("%i    %i\n ",com[1],com[2]);
						 	topologie[com[1]][com[2]] = -1;
						 	topologie[com[2]][com[1]] = -1;
						 	// luam toti vecinii noi ai nodului
						 	int vec[10];
							for(i = 0; i < 10; i++)
								vec[i] = -1;
							vecini(topologie,nod_id,vec);
							
							msg lsa;
							lsa.type = 1;
							lsa.sender = nod_id;
							lsa.creator = nod_id;
							lsa.timp = timp;
							lsa.nr_secv = nr_secv;
							nr_secv ++;
							
							char payload[1400] ;
							int k = 0;
							for(i = 0;i < KIDS; i++){
								if(vec[i] !=-1){
									int x = digits(i) + 2 + digits(vec[i]);
									sprintf(payload+k,"%i%c%i%c",i,' ',vec[i],' ');
									k +=x;
								}
							}
						
							sprintf(payload+k,"%c",'\0');
						
							memcpy(lsa.payload, payload,strlen(payload));
							
							for(i = 0 ; i < KIDS; i++)
								if(vec[i] != -1){
									lsa.next_hop = i;
									write (pipeout, &lsa, sizeof(msg)); 
								}	
							int put= 0;
							int ok = newmsg(LSADatabase,lsa,indexdb,&put);
							if(ok == 2){
								LSADatabase[put] = lsa;
							}else{
								LSADatabase[indexdb] = lsa;
								indexdb++;
							
							}
							//refacem tabela de rutare 
							dijkstra(nod_id,topologie,tab_rutare);
						 	
						 	
							} break;
					case 4 :  // eveniment de tip 4 
						 {	
						 	//printf("am primit %i cu payload %s\n",nod_id, mesaj.payload);
						 	msg pachet;
						 	pachet.type = 4;
						 	pachet.sender = nod_id;
						 	pachet.creator = nod_id;
						 	pachet.timp = timp;
						 	pachet.nr_secv = nr_secv;
						 	nr_secv ++;
						 	pachet.next_hop = tab_rutare[com[2]][1];
						 
						 	pachet.len = com[2];
						 	write (pipeout, &pachet, sizeof(msg)); 
						 	
						 	
							} break;
					default : break;

				}
				break;
			}
			case 8: //complet implementat - nu modificati! (exceptie afisari on/off)
				{
				//printf ("Timp %d, Nod %d, msg tip 8 - cerere tabela de rutare\n", timp+1, nod_id);
				mesaj.type = 10;  //trimitere tabela de rutare
				mesaj.sender = nod_id;
				memcpy (mesaj.payload, &tab_rutare, sizeof (tab_rutare));
				//Observati ca acest tip de mesaj (8) se proceseaza imediat - nu se pune in nicio coada (vezi enunt)
				write (pipeout, &mesaj, sizeof(msg)); 
				}
				break;
				
			case 9: //complet implementat - nu modificati! (exceptie afisari on/off)
				{
				//Aici poate sa apara timp -1 la unele "noduri"
				//E ok, e vorba de procesele care nu reprezentau rutere in retea, deci nu au de unde sa ia valoarea corecta de timp
				//Alternativa ar fi fost ca procesele neparticipante la simularea propriu-zisa sa ramana blocate intr-un apel de read()
				printf ("Timp %d, Nod %d, msg tip 9 - terminare simulare\n", timp, nod_id);
				gata = TRUE;
				}
				break;
				

			default:
				printf ("\nEROARE: Timp %d, Nod %d, msg tip %d - NU PROCESEZ ACEST TIP DE MESAJ\n", timp, nod_id, mesaj.type);
				exit (-1);
		}			
	}

return 0;

}
