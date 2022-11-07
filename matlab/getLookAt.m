function m = getLookAt(eye, target, up)
v = eye - target;
vz = v / norm(v);%ветор столбец
v = cross(up, vz);%up - ? получается число или матрица
vx = v / norm(v);
v = cross(vz, vx);
vy = v / norm(v);

new_m = [
    vx(1, 1), vx(1, 2), vx(1, 3), 0;
    vy(1, 1), vy(1, 2), vy(1, 3), 0;
    vz(1, 1), vz(1, 2), vz(1,3), 0;
    0, 0, 0, 1;
    ];
abc = getTranslation(-eye(1, 1), -eye(1, 2), -eye(1, 3));
m = new_m * getTranslation(-eye(1, 1), -eye(1, 2), -eye(1, 3));

end