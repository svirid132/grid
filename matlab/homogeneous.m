p = [1 0.5 1 0.5];

hom2cart(p)

x = 0:100;
y = 0:100;
[X,Y] = meshgrid(x,y);
%Z = X + Y;
A = 1; 
B = 2;
C = -1;
D = -5;
Z = -(A*X + B*Y + D)/C;
plot3(X, Y, Z)
