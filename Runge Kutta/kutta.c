#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double x0 = 0,
             xf = 4,
             yi = 1,
             h  = 0.1;

double f(double x, double y) {
    return 1 - x + 4*y;
}

double solucao_exata(double x) {
    return (19.0 * exp(4*x) + 4.0 * x - 3.0) / 16.0;
}

double rk_2(double xn, double yn) {
    double k1 = f(xn, yn);
    double k2 = f(xn + h, yn + h * k1);
    return yn + h/2 * (k1 + k2);
}

double rk_3(double xn, double yn) {
    double k1 = f(xn, yn);
    double k2 = f(xn + h/2, yn + h/2 * k1);
    double k3 = f(xn + h, yn - h * k1 + 2*h * k2);
    return yn + h/6 * (k1 + 4 * k2 + k3);
}

double rk_4(double xn, double yn) {
    double k1 = f(xn, yn);
    double k2 = f(xn + h/2, yn + h/2 * k1);
    double k3 = f(xn + h/2, yn + h/2 * k2);
    double k4 = f(xn + h, yn + h * k3);
    return yn + h/6 * (k1 + 2*k2 + 2*k3 + k4);
}

int main() {
    int n = (int) ((xf - x0) / h) + 1; // Número de pontos
    double x[n], y_rk2[n], y_rk3[n], y_rk4[n], y_exata[n];

    x[0] = x0;
    
    y_exata[0] = solucao_exata(x0);
    y_rk2[0] = y_rk3[0] = y_rk4[0] = yi;

    for (int i = 0; i < n-1; i++) {
        x[i+1] = x[i] + h;

        y_exata[i+1] = solucao_exata(x[i+1]);
        y_rk2[i+1] = rk_2(x[i], y_rk2[i]);
        y_rk3[i+1] = rk_3(x[i], y_rk3[i]);
        y_rk4[i+1] = rk_4(x[i], y_rk4[i]);
    }

    // Salva os pontos
    FILE *f = fopen("resultado.csv", "w");
    fprintf(f, "x,RK-2,RK-3,RK-4,Solução exata\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%f,%f,%f,%f,%f\n", x[i], y_rk2[i], y_rk3[i], y_rk4[i], y_exata[i]);
    }
    fclose(f);

    // Gera o script do gnuplot
    FILE *gp = fopen("script.gp", "w");
    fprintf(gp,
        "set terminal qt\n"
        "set datafile separator ','\n"
        "set title 'Métodos de Runge-Kutta'\n"
        "set xlabel 'x'\n"
        "set ylabel 'y'\n"
        "set grid\n"
        "plot 'resultado.csv' using 1:2 with points lt 1 pt 7 lw 1 title 'RK-2', \\\n"
        "     'resultado.csv' using 1:3 with points lt 2 pt 5 lw 1 title 'RK-3', \\\n"
        "     'resultado.csv' using 1:4 with points lt 3 pt 9 lw 1 title 'RK-4', \\\n"
        "     'resultado.csv' using 1:5 with lines lw 2 lt rgb 'black' title 'Solução Exata'\n"
        "pause -1\n"
    );
    fclose(gp);

    // Plota o gráfico
    system("gnuplot script.gp");

    return 0;
}
