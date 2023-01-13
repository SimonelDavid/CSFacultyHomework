function X=ex1_lab6(m,p)

  n=100;

  %normrnd(m, sigma, nr_lin, nr_col)
  x = normrnd(m, p, 1, 1000);

  %histograma cu 10 bare
  [frecv_abs, mid_points] = hist(x, 10);

  %NORM = suma inaltimilor barelor
  clf; hold on;
  hist(x, mid_points, 10/(max(x) - min (x)))

  f = @(t) normpdf(t, 165, 10)
  fplot(f, [min(x), max(x)], 'LineWidth', 2)
  axis([135, 195, 0, 0.05]);

  mean(x) %media din vectorul de inaltimi
  std(x) %valoarea standard

  mean(160<x & x<170)
  normcdf(170,m,p)-normcdf(160,m,p)

  %pentru test sa desenam histograme, sa stim normcdf, normrnd, normpdf

endfunction
