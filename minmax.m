function [minx,maxx] = minmax(x)
minx = min(x(isfinite(x)));
maxx = max(x(isfinite(x)));
if minx == maxx
  minx = maxx-1;
  maxx = maxx+1;
end
end