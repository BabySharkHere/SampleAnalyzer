#include "histogram.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#define N 100
#define M 9
using namespace std;

//Построение гистограммы с нормализацией
void histogramWithNormalize(double matrix[N][M], int numberOfUnique, int widthMass, int minimum, int maximum){
    double histMatrix[N][M];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            histMatrix[i][j] = 0;
        }
    }
    int numberOfSteps = 1+3.22*log10(N);
    int widthOfSteps = widthMass/numberOfSteps;
    cout << endl << endl << endl << endl;
    int k = 0, j = 0, counter = minimum;
    while(counter <= maximum){
        for(int i = 0; i < counter+widthOfSteps; i++){
            k++;
        }
        histMatrix[j][0] = k;
        counter+=widthOfSteps;
    }
    int sumCheck = 0;
    for(int i = 0; i < numberOfSteps; i++){
        sumCheck+=histMatrix[i][0];
    }
    if(sumCheck != N) cout << "Ошибка проверки по частоте после нормализации по формуле Стюрджеса" << endl;
    else cout << "Проверка по частоте после нормализации по формуле Стюрджес прошла успешно" << endl;
    
    int allHist = 10;
    for(int i = 0; i < numberOfSteps; i++){
        histMatrix[i][1] = histMatrix[i][0]/allHist;
    }
    
    for(int i = 0; i < numberOfSteps; i++){
        cout << setfill('*') << setw(histMatrix[i][1]) << '*' << endl;
    }
    
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << histMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

//Гистограма плотности распределения
void histogram(double matrix[N][M], int numberOfUnique){
    double histMatrix[numberOfUnique][2];
    for(int i = 0; i < numberOfUnique; i++){
        for(int j = 0; j < 2; j++){
            histMatrix[i][j] = 0;
        }
    }
    
    for(int i = 0; i < numberOfUnique; i++){
        histMatrix[i][0] = matrix[i][1];
        histMatrix[i][1] = matrix[i][2];
    }
    
    
    cout << endl << endl << "Гистограма плотности распределения" << endl;
    //Зависит от частоты
    //Вывод в консоль матрицы для построения гистограммы
    /*for(int i = 0; i < numberOfUnique; i++){
        for(int j = 0; j < 2; j++){
            cout << histMatrix[i][j] << " ";
        }
        cout << endl;
    }*/
    //Всё поле = 80 символов, Высота +- 15 символов.
    cout << '0' << setfill(' ') << setw(15) << "0.2" << setw(15) << "0.4" << setw(15) << "0.6" << setw(15) << "0.8" << setw(15) << '1' << endl;
    cout << 'Y' << setfill('-') << setw(76) << '-' << "->" << endl;
    for(int i = 0; i < numberOfUnique; i++){
        cout << "|" << setfill('*') << setw((histMatrix[i][1]+1/N)*7.5) << "\t" << histMatrix[i][0]<< endl;
    }
    cout << "|" << endl << "⌵ X" << endl;
    /*for(int i = 0; i < numberOfUnique; i++){
        cout << setfill('*') << setw()
    }*/
}
//Гистограма плотности распределения в файл
void histogramToFile(double matrix[N][M], int numberOfUnique, string fileName){
    ofstream fileToWrite;
    fileToWrite.open(fileName, ios::app);
    
    double histMatrix[numberOfUnique][2];
    for(int i = 0; i < numberOfUnique; i++){
        for(int j = 0; j < 2; j++){
            histMatrix[i][j] = 0;
        }
    }
    
    for(int i = 0; i < numberOfUnique; i++){
        histMatrix[i][0] = matrix[i][1];
        histMatrix[i][1] = matrix[i][2];
    }
    
    if(fileToWrite.is_open()){
        fileToWrite << endl << endl << "Гистограма плотности распределения" << endl;
        
        fileToWrite << '0' << setfill(' ') << setw(15) << "0.2" << setw(15) << "0.4" << setw(15) << "0.6" << setw(15) << "0.8" << setw(15) << '1' << endl;
        fileToWrite << 'Y' << setfill('-') << setw(76) << '-' << "->" << endl;
        for(int i = 0; i < numberOfUnique; i++){
            fileToWrite << "|" << setfill('*') << setw((histMatrix[i][1]+1/N)*7.5) << "\t" << histMatrix[i][0]<< endl;
        }
        fileToWrite << "|" << endl << "⌵ X" << endl;
    }
    fileToWrite.close();
}
