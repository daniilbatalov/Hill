#ifndef HILL_H
#define HILL_H

#include <iostream>
#include <QString>
#include <QVector>
#include "matrix.h"
#include "vector3.h"
enum LanguageType
{
    EN,
    EN_PRIME,
    RU,
    RU_PRIME,
    CUSTOM
};

class Hill
{
private:
    QString alphabet;
    LanguageType lang;
public:
    Hill();
    Hill(QString, QString, LanguageType);
    QString encode(QString message);
    QString decode(QString message);
    void makePrime();
    Matrix mat;

};

#endif // HILL_H
