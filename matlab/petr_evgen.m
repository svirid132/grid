pW = 1920 / 2;%Половина ширины экрана
pH = 1080 / 2;%Половина высоты экран

dy = pi / 180;%угол В радианах
%dx = pi / 180 * 90;%угол в радианах
dx = 0.2;
m = [cos(dy) -sin(dy)*sin(dx) sin(dy)*cos(dx); 
    0 cos(dx) sin(dx);
    -sin(dy) -cos(dy)*sin(dx) cos(dy)*sin(dx)];

v1 = m * [-1; 1; 0;];
v2 = m * [1; 1; 0;];
v3 = m * [-1; -1; 0;];
v4 = m * [1; -1; 0;];

line([v1(1, 1) + pW, v2(1, 1) + pW], [v1(2, 1) + pH, (v2(2, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v2(1, 1) + pW, v4(1, 1) + pW], [v2(2, 1) + pH, (v4(2, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v4(1, 1) + pW, v3(1, 1) + pW], [v4(2, 1) + pH, (v3(2, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v3(1, 1) + pW, v1(1, 1) + pW], [v3(2, 1) + pH, (v1(2, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)

