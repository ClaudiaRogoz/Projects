function test_grafic(eps)
x=linspace(-pi,pi,1001);
for j=1:1001
			fx(j)=exp(3*cos(x(j)))/(2*pi*besseli(0,3));
end
    subplot(1,2,1) , plot(x,fx,'r');
    hold on;
    
    [N,fa]=eval_interpolator_c(1,eps);
    if N~=inf
    plot(x,fa,'b');
	end
    hold on;
    
    [N,fa]=eval_interpolator_c(2,eps);
    if N~=inf
    plot(x,fa,'g');
    end
    hold on;
    [N,fa]=eval_interpolator_c(3,eps);
	if N~=inf
    plot(x,fa,'y');
	end
    hold on;
    [N,fa]=eval_interpolator_c(4,eps);
    if N~=inf
	plot(x,fa,'m');
    end
	hold on;
    [N,fa]=eval_interpolator_c(5,eps);
    if N~=inf
	plot(x,fa,'c');
    end
	hold on;
    [N,fa]=eval_interpolator_c(6,eps);
     if N~=inf
	plot(x,fa,'k');
     end
a=load('sunspot.dat');
subplot(1,2,2), plot(a(:,1),a(:,2),'r');
    hold on;
    [N,fa]=eval_interpolator_c(1,eps);
    if N~=inf
    plot(x,fa,'g');
    end
	   hold on;
    
    [N,fa]=eval_interpolator_c(2,eps);
    if N~=inf
    plot(x,fa,'m');
    hold on;
	end  
	
    
    [N,fa]=eval_interpolator_c(3,eps);
    if N~=inf
    plot(x,fa,'k');
    end
	   hold on;
    
    [N,fa]=eval_interpolator_c(4,eps);
    if N~=inf
    plot(x,fa,'c');
    end
	   hold on;
    
    [N,fa]=eval_interpolator_c(5,eps);
    if N~=inf
    plot(x,fa,'b');
    end
	   hold on;
    
    [N,fa]=eval_interpolator_c(6,eps);
    if N~=inf
    plot(x,fa,'y');
    end
end
    
    
    
    