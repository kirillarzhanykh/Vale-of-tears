set terminal pngcairo enhanced color size 800,600
set output 'interpolation_plot.png'
a = -6.6442
b = 41.5263
c = 1.05746
d = -0.704972
f(x) = a * (cos(x) / (2 * sin(x)) + sin(x)**2) + b * (cos(x) / (8 * sin(x))) + c * (-x + 16 * x**2 / pi) + d * (x)
g(x) = x**3
set xlabel 'x'
set ylabel 'y'
set grid
set xrange[-pi/2: 2*pi]
set yrange[-(pi/2)**3: (2*pi)**3]
set title 'Линейная интерполяция x^3'
plot f(x) title 'Interpolation'  lc rgb 'blue',                        g(x) title 'X^3'  lc rgb 'black',                             'data.txt' using 1:3 with points title 'key points' lc rgb 'red'
