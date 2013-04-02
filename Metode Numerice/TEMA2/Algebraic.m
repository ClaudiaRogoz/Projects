function pr=Algebraic( file_in,d )
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
K=zeros(nrn,nrn);
l=zeros(nrn,1);
% l este un vector in care se memoreaza nr de noduri adiacente pt nodul i
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
% I matricea unitate 
I=eye(nrn);

M=(K*A)';
% pt aflare lui R dupa formula R=inv((I-d*M))(1-d)/nrn*u notam B=I-d*M; si
% calculam inv(b) cu algoritmul Gram-Schmidt 
B=I-d*M;



% algoritmul qr gs
Q = B;
	R = zeros( nrn, nrn );
	for k = 1 : nrn
        % matricea R va avea pe diag principala norma elementelor de pe coloana k din Q 
            R( k, k ) = norm( Q( 1 : nrn, k ) );
            % modificam elementele de pe coloana k cu cat erau inainte/
            % norma adica R(k,k);
            Q( 1 : nrn, k ) = Q( 1 : nrn, k ) / R( k, k );
	   for j = k + 1 : nrn
           % elementul R(k,j) se modifica devenind produsul scalar dintre
           % coloana k si coloana j adica coloana k transpusa inmultita cu
           % coloana j rezultatul fiind un element
            R( k, j ) = Q( 1 : nrn, k )' * Q( 1 : nrn, j );
            % coloana j ia valoarea coloana j - proiectia coloanei j pe
            % coloana k supra norma colonei k adica Q( 1 : nrn, k ) * R( k, j )
            Q( 1 : nrn, j ) = Q(1 : nrn, j ) - Q( 1 : nrn, k ) * R( k, j );
       end
    end
%sfarsit qr gs
% B=Q*R inv(Q)=Q'si R este matrice superior tringhiulara B*inv(B)=I si
% dorim sa aflam pe inv(B) Q*R*inv(B)=I R*inv(b)=Q' care formeaza n sisteme
% de n ecuatii superior triunghiulare pe care le vom rezolva cu scopul
% aflarii lui inv(B) care va fi format din rezultatele fiecarui sistem de
% ecuatii 

% rezolvarea celor n sisteme de ecuatii
Lib=Q';
Bm=zeros(nrn);
for i=1:nrn
    x = zeros(nrn,1);
    x(nrn) = Lib(nrn,i)/R(nrn, nrn);
    for j = nrn-1:-1:1
        x(j)=(Lib(j,i)-R(j,j+1:nrn)*x(j+1:nrn))/R(j,j);
    end
    for k=1:nrn
    Bm(k,i)=x(k);
end
% Bm este inv(B) adica inv(I-d*M)
u=ones(nrn,1);

PR=Bm*(((1-d)/nrn)*u);

 
pr=PR;

end

