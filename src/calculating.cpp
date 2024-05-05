#include "calculating.h"
#include <iostream>
#define N 100
#define M 9

//Минимальное значение
double min(double matrix[N][M], int numberOfUnique){
    
    double min = 999999;
    for(int i = 0; i < numberOfUnique; i++){
        if(matrix[i][1] < min){
            min = matrix[i][1];
        }
    }
    return min;
}

//Максимальное значение
double max(double matrix[N][M]){
    
    double max = -999999;
    for(int i = 0; i < N; i++){
        if(matrix[i][1] > max){
            max = matrix[i][1];
        }
    }
    return max;
}

//Медиана
double mediana(double matrix[N][M]){
    double mediana = 0;
    if(N%2 != 0){
        mediana = matrix[N/2][0];
    }
    else{
        mediana = (matrix[N/2][0]+matrix[N/2+1][0])/2;
    }
    return mediana;
}
//Мода
double moda(double matrix[N][M], int numberOfUniq){
    double moda = 0;
    int maxFrequency = 0;
    for(int i = 0; i < numberOfUniq; i++){
        if(matrix[i][2] > maxFrequency){
            moda = matrix[i][1];
            maxFrequency = matrix[i][2];
            //std::cout << moda << " " << maxFrequency << std::endl;
        }
    }
    return moda;
}
//Нижний квартиль
double loverQuartil(double matrix[N][M]){
    double lover = 0;
    if(N%2 != 0){
        lover = matrix[N+1/4][0];
    }
    else{
        lover = matrix[N/4][0];
    }
    return lover;
}

//Верхний квартиль
double upperQuartil(double matrix[N][M]){
    double upper = 0;
    if(N%2 != 0){
        upper = matrix[3*(N+1)/4][0];
    }
    else{
        upper = matrix[3*N/4][0];
    }
    return upper;
}

//Дисперсия
double dispersion(double matrix[N][M], int numberOfUnique){
    double disp = 0;
    for(int i = 0; i < numberOfUnique; i++){
        disp += matrix[i][6];
    }
    disp /= N;
    return disp;
}

//Центральный момент третьего порядка
double midMoment3(double matrix[N][M], int numberOfUnique){
    double midmoment = 0;
    for(int i = 0; i < numberOfUnique; i++){
        midmoment += matrix[i][7];
    }
    return midmoment/N;
}

//Центральный момент четвёртого порядка
double midmoment4(double matrix[N][M], int numberOfUnique){
    double midmoment = 0;
    for(int i = 0; i < numberOfUnique; i++){
        midmoment += matrix[i][8];
    }
    return midmoment/N;
}
