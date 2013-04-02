function pr=Iterative(file_in,d,eps)
%deschidem fisierul de intrare si citim numarul de noduri si formam
%matricea de adiacenta 
f=fopen(file_in,'r');
nrn=fscanf(f,'%i',1);
% construim matricea de adiacenta 
A=zeros(nrn,nrn);
for i=1:nrn
pr=fscanf(f,'%i',1);
nrs=fscanf(f,'%i',1);
for j=1:nrs
n=fscanf(f,'%i',1);
if n~=i
A(i,n)=1;
end
end
end
% PR reprezinta matrice page rank initializata cu 1/(numarul total de
% pagini / noduri)
PR=zeros(nrn,1);
PR(1:nrn)=1/nrn;

K=zeros(nrn,nrn);
% l este un vector in care se memoreaza nr de noduri adiacente pt nodul i
l=zeros(nrn,1);

for i=1:nrn
    for j=1:nrn
        l(i)=l(i)+A(i,j);
    end
end
% calculam matricea inv(K) care  are pe diag principala 1/ nr de noduri adiacente
% pentru nodul i 
    for i=1:nrn
        K(i,i)=1/l(i);
    end
% calculam matricea M
M=(K*A)';
% u vectorul unitate
u=ones(nrn,1);
% PR1 este vectorul PR la pasul k-1 
PR1=PR;
% initializam pe PR conform formulei 
PR=d*M*PR1+(1-d)/nrn*u;
% cat timp abs(PR1-PR)<=eps returneaza un vector cu 1 unde se respecta
% conditia si cu 0 unde nu se respecta suma tuturor elementelor trebuie sa
% fie egal cu nr de noduri adica 1 
while sum(abs(PR1-PR)<=eps)~=nrn
    PR1=PR;
    PR=d*M*PR1+(1-d)/nrn*u;
    
end
   pr=PR;
end