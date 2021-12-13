#include "hill.h"

Hill::Hill(){};
Hill::Hill(QString pass, QString alpha, LanguageType lng)
{
    alphabet = alpha;
    lang = lng;
    QVector<int> temp;
    for (int i = 0; i < 9; i++)
    {
        int code = alphabet.indexOf(pass.at(i));
        temp.append(code);
    }
    mat = Matrix(temp, alpha.size());
}
int mod2(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}
QString Hill::encode(QString message)
{
    QVector<Vector3> temp;
    QString result;
    while (message.size() % 3 != 0)
    {
        message.append(alphabet.at(alphabet.size() - 2));
    }
    for (int i = 0; i < message.size(); i+=3)
    {
        temp.append(Vector3(alphabet.indexOf(message.at(i)),alphabet.indexOf(message.at(i + 1)),alphabet.indexOf(message.at(i + 2))));
    }
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i] = temp[i] * mat;
        temp[i].x(mod2(temp[i].x(), mat.get_modulo()));
        temp[i].y(mod2(temp[i].y(), mat.get_modulo()));
        temp[i].z(mod2(temp[i].z(), mat.get_modulo()));
        result.append(alphabet.at(temp[i].x()));
        result.append(alphabet.at(temp[i].y()));
        result.append(alphabet.at(temp[i].z()));
    }
    return result;
}
QString Hill::decode(QString message)
{
    QVector<Vector3> temp;
    QString result;
    while (message.size() % 3 != 0)
    {
        message.append(alphabet.back());
    }
    for (int i = 0; i < message.size(); i+=3)
    {
        temp.append(Vector3(alphabet.indexOf(message.at(i)),alphabet.indexOf(message.at(i + 1)),alphabet.indexOf(message.at(i + 2))));
    }
    Matrix inv = mat.inverse();
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i] = temp[i] * inv;
        temp[i].x(mod2(temp[i].x(), inv.get_modulo()));
        temp[i].y(mod2(temp[i].y(), inv.get_modulo()));
        temp[i].z(mod2(temp[i].z(), inv.get_modulo()));
        result.append(alphabet.at(temp[i].x()));
        result.append(alphabet.at(temp[i].y()));
        result.append(alphabet.at(temp[i].z()));
    }
    return result;
}
void Hill::makePrime()
{
    switch (lang)
    {
    case EN:
    {
        alphabet.append(".? ");
        lang = EN_PRIME;
        mat.add_modulo(3);
        mat.updateDeterminant();
        break;
    }
    case RU:
    {
        alphabet.append("., ?");
        lang = RU_PRIME;
        mat.add_modulo(4);
        mat.updateDeterminant();
        break;
    }
    default:
    {
        std::cout << "Cannot make the size of the alphabet prime." << std::endl;
        break;
    }
    }
}
