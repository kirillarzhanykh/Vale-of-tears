set terminal pngcairo enhanced color size 1000,1000
set output 'PCA.png'
x1 = 0.693164
y1 = 0.669218
z1 = 0.267716
x2 = -0.141051
y2 = -0.238301
z2 = 0.960894
x3 = -0.706844
y3 = 0.703818
z3 = 0.070788
arcsin1 = 15.5284
arccos1 = 43.993
arcsin2 = 73.9238
arccos2 = 120.621
arcsin3 = 4.05925
arccos3 = 135.123
set xlabel 'x'
set ylabel 'y'
set zlabel 'z'
set xrange[-10: 10]
set yrange[-10: 10]
set zrange[-10: 10]
set view 90 - arcsin3, 90 + arccos3
set arrow 1 from 0, 0, 0 to x1, y1, z1 lc rgb 'blue'
set arrow 2 from 0, 0, 0 to x2, y2, z2 lc rgb 'red'
set arrow 3 from 0, 0, 0 to x3, y3, z3 lc rgb 'green'
splot 'data2.txt' using 1:2:3 with points title 'points' lc rgb 'black'
