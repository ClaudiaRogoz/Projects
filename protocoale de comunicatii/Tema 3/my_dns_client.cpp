#include "helpers.h"
#include "dns.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


char* qname(char* str){
	char * cstr, *p;
	cstr = (char*)malloc(strlen(str)+1);
	strcpy (cstr, str);
	char* rez =(char*)malloc(strlen(str)+3);
	// parsam domeniul in functie de . si calculam dimensiunea tokenului respectiv pe care 
	// o adaugam la inceputul secventei 
	
	p=strtok (cstr,".");
	while (p!=NULL)
	{
		
		char len = (char) (strlen(p));
		
		
		sprintf(rez + strlen(rez), "%c",strlen(p));
		strcat(rez,p);
		p=strtok(NULL,".");
		
	}
	int x = 0;
	sprintf(rez + strlen(rez), "%c",0);
	return rez;
}


void getname(unsigned char* buf1,unsigned char* init,int* count, unsigned char * rrname)
{
	
	*count = 1;
	rrname[0]='\0';
	printf("init ; %d", *(buf1+1));
	//numele de domeniu o sa fie compressed 
	//facem decompresie adica atunci cand gasim un caracter >= 192 (11000000) atunci se face salt la o alta locatie de memorie
	// care pointeaza la restul numelui iar apoi gasim noua locatie de memorie care este reprezentat de diferenta dintre 
	// cei 2 octeti curenti si 49152 = 11000000 00000000 
	int ok = 0;
	int salt = 0;
	int nr = 0;
	while(*buf1!=0)
	{	
		if(*buf1>=192)
		{
		
			// sarim la locatia respectiva de memorie reprezentata de urmatorii octeti
			// dupa primii 11
			buf1 = init + (*buf1)*256 + *(buf1+1) - 49152 - 1;
			ok = 1; 
		
		}
		else
		{
			rrname[nr++]=*buf1;
		}
		
		buf1 = buf1+1;
		
		if(ok==0)
		{
			*count = *count + 1;
		}
	}
	
	rrname[nr]='\0'; 
	
	if(ok==1)
	{
		*count = *count + 1;
	}
	
	
}

char* convert(unsigned char *domain){
	int i,j; 
	int  x = strlen((char*)domain);
	unsigned char * newname = (unsigned char*) malloc(strlen((char*)domain));
	
	int k = 0;
	for(i = 0; i < strlen((char*)domain); i++){
		int nr = domain[i];
		
		for(j = 0 ; j < nr; j++){
			i++;
			newname[k] = domain[i];
			k++;
			printf("%i\n",j);
		}
		
		newname[k++] = '.';
	}
	return (char*)newname;	
}

