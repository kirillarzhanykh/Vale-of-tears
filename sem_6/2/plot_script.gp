set terminal pngcairo enhanced color size 800,600
set output 'interpolation_plot.png'
x_1 = 1
a_1 = 1.35914
b_1 = 1
c_1 = -6.36891
d_1 = 28.0377
p_1(x) = a_1 + b_1 * (x - x_1) + c_1 * (x - x_1)**2 + d_1 * (x - x_1)**3
x_2 = 2
a_2 = 24.028
b_2 = 72.3754
c_2 = 65.9267
d_2 = 107.98
p_2(x) = a_2 + b_2 * (x - x_2) + c_2 * (x - x_2)**2 + d_2 * (x - x_2)**3
x_3 = 3
a_3 = 270.31
b_3 = 528.17
c_3 = 376.325
d_3 = 251.585
p_3(x) = a_3 + b_3 * (x - x_3) + c_3 * (x - x_3)**2 + d_3 * (x - x_3)**3
x_4 = 4
a_4 = 1426.39
b_4 = 2035.58
c_4 = 1116.32
d_4 = 466.053
p_4(x) = a_4 + b_4 * (x - x_4) + c_4 * (x - x_4)**2 + d_4 * (x - x_4)**3
f(x) = exp(x) / (2 * x) + x**5 * log(x)
set xlabel 'x'
set ylabel 'y'
set grid
set xrange[1 : 5]
set yrange[f(1) : f(5)]
set title 'Интерполяция сплайнами Эрмита'
plot f(x) lw 4 lc rgb 'green',                        p_1(x) lw 2 lc rgb 'red',                        p_2(x) lw 2 lc rgb 'blue',                        p_3(x) lw 2 lc rgb 'yellow',                        p_4(x) lw 2 lc rgb 'black',                        'data.txt' using 1:2 with points title 'key points' lc rgb 'black'
