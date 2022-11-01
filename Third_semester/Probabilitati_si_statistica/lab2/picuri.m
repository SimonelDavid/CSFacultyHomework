function picuri(NS)
  clf;
  hold on;
  axis equal;
  rectangle('Position', [0, 0, 1, 1]);
  counter = 0;
  for(step =  1 : NS)
    x = rand;
    y = rand;
    P = [x, y];
    O = [0.5, 0.5];
    if pdist([P; O]) < 0.5
      counter++;
      plot(x, y, '*r');
    endif
  end

 counter / NS * 4
