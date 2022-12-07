function [X,Y]=boxmuler(nr_sim)
  u1 = rand(1,nr_sim);
  u2 = rand(1,nr_sim);
  R = sqrt(-2*log(u1));
  V = 2*pi*u2;
  X = R.*cos(V);
  Y = R.*sin(V);

endfunction
