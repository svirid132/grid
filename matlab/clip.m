function [va, vb] = clip(v1, v2, near)

if v1(4, 1) <= near && v2(4, 1) <= near
    va = v1;
    vb = v2;
    return;
elseif v1(4, 1) <= near && v2(4, 1) > near
        n = (v1(4, 1) - near) / (v1(4, 1) - v2(4, 1));
        xc = (n * v1(1, 1)) + ((1 - n) * v2(1, 1));
        yc = (n * v1(2, 1)) + ((1-n) * v2(2, 1));
        zc = (n * v1(3, 1)) + ((1-n) * v2(3, 1));
        wc = near;
        vc = [xc; yc; zc; wc;];
        va = v1;
        vb = vc;
        return;
elseif v1(4, 1) > near && v2(4, 1) <= near
        n = (v2(4, 1) - near) / (v2(4, 1) - v1(4, 1));
        xc = (n * v2(1, 1)) + ((1 - n) * v1(1, 1));
        yc = (n * v2(2, 1)) + ((1-n) * v1(2, 1));
        zc = (n * v2(3, 1)) + ((1-n) * v1(3, 1));
        wc = near;
        vc = [xc; yc; zc; wc;];
        va = vc;
        vb = v2;
        return;
end

va = [0; 0; 0; 1]
vb = [0; 0; 0; 1];
%v1 - front v2 - behind
%n = (w1 - near) / (w1 - w2);
%xc = (n * x1) + ((1 - n) * x2);
%yc = (n * y1) + ((1-n) * y2);
%zc = (n * z1) + ((1-n) * z2);
%wc = near;
%vc = [xc, yc, zc, wc];

%if near >= v1(4, 1)
%    va = v1;
%else
%    vb = v2;
end

