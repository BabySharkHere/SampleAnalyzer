#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "calculating.hpp"
#include "histogram.hpp"
#include "empiricFunction.hpp"
#define N 100   //число строк (объём выборки)
#define M 9 //число столбцов
#define pathToFile "path" //Путь до файла с выборкой

using namespace std;

void menu();
void readMass(double startMatrix[N][M]);
void unique(double uniqueMatrix[N][M]);
int frequencyMultyUnique(double frUniqMatrix[N][M], int numberOfUnique);
void relativeFrequency(double frequencyMatrix[N][M], int numberOfUnique);
void relativeSaveFrequency(double saveFrequencyMatrix[N][M], int numberOfUnique);
void squareThirdFourth(double matrix[N][M], int numberOfUnique, double medium);
void writeMatrix(double outMatrix[N][M], int numberOfUnique);
void writeMatrixToFile(double outMatrix[N][M], int numberOfUnique);
void writeMatrixFile(double outMatrix[N][M], int numberOfUnique);
void writeAnalisysToFile(double outMatrix[N][M], int numberOfUnique);
void writeMatrixTextToFile(double outMatrix[N][M], int numberOfUnique);

int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "ru");
    double startMatrix[N][M];
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            startMatrix[i][j] = 0;
        }
    }
    
    readMass(startMatrix);
    unique(startMatrix);
    
    int numberOfUnique = 0;
    for(int i = 0; i < N; i++){
        if (startMatrix[i][1] != 0){
            numberOfUnique++;
        }
    }
    
    double sum = frequencyMultyUnique(startMatrix, numberOfUnique);
    cout << "Количество уникальных членов: " << numberOfUnique << endl;
    cout << "Объём выборки: " << N << endl;
    cout << "Сумма столбцов 'Уникальные' умножить на 'Частота': " << sum << endl;
    double medium = sum/N;
    cout << "Выборочное среднее: " << medium << endl;
    double maximum = max(startMatrix);
    double minimum = min(startMatrix,numberOfUnique);
    double widthMass = max(startMatrix) - min(startMatrix, numberOfUnique);
    cout << "Максимальное значение: " << maximum << endl;
    cout << "Минимальное значение: " << minimum << endl;
    cout << "Размах выборки: " << widthMass << endl;
    cout << "Мода: " << moda(startMatrix, numberOfUnique) << endl;
    cout << "Медиана: " << mediana(startMatrix) << endl;
    cout << "Нижний квартиль: " << loverQuartil(startMatrix) << endl;
    cout << "Верхний квартиль: " << upperQuartil(startMatrix) << endl;
    cout << "Интерквартальный размах: " << upperQuartil(startMatrix)-loverQuartil(startMatrix) << endl;
    squareThirdFourth(startMatrix, numberOfUnique, medium);
    double disp = dispersion(startMatrix, numberOfUnique);
    cout << "Выборочная дисперсия: " << disp << endl;
    cout << "СКО: " << sqrt(disp) << endl;
    cout << "Среднее отклонение: " << 0.477*sqrt(2)*sqrt(disp) << endl;
    double mimoment3 = midMoment3(startMatrix, numberOfUnique);
    double mimoment4 = midmoment4(startMatrix, numberOfUnique);
    cout << "Центральный момент третьего порядка: " << mimoment3 << endl;
    cout << "Центральный момент четвёртого порядка: " << mimoment4 << endl;
    cout << "Коэффициент ассиметрии: " << mimoment3/pow(sqrt(disp), 3) << endl;
    cout << "Коэффициент эксцесса: " << 3-mimoment4/pow(sqrt(disp), 4) << endl;
    relativeFrequency(startMatrix, numberOfUnique);
    relativeSaveFrequency(startMatrix, numberOfUnique);
    writeMatrix(startMatrix, numberOfUnique);
    
    histogram(startMatrix, numberOfUnique);
    empiricFunction(startMatrix, numberOfUnique);
    
    cout << "Хотите вывести общий файл с полной информацией из консоли? y/n" << endl;
    char ch;
    cin >> ch;
    if (ch == 'y'){
        writeMatrixToFile(startMatrix, numberOfUnique);
        cout << "Файл записан. Завершаю программу..." << endl;
    }
    else{
        cout << "Вы хотите записать таблицу в отдельный файл? y/n" << endl;
        cin >> ch;
        if(ch == 'y'){
            cout << "Вы хотите вывести таблицей или текстом? y-табл/n-текстом" << endl;
            cin >> ch;
            if (ch == 'y'){
                writeMatrixFile(startMatrix, numberOfUnique);
                cout << "Файл записан. Завершаю программу..." << endl;
            }
            else if (ch == 'n') {
                writeMatrixTextToFile(startMatrix, numberOfUnique);
                cout << "Файл записан. Завершаю программу..." << endl;
            }
        }
        else {
            cout << "Вы хотите вывести только подсчёты(без матрицы)? y/n" << endl;
            cin >> ch;
            if(ch == 'y'){
                writeAnalisysToFile(startMatrix, numberOfUnique);
            }
        }cout << "Завершаю программу..." << endl;
    }
    return 0;
}

