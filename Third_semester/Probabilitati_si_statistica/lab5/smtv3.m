function X=smtv3(ns,x,p)
  for j=1: ns
    r=rand;
    suma=0;
    for i=1: length(p)
      if suma<r && r<suma+p(i)
        X(j)=x(i);
        break;
      endif
      suma=suma+p(i);
    endfor
  endfor


 clf; grid on; hold on;
 N=hist(X,x); %hist numara cate valori de x(i) am in X
 bar(x,N/ns,'hist','FaceColor','b'); %pentru valorile x, deseneaza deasupra fiecarui x o bara cu cate repetitii am rap la nr de sim


 endfunction
