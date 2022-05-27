#ifndef CLOCK_H
#define CLOCK_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QtMath>
#include <QTime>
#include "object.h"

class Clock : protected Object {
public:
    Clock();
    void updateTime();
    QVector<float> vertices();
    QVector<float> normals();
    QVector<float> hourArrow();
    QVector<float> minuteArrow();
    QVector<float> secondArrow();
    QVector<float> ticks();

private:
    void make() override;
    void makeBody();
    void makeDial();
    void makeArrows();
    void makeButton();
    void makeTriangle();

    const QVector3D blackColor = {0.0, 0.0, 0.0};
    const int division = 50;
    float height, width, depth;
    float dialRadius;
    QVector<QVector3D> objectVertex, objectNormal;
    QVector<QVector2D> bodyOutline;
    QVector<QVector2D> dialOutline;
    QVector<QVector3D> hourArrowVertex, minuteArrowVertex, secondArrowVertex;
    QVector<QVector3D> ticksVertex;

};

#endif // CLOCK_H
