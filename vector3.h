#ifndef VECTOR3_H
#define VECTOR3_H

#include <QVector>
#include "matrix.h"

class Vector3
{
private:
    QVector<int> vec;
public:
    Vector3(int x, int y, int z);
    Vector3 operator*(const Matrix& m);
    int x();
    int y();
    int z();
    void x(int value);
    void y(int value);
    void z(int value);
};

#endif // VECTOR3_H
