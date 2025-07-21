#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 500

unsigned char paleta[16][3] = {
    {66,  30,  15 },
    {25,  7,   26 },
    {9,   1,   47 },
    {4,   4,   73 },
    {0,   7,   100},
    {12,  44,  138},
    {24,  82,  177},
    {57,  125, 209},
    {134, 181, 229},
    {211, 236, 248},
    {241, 233, 191},
    {248, 201, 95 },
    {255, 170, 0  },
    {204, 128, 0  },
    {153, 87,  0  },
    {106, 52,  3  }
};

int numeroIteracoes(double x0, double y0) {
    double x = 0, y = 0;
    int iter = 0;

    // |z|² <= 2² (|z|² = x² + y²)
    while (x*x + y*y <= 4 && iter < MAX_ITER) {

        double x_ = x*x - y*y + x0; // x = x² - y² + x0
        double y_ = 2*x*y + y0;     // y = 2xy + y0

        x = x_; y = y_;
        iter++;
    }

    return iter;
}

int pertenceAoConjunto(int iter) {
    return iter == MAX_ITER;
}

int main() {
    double re_min = -2.13,
           re_max = 1.13,
           im_min = -1.13,
           im_max = 1.13;

    // Cabeçalho do arquivo ppm
    FILE *fp = fopen("mandelbrot.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // Percorre cada pixel
    for (int py = 0; py < HEIGHT; py++) {
        for (int px = 0; px < WIDTH; px++) {
            // Converte a posição do pixel para a coordenada correspondente
            double x0 = re_min + (re_max - re_min) * px / (WIDTH - 1);
            double y0 = im_min + (im_max - im_min) * py / (HEIGHT - 1);

            int iter = numeroIteracoes(x0, y0);

            // Escolhe a cor do pixel
            unsigned char color[3];
            if (pertenceAoConjunto(iter)) {
                color[0] = 60;
                color[1] = 40;
                color[2] = 128;
            } else {
                int idx = iter % 16;
                color[0] = paleta[idx][0];
                color[1] = paleta[idx][1];
                color[2] = paleta[idx][2];
            }

            fwrite(color, 1, 3, fp);
        }
    }

    fclose(fp);

    printf("Imagem gerada!\n");

    return 0;
}
