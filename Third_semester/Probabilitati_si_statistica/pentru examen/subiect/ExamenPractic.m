function PA=ExamenPractic(N,c)
  PA=0
  urn=['a','a','a','a','a','a','a','a','n','n','n','n']
  for rep=1:N
    balls=randsample(urn,12);
    if c=='a'
    for x=1:12
      if balls(x)=='a' && x>2
          PA++;
      end
    end

end
PA=PA/N
