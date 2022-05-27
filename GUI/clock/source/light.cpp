#include "../headers/light.h"

Light::Light(QVector3D position, float size) {
    lightPosition = position;
    lightSize = size;
    make();
}

void Light::setPosition(QVector3D position) {
    lightPosition = position;
    make();
}

QVector3D Light::position() const {
    return lightPosition;
}

QVector<float> Light::vertices() {
    return Object::parseVectors(objectVertex);
}

int Light::modelSize() const {
    return objectVertex.size();
}

void Light::make() {
    auto makeCircle = [=] (float angle) -> QVector<QVector3D> {
        float radius = lightSize * qCos(qDegreesToRadians(angle));
        float yPosition = lightSize * qSin(qDegreesToRadians(angle));
        QVector<QVector3D> circle;
        for (int i = 0; i < division; i++)
            circle.push_back({
                lightPosition.x() + radius * (float) qCos(2 * M_PI / division * i),
                lightPosition.y() + yPosition,
                lightPosition.z() + radius * (float) qSin(2 * M_PI / division * i)
            });
        return circle;
    };

    circles.clear();
    for (int angle = 60; angle >= -60; angle -= 30)
        circles.push_back(makeCircle(1.0 * angle));

    makeSphere();
}

void Light::makeSphere() {
    objectVertex.clear();

    int circleIndex = 0;
    Object::addTriangle(objectVertex,
                        circles[circleIndex][division - 1],
                        {lightPosition.x(), lightPosition.y() + lightSize, lightPosition.z()},
                        circles[circleIndex][0]);
    for (int i = 1; i < circles[circleIndex].size(); i++)
        Object::addTriangle(objectVertex,
                            circles[circleIndex][i - 1],
                            {lightPosition.x(), lightPosition.y() + lightSize, lightPosition.z()},
                            circles[circleIndex][i]);

    for (circleIndex = 0; circleIndex < circles.size() - 1; circleIndex++) {
        Object::addRectangle(objectVertex,
                             circles[circleIndex][division - 1],
                             circles[circleIndex][0],
                             circles[circleIndex + 1][0],
                             circles[circleIndex + 1][division - 1]);
        for (int i = 1; i < circles[circleIndex].size(); i++)
            Object::addRectangle(objectVertex,
                                 circles[circleIndex][i - 1],
                                 circles[circleIndex][i],
                                 circles[circleIndex + 1][i],
                                 circles[circleIndex + 1][i - 1]);
    }

    Object::addTriangle(objectVertex,
                        circles[circleIndex][division - 1],
                        {lightPosition.x(), lightPosition.y() - lightSize, lightPosition.z()},
                        circles[circleIndex][0]);
    for (int i = 1; i < circles[circleIndex].size(); i++)
        Object::addTriangle(objectVertex,
                            circles[circleIndex][i - 1],
                            {lightPosition.x(), lightPosition.y() - lightSize, lightPosition.z()},
                            circles[circleIndex][i]);
}
