function fr=birthday(NS=1000, n=27)
  contor = 0;
  for i=1:NS
    v = randi(365,1,n);
    v = sort(v);
    x = length(i);
    y = length(i)-1;
    if x != y
      contor++;
    endif
  endfor
  printf(" %d ", v);
  fr = contor/NS;

