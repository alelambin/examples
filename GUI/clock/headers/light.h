#ifndef LIGHT_H
#define LIGHT_H

#include <QVector>
#include <QVector3D>
#include <QtMath>
#include "object.h"

class Light : protected Object {
public:
    Light(QVector3D position, float size);
    void setPosition(QVector3D position);
    QVector3D position() const;
    QVector<float> vertices();
    int modelSize() const;

private:
    virtual void make() override;
    void makeSphere();

    const int division = 10;
    QVector3D lightPosition;
    float lightSize;
    QVector<QVector3D> objectVertex;
    QVector<QVector<QVector3D>> circles;

};

#endif // LIGHT_H