void menu(){
    cout << "1. Увидеть, что значат столбцы";
}

void readMass(double startMatrix[N][M]){    //считывание матрицы
    ifstream inputMatrixFromTXT;
    inputMatrixFromTXT.open(pathToFile, ios::in);
    if(inputMatrixFromTXT.is_open()){
        while(!inputMatrixFromTXT.eof()){
            for(int i = 0; i < N; i++){
                inputMatrixFromTXT >> startMatrix[i][0];
            }
        }
    }
    inputMatrixFromTXT.close();
}

void writeMatrix(double outMatrix[N][M], int numberOfUnique){   //вывод матрицы
    cout << endl << endl;
    cout << setw(15) << "Данные " << setw(25) << "Уникальные " << setw(18) << "Частота " << setw(10) << "Данные*Чаcтота " << setw(10) << "ОтнЧа " << setw(18) << "ОтнНакопЧаст " << setw(14) << "Вторая " << setw(16) << "Третья " << setw(23) << "Четвёртая " << endl;
    for(int i = 0; i < numberOfUnique; i++){
        for(int j = 0; j < M; j++){
            cout << setw(10) << setprecision(4) << outMatrix[i][j] << " ";
        }
        cout << endl;
    }
    for(int i = numberOfUnique; i < N; i++){
        cout << setw(10) << outMatrix[i][0] << " ";
        cout << endl;
    }
}

void unique(double uniqueMatrix[N][M]){ //количество уникальных челенов
    double k = 1;
    int c = 0;
    for(int i = 0; i < N-1; i++){
        if (uniqueMatrix[i][0] == uniqueMatrix[i + 1][0]){
            k++;
            }
        else{
            uniqueMatrix[c][1] = uniqueMatrix[i][0];
            uniqueMatrix[c][2] = k;
            k = 1;
            c++;
            }
    }
    if(uniqueMatrix[N-2][0] == uniqueMatrix[N-1][0]){
        uniqueMatrix[c][1] = uniqueMatrix[N-1][0];
        uniqueMatrix[c][2] = k;
    }
    else {
        uniqueMatrix[c][1] = uniqueMatrix[N-1][0];
        uniqueMatrix[c][2] = k;
    }
}

//Данные*Частота
int frequencyMultyUnique(double frUniqMatrix[N][M], int numberOfUnique){
    int sum = 0;
    for(int i = 0; i < numberOfUnique; i++){
        frUniqMatrix[i][3] = frUniqMatrix[i][2]*frUniqMatrix[i][1];
        sum += frUniqMatrix[i][3];
    }
    
    return sum;
}

//относительная частота
void relativeFrequency(double frequencyMatrix[N][M], int numberOfUnique){
    double sumCheck = 0;
    for(int i = 0; i < numberOfUnique; i++){
        frequencyMatrix[i][4] = frequencyMatrix[i][2]/N;
        sumCheck += frequencyMatrix[i][4];
    }
    cout << "Проверка на сумму частот: " << sumCheck << endl;
}

//относительная накопленная частота
void relativeSaveFrequency(double saveFrequencyMatrix[N][M], int numberOfUnique){
    double saveFrequency = 0;
    for(int i = 0; i < numberOfUnique; i++){
        saveFrequency += saveFrequencyMatrix[i][4];
        saveFrequencyMatrix[i][5] = saveFrequency;
    }
}

