#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


int** naiwne(int** Matrix1, int** Matrix2, int** ResultMatrix, int size1, int size2, int size3);
int** strassen(int** Matrix1, int** Matrix2, int** ResultMatrix, int size);
void sum(int** a, int** b, int** result, int size);
void subtract(int** a, int** b, int** result, int size);
int** allocate_real_matrix(int size, int random);
int** free_real_matrix(int** v, int size);

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

    cout << "Podaj wymiar macierzy kwadratowej: ";
    cin >> size1;
    size2 = size1; size3 = size1;

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

    cout << "Koniec algorytmu naiwnego - nacisnij enter zeby zwolnic pamiec";
    cin.clear(); cin.ignore(INT_MAX, '\n');
    cin.get();

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

    cout << "\nPamiec wyczyszczona - nacisnij enter zeby zaczac algorytm Strassena";
    cin.clear(); cin.ignore(INT_MAX, '\n');

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

    ResultMatrix = strassen(Matrix1, Matrix2, ResultMatrix, size1);

    cout << "Koniec algorytmu Strassena - nacisnij enter zeby zwolnic pamiec";
    cin.clear(); cin.ignore(INT_MAX, '\n');

    for (i = 0; i < size1; i++)
    {
        delete[] Matrix1[i];
        delete[] ResultMatrix[i];
    }

    for (i = 0; i < size1; i++) delete[] Matrix2[i];
    delete[] Matrix1;
    delete[] Matrix2;
    delete[] ResultMatrix;

    cout << "\nPamiec wyczyszczona - nacisnij enter zeby zakonczyc.";
    cin.clear(); cin.ignore(INT_MAX, '\n');

    return 0;
}


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

int** strassen(int** Matrix1, int** Matrix2, int** ResultMatrix, int size) {

    // najprostszy przypadek: kiedy macierz ma rozmiar 1 na 1:
    if (size == 1) {
        ResultMatrix[0][0] = Matrix1[0][0] * Matrix2[0][0];
        return ResultMatrix;;
    }

    // pozostałe przypadki:
    else {
        int newSize = size / 2;
        int** a11, ** a12, ** a21, ** a22;
        int** b11, ** b12, ** b21, ** b22;
        int** c11, ** c12, ** c21, ** c22;
        int** p1, ** p2, ** p3, ** p4, ** p5, ** p6, ** p7;

        // alokacja pamięci:
        a11 = allocate_real_matrix(newSize, -1);
        a12 = allocate_real_matrix(newSize, -1);
        a21 = allocate_real_matrix(newSize, -1);
        a22 = allocate_real_matrix(newSize, -1);

        b11 = allocate_real_matrix(newSize, -1);
        b12 = allocate_real_matrix(newSize, -1);
        b21 = allocate_real_matrix(newSize, -1);
        b22 = allocate_real_matrix(newSize, -1);

        c11 = allocate_real_matrix(newSize, -1);
        c12 = allocate_real_matrix(newSize, -1);
        c21 = allocate_real_matrix(newSize, -1);
        c22 = allocate_real_matrix(newSize, -1);

        p1 = allocate_real_matrix(newSize, -1);
        p2 = allocate_real_matrix(newSize, -1);
        p3 = allocate_real_matrix(newSize, -1);
        p4 = allocate_real_matrix(newSize, -1);
        p5 = allocate_real_matrix(newSize, -1);
        p6 = allocate_real_matrix(newSize, -1);
        p7 = allocate_real_matrix(newSize, -1);

        int** aResult = allocate_real_matrix(newSize, -1);
        int** bResult = allocate_real_matrix(newSize, -1);

        int i, j;

        //dzielenie macierzy na cztery podmacierze:
        for (i = 0; i < newSize; i++) {
            for (j = 0; j < newSize; j++) {
                a11[i][j] = Matrix1[i][j];
                a12[i][j] = Matrix1[i][j + newSize];
                a21[i][j] = Matrix1[i + newSize][j];
                a22[i][j] = Matrix1[i + newSize][j + newSize];

                b11[i][j] = Matrix2[i][j];
                b12[i][j] = Matrix2[i][j + newSize];
                b21[i][j] = Matrix2[i + newSize][j];
                b22[i][j] = Matrix2[i + newSize][j + newSize];
            }
        }

        //obliczanie macierzy od M1 do M7:

        sum(a11, a22, aResult, newSize); // a11 + a22
        sum(b11, b22, bResult, newSize); // b11 + b22
        strassen(aResult, bResult, p1, newSize); // p1 = (a11+a22) * (b11+b22)

        sum(a21, a22, aResult, newSize); // a21 + a22
        strassen(aResult, b11, p2, newSize); // p2 = (a21+a22) * (b11)

        subtract(b12, b22, bResult, newSize); // b12 - b22
        strassen(a11, bResult, p3, newSize); // p3 = (a11) * (b12 - b22)

        subtract(b21, b11, bResult, newSize); // b21 - b11
        strassen(a22, bResult, p4, newSize); // p4 = (a22) * (b21 - b11)

        sum(a11, a12, aResult, newSize); // a11 + a12
        strassen(aResult, b22, p5, newSize); // p5 = (a11+a12) * (b22)

        subtract(a21, a11, aResult, newSize); // a21 - a11
        sum(b11, b12, bResult, newSize); // b11 + b12
        strassen(aResult, bResult, p6, newSize); // p6 = (a21-a11) * (b11+b12)

        subtract(a12, a22, aResult, newSize); // a12 - a22
        sum(b21, b22, bResult, newSize); // b21 + b22
        strassen(aResult, bResult, p7, newSize); // p7 = (a12-a22) * (b21+b22)

        //obliczanie c21, c21, c11 i c22:

        sum(p3, p5, c12, newSize); // c12 = p3 + p5
        sum(p2, p4, c21, newSize); // c21 = p2 + p4

        sum(p1, p4, aResult, newSize); // p1 + p4
        sum(aResult, p7, bResult, newSize); // p1 + p4 + p7
        subtract(bResult, p5, c11, newSize); // c11 = p1 + p4 - p5 + p7

        sum(p1, p3, aResult, newSize); // p1 + p3
        sum(aResult, p6, bResult, newSize); // p1 + p3 + p6
        subtract(bResult, p2, c22, newSize); // c22 = p1 + p3 - p2 + p6

        //grupowanie wyników w jedną macierz:
        for (i = 0; i < newSize; i++) {
            for (j = 0; j < newSize; j++) {
                ResultMatrix[i][j] = c11[i][j];
                ResultMatrix[i][j + newSize] = c12[i][j];
                ResultMatrix[i + newSize][j] = c21[i][j];
                ResultMatrix[i + newSize][j + newSize] = c22[i][j];
            }
        }

        //dealokacja pamięci:
        a11 = free_real_matrix(a11, newSize);
        a12 = free_real_matrix(a12, newSize);
        a21 = free_real_matrix(a21, newSize);
        a22 = free_real_matrix(a22, newSize);

        b11 = free_real_matrix(b11, newSize);
        b12 = free_real_matrix(b12, newSize);
        b21 = free_real_matrix(b21, newSize);
        b22 = free_real_matrix(b22, newSize);

        c11 = free_real_matrix(c11, newSize);
        c12 = free_real_matrix(c12, newSize);
        c21 = free_real_matrix(c21, newSize);
        c22 = free_real_matrix(c22, newSize);

        p1 = free_real_matrix(p1, newSize);
        p2 = free_real_matrix(p2, newSize);
        p3 = free_real_matrix(p3, newSize);
        p4 = free_real_matrix(p4, newSize);
        p5 = free_real_matrix(p5, newSize);
        p6 = free_real_matrix(p6, newSize);
        p7 = free_real_matrix(p7, newSize);
        aResult = free_real_matrix(aResult, newSize);
        bResult = free_real_matrix(bResult, newSize);
    } //koniec przypadku else
    return ResultMatrix;
} //koniec funkcji Strassen

