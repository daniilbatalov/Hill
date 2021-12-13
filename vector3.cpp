#include "vector3.h"

Vector3::Vector3(int x, int y, int z)
{
    vec.append(x);
    vec.append(y);
    vec.append(z);
}
Vector3 Vector3::operator*(const Matrix& m)
{
    int nx, ny, nz;
    nx = (this->vec.at(0))* m.get_data_i_j(0, 0) + (this->vec.at(1))* m.get_data_i_j(1, 0) + (this->vec.at(2))* m.get_data_i_j(2, 0);
    ny = (this->vec.at(0))* m.get_data_i_j(0, 1) + (this->vec.at(1))* m.get_data_i_j(1, 1) + (this->vec.at(2))* m.get_data_i_j(2, 1);
    nz = (this->vec.at(0))* m.get_data_i_j(0, 2) + (this->vec.at(1))* m.get_data_i_j(1, 2) + (this->vec.at(2))* m.get_data_i_j(2, 2);
    return Vector3(nx, ny, nz);
}
int Vector3::x()
{
    return vec.at(0);
}
int Vector3::y()
{
    return vec.at(1);
}
int Vector3::z()
{
    return vec.at(2);
}
void Vector3::x(int value)
{
    vec[0] = value;
}
void Vector3::y(int value)
{
    vec[1] = value;
}
void Vector3::z(int value)
{
    vec[2] = value;
}
