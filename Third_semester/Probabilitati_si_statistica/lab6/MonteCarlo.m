function int_val=MonteCarlo(g,a,b,M,nr_sim)
  x=unifrnd(a,b,1,nr_sim);
  y=unifrnd(0,M,1,nr_sim);

  clf;hold on;
  %rectangle('Position',[a,0,b-a,M],'FaceColor','k')
  plot(x(y<g(x)),y(y<g(x)),'hr')
  fplot(g,[a,b])

  int_val=mean(y<g(x))*(b-a)*M;
endfunction
