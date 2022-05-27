#ifndef FLOOR_H
#define FLOOR_H

#include <QVector>
#include <QVector3D>
#include <QtMath>
#include "object.h"

class Floor : protected Object {
public:
    Floor(float radius, float yPosition);
    QVector<float> vertices();

private:
    virtual void make() override;

    const int division = 50;
    float floorRadius, floorPosition;
    QVector<QVector3D> objectVertex;

};

#endif // FLOOR_H
