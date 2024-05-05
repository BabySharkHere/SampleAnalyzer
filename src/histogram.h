#ifndef histogram_hpp
#define histogram_hpp

#include <stdio.h>
#include <string>
#define N 100
#define M 9
#endif /* histogram_hpp */


void histogramWithNormalize(double matrix[N][M], int numberOfUnique, int widthMass, int minimum, int maximum);
void histogram(double matrix[N][M], int numberOfUnique);
void histogramToFile(double matrix[N][M], int numberOfUnique, std::string fileName);
