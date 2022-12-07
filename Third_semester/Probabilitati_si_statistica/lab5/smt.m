function X=smt(x,p)
  r=rand
  if r<p(1)
    X=x(1);
  else
    X=x(2);
  endif

