ptn = 20
x = 0
y = 10

function y = sigm(x)
  p0 = 10;
  K = 1000;
  y = (K.*p0)./(((K-p0).*exp(-1.41.*x)) + p0);
endfunction

function z = difeq(y)
  r0 = 1.41;
  K = 1000;
  z = r0.*(1-(y./K)).*y;
endfunction

y = zeros(1,ptn, "double")
f = zeros(1,ptn, "double")
x = linspace(0,10,ptn)

y(1) = 10
for i=1:ptn
  if (i == 1)
    f(i) = difeq(y(i));
  else
    y(i) = y(i-1) + (0.5.*f(i-1));
##    f(i) = difeq(y(i));
    for j=1:1
      f(i) = difeq(y(i))
      y(i) = y(i-1) + ((0.5/2).*(f(i-1) + f(i)))
      f(i) = difeq(y(i))
    endfor
  endif
endfor
z = sigm(x)

w = z-y
[hax,h1,h2] = plotyy (x,y,x,z);
plot(x,w);


