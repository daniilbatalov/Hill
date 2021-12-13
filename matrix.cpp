#include "matrix.h"
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}
Matrix::Matrix()
{

}
Matrix::Matrix(QVector<int> arr, int m)
{
    for (int i = 0; i < 9; i++)
    {
        data[i / 3][i % 3] = arr.at(i);
    }
    modulo = m;
    det = this->Determinant();
    if (det == 0)
    {
        wrong_key = true;
    }
    else
    {
        wrong_key = false;
    }

}
int det2x2(QVector<QVector<int>> a)
{
    return (a[0][0]*a[1][1] - a[0][1]*a[1][0]);
}
int Matrix::Determinant()
{
    int a11 = this->data[0][0];
    int a12 = this->data[0][1];
    int a13 = this->data[0][2];
    int a21 = this->data[1][0];
    int a22 = this->data[1][1];
    int a23 = this->data[1][2];
    int a31 = this->data[2][0];
    int a32 = this->data[2][1];
    int a33 = this->data[2][2];
    int d = (a11 * a22 * a33 + a13 * a21 * a32 + a12 * a23 * a31 - a13 * a22 * a31 - a11 * a23 * a32 - a12 * a21 * a33);
    return mod(d, modulo);
}
int Minor(QVector<QVector<int>> arr, int i, int j)
{
    QVector<QVector<int>> temp;
    for (int ic = 0; ic < 3; ic++)
    {
        QVector<int> int_temp;
        for(int jc = 0; jc < 3; jc++)
        {
            if (i == ic || j == jc)
            {
                continue;
            }
            else
            {
                int_temp.append(arr.at(ic).at(jc));
            }
        }
        if(!int_temp.empty())
        {
            temp.append(int_temp);
        }
    }
    return ((i + j) % 2 == 0) ? det2x2(temp) : -1 * det2x2(temp);
}
int gcd (int a, int b, int &x, int &y)
{
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
Matrix Matrix::inverse()
{
    int x, y;
    gcd(det, modulo, x, y);
    //x = (x % modulo + modulo) % modulo;
    x = mod(x, modulo);
    int adj[3][3];
    QVector<QVector<int>> temp_data;
    for (int i = 0; i < 3; i++)
    {
        QVector<int> int_temp;
        for (int j = 0; j < 3; j++)
        {
            int_temp.append(data[i][j]);
        }
        temp_data.append(int_temp);
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            adj[i][j] = mod((Minor(temp_data, i, j) * x), modulo);
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = i; j < 3; j++)
        {
            int temp = adj[i][j];
            adj[i][j] = adj[j][i];
            adj[j][i] = temp;
        }
    }
    QVector<int> adj_data;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            adj_data.append(adj[i][j]);
        }
    }
    return Matrix(adj_data, modulo);
}
void Matrix::print_data()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int Matrix::get_data_i_j(int i, int j) const
{
    return data[i][j];
}
void Matrix::add_modulo(int value)
{
    modulo += value;
}
int Matrix::get_modulo()
{
    return modulo;
}
void Matrix::updateDeterminant()
{
    det = this->Determinant();
    wrong_key = (det == 0) ? true : false;
}
