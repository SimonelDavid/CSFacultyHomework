function A=aranj(v, k)
  A=[];
  combs = nchoosek(v,k);
  cc = length(combs);
  for step=1:cc
    linie = combs(step,:)
    permutari = perms(linie);
    A=[A;permutari];
  endfor

