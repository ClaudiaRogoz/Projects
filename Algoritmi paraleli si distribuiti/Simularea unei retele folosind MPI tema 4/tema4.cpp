#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <unistd.h>
#include <string.h>

using namespace std;

vector<string> split(string const &input){

	istringstream buffer(input);
	vector<string> ret;
	
	copy(istream_iterator<string>(buffer),istream_iterator<string>(),back_inserter(ret));
	
	return ret;
	
}


int main(int argc, char *argv[])
{
	int noTasks, rank, n = 8;
	int recv, sync = 0;
	int x,y;
	int tag = 0,tag1 = 1;

	int ok = 0, efrunza = 1;
	
	if(argc != 3){
		printf("Not proper use\n");
		return 0;
	}
	char* fistopo = argv[1];
	char* fismesaj = argv[2];
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &noTasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// citesc vecinii
	ifstream infile1(fistopo);
	int i = 0;
	int j = 0;
	char line[128];
	string str;
	map<int,int> tabelarutare;
	while(getline(infile1,str) != NULL){
		if(i == rank){
			break;
		}
		i++;
	}
	vector<string> vec = split(str);
	vector<int> vecini;
	for(int k = 1; k < vec.size(); k++){
		int val = atoi(vec.at(k).c_str());
		vecini.push_back(val);	
	}
	
	
	// citesc mesajele din fisier 
	ifstream infile2(fismesaj);
	int nrmes;
	vector<string> mesaje;
	infile2>>nrmes;
	
	getline(infile2,str);
	for(i = 0; i < nrmes; i++){
		getline(infile2,str);
		mesaje.push_back(str);
		//cout<<str<<"  ";
	}
	map<string,string> detrimis;
	int nr = 0;
	for(i = 0; i < mesaje.size(); i++){
		vector<string> mess = split(mesaje.at(i));
		int sursa = atoi(mess.at(0).c_str());
		if(sursa == rank){
			string mesaj;
			for(j = 2; j < mess.size(); j++){
				mesaj += mess.at(j);
				mesaj += " ";
			}
			detrimis[mess.at(1)] = mesaj;
		}
	}
	
	
	
	
	
	int sondaj = 1;
	vector<int> deomis;
	int parinte ;
	//daca sunt nodul initiator 
	if(rank == 0){
		//incep sa trimit mesaje de sondaj catre toti vecinii mei
		for(i = 0; i < vecini.size(); i++){
			MPI_Send(&sondaj, 1, MPI_INT, vecini.at(i), tag, MPI_COMM_WORLD);
		}
		
		int tabela[noTasks];
		// tabela de rutare pana in momentul de fata imi indica sa trimit tot spre parinte
		for(i = 0; i < vecini.size(); i++){
			int aux[noTasks];
			if(aux[1] != -3){
				// primim tabela de rutare a copiilor
				MPI_Recv(aux, noTasks, MPI_INT, vecini.at(i), tag1,MPI_COMM_WORLD,&status);
				// iar daca pe o anumita pozitie destinatia este diferita de rank
				// atunci updatam tabela noastra de rutare
				for(j = 0; j < noTasks; j++){
					if(aux[j] != rank){
						tabelarutare[j] = vecini.at(i);
					
					}
				}
			}
		}
	
	}else{
		int efrunza = 1;
		// daca nu sunt initiator atunci primesc sondaj si trimit mai departe 
		MPI_Recv(&recv,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
		parinte = status.MPI_SOURCE;
		int tabela[noTasks];
		MPI_Request request;
		// tabela de rutare pana in momentul de fata imi indica sa trimit tot spre parinte
		for(i = 0; i < noTasks; i++){
			
			tabelarutare[i] = parinte;
			tabela[i] = parinte;
			
		}
		tabelarutare[rank] = rank;
		tabela[rank] = rank;
		
		// trimitem sondaj mai departe si vedem daca nodul curent este frunza
		for (i = 0; i < vecini.size(); i++) {
			if (vecini.at(i) != parinte) {
				efrunza = 0;
				MPI_Send(&recv, 1, MPI_INT, vecini.at(i), tag, MPI_COMM_WORLD);
			}
		}
		
		int aux;
		MPI_Request request1;
		//cout<<"inainte de recv "<<rank << endl;
		int nul[noTasks];
		for(i = 0; i < noTasks; i++){
			nul[i] = -3;			
		}
		MPI_Request r[vecini.size()];
		
		
		//eliminam ciclurile 
		for (i = 0; i < vecini.size(); i++) {
			//if(vecini.at(i) != parinte){
				MPI_Irecv(&aux, 1, MPI_INT,vecini.at(i), 						tag,MPI_COMM_WORLD,&r[i]);
				sleep(1);
				int flag,index;
				//cout<<"sunt "<<rank <<"si trebuie omis" << status.MPI_SOURCE<<endl;
				MPI_Testany(i+1,r,&index,&flag,&status);
				
				if(flag != 0 && index != MPI_UNDEFINED){	
					deomis.push_back(status.MPI_SOURCE);
		//			cout<<"Am primit in "<<rank<<" de la "<<status.MPI_SOURCE<<endl;
					
					MPI_Send(nul, noTasks, MPI_INT, 						status.MPI_SOURCE,tag1,MPI_COMM_WORLD);
				
				}
			//}
		}
		
		
		// daca este frunza atunci trimitem tabela de rutare 
		if(efrunza){ 
		//	cout<<"sunt frunza"<<rank<<endl;
			MPI_Send(tabela, noTasks, MPI_INT, parinte, tag1, MPI_COMM_WORLD);
			
		}else{
		// daca nu este frunza asteptam tabelele de rutare de la toti vecinii mai putin parintele
			
			for(i = 0; i < vecini.size(); i++){
			int aux[noTasks];
				if(vecini.at(i) != parinte){
					// primim tabela de rutare a copiilor
					MPI_Recv(aux, noTasks, MPI_INT, vecini.at(i), tag1, 							MPI_COMM_WORLD,&status);
					
					// iar daca pe o anumita pozitie destinatia este diferita de rank
						// atunci updatam tabela noastra de rutare
					if(aux[1] != -3){
						for(j = 0; j < noTasks; j++){
							if(aux[j] != rank){
								tabelarutare[j] = vecini.at(i);
								tabela[j] = vecini.at(i);
							}
						}
					}
				}
				
			}
			
			//trimite matricea mai sus
			MPI_Send(tabela, noTasks, MPI_INT, parinte, tag1, MPI_COMM_WORLD);
			
		}
		
		
	
	}
	cout<<"Tabela de rutare pentru " << rank<<"    ";
		
	for(int i = 0; i < noTasks;i++){
		cout<<i<<"==>"<<tabelarutare[i]<<"   ";
	}
	cout<<endl;
	
	// stergem vecinii care trebuiesc omisi adica unde au fost cicluri
	//cout<<"pentru rank "<<rank<<"am de omis "<<vecini.size()<<endl; 
	vector<int> desters;
	for(i = 0; i < vecini.size(); i++){
		for(j = 0; j < deomis.size(); j++){ 
			if(vecini.at(i) == deomis.at(j)){
				vecini.erase(vecini.begin() + i);
			}
		}
	}
	
	cout<<"Sfarsit faza 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!"<<rank<<endl;
	
	int tag2 = 3;
	map<string,string>::iterator iter;
	//trimitem toate mesajele pe care le avem de trimis 
	for(iter = detrimis.begin(); iter != detrimis.end(); iter++){
		string x = (*iter).first;
		//int detrim = atoi((*iter).first.c_str());
		string mesaj = (*iter).second;
		int size = mesaj.size();
		// daca este mesaj de broadcast trimitem la toate nodurile in
		// in corespondenta cu tabela de rutare
		if(x == "B"){
			int x = -1;
			for(i = 0; i < noTasks; i++){
				if(i != rank){
					int nexthop = tabelarutare[i];
					ostringstream convert;
					convert << i;
					string mf = convert.str() + " " +  mesaj;
					char * mms = new char[mf.size() + 1];
					strcpy(mms,mf.c_str());
					size = mf.size();
					MPI_Send(mms,size,MPI_CHAR,nexthop,tag2, MPI_COMM_WORLD);
				}
			}
		// daca nu este broadcast atunci trimitem doar acelui vecin
		}else{
			int detrim = atoi((*iter).first.c_str());
			int nexthop = tabelarutare[detrim];
			ostringstream convert;
			convert << detrim;
			string mf = convert.str() + " " +  mesaj;
			char * mms = new char[mf.size() + 1];
			strcpy(mms,mf.c_str());
			size = mf.size();
			MPI_Send(mms,size,MPI_CHAR,nexthop,tag2, MPI_COMM_WORLD);
		}
		
	}
	
	sleep(2);
	char bcast[10] = "bcast";
	// trimitem mesaje de broadcast pentru toate nodurile pentru a le informa ca am terminat de trimis
	for(i = 0; i < noTasks; i++){
		if(i != rank){
			int nexthop = tabelarutare[i];
			ostringstream convert;
			convert << i;
			string mf = convert.str() + " " + bcast;
			char * mms = new char[mf.size() + 1];
			strcpy(mms,mf.c_str());
			int size = mf.size();
			MPI_Send(mms,size,MPI_CHAR,nexthop,tag2, MPI_COMM_WORLD);
		}
	}
	// reverificam daca nodul este frunza
	if(vecini.size() == 1) 
		efrunza = 1;
	else efrunza = 0;
	
	
	ok = 1;
	char msj[50];
	int countbcast = 0;
	int countvecini = 0;
	// asteptam mesaje atat timp cat nu am primit toate mesajele de terminare si mesajele de terminare
	// ale copiilor pentru a asigura o rutare reusita
	while(ok){
		// asteptam mesaje
		MPI_Recv(msj,50,MPI_CHAR,MPI_ANY_SOURCE,tag2,MPI_COMM_WORLD,&status);
		int count = 50;
		char final[10] = "final";
		MPI_Get_count(&status,MPI_CHAR,&count);
		msj[count] = '\0';
		string msjs = msj;
		vector<string> vecstr = split(msjs); 
		int dest = atoi(vecstr.at(0).c_str());
		char* mesajstrip = new char[vecstr.at(1).size() + 1];
		strcpy(mesajstrip,vecstr.at(1).c_str());
		// daca este mesaj ed final (adica de la un copil ) sau de broadcast 
		if(strcmp(mesajstrip,bcast) == 0 || strcmp(mesajstrip,final) == 0){
			/*if(strcmp(mesajstrip,final) == 0){
				cout<<mesajstrip<<" "<<rank<<" bcast:"<<countbcast<<endl;
			}*/
			if(dest == rank){
				countbcast++;
				//cout<<"bcast"<<rank<<"  "<<countbcast<<endl;
				// daca e frunza si am primit mesaje de bcast de la vecini anunt parintele 
				// ca am terminat de primit 
				if(efrunza){
					if(countbcast >= (noTasks -1) ) {
						ok = 0;
						ostringstream stream;
						stream << parinte;
						string f = final;
						string mp = stream.str() + " " + f;
						char* mpa = new char[mp.size() + 1];
						strcpy(mpa,mp.c_str());
						MPI_Send(mpa,mp.size(),MPI_CHAR,parinte,tag2, MPI_COMM_WORLD);
					}
				// daca nu e frunza iar numaram vecinii de la care am primit 
				// mesaj de final iar daca am primit toate mesajele se termina		
				}else{
					if(countbcast >= (noTasks - 1) && (strcmp(mesajstrip,final) == 0) ){
						countvecini++;
						if(rank != 0){
							if(countvecini == vecini.size() - 1){
								ok = 0;
								ostringstream stream;
								stream << parinte;
								string f = final;
								string mp = stream.str() + " " + f;
								char* mpa = new char[mp.size() + 1];
								strcpy(mpa,mp.c_str());
								MPI_Send(mpa,mp.size(),MPI_CHAR,parinte,tag2, MPI_COMM_WORLD);
							
							}
						}else{
						// rankul 0 nu are parinte deci el trebuie sa primeasca doar de la vecini
							if(countvecini == vecini.size() ){
								ok = 0;
								cout<<"AM TERMINAT FAZA 2 "<<rank<<endl;
								}
						}
						
					}
				}
			}else{
				int next = tabelarutare[dest];
				int sz = msjs.size();
				MPI_Send(msj,sz,MPI_CHAR,next,tag2, MPI_COMM_WORLD);
			}
		}else{
			// mesaj normal iar prim1 este destinatia;
			// trebuie sa trimit mai departe mesajul sau daca sunt eu destinatia afisez
			if(dest == rank){
				cout<<"Sunt "<<rank<<" si mesajul  "<<msj<<" a ajuns la destinatie "<<endl;
			}else{
				cout<<"Sunt "<<rank<<"si am primit de la "<<status.MPI_SOURCE<<" mesajul : "<<msj<<endl;
				int next = tabelarutare[dest];
				int sz = msjs.size();
				MPI_Send(msj,sz,MPI_CHAR,next,tag2, MPI_COMM_WORLD);
			}
			
			
		}
	}
	
	/*
	// FAZA 3 alegerea liderului 
	// rank ul 0 se ocupa de numararea voturilor 
	if(rank == 0){
		vector<int> voturis;
		vector<int> voturia;
		for(i = 0; i < noTasks - 1; i++){
			voturis.push_back(0);
			voturia.push_back(0);
		}
		int vot[2];
		int tag3 = 4;
		for(i = 1; i < noTasks; i++){
			MPI_Recv(vot,2,MPI_INT,i,tag3,MPI_COMM_WORLD,&status);
			voturis[vot[0]] ++;
			voturia[vot[1]] ++;
		}
		
		for(i = 0; i < noTasks -1; i++){
			
		} 
	}else{
		
	
	}
	
	*/
	
	
	
	
	
	
	MPI_Finalize();
	

	
	return 0;
}
