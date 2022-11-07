clear all;
%51 52 
degress = 52;
scale = 3;

Scale = getScale(scale, scale, scale)
Translation = getTranslation(0, 0, 0) * Scale
getLookAt_1 = getLookAt([0 0 0], [degressToRadians(degress) degressToRadians(0) -1], [0 1 0])
LookAt = getLookAt_1 * Translation
near = -1;
Frustum = frustum(-1, 1, -1, 1, near, -1000) * LookAt%Присваеивает w через z
m = getPerspectiveProjection(90, 1, near, -1000) * Frustum
m = m / norm(m);
v = [-1; 1; 0; 1;];
v = m * v;
v = v / norm(v);
x = v(1)
w = v(4)
new_x = x / w
y = v(2) / v(4);
