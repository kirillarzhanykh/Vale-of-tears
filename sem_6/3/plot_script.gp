set terminal pngcairo enhanced color size 1000,1000
set output 'PCA.png'
x0 = 1.71716
y0 = 2.28284
z0 = 1.35951
x1 = 2.77266
y1 = 2.67687
z1 = 1.07086
x2 = -0.282101
y2 = -0.476602
z2 = 1.92179
x3 = -0.706844
y3 = 0.703818
z3 = 0.070788
set xlabel 'x'
set ylabel 'y'
set zlabel 'z'
set view 50, 200
set arrow 1 from x0, y0, z0 to x0 + x1, y0 + y1, z0 + z1 lc rgb 'blue'
set arrow 2 from x0, y0, z0 to x0 + x2, y0 + y2, z0 + z2 lc rgb 'red'
set arrow 3 from x0, y0, z0 to x0 + x3, y0 + y3, z0 + z3 lc rgb 'green'
splot -(((x - x0)*x3 + (y - y0)*y3)/z3 + z0) title 'approximative plane' lc rgb 'grey',                    'data.txt' using 1:2:3 with points title 'points' lc rgb 'black'
