pW = 1920 / 2;%Половина ширины экрана
pH = 1080 / 2;%Половина высоты экран

dy = 0;
dx = 0.8;
zc = 3;

m = [cos(dy) sin(dy)*sin(dx) 0 sin(dy)*cos(dx)/zc; 
    0 cos(dx) 0 -sin(dx)/zc;
    sin(dy) -cos(dy)*sin(dx)  0 -cos(dy)*cos(dx)/zc;
    0 0 0 1;];

v1 = m * [-1; 1; 0; 1;];
v2 = m * [1; 1; 0; 1;];
v3 = m * [-1; -1; 0; 1;];
v4 = m * [1; -1; 0; 1;];
v5 = m * [-1; 0; 0; 1;];%Линия по середине
v6 = m * [1; 0; 0; 1;];%Линия по середине
v7 = m * [0; 1; 0; 1;];
v8 = m * [0; -1; 0; 1;];

line([v1(1, 1) / v1(4, 1) + pW, v2(1, 1) / v2(4, 1) + pW], [v1(2, 1) / v1(4, 1) + pH, (v2(2, 1) / v2(4, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v2(1, 1) / v2(4, 1) + pW, v4(1, 1) / v4(4, 1) + pW], [v2(2, 1) / v2(4, 1) + pH, (v4(2, 1) / v4(4, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v4(1, 1) / v4(4, 1) + pW, v3(1, 1) / v3(4, 1) + pW], [v4(2, 1) / v4(4, 1) + pH, (v3(2, 1) / v3(4, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v3(1, 1) / v3(4, 1)+ pW, v1(1, 1) / v1(4, 1) + pW], [v3(2, 1) / v3(4, 1) + pH, (v1(2, 1) / v1(4, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)

line([v5(1, 1) / v5(4, 1)+ pW, v6(1, 1) / v6(4, 1) + pW], [v5(2, 1) / v5(4, 1) + pH, (v6(2, 1) / v6(4, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
line([v7(1, 1) / v7(4, 1)+ pW, v8(1, 1) / v8(4, 1) + pW], [v7(2, 1) / v7(4, 1) + pH, (v8(2, 1) / v8(4, 1) + pH)],'color','b') % Blue line from (4,0) to (4,10)
