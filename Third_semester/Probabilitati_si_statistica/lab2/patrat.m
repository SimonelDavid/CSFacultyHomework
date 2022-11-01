function patrat(NS = 500)
  clf;
  hold on;
  axis equal;
  rectangle('Position', [0, 0, 1, 1]);
  plot(0.5, 0.5, '*r');
  x = rand;
  y = rand;
  P = [x, y];
  O = [0.5, 0.5];
  if pdist([P; O]) < 0.5
    plot(x, y, '*r')
  endif
