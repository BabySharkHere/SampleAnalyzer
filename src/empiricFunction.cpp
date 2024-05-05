#include "empiricFunction.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#define N 100
#define M 9

using namespace std;

//График эмпирической функции распределения
void empiricFunction(double matrix[N][M], int numberOfUnique){
    double empiricMatrix[numberOfUnique][2];
    for(int i = 0; i < numberOfUnique; i++){
        for(int j = 0; j < 2; j++){
            empiricMatrix[i][j] = 0;
        }
    }
    empiricMatrix[0][0] = -99999;
    empiricMatrix[0][1] = 0;
    for(int i = 1; i < numberOfUnique+1; i++){
        empiricMatrix[i][0] = matrix[i-1][1];
        empiricMatrix[i][1] = matrix[i-1][5];
    }
    
    //Выводим в консоль матрицу эмпирической функции распределения
    /*for(int i = 0; i < numberOfUnique+1; i++){
        for(int j = 0; j < 2; j++){
            cout << empiricMatrix[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << endl << endl << "График эмпирической функции распределения" << endl;
    
    cout << '0' << setfill(' ') << setw(15) << "0.2" << setw(15) << "0.4" << setw(15) << "0.6" << setw(15) << "0.8" << setw(15) << '1' << endl;
    cout << 'Y' << setfill('-') << setw(76) << '-' << "->" << endl;
    for(int i = 0; i < numberOfUnique+1; i++){
        cout << "|" << setfill('*') << setw((empiricMatrix[i][1])*75) << "\t" << empiricMatrix[i][0] << "-" << empiricMatrix[i+1][0] << endl;
    }
    cout << "|" << endl << "⌵ X" << endl;
}

//График эмпирической функции распределения в файл
void empericFunctionToFile(double matrix[N][M], int numberOfUnique, string fileName){
    ofstream fileToWrite;
    fileToWrite.open(fileName, ios::app);
    
    double empiricMatrix[numberOfUnique][2];
    for(int i = 0; i < numberOfUnique; i++){
        for(int j = 0; j < 2; j++){
            empiricMatrix[i][j] = 0;
        }
    }
    empiricMatrix[0][0] = -99999;
    empiricMatrix[0][1] = 0;
    for(int i = 1; i < numberOfUnique+1; i++){
        empiricMatrix[i][0] = matrix[i-1][1];
        empiricMatrix[i][1] = matrix[i-1][5];
    }
    
    //Выводим в консоль матрицу эмпирической функции распределения
    /*for(int i = 0; i < numberOfUnique+1; i++){
        for(int j = 0; j < 2; j++){
            cout << empiricMatrix[i][j] << " ";
        }
        cout << endl;
    }*/
    if(fileToWrite.is_open()){
        fileToWrite << endl << endl << "График эмпирической функции распределения" << endl;
        
        fileToWrite << '0' << setfill(' ') << setw(15) << "0.2" << setw(15) << "0.4" << setw(15) << "0.6" << setw(15) << "0.8" << setw(15) << '1' << endl;
        fileToWrite << 'Y' << setfill('-') << setw(76) << '-' << "->" << endl;
        for(int i = 0; i < numberOfUnique+1; i++){
            fileToWrite << "|" << setfill('*') << setw((empiricMatrix[i][1])*75) << "\t" << empiricMatrix[i][0] << "-" << empiricMatrix[i+1][0] << endl;
        }
        fileToWrite << "|" << endl << "⌵ X" << endl;
    }
    fileToWrite.close();
}
