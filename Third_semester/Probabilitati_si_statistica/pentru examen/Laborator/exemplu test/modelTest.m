function modelTest
      x = normrnd(100,20,1,1000);
      minim = min(x);
      maxim = max(x);
      fav = 0;
      for step = 1:1000;
          if x(step) < 140 && x(step )> 80;
            fav = fav + 1;
          endif
      endfor
      p = fav/1000

      [_,XX] = hist(x,13);
      hist(x,XX,13/(maxim-minim+1))

      i = 0.1;
      hold on
      for  j = minim:i:maxim;
          y = normpdf(j,100,20);
          plot(j,y,'r')
       endfor
end
