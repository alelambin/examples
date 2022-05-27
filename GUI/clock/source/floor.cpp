#include "../headers/floor.h"

Floor::Floor(float radius, float yPosition) {
    floorRadius = radius;
    floorPosition = yPosition;
    make();
}

QVector<float> Floor::vertices() {
    return Object::parseVectors(objectVertex);
}

void Floor::make() {
    objectVertex.clear();

    for (int i = 0; i < division; i++)
        objectVertex.push_back({
            floorRadius * (float) qCos(2 * M_PI * i / division),
            floorPosition,
            floorRadius * (float) qSin(2 * M_PI * i / division)
        });
}
