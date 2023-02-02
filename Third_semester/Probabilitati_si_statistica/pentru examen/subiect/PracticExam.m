function t=PracticExam(N=1000)
  PA = 0;
  PB = 0;
  urn='aaaaaaaannnn';
  for i=1:N
    bile=randsample(urn, 4, replacement=false);

    #pct A
    a = 0;
    for j=1:length(bile)

      if bile(j) == 'a'
        a = a + 1;
      endif
      if a >= 3
        PA++;
      endif
    endfor

    #pct B
    a = 0;
    for j=1:length(bile)

      if bile(j) == 'n'
        a = a + 1;
      endif
      if a == 2 || a == 3
        PB++;
      endif
    endfor
  endfor

  PA
  rez_PA = PA / N
  PB
  rez_PB = PB / N