//Вторая, третья, четвёртая степени
void squareThirdFourth(double matrix[N][M], int numberOfUnique, double medium){
    for(int i = 0; i < numberOfUnique; i++){
        matrix[i][6] = pow(matrix[i][1]-medium, 2)*matrix[i][2];
        matrix[i][7] = pow(matrix[i][1]-medium, 3)*matrix[i][2];
        matrix[i][8] = pow(matrix[i][1]-medium, 4)*matrix[i][2];
    }
}

//Запись матрицы в файл
void writeMatrixTextToFile(double outMatrix[N][M], int numberOfUnique){
    ofstream fileToWrite;
    cout << "Введите название файла, в который в хотите записать таблицу" << endl;
    string fileName;
    cin >> fileName;
    fileName += ".txt";
    fileName.insert(0,"/Users/daniiltihonov/Desktop/");
    fileToWrite.open(fileName);
    if(fileToWrite.is_open()){
        for(int i = 0; i < N; i++){
            fileToWrite << outMatrix[i][0] << endl;
        }
        fileToWrite << endl << endl << endl;
        for(int j = 1; j < M; j++){
            for(int i = 0; i < numberOfUnique; i++){
                fileToWrite << outMatrix[i][j] << "\n";
            }
            fileToWrite << endl << endl << endl;
        }
        fileToWrite.close();
    }
}

//Запись матрицы в файл с аналитикой
void writeAnalisysToFile(double outMatrix[N][M], int numberOfUnique){
    ofstream fileToWrite;
    cout << "Введите название файла, в который в хотите записать подсчёты из консоли" << endl;
    string fileName;
    cin >> fileName;
    fileName += ".txt";
    fileName.insert(0,"/Users/daniiltihonov/Desktop/");
    fileToWrite.open(fileName);
    if(fileToWrite.is_open()){
        double sum = frequencyMultyUnique(outMatrix, numberOfUnique);
        fileToWrite << "Количество уникальных членов: " << numberOfUnique << endl;
        fileToWrite << "Объём выборки: " << N << endl;
        fileToWrite << "Сумма столбцов 'Уникальные' умножить на 'Частота': " << sum << endl;
        double medium = sum/N;
        fileToWrite << "Выборочное среднее: " << medium << endl;
        double maximum = max(outMatrix);
        double minimum = min(outMatrix,numberOfUnique);
        double widthMass = max(outMatrix) - min(outMatrix, numberOfUnique);
        fileToWrite << "Максимальное значение: " << maximum << endl;
        fileToWrite << "Минимальное значение: " << minimum << endl;
        fileToWrite << "Размах выборки: " << widthMass << endl;
        fileToWrite << "Мода: " << moda(outMatrix, numberOfUnique) << endl;
        fileToWrite << "Медиана: " << mediana(outMatrix) << endl;
        fileToWrite << "Нижний квартиль: " << loverQuartil(outMatrix) << endl;
        fileToWrite << "Верхний квартиль: " << upperQuartil(outMatrix) << endl;
        fileToWrite << "Интерквартальный размах: " << upperQuartil(outMatrix)-loverQuartil(outMatrix) << endl;
        double disp = dispersion(outMatrix, numberOfUnique);
        fileToWrite << "Выборочная дисперсия: " << disp << endl;
        fileToWrite << "СКО: " << sqrt(disp) << endl;
        fileToWrite << "Среднее отклонение: " << 0.477*sqrt(2)*sqrt(disp) << endl;
        double mimoment3 = midMoment3(outMatrix, numberOfUnique);
        double mimoment4 = midmoment4(outMatrix, numberOfUnique);
        fileToWrite << "Центральный момент третьего порядка: " << mimoment3 << endl;
        fileToWrite << "Центральный момент четвёртого порядка: " << mimoment4 << endl;
        fileToWrite << "Коэффициент ассиметрии: " << mimoment3/pow(sqrt(disp), 3) << endl;
        fileToWrite << "Коэффициент эксцесса: " << 3-mimoment4/pow(sqrt(disp), 4) << endl;
    }
}

void writeMatrixFile(double outMatrix[N][M], int numberOfUnique){
    ofstream fileToWrite;
    cout << "Введите название файла, в который в хотите записать таблицу" << endl;
    string fileName;
    cin >> fileName;
    fileName += ".txt";
    fileName.insert(0,"/Users/daniiltihonov/Desktop/");
    fileToWrite.open(fileName);
    if(fileToWrite.is_open()){
        fileToWrite << setw(15) << "Данные " << setw(25) << "Уникальные " << setw(18) << "Частота " << setw(10) << "Данные*Чаcтота " << setw(10) << "ОтнЧа " << setw(18) << "ОтнНакопЧаст " << setw(14) << "Вторая " << setw(16) << "Третья " << setw(23) << "Четвёртая " << endl;
        for(int i = 0; i < numberOfUnique; i++){
            for(int j = 0; j < M; j++){
                fileToWrite << setw(10) << setprecision(4) << outMatrix[i][j] << " ";
            }
            fileToWrite << endl;
        }
        for(int i = numberOfUnique; i < N; i++){
            fileToWrite << setw(10) << outMatrix[i][0] << " ";
            fileToWrite << endl;
        }
    }
    fileToWrite.close();
}

void writeMatrixToFile(double outMatrix[N][M], int numberOfUnique){
    ofstream fileToWrite;
    cout << "Введите название файла, в который в хотите записать всю информацию из консоли" << endl;
    string fileName;
    cin >> fileName;
    fileName += ".txt";
    fileName.insert(0,"/Users/daniiltihonov/Desktop/");
    fileToWrite.open(fileName);
    if(fileToWrite.is_open()){
        double sum = frequencyMultyUnique(outMatrix, numberOfUnique);
        fileToWrite << "Количество уникальных членов: " << numberOfUnique << endl;
        fileToWrite << "Объём выборки: " << N << endl;
        fileToWrite << "Сумма столбцов 'Уникальные' умножить на 'Частота': " << sum << endl;
        double medium = sum/N;
        fileToWrite << "Выборочное среднее: " << medium << endl;
        double maximum = max(outMatrix);
        double minimum = min(outMatrix,numberOfUnique);
        double widthMass = max(outMatrix) - min(outMatrix, numberOfUnique);
        fileToWrite << "Максимальное значение: " << maximum << endl;
        fileToWrite << "Минимальное значение: " << minimum << endl;
        fileToWrite << "Размах выборки: " << widthMass << endl;
        fileToWrite << "Мода: " << moda(outMatrix, numberOfUnique) << endl;
        fileToWrite << "Медиана: " << mediana(outMatrix) << endl;
        fileToWrite << "Нижний квартиль: " << loverQuartil(outMatrix) << endl;
        fileToWrite << "Верхний квартиль: " << upperQuartil(outMatrix) << endl;
        fileToWrite << "Интерквартальный размах: " << upperQuartil(outMatrix)-loverQuartil(outMatrix) << endl;
        double disp = dispersion(outMatrix, numberOfUnique);
        fileToWrite << "Выборочная дисперсия: " << disp << endl;
        fileToWrite << "СКО: " << sqrt(disp) << endl;
        fileToWrite << "Среднее отклонение: " << 0.477*sqrt(2)*sqrt(disp) << endl;
        double mimoment3 = midMoment3(outMatrix, numberOfUnique);
        double mimoment4 = midmoment4(outMatrix, numberOfUnique);
        fileToWrite << "Центральный момент третьего порядка: " << mimoment3 << endl;
        fileToWrite << "Центральный момент четвёртого порядка: " << mimoment4 << endl;
        fileToWrite << "Коэффициент ассиметрии: " << mimoment3/pow(sqrt(disp), 3) << endl;
        fileToWrite << "Коэффициент эксцесса: " << 3-mimoment4/pow(sqrt(disp), 4) << endl;
        fileToWrite << endl << endl;
        fileToWrite << setw(15) << "Данные " << setw(25) << "Уникальные " << setw(18) << "Частота " << setw(10) << "Данные*Чаcтота " << setw(10) << "ОтнЧа " << setw(18) << "ОтнНакопЧаст " << setw(14) << "Вторая " << setw(16) << "Третья " << setw(23) << "Четвёртая " << endl;
        for(int i = 0; i < numberOfUnique; i++){
            for(int j = 0; j < M; j++){
                fileToWrite << setw(10) << setprecision(4) << outMatrix[i][j] << " ";
            }
            fileToWrite << endl;
        }
        for(int i = numberOfUnique; i < N; i++){
            fileToWrite << setw(10) << outMatrix[i][0] << " ";
            fileToWrite << endl;
        }
    }
    fileToWrite.close();
    histogramToFile(outMatrix, numberOfUnique, fileName);
    empericFunctionToFile(outMatrix, numberOfUnique, fileName);
}


