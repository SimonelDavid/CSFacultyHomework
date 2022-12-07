function X=smtv2(x,p)
  r=rand;
  suma=0;
  for i=1: length(p)
    if suma<r && r<suma+p(i)
      X=x(i);
      break;
    endif
    suma=suma+p(i);
  endfor