//funkcja sumująca dwie macierze
void sum(int** a, int** b, int** result, int size) {

    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

//funkcja odejmująca jedną macierz od drugiej
void subtract(int** a, int** b, int** result, int size) {

    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

// Jeżeli zmienna losowa jest zerem to funkcja inicjalizuje macierz o wartościach zerowych,
// jeżeli jest jedynką to inicjalizuje macierz z losowymi wartościami.
// Jeżeli jest jakąkolwiek inną wartością to macierz jest inicjalizowana bez żadnych wartości
int** allocate_real_matrix(int size, int random) {

    int a, i, j, n = size, m = size;

    // alokuje jeden wektor wektoru (macierz)

    int** v = new int* [n];

    if (v == NULL) {
        cout << "** Blad alokacji macierzy: Niewystarczajaca pamiec **";
        return (NULL);
    }

    // alokacja każdego rzędu macierzy
    for (i = 0; i < n; i++) {
        v[i] = new int[m];
        if (v[i] == NULL) {
            cout << "** Blad: Niewystarczajaca pamiec **";
            free_real_matrix(v, n);
            return (NULL);
        }

        // inicjalizacja macierzy o wartościach zerowych
        if (random == 0) {
            for (j = 0; j < m; j++)
                v[i][j] = 0;
        }

        // inicjalizacja macierzy o wartościach losowych z przedziału od 0 do 10
        else {
            if (random == 1) {
                for (j = 0; j < m; j++) {
                    a = rand();
                    v[i][j] = (a - (int)a) * 10;
                }
            }
        }
    }

    return (v);     // zwraca wskaźnik na wektor.
}

// Ta funkcja dealokuje macierz (zwalnia pamięć)
int** free_real_matrix(int** v, int size) {

    int i;

    if (v == NULL) {
        return (NULL);
    }

    for (i = 0; i < size; i++) {
        if (v[i]) {
            delete[] v[i];  // zwalnia rząd macierzy
            v[i] = NULL;
        }
    }

    delete[] v;  // zwalnia wskaźnik 
    v = NULL;

    return (NULL);   //zwraca wskaźnik NULL 
}