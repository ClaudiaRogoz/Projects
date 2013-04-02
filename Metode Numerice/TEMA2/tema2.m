function    tema2( file_in,d,eps )
% apelam functiile algebraic si iterative si retinem in vectorii PRa si PRi
% rezultatele functiilor 
PRa=Algebraic(file_in,d);
PRi=Iterative(file_in,d,eps);
% formam fisierul de iesire file_in.out
% citim din fisier  
file_out=strcat(file_in,'.out');
g=fopen(file_in,'r');
nrn=fscanf(g,'%i',1);
A=zeros(nrn,nrn);
for i=1:nrn
pr=fscanf(g,'%i',1);
nrs=fscanf(g,'%i',1);
for j=1:nrs
n=fscanf(g,'%i',1);
if n~=i
A(i,n)=1;
end
end
end
val1=fscanf(g,'%f',1);
val2=fscanf(g,'%f',1);
% punem conditia ca functia f sa fie continua pentru capetele intervalelor
% val1 si val2 si calcul a si b
a=1/(val2-val1);
b=(-1)*val1/(val2-val1);
fclose(g);

% deschide fisierul de iesire si scriem rezultatele : numarul de nodori si
% rezultatele celor 2 functii algebraic si iterative 
f=fopen(file_out,'w');
fprintf(f,'%i\n',nrn);
fprintf(f,'%f\n',PRi);
fprintf(f,'\n');
fprintf(f,'%f\n',PRa);
fprintf(f,'\n');
% vom sorta descrescator vecotul Pra folosind sortarea prin interschimbare 
PRa1=PRa;
% obtinem un vector cu numere consecutive de la 1 la nrn care reprezinta
% indicii nodurilor 
for i=1:nrn
    in(i)=i;
end
% parcurgem vectorul PRa1 si comparam elementele cele care nu respecta
% ordinea vor fi intreschimbate la fel si indicii lor pt ca fiecare
% element sa isi pastreze indicele initial 
for i=1:nrn
    for j=i+1:nrn
        if PRa1(i)<PRa1(j)
            aux=PRa1(i);
            PRa1(i)=PRa1(j);
            PRa1(j)=aux;
            
            aux=in(i);
            in(i)=in(j);
            in(j)=aux;
            
            
        end
    end
end
% aplicam functia f vectorului PRa1 si afisam in fisierul de iesire 
for i=1:nrn
    if PRa1(i)>=0&&PRa1(i)<val1
        fx=0;
    fprintf(f,'%i %i %f',i,in(i),fx);
    fprintf(f,'\n');
    else
        if PRa1(i)>=val1&&PRa(i)<=val2
            fx=a*PRa1(i)+b;
            fprintf(f,'%i %i %f',i,in(i),fx);
            fprintf(f,'\n');
        else 
            fx=1;
            fprintf(f,'%i %i %f',i,in(i),fx);
            fprintf(f,'\n');
        end
    end
    
end
fclose(f);
end
