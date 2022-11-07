function m = getScale(sx, sy, sz)
m = [sx, 0, 0, 0;
    0, sy, 0, 0;
    0, 0, sz, 0
    0, 0, 0, 1;];
end