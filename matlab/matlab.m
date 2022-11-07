clear all;
a = 2;
%1.309 0.785398 
vector = [1, 2, 0];
vector = vector / norm(vector);
m = getTranslation(0, 0, 1);
m = getLookAt([0 0 0], [0 0.1 -1], [0 1 0]) * m;
near = -1;
m = frustum(-1, 1, -1, 1, near, -1000) * m;
m = getPerspectiveProjection(90, 1920 / 1080, near, -1000) * m;
%m = [1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1] * m;%ортографическое преобразование

pW = 1920 / 2;%Половина ширины экрана
pH = 1080 / 2;%Половина высоты экран
v1 = m * [-1; 1; 0; 1;];
v2 = m * [1; 1; 0; 1;];
v3 = m * [-1; -1; 0; 1;];
v4 = m * [1; -1; 0; 1;];

%v1(1, 1) = v1(1, 1) / v1(4, 1)  * pW;
%v1(2, 1) = v1(2, 1) / v1(4, 1) * pH;

%v2(1, 1) = v2(1, 1) / v2(4, 1) * pW;
%v2(2, 1) = v2(2, 1) / v2(4, 1) * pH;

%v3(1, 1) = v3(1, 1) / v3(4, 1) * pW;
%v3(2, 1) = v3(2, 1) / v3(4, 1) * pH;

%v4(1, 1) = v4(1, 1) / v4(4, 1) * pW;
%v4(2, 1) = v4(2, 1) / v4(4, 1) * pH;

near = 0;
%[va, vb] = clip(v1, v2, near);
va = v1;
vb = v2;
va(1, 1) = va(1, 1) / va(4,1) * pW;
va(2, 1) = va(2, 1) / va(4, 1) * pH;
vb(1, 1) = vb(1, 1) / vb(4,1) * pW;
vb(2, 1) = vb(2, 1) / vb(4, 1) * pH;
x1 = va(1, 1) + pW;
x2 = vb(1, 1) + pW;
y1 = va(2, 1) + pH;
y2 = vb(2, 1) + pH;
line([x1, x2], [y1, y2],'color','b') % Blue line from (4,0) to (4,10)

%[va, vb] = clip(v4, v3, near);
va = v4;
vb = v3;
va(1, 1) = va(1, 1) / va(4,1) * pW;
va(2, 1) = va(2, 1) / va(4, 1) * pH;
vb(1, 1) = vb(1, 1) / vb(4,1) * pW;
vb(2, 1) = vb(2, 1) / vb(4, 1) * pH;
x1 = va(1, 1) + pW;
x2 = vb(1, 1) + pW;
y1 = va(2, 1) + pH;
y2 = vb(2, 1) + pH;
line([x1, x2], [y1, y2],'color','b') % Blue line from (4,0) to (4,10)

%[va, vb] = clip(v2, v4, near)
va = v2;
vb = v4;
va(1, 1) = va(1, 1) / va(4,1) * pW;
va(2, 1) = va(2, 1) / va(4, 1) * pH;
vb(1, 1) = vb(1, 1) / vb(4,1) * pW;
vb(2, 1) = vb(2, 1) / vb(4, 1) * pH;
x1 = va(1, 1) + pW;
x2 = vb(1, 1) + pW;
y1 = va(2, 1) + pH;
y2 = vb(2, 1) + pH;
line([x1, x2], [y1, y2],'color','b') % Blue line from (4,0) to (4,10)

%[va, vb] = clip(v3, v1, near);
va = v3;
vb = v1;
va(1, 1) = va(1, 1) / va(4,1) * pW;
va(2, 1) = va(2, 1) / va(4, 1) * pH;
vb(1, 1) = vb(1, 1) / vb(4,1) * pW;
vb(2, 1) = vb(2, 1) / vb(4, 1) * pH;
x1 = va(1, 1) + pW;
x2 = vb(1, 1) + pW;
y1 = va(2, 1) + pH;
y2 = vb(2, 1) + pH;
line([x1, x2], [y1, y2],'color','b') % Blue line from (4,0) to (4,10)

axis([0 1920 0 1080]) % Set the axis limits от 0 до 10

%b = [1 2; 3 4] * [1; 2];