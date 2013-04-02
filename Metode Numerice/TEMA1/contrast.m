function   contrast( file_in,a,b)
    f=fopen(file_in,'r'); %deschiderea fisierului din care vom prelua matricea imaginii
    tip=fgets(f); % citim prima linie P2 in cazul nostru care semnifica tipul fisierului
    c=fgets(f); % a doua linie este un comentariu 
    w=fscanf(f,'%i',1); % nr de coloane 
    h=fscanf(f,'%i',1); % nr de linii
    pmax=fscanf(f,'%i',1); % valoarea pixelului maxim
    mx=fscanf(f,'%i'); % matricea 
    mx=mx(:); % liniarizam matricea 
    mmin=min(mx); % aflam valoarea minima
    mmax=max(mx); % valoarea maxima
    mx(1:w*h)=(b-a)*(mx(1:w*h)-mmin)/(mmax-mmin)+a; % aplicam formula pt contrast 
    fclose(f); % inchidem fisierul de intrare 
    g=fopen('out_contrast.pgm','w'); % deschidem fisierul de iesire
    fprintf(g,'%s',tip); % afisam in fisierul de iesire tipul fisierului
    fprintf(g,'%i %i\n%i\n',w,h,pmax); % afisam nr de coloane si linii respectiv valoarea pixelului maxim 
    fprintf(g,'%d\n',mx); % afisam matricea 
    fclose(g); % inchidem fisierul de iesire
end


