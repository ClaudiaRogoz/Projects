function  filter(file_in,filter_type)
    f=fopen(file_in,'r'); %deschiderea fisierului de intrare 
        % citirea datelor din fisier 
    tip=fgets(f);
    c=fgets(f);
    w=fscanf(f,'%i',1);
    h=fscanf(f,'%i',1);
    pmax=fscanf(f,'%i',1);
    m=fscanf(f,'%i',[w h]);
        %crearea unei matrici cu zerouri ce va reprezenta matricea initiala bordata
        %cu zerouri 
    x=zeros(w+2,h+2);
    fclose(f);
        % crearea matricei  bordata
    x(2:w+1,2:h+1)=m(1:w,1:h);
    % aplicarea efectului smooth
    if strcmp(filter_type,'smooth')==1  % verificarea tipului filtrului
         % aplicarea formulei pt smooth
        m(1:w,1:h)=(x(1:w,1:h)+x(2:w+1,1:h)+x(3:w+2,1:h)+x(1:w,2:h+1)+x(2:w+1,2:h+1)+x(3:w+2,2:h+1)+x(1:w,3:h+2)+x(2:w+1,3:h+2)+x(3:w+2,3:h+2))/9;
         % afisarea noii matrici in fisierul out_smooth
        g=fopen('out_smooth.pgm','w');
        fprintf(g,'%s',tip);
        fprintf(g,'%i %i\n%i\n',w,h,pmax);
        fprintf(g,'%i\n',m);
        fclose(g);
    end
    % aplicarea efectului blur
    if strcmp(filter_type,'blur')==1   % verificarea tipului filtrului
             % aplicarea formulei pt blur
         m(1:w,1:h)=(x(1:w,1:h)+2*x(2:w+1,1:h)+x(3:w+2,1:h)+2*x(1:w,2:h+1)+4*x(2:w+1,2:h+1)+2*x(3:w+2,2:h+1)+x(1:w,3:h+2)+2*x(2:w+1,3:h+2)+x(3:w+2,3:h+2))/16;
             % afisarea noii matrici in fisierul out_blur
        g=fopen('out_blur.pgm','w');
        fprintf(g,'%s',tip);
        fprintf(g,'%i %i\n%i\n',w,h,pmax);
        fprintf(g,'%i\n',m);
        fclose(g);
    end
        % aplicarea efectului sharpen
    if strcmp(filter_type,'sharpen')==1 % verificarea tipului filtrului
         % aplicarea formulei pt sharpen
        m(1:w,1:h)=((-2)*x(2:w+1,1:h)+(-2)*x(1:w,2:h+1)+11*x(2:w+1,2:h+1)+(-2)*x(3:w+2,2:h+1)+(-2)*x(2:w+1,3:h+2))/3;
            % verificarea daca elementele obtinute in noua matrice sunt mai mici
            % decat 0 sau mai mari decat 255 in caz afirmativ se vor inlocui aceste
            % valori cu valoarea 0 respectiv 255
        m(m>255)=255;
        m(m<0)=0;
            % afisarea noii matrici in fisierul out_sharpen
        g=fopen('out_sharpen.pgm','w');
        fprintf(g,'%s',tip);
        fprintf(g,'%i %i\n%i\n',w,h,pmax);
        fprintf(g,'%i\n',m);
        fclose(g);
    end
        % aplicarea efectului emboss
    if strcmp(filter_type,'emboss')==1 % verificarea tipului filtrului
            % aplicarea formulei pt emboss
        m(1:w,1:h)=((-1)*x(1:w,1:h)+(-1)*x(3:w+2,1:h)+4*x(2:w+1,2:h+1)+(-1)*x(1:w,3:h+2)+(-1)*x(3:w+2,3:h+2))+127;
            % verificarea daca elementele obtinute in noua matrice sunt mai mici
            % decat 0 sau mai mari decat 255 in caz afirmativ se vor inlocui aceste
            % valori cu valoarea 0 respectiv 255
        m(m<0)=0;
        m(m>255)=255;
    
            % afisarea noii matrici in fisierul out_emboss
        g=fopen('out_emboss.pgm','w');
        fprintf(g,'%s',tip);
        fprintf(g,'%i %i\n%i\n',w,h,pmax);
        fprintf(g,'%i\n',m);
        fclose(g);
  
    end
    

end

