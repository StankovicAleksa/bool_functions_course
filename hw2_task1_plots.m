
n=100
y=zeros(1,n)
x = linspace(-1,1,100)
plot(x,1/pi*(asin(1/pi*asin(x))))
title('Stab_{\rho}[Maj_n^{\otimes 2}]')
xlabel('\rho')
figure()
f = @(y) 1/2*(y-y.^3)
plot(x,f(f(f(x))))
xlabel('\rho')
title('Stab_{\rho}[Maj_3^{\otimes 3}]')