int main(int argc, char *argv[])
{

    	char buffer[BUFLEN];
   	 
   	 if (argc != 3) {
   	    fprintf(stderr,"Usage %s domain name/ip address type\n", argv[0]);
	    exit(0);
   	 }
   	 int type;
   	 if(strcmp(argv[2],"MX")==0){
	   	 type = MX;
	 }
   	 else if(strcmp(argv[2],"A")==0){
	   	 type = A;
	 }	 
	 else if(strcmp(argv[2],"CNAME")==0){
	   	 type = CNAME;
	 }
	 else if(strcmp(argv[2],"NS")==0){
	   	 type = NS;
	 }
	 else if(strcmp(argv[2],"PTR")==0){
	   	 type = A;
	 }else{
		 fprintf(stderr,"bad command\n");
		 exit(0);
	 }
	 
	struct sockaddr_in to_station;
	char buf[BUFLEN];
    	
    	// deschidere socket 
    	int s = socket(AF_INET,SOCK_DGRAM,0);
	if(s== -1){
		fprintf(stderr, "Socket open failed");
		exit(0);
	}
	
    	// cautare server dns pentru conectare 
    	FILE * f = fopen("dns_servers.conf","r");
    	         

         if( f == NULL )
         {
               puts ( "cannot open dns conf file" );
               exit(0);
         }
     
         while(1){
         
        	if(fgets(buffer,sizeof(buffer),f) != NULL){
        	    
        		if(buffer[0] == '#'){
        			printf("comentariu\n %s ",buffer);
        			continue;
        		}else{
        			printf("nu este comentariu\n %s ",buffer);
        			
        		}
        	}else{
        		
        		break;
        	}
        	
        	
        	// ne conectam la primul server dns din resolv.conf
		// iar daca nu ne satisface cererea trecem la urmatorul
        	to_station.sin_family = AF_INET;
		to_station.sin_port = htons(53);
		to_station.sin_addr.s_addr = inet_addr(buffer);

		int ok = 0;
		
		// formam mesajul pentru sento care trebuie sa contine header si question 
		// facem 2 buffere care o sa pointeze catre structurile noastre de date 
		// modificam structurile header si question si concatenam la final cele 2 buffere
		char* domain = argv[1];
		
		// adaugam q name in buffer 
		char* q = qname(domain);	
		unsigned char tosendheader[65536];	
		
		
		dns_header_t* mesajx = (dns_header_t*) &tosendheader;
		
		mesajx->id = htons(1002);
		mesajx->rd = 1;
		mesajx->tc = 0;
		mesajx->aa = 0;
		mesajx->opcode = 0;
		
		mesajx->qr = 0;
		mesajx->rcode = 0; 
		mesajx->z = 0;
		mesajx->ra = 0;
		mesajx->qdcount = htons(1);
		mesajx->ancount = 0;
		mesajx->nscount = 0;
		mesajx->arcount = 0;
		memcpy(tosendheader + sizeof(dns_header_t),q,strlen(q));
		dns_question_t* mesaj1 = (dns_question_t*)&tosendheader[sizeof(dns_header_t) + strlen(q) + 1];
		
		mesaj1->qtype = htons(type);
		
		switch(type){
			case MX :
			{
			printf("MX\n");
			
			ok = 1;
			break;
			}
			case A:
			{
			printf("A\n");
			
			ok = 1;
			break;
			}
			case NS:
			{
			printf("NS\n");
			
			ok = 1;
			break;
			}
			case PTR:
			{
			printf("PTR\n");
			ok = 1;
			break;
			}
			case CNAME:
			{
			printf("CNAME\n");
			ok = 1;
			break;
			}
			

		}
		
		mesaj1->qclass = htons(IN);

		
		int sent = sendto(s , tosendheader , sizeof(dns_header_t) + sizeof(dns_question_t) + strlen(q) + 1 , 0 ,(struct sockaddr*) &to_station , sizeof(struct sockaddr));
		
		int len_quest = sizeof(dns_question_t) + strlen(q) + 1;
		
		if(sent < 0 ){
			fprintf(stderr,"failed");
			exit(0);
		}else{
			printf("am trimis : %i\n",sent);
		}
		
		
		int i ;
		FILE* l = fopen("logfile","at");
		fprintf(l,"\n; Trying: %s %s\n",argv[1],argv[2]);
		
		int n =  sizeof(dns_header_t) + strlen(q) + sizeof(dns_question_t) + 1;
		
		int size =  sizeof(struct sockaddr);
		unsigned char answer[65536];
		int lung=recvfrom(s, answer,65536, 0, (struct sockaddr*) &to_station, (socklen_t*)(&size));
		
		
		printf("Received : %i \n",lung);
		
		dns_header_t* head = (dns_header_t*) answer;
		printf("Answers : %i \n",ntohs(head->ancount));
		printf("Questions : %i \n",ntohs(head->qdcount));
		printf("NS : %i \n",ntohs(head->nscount));
		printf("AR : %i \n",ntohs(head->arcount));
		unsigned char* ansbuf = answer + n;
		int salt = 0;
		
	//afisare toate raspunsurile 
		// extragere name din buffer primii octeti dupa answer,question,qname
		for(i = 0 ; i < 1 /*ntohs(head->ancount)*/; i++){
			unsigned char * namerr = (unsigned char*) malloc(256);
			getname(ansbuf,answer,&salt,namerr);
			printf("%i",strlen((char*)namerr));
		
			char* domainrr = convert(namerr);
			printf("Name : %s ",domainrr);
			// continuam sa prelucram bufferul ansbuf 
			fprintf(f,"%s\t",domainrr); 
			ansbuf = ansbuf + salt;
			dns_rr_t* rec = (dns_rr_t*) ansbuf;
			printf("type %d\n",ntohs(rec->type));
			
			
		}
		
		
		
		
		
		
		
		if(ok == 1) {
			break;
		}
		
		}
		
		fclose(f);

}


