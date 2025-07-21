set terminal qt
set datafile separator ','
set title 'Métodos de Runge-Kutta'
set xlabel 'x'
set ylabel 'y'
set grid
plot 'resultado.csv' using 1:2 with points lt 1 pt 7 lw 1 title 'RK-2', \
     'resultado.csv' using 1:3 with points lt 2 pt 5 lw 1 title 'RK-3', \
     'resultado.csv' using 1:4 with points lt 3 pt 9 lw 1 title 'RK-4', \
     'resultado.csv' using 1:5 with lines lw 2 lt rgb 'black' title 'Solução Exata'
pause -1
