#ifndef openGLgraphics_hpp
#define openGLgraphics_hpp
#define N 100
#define M 9

#include <stdio.h>
double max(double matrix[N][M]);
double min(double matrix[N][M], int numberOfUnique);
double mediana(double matrix[N][M]);
double moda(double matrix[N][M], int numberOfUniq);
double loverQuartil(double matrix[N][M]);
double upperQuartil(double matrix[N][M]);
double dispersion(double matrix[N][M], int numberOfUnique);
double midMoment3(double matrix[N][M], int numberOfUnique);
double midmoment4(double matrix[N][M], int numberOfUnique);
#endif /* openGLgraphics_hpp */
