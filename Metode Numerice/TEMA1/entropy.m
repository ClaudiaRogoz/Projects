function entropy( file_in, a, b, c )

        %calculul entropiei 
        % citirea datelor de intrare din fisierul file_in
    f=fopen(file_in,'r');
    tip=fgets(f);
    co=fgets(f);
    w=fscanf(f,'%i',1);
    h=fscanf(f,'%i',1);
    pmax=fscanf(f,'%i',1);
    m=fscanf(f,'%i',[w h]);
        % initializarea cu zeroruri a unei matrici ce va reprezenta matricea
        % initiala bordata 
    x=zeros(w+2,h+2);
    fclose(f);
        %x matricea m bordata cu zerouri 
    x(2:w+1,2:h+1)=m(1:w,1:h); 
        % x1 este matricea m dupa trecerea prin predictor
    x1=zeros(w,h);
         % calculam valoarea matricei dupa trecerea prin predictor
    x1(1:w,1:h)=a*x(1:w,2:h+1)+b*x(1:w,1:h)+c*x(2:w+1,1:h);

    e=zeros(w,h);
        % dechiderea fisierului de iesire out_entropy.txt
    g=fopen('entropy.txt','w');
        % calcularea imaginii reziduale
    e(1:w,1:h)=m(1:w,1:h)-ceil(x1(1:w,1:h));

    unq=unique(e); % vector cu elementele din imaginea reziduala o singura data
    lunq=length(unq); % nr de elemente unice in imaginea reziduala
    en=0;
    m=m(:);
        % parcurgem elementele unice din imaginea reziduala
    for i=1:lunq 
            % si pentru fiecare element ii calculam nr de aparitii in imaginea
            % reziduala vlun vector in care se retin nr de aparitii
        vlun(i)=length(e(e==unq(i)));
        prob(i)=vlun(i)/(w*h); % calcularea probabilitatii
            % aplicarea formulei pt calculul entropiei;
        en=en+(-1)*(prob(i)*log2(prob(i)));
    end
    fprintf(g,'%f\n',en);
    fclose(g);
end