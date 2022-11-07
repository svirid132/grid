function m = getPerspectiveProjection(fovy, aspect, n, f)
radians = pi / 180 * fovy;
sx = (1 / tan(radians / 2)) / aspect;
sy = (1 / tan(radians / 2));
sz = (f + n) / (f - n);
dz = (-2 * f * n) / (f - n);
m = [
    sx, 0, 0, 0;
    0, sy, 0, 0;
    0, 0, sz, dz;
    0, 0, -1, 0;
    ];
end