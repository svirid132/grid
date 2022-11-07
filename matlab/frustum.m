%Усечение пирамиды
function m = frustum(left, right, bottom, top, near, far)
    m = [2 * near / (right - left) 0 (right + left) / (right - left) 0;
        0 2 * near / (top - bottom) (top + bottom) / (top - bottom) 0;
        0 0 -(far + near) / (far - near) -2*far*near/(far- near);
        0 0 -1 0];
end