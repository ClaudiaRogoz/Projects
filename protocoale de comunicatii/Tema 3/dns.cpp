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
		
		char* tosendheader = (char*)malloc(sizeof(dns_header_t));
		dns_header_t* mesajx = (dns_header_t*)tosendheader;
		
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
		mesajx->ancount = htons(0);
		mesajx->nscount = htons(0);
		mesajx->arcount = htons(0);
		
		
		char* domain = argv[1];
		
		// adaugam q name in buffer 
		char* q = qname(domain);
		
		char* tosendquestion = (char*)malloc(sizeof(dns_question_t) + strlen(q));
		
		tosendquestion = (char*) memcpy(tosendquestion,q,strlen(q));
		
		printf("buffer length aici  %i\n ", strlen(tosendquestion));
		
		printf("q: %s \n",q);
		dns_question_t *mesaj1 = (dns_question_t*)(tosendquestion +(strlen(tosendquestion))) ;
		switch(type){
			case MX :
			{
			printf("MX\n");
			mesaj1->qtype = htons(MX);
			ok = 1;
			break;
			}
			case A:
			{
			printf("A\n");
			mesaj1->qtype =htons(A);
			ok = 1;
			break;
			}
			case NS:
			{
			printf("NS\n");
			mesaj1->qtype = htons(NS);
			ok = 1;
			break;
			}
			case PTR:
			{
			printf("PTR\n");
			mesaj1->qtype = htons(PTR);
			ok = 1;
			break;
			}
			case CNAME:
			{
			printf("CNAME\n");
			mesaj1->qtype = htons(CNAME);
			ok = 1;
			break;
			}
			

		}
		printf("buffer length %i ", strlen(tosendquestion));
		
		mesaj1->qclass = htons(IN);
		printf("buffer length %i ", strlen(tosendquestion));
		
		if(ok == 1){
			printf("SUCCES\n");
		}else{
			fprintf(stderr,"Bad Input");
		}
		
		char* tosend = (char*) malloc(strlen(tosendheader) + strlen(tosendquestion) + 1);
		printf("tosend header %i\n" ,strlen(tosendheader));
		strcpy(tosend,tosendheader);
		printf("tosend question %i\n" ,strlen(tosendquestion));
		
		strcat(tosend,tosendquestion);
		printf("header %i\n question %i\n tot %i\n",strlen(tosendheader),strlen(tosendquestion), strlen(tosend));
		int sent = sendto(s , tosend , strlen(tosend) , 0 ,(struct sockaddr*) &to_station , sizeof(struct sockaddr));
		printf("sent %i\n buffer %s    %i \n" , sent,tosend,strlen(tosend));
		char* buffer;
		int x ;
		int lung = 0;
		char buf[65000];
		int size =  sizeof(struct sockaddr);
		
	lung=recvfrom(s, buf ,65000, 0, (struct sockaddr*) &to_station, (socklen_t*)(&size));
	printf("=================");
	if(lung > 0)
	{
	printf("%s\n",buf);
	printf("%i\n",lung);
	}else{
		fprintf(stderr,"failed");
		exit(0);
	}
	
		if(ok == 1){
			printf("Succes \n");
			exit(0);
		}
		
		
         }
        
    	
	
    return 0;
}
