#ifndef OBJECT_H
#define OBJECT_H

#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include "material.h"

class Object {
public:
    virtual ~Object() = default;
    static Material material(const QString name);

protected:
    virtual void make() = 0;
    static void addTriangle(QVector<QVector3D> &vertices,
                            QVector3D point1, QVector3D point2, QVector3D point3);
    static void addTriangle(QVector<QVector3D> &vertices, QVector<QVector3D> &normals,
                            QVector3D point1, QVector3D point2, QVector3D point3);
    static void addRectangle(QVector<QVector3D> &vertices,
                             QVector3D point1, QVector3D point2, QVector3D point3, QVector3D point4);
    static void addRectangle(QVector<QVector3D> &vertices, QVector<QVector3D> &normals,
                             QVector3D point1, QVector3D point2, QVector3D point3, QVector3D point4);
    static void rotate(QVector<QVector3D> &vector, float angle);
    static void transfer(QVector<QVector3D> &vector, float offset, float x, float y, float z);
    static QVector<float> parseVectors(QVector<QVector3D> &vector);

};

#endif // OBJECT_H
