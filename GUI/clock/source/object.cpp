#include "../headers/object.h"

Material Object::material(const QString name) {
    if (name.toLower() == "emerald")
        return Material{
            {0.0215, 0.1745, 0.0215},
            {0.07568, 0.61424, 0.07568},
            {0.633, 0.727811, 0.633},
            0.6
        };
    if (name.toLower() == "pearl")
        return Material{
            {0.25, 0.20725, 0.20725},
            {1.0, 0.829, 0.829},
            {0.296648, 0.296648, 0.296648},
            0.088
        };
    if (name.toLower() == "ruby")
        return Material{
            {0.1745, 0.01175, 0.01175},
            {0.61424, 0.04136, 0.04136},
            {0.727811, 0.626959, 0.626959},
            0.6
        };
    if (name.toLower() == "bronze")
        return Material{
            {0.2125, 0.1275, 0.054},
            {0.714, 0.4284, 0.18144},
            {0.393548, 0.271906, 0.166721},
            0.2
        };
    if (name.toLower() == "chrome")
        return Material{
            {0.25, 0.25, 0.25},
            {0.4, 0.4, 0.4},
            {0.774597, 0.774597, 0.774597},
            0.6
        };
    if (name.toLower() == "copper")
        return Material{
            {0.19125, 0.0735, 0.0225},
            {0.7038, 0.27048, 0.0828},
            {0.256777, 0.137622, 0.086014},
            0.1
        };
    if (name.toLower() == "gold")
        return Material{
            {0.24725, 0.1995, 0.0745},
            {0.75164, 0.60648, 0.22648},
            {0.628281, 0.555802, 0.366065},
            0.4
        };
    if (name.toLower() == "silver")
        return Material{
            {0.19225, 0.19225, 0.19225},
            {0.50754, 0.50754, 0.50754},
            {0.508273, 0.508273, 0.508273},
            0.4
        };
    if (name.toLower() == "white plastic")
        return Material{
            {0.0, 0.0, 0.0},
            {0.55, 0.55, 0.55},
            {0.7, 0.7, 0.7},
            0.25
        };
    if (name.toLower() == "red plastic")
        return Material{
            {0.0, 0.0, 0.0},
            {0.5, 0.0, 0.0},
            {0.7, 0.6, 0.6},
            0.25
        };
    if (name.toLower() == "green plastic")
        return Material{
            {0.0, 0.0, 0.0},
            {0.1, 0.35, 0.1},
            {0.45, 0.55, 0.45},
            0.25
        };
    if (name.toLower() == "cyan plastic")
        return Material{
            {0.0, 0.1, 0.06},
            {0.0, 0.50980392, 0.50980392},
            {0.50196078, 0.50196078, 0.50196078},
            0.25
        };
    if (name.toLower() == "white rubber")
        return Material{
            {0.05, 0.05, 0.05},
            {0.5, 0.5, 0.5},
            {0.7, 0.7, 0.7},
            0.078125
        };
    if (name.toLower() == "yellow rubber")
        return Material{
            {0.05, 0.05, 0.0},
            {0.5, 0.5, 0.4},
            {0.7, 0.7, 0.04},
            0.078125
        };
    throw std::runtime_error("Error: Wrong name");
}

void Object::addTriangle(QVector<QVector3D> &vertices,
                         QVector3D point1, QVector3D point2, QVector3D point3) {
    vertices.push_back(point1);
    vertices.push_back(point2);
    vertices.push_back(point3);
}

void Object::addTriangle(QVector<QVector3D> &vertices, QVector<QVector3D> &normals,
                         QVector3D point1, QVector3D point2, QVector3D point3) {
    Object::addTriangle(vertices, point1, point2, point3);

    QVector3D normal = QVector3D::crossProduct(point2 - point1, point3 - point1);
    Object::addTriangle(normals, normal, normal, normal);
}

void Object::addRectangle(QVector<QVector3D> &vertices,
                          QVector3D point1, QVector3D point2, QVector3D point3, QVector3D point4) {
    Object::addTriangle(vertices, point1, point2, point3);
    Object::addTriangle(vertices, point1, point3, point4);
}

void Object::addRectangle(QVector<QVector3D> &vertices, QVector<QVector3D> &normals,
                          QVector3D point1, QVector3D point2, QVector3D point3, QVector3D point4) {
    Object::addTriangle(vertices, normals, point1, point2, point3);
    Object::addTriangle(vertices, normals, point1, point3, point4);
}

void Object::rotate(QVector<QVector3D> &vector, float angle) {
    QMatrix4x4 rotateMatrix;
    rotateMatrix.rotate(angle, 0, 0, 1);
    for (auto &vec : vector)
        vec = vec * rotateMatrix;
}

void Object::transfer(QVector<QVector3D> &vector, float offset, float x, float y, float z) {
    for (auto &vec : vector)
        vec = vec + offset * QVector3D(x, y, z);
}

QVector<float> Object::parseVectors(QVector<QVector3D> &vector) {
    QVector<float> result = {};
    for (auto vertex : vector) {
        result.push_back(vertex.x());
        result.push_back(vertex.y());
        result.push_back(vertex.z());
    }
    return result;
}
