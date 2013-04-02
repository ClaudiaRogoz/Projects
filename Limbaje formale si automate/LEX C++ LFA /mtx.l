%{

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <iterator>

using namespace std;

struct Node{
	std::string action;
	std::map<std::string,Node*> vecini;
};

std::map<std::string,Node*> masini;

string orice = "orice";
string *text;
vector<string> split(string const &input){

	istringstream buffer(input);
	vector<string> ret;
	
	copy(istream_iterator<string>(buffer),istream_iterator<string>(),back_inserter(ret));
	
	return ret;
	
}
// functie ajutatoare care afiseaza recursiv toate nodurile din arbore
void afisnoduri(Node* n){
	cout<<"&"<<n->action<<"&"<<endl;
	if(n->vecini.size() != 0){
		map<string,Node*>::iterator it;
		for(it = n->vecini.begin(); it!= n->vecini.end(); it++)
		{	
			//cout<<"   parintele meu este :"<<n->action<<"si eu pe tranzitia "<<(*it).first<<" caca "<<(*it).second->action<<endl;
			afisnoduri((*it).second);
		}
	}else {
		return;
	}
}
// curent loop stiva care imi spune in ce loop ma aflu
vector<string> curentloop;

void aplicamasina(string masina,Node * n){
	
		//cout<<n->action<<"  "<<n->vecini.size()<<"  "<<*text<<endl;
		
		if(n->action != masina){
			
			string act = n->action;
			
			// merge la dreapta
			if(act == "R"){
				size_t found;
				
				found = (*text).find(">");
			
				if(found != string::npos){
					(*text).erase(found,1);
				}
				if(found == text->size() - 1){
					(*text) = (*text) + "#";
				}
				(*text).insert(found+1,">");
			} else 
			// merge la stanga
			if(act == "L"){
				size_t found;
				
				found = (*text).find(">");
				if(found != string::npos){
					(*text).erase(found,1);
				}
				if(found == 0){
					(*text) ="#"+(*text);
					found ++;
				}
				(*text).insert(found-1,">");
			} else
			// inlocuieste cu ceva din alfabet
			if(act.size() == 1){
				if(act!="R" && act != "L"){
					size_t found;
					found = text->find(">");
					if(found != string::npos){
						(*text).replace(found+1,1,act);
					}
				
				}
			} else 
			// dreapta pana la ceva din alfabet sau diferit de ceva din alfabet
			if(act.size() > 1 && act[0] == 'R'){
				size_t found;
				int p1 = act.find("(");
				int p2 = act.find(")");
				string s;
				
				s = act.substr(p1+1,p2-p1-1);
				if(s[0] != '!'){
					found = text->find(">");
					int pos = -1;
					if(s[0] == '#'){
						
						string subdie = text->substr(found+2);
						
						int ok = subdie.find("#");
						if(ok == -1){
							(*text) = (*text) + "#";
						}
					}
					if(found != string::npos){
						for(int i = found + 2; i < text->size(); i++){
							if((*text)[i] == s[0]){
								pos = i;
								break;
							}
						}
						if(pos != -1){
							text->erase(found,1);
							text->insert(pos-1,">");
						}
					}
				}else{
					found = text->find(">");
					int pos = -1;
					if(found == text->size() -2 && s[1] != '#'){
						(*text) = (*text) + "#";
					}
					if(found != string::npos){
						for(int i = found + 2; i < text->size(); i++){
							if((*text)[i] != s[1]){
								pos = i;
								break;
							}
						}
						if(pos != -1){
							text->erase(found,1);
							text->insert(pos-1,">");
						}
					}
				}
			}   else
			//stanga pana la ceva din alfabet
			if(act.size() > 1 && act[0] == 'L'){
				size_t found;
				int p1 = act.find("(");
				int p2 = act.find(")");
				string s;
				s = act.substr(p1+1,p2-p1-1);
				if(s[0] != '!'){
					found = text->find(">");
					int pos = -1;
				
					if(found == 0 && s[0] == '#'){
						(*text) ="#" + (*text) ;
						found++;
					}
					if(found != string::npos){
						for(int i = found - 1; i >= 0; i--){
							if((*text)[i] == s[0]){
								pos = i;
								break;
							}
						}
					
						if(pos != -1){
							text->erase(found,1);
							text->insert(pos,">");
						}
					}
				// stanga pana la ceva diferit 
				}else{
					found = text->find(">");
					int pos = -1;
				
					if(found == 0 && s[1] != '#'){
						(*text) ="#" + (*text) ;
						found++;
					}
					if(found != string::npos){
						for(int i = found - 1; i >= 0; i--){
							if((*text)[i] != s[1]){
								pos = i;
								break;
							}
						}
					
						if(pos != -1){
							text->erase(found,1);
							text->insert(pos,">");
						}
					}
				}
			} else 
			if(act.find("@") != -1){
				// inceput de loop
				
			}
			else if(act.find("&") != -1){
				// adaugam in stiva numele buclei + @ pentru a cauta la intoarcere inceputul buclei
				string s = act.substr(1);
				s += "@";
				curentloop.push_back(s);
				return;
			}else{
			// masini neelementare dar definite mai sus in fisierul de intrare 
				std::map<std::string,Node*>::iterator it = masini.find(n->action);
				if( it != masini.end()){
					aplicamasina(n->action,masini[n->action]);
				}
			}
		}
	
	
	
	if(n->vecini.size() != 0){
		int i = (*text).find(">");
		string subs = (*text).substr(i+1,1);
		// daca este tranzitie 
		if(n->action == "tranz"){
			int ok = 0;
			// getkeys 
			map<string,Node*>::iterator it;
			vector<string> keys;
			for(it = n->vecini.begin(); it != n->vecini.end(); it++){
				keys.push_back((*it).first);
			}
			//okkey tranzitia pe care trebuie sa merg
			string okkey;
			for(int i = 0; i < keys.size(); i++){
				string key = keys.at(i);
				//cout<<"cheie  "<<key<<endl;
				// daca se potriveste perfect este ok
				if(keys.at(i) == subs){
					ok = 1;okkey = key;
					break;
				// daca contine ! si nu contine acel string este ok
				}else if(key.find("!")!= string::npos && key.find(subs) == string::npos){
				//	cout<<"aicisea !"<<endl;
					ok = 1; okkey = key;break;
				// daca nu contine ! si daca este printre elementele specificate este ok
				}else if(key.find(subs) != string::npos && key.find("!") == string::npos){
				//	cout<<"aicisea"<<endl;
					ok = 1; okkey = key;break;
				}
			}
			// daca se poate face tranzitie ma duc in recursivitate pe ramura care contine cheia ok 
			if(ok == 1){
			//	cout<<"in tranz"<<n->vecini[okkey]->action<<endl;
				aplicamasina(masina,n->vecini[okkey]);
			}
			
		}
		else{
			map<string,Node*>::iterator it;
			for(it = n->vecini.begin(); it!= n->vecini.end(); it++)
				aplicamasina(masina,(*it).second);
		}
	}else {
		return;
	}
	// intoarcere din recursivitate daca am loop si daca ajung la loop atunci ma duc in recursivitate pe nodul loop@
	// pentru ca in modul acesta ma pot intoarce din nou la el, daca as fi facut pe urmatorul nod la intoarcere ar fi sarit peste loop@
	if(curentloop.size() != 0){
		string loopname = curentloop.back();
		if(loopname == n->action){
			//cout<<"amajuns"<<endl;
			curentloop.pop_back();
			aplicamasina(masina,n);
			
		}else
			return;
	}
	
	
}



	
%}

