#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <iostream>

class Matrix
{
private:
    int data[3][3];
    int det;
    int modulo;
public:
    Matrix();
    Matrix(QVector<int> data,  int m);
    int Determinant();
    Matrix inverse();
    void print_data();
    bool wrong_key;
    int get_data_i_j(int i, int j) const;
    void add_modulo(int value);
    int get_modulo();
    void updateDeterminant();

};

#endif // MATRIX_H
