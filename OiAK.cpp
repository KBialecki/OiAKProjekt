#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int** naiwne(int** Matrix1, int** Matrix2, int** ResultMatrix, int size1, int size2, int size3) {
    int i, j, s, k;
    for (i = 0; i < size1; i++)
        for (j = 0; j < size3; j++)
        {
            s = 0;
            for (k = 0; k < size2; k++) s += Matrix1[i][k] * Matrix2[k][j];
            ResultMatrix[i][j] = s;
        }
    return ResultMatrix;
}

int main()
{
    // randomizacja
    srand((unsigned)time(0));
    int rangeStart = 1, rangeEnd = 100;

    // zmienne macierzowe
    int** Matrix1, ** Matrix2, ** ResultMatrix, size1, size2, size3;
    // reszta
    int i, j, k, s, randomNumber;

    // odczytujemy wymiary macierzy z konsoli (zrobi się ładniej)

    cin >> size1 >> size2 >> size3;

    // tworzymy macierze o odpowiednich rozmiarach (M1 to size1 x size2, M2 to size2 x size3, Result to size1 x size3)

    Matrix1 = new int* [size1];
    Matrix2 = new int* [size2];
    ResultMatrix = new int* [size1];

    for (i = 0; i < size1; i++)
    {
        Matrix1[i] = new int[size2];
        ResultMatrix[i] = new int[size3];
    }

    for (i = 0; i < size2; i++) Matrix2[i] = new int[size3];

    // generujemy dane dla macierzy pierwszej

    for (i = 0; i < size1; i++)
        for (j = 0; j < size2; j++) Matrix1[i][j] = (rand() % rangeEnd) + rangeStart;

    // generujemy dane dla macierzy drugiej

    for (i = 0; i < size2; i++)
        for (j = 0; j < size3; j++) Matrix2[i][j] = (rand() % rangeEnd) + rangeStart;

    cout << endl;

    // mnożymy macierz M1 przez M2 i wynik umieszczamy w ResultMatrix (da się czyściej na pewno)

    ResultMatrix = naiwne(Matrix1, Matrix2, ResultMatrix, size1, size2, size3);

    /*
        strassen
    */


    // zwalniamy pamięć

    for (i = 0; i < size1; i++)
    {
        delete[] Matrix1[i];
        delete[] ResultMatrix[i];
    }

    for (i = 0; i < size2; i++) delete[] Matrix2[i];
    delete[] Matrix1;
    delete[] Matrix2;
    delete[] ResultMatrix;
    return 0;
}