DIGIT	[0-9]
ID	[a-z][a-z0-9]*
SPACE	[ ]
SPACEO	[ ]*
MASINA	([A-Za-z]|[0-9]|[_])*
LOOP	([a-z]|[0-9]|[_])*
SFMAS	[;]{2}
APEL	([A-Za-z#@$*!<>]|[0-9]|[_()])*
TRAN	([A-Za-z#@$*!<>, ]|[0-9]|[_()])*
EXC 	[!]*
CURL1	[{]*
CURL2	[}]*
PARAID	([A-Za-z#@$*!<>, ]|[0-9]|[_()])*
%s alfabet1 alfabet2 comm newdecl turing exe tran decl

%%


	using namespace std;
	string id;
	char* value;
	
	vector<char> alfa;
	char alfabet[100];
	map<string,char> simple;
	map<string,string> complex;
	map<char*,char>::iterator it;
	Node* curent;
	vector<Node*> curente;
	string numecurent;
	Node* beforetrancurent;
	int nrtran = 0;
	string tranzitii = "tranz";
	string curenttran = orice;
	
 /* preluarea alfabetului */

^alphabet{SPACE}::{SPACE} { 
		BEGIN(alfabet1);
		}
		
<alfabet1>[a-z0-9@#$*]{SPACE} { 	alfa.push_back(yytext[0]);
			}

<alfabet1>;\n 


 /* stergerea comentariilor */
^(;)	{ BEGIN(comm); }

<comm>. 
<comm>\n { BEGIN(INITIAL);}


 /* declaratii */
^{ID}{SPACE}"="{SPACE} { 	BEGIN(newdecl); char *id1 = strdup(yytext); 

				int i = 0;
				char * copy = id1;
				while(*copy != ' '){
					i++;
					copy++;
				}
	
				id1[i] = '\0';
				id = id1;
				
			}

<newdecl>{SPACE}[;]"\n" { BEGIN(INITIAL);}

<newdecl>[^{] { 
				simple.insert(pair<string,char>(id,yytext[0])); 
				}

^{ID}{SPACEO}":="{SPACEO}	{	BEGIN(decl);
								string s = yytext;
								size_t spa = s.find_first_of(" ");
								id = s.substr(0,spa);
								
								}
<decl>[{]{SPACEO}{PARAID}{SPACEO}[}]	{ 
									      complex[id] = yytext;
										}


<decl>{SPACEO}[;]"\n"	{BEGIN(INITIAL);}


 /* masini */

^{MASINA}{SPACEO}::={SPACEO}	{  BEGIN(turing);
								string s = yytext;
								//cout<<s<<endl;
								vector<string> vec = split(s);
								numecurent = vec.at(0);
								Node* n = new Node;
								n->action = numecurent;
								map<string,Node*> v;
								n->vecini = v;
								//curent = n;
								curente.push_back(n);
								masini[numecurent] = n;
							}

<turing>{SPACEO};;"\n"	{ BEGIN(INITIAL);
			
			}	


<turing>{LOOP}"@"	{
						Node *n = curente.back();
						curente.pop_back();
						Node *n1 = new Node;
						n1->action = yytext;
						map<string,Node*> v;
						n1->vecini = v;
						n->vecini[curenttran] = n1;
						//curent = n1;
						curente.push_back(n1);
					}

<turing>"&"{LOOP}{SPACEO}	{
						Node *n = curente.back();
						curente.pop_back();
						Node *n1 = new Node;
						string s = yytext;
						string s1 = s.substr(0,s.size() -1);
						n1->action = s1;
						map<string,Node*> v;
						n1->vecini = v;
						n->vecini[curenttran] = n1;
						//curent = n1;
						curente.push_back(n1);
					}

<turing>{SPACEO}";""\n"		{	BEGIN(tran);
						curente.pop_back();
					}

<turing>"["	{ BEGIN(exe);}

<exe>{APEL}	{	
				string yy = yytext;
				string gasit;
				int p1 = yy.find("<");
				if(p1 != -1){
					string cautat = "";
					
					int p2 = yy.find(">");
					string idca = yy.substr(p1+1,p2-p1-1);
					map<string,char>::iterator it;
					map<string,string>::iterator itt;
					for(it = simple.begin(); it != simple.end(); it++){
						if((*it).first == idca){
							gasit = (*it).second;
						}
					}
					for(itt = complex.begin(); itt != complex.end(); itt++){
						if((*itt).first == idca){
							gasit = (*it).second;
						}
					}
					yy.replace(p1,p2-p1+1,gasit);
				
				}
				
				Node *n = curente.back();
				curente.pop_back();
				Node *n1 = new Node;
				n1->action = yy;
				map<string,Node*> v;
				n1->vecini = v;
				n->vecini[curenttran] = n1;
				//curent = n1;
				curente.push_back(n1);
			}


<exe>"]"{SPACEO}	{  BEGIN(turing);}

<turing>[(]"\n"	{
					BEGIN(tran);
					nrtran ++;
					Node *n = curente.back();
					curente.pop_back();
					Node *n1 = new Node;
					//string s = tranzitii;
					//ostringstream convert;
					//convert << nrtran;
					n1->action = tranzitii /*+ convert.str() */;
					map<string,Node*> v;
					n1->vecini = v;
					n->vecini[curenttran] = n1;
					//curent = n1;
					curente.push_back(n1);
			}




<tran>{SPACEO}{EXC}{CURL1}{TRAN}{CURL2}{SPACEO}"->"{SPACEO}[[]{APEL}[]]{SPACEO}	{
										string s = yytext;
										size_t sag = s.find("->");
										string altu = s.substr(0,s.size() - sag);
										size_t p1 = s.find("{");
										size_t p2 = s.find("}");
										string s1,s2;
										s1 = s.substr(p1+1,p2-p1-1);
										
										if(altu.find("!")!= -1){
											s1 = "!" + s1;
										}
										
										
										p1 = s.find("["); p2 = s.find("]");
										s2 = s.substr(p1+1,p2-p1-1);
										Node *n = curente.back();
										Node *n1 = new Node;
										n1->action = s2;
										map<string,Node*> v; n1->vecini = v;
										curenttran = s1;
										n->vecini[curenttran] = n1;
										curente.push_back(n1);
										BEGIN(turing);
										
							}
						

<tran>[)]{SPACEO}{SFMAS}"\n"	{ 	
								BEGIN(INITIAL);
								nrtran--;				
							}
							
					
<tran>{SPACEO}[)]{SPACEO}[;]"\n"		{
						nrtran--;
						curente.pop_back();
					}

<tran>[\t]

^"\n" {}

%%




int main(int argc, char *argv[]){
	using namespace std;
	if(argc != 4){
		cout<<"Eroare folositi ./mtx fisinput masina sir"<<endl;
		exit(0);
	}
	
	char * fisinput = argv[1];
	char* masina = argv[2];
	char * sirintrare = argv[3];
	//cout<<fisinput<<" "<<masina<<" "<<sirintrare<<endl;
	
	yyin = fopen(fisinput,"r");
	yylex();
	string m = masina;
	string text1 = sirintrare;
	//aplicamasina(m,masini[m],&text);
	//cout<<"afisez asta:"<<endl;
	text = &text1;
	aplicamasina(m,masini[m]);
	//afisnoduri(masini[m]);
	/*int curs = text1.find(">");
	text1.erase(0,curs-1);
	
	text1+="#";
	*/
	// finisam sirul de iesire
	int inceput = text1.find_first_not_of("#");
	
	if(inceput == 0){
		text1 = "#" + text1;
	}
	else
	if(inceput - 1 != 0){
		text1.erase(0,inceput -1);
	}
	
	int last = text1.find_last_not_of("#");
	if(last == (text1.size() - 1)){
		text1 += "#";
	}else if(last < (text1.size() -1)) {
		int k = text1.size() - last;
		text1.erase(last+2,k);
	}
	cout<<text1<<endl;
	
}
