#include "../headers/clock.h"

Clock::Clock() {
    height = 2;
    width = 2;
    depth = 0.7;
    dialRadius = 0.85;

    make();
}

void Clock::updateTime() {
    makeArrows();
}

QVector<float> Clock::vertices() {
    return Object::parseVectors(objectVertex);
}

QVector<float> Clock::normals() {
    return Object::parseVectors(objectNormal);
}

QVector<float> Clock::hourArrow() {
    return Object::parseVectors(hourArrowVertex);
}

QVector<float> Clock::minuteArrow() {
    return Object::parseVectors(minuteArrowVertex);
}

QVector<float> Clock::secondArrow() {
    return Object::parseVectors(secondArrowVertex);
}

QVector<float> Clock::ticks() {
    return Object::parseVectors(ticksVertex);
}

void Clock::make() {
    objectVertex.clear();
    objectNormal.clear();

    bodyOutline.clear();
    float radius = height / 2;
    for (int i = 0; i <= division; i++) {
        QVector2D point(
            radius * qCos(M_PI * (1.0 - 1.0 * i / division)),
            radius * qSin(M_PI * (1.0 - 1.0 * i / division))
        );
        bodyOutline.push_back(point);
    }

    dialOutline.clear();
    int partition = 3 * division / 2;
    for (int i = 0; i <= partition; i++) {
        QVector2D point(
            dialRadius * qCos(M_PI * (5.0 / 4.0 - 3.0 / 2.0 * i / partition)),
            dialRadius * qSin(M_PI * (5.0 / 4.0 - 3.0 / 2.0 * i / partition))
        );
        dialOutline.push_back(point);
    }

    makeBody();
    makeDial();
    makeButton();
    makeTriangle();
    makeArrows();
}

void Clock::makeBody() {
    float radius = height / 2;

    /* side */
    Object::addRectangle(objectVertex, objectNormal,
        {-radius, -radius, -depth / 2},
        {-radius, -radius, depth / 2},
        {-radius, 0, depth / 2},
        {-radius, 0, -depth / 2}
    );
    for (int i = 0; i < bodyOutline.size() - 1; i++) {
        float x0 = bodyOutline[i].x(), x1 = bodyOutline[i + 1].x();
        float y0 = bodyOutline[i].y(), y1 = bodyOutline[i + 1].y();
        Object::addRectangle(objectVertex, objectNormal,
            {x0, y0, -depth / 2},
            {x0, y0, depth / 2},
            {x1, y1, depth / 2},
            {x1, y1, -depth / 2}
        );
    }
    Object::addRectangle(objectVertex, objectNormal,
        {radius, 0, -depth / 2},
        {radius, 0, depth / 2},
        {radius, -radius, depth / 2},
        {radius, -radius, -depth / 2}
    );

    /* back */
    for (int i = 0; i < bodyOutline.size(); i++) {
        if (i < bodyOutline.size() - 1)
            Object::addTriangle(objectVertex, objectNormal,
                {-radius, -radius, -depth / 2},
                {bodyOutline[i].x(), bodyOutline[i].y(), -depth / 2},
                {bodyOutline[i + 1].x(), bodyOutline[i + 1].y(), -depth / 2}
            );
        else
            Object::addTriangle(objectVertex, objectNormal,
                {-radius, -radius, -depth / 2},
                {bodyOutline[i].x(), bodyOutline[i].y(), -depth / 2},
                {radius, -radius, -depth / 2}
            );
    }

    /* front */
    int dialIndex, bodyIndex;
    Object::addRectangle(objectVertex, objectNormal,
        {radius, -radius, depth / 2},
        {dialOutline[dialOutline.size() - 1].x(), dialOutline[dialOutline.size() - 1].y(), depth / 2},
        {dialOutline[0].x(), dialOutline[0].y(), depth / 2},
        {-radius, -radius, depth / 2}
    );
    for (dialIndex = 0; dialOutline[dialIndex + 1].y() < 0; dialIndex++) {
        Object::addTriangle(objectVertex, objectNormal,
            {dialOutline[dialIndex].x(), dialOutline[dialIndex].y(), depth / 2},
            {dialOutline[dialIndex + 1].x(), dialOutline[dialIndex + 1].y(), depth / 2},
            {-radius, -radius, depth / 2}
        );
    }
    Object::addTriangle(objectVertex, objectNormal,
        {-radius, -radius, depth / 2},
        {dialOutline[dialIndex].x(), dialOutline[dialIndex].y(), depth / 2},
        {-radius, 0, depth / 2}
    );
    for (bodyIndex = 0; bodyIndex < bodyOutline.size() - 1; dialIndex++, bodyIndex++) {
        Object::addRectangle(objectVertex, objectNormal,
            {bodyOutline[bodyIndex].x(), bodyOutline[bodyIndex].y(), depth / 2},
            {dialOutline[dialIndex].x(), dialOutline[dialIndex].y(), depth / 2},
            {dialOutline[dialIndex + 1].x(), dialOutline[dialIndex + 1].y(), depth / 2},
            {bodyOutline[bodyIndex + 1].x(), bodyOutline[bodyIndex + 1].y(), depth / 2}
        );
    }
    Object::addTriangle(objectVertex, objectNormal,
        {radius, 0, depth / 2},
        {dialOutline[dialIndex].x(), dialOutline[dialIndex].y(), depth / 2},
        {radius, -radius, depth / 2}
    );
    for (; dialIndex < dialOutline.size() - 1; dialIndex++) {
        Object::addTriangle(objectVertex, objectNormal,
            {dialOutline[dialIndex].x(), dialOutline[dialIndex].y(), depth / 2},
            {dialOutline[dialIndex + 1].x(), dialOutline[dialIndex + 1].y(), depth / 2},
            {radius, -radius, depth / 2}
        );
    }

    /* buttom */
    Object::addRectangle(objectVertex, objectNormal,
        {-radius, -radius, -depth / 2},
        {-radius, -radius, depth / 2},
        {radius, -radius, depth / 2},
        {radius, -radius, -depth / 2}
    );
}

void Clock::makeDial() {
    for (int i = 0; i < dialOutline.size(); i++) {
        if (i < dialOutline.size() - 1) {
            Object::addRectangle(objectVertex, objectNormal,
                {dialOutline[i].x(), dialOutline[i].y(), depth / 2},
                {dialOutline[i].x(), dialOutline[i].y(), (float) (depth / 2 - 0.1)},
                {dialOutline[i + 1].x(), dialOutline[i + 1].y(), (float) (depth / 2 - 0.1)},
                {dialOutline[i + 1].x(), dialOutline[i + 1].y(), depth / 2}
            );
            Object::addTriangle(objectVertex, objectNormal,
                {dialOutline[i].x(), dialOutline[i].y(), (float) (depth / 2 - 0.1)},
                {dialOutline[0].x(), dialOutline[0].y(), (float) (depth / 2 - 0.1)},
                {dialOutline[i + 1].x(), dialOutline[i + 1].y(), (float) (depth / 2 - 0.1)}
            );
        } else {
            Object::addRectangle(objectVertex, objectNormal,
                {dialOutline[i].x(), dialOutline[i].y(), depth / 2},
                {dialOutline[i].x(), dialOutline[i].y(), (float) (depth / 2 - 0.1)},
                {dialOutline[0].x(), dialOutline[0].y(), (float) (depth / 2 - 0.1)},
                {dialOutline[0].x(), dialOutline[0].y(), depth / 2}
            );
        }
    }
}

void Clock::makeArrows() {
    hourArrowVertex.clear();
    minuteArrowVertex.clear();
    secondArrowVertex.clear();
    ticksVertex.clear();

    QTime time = QTime::currentTime();
    float arrowWidth = 0.15;
    float hourLength = 0.2, minuteLength = 0.4, secondLength = 0.45;
    float offset = dialRadius * (1.0 - qSin(M_PI / 3)) / 2;
    float z = depth / 2 - 0.09;

    hourArrowVertex.push_back({arrowWidth / 2, 0, z});
    hourArrowVertex.push_back({0, -arrowWidth / 2, z});
    hourArrowVertex.push_back({-arrowWidth / 2, 0, z});
    hourArrowVertex.push_back({-arrowWidth / 2, hourLength, z});
    hourArrowVertex.push_back({0, hourLength + arrowWidth / 2, z});
    hourArrowVertex.push_back({arrowWidth / 2, hourLength, z});
    rotate(hourArrowVertex, time.hour() * 30 + time.minute() / 2);
    transfer(hourArrowVertex, offset, 0, 1, 0);

    minuteArrowVertex.push_back({arrowWidth / 2, 0, z});
    minuteArrowVertex.push_back({0, -arrowWidth / 2, z});
    minuteArrowVertex.push_back({-arrowWidth / 2, 0, z});
    minuteArrowVertex.push_back({-arrowWidth / 2, minuteLength, z});
    minuteArrowVertex.push_back({0, minuteLength + arrowWidth / 2, z});
    minuteArrowVertex.push_back({arrowWidth / 2, minuteLength, z});
    rotate(minuteArrowVertex, time.minute() * 6);
    transfer(minuteArrowVertex, offset, 0, 1, 0);

    secondArrowVertex.push_back({0, 0, z});
    secondArrowVertex.push_back({0, secondLength, z});
    rotate(secondArrowVertex, time.second() * 6);
    transfer(secondArrowVertex, offset, 0, 1, 0);

    for (int i = 0; i < 12; i++) {
        float x0 = 0.5 * qCos(2.0 * M_PI * i / 12), x1 = 0.6 * qCos(2.0 * M_PI * i / 12);
        float y0 = 0.5 * qSin(2.0 * M_PI * i / 12), y1 = 0.6 * qSin(2.0 * M_PI * i / 12);
        ticksVertex.push_back({x0, y0 + offset, z});
        ticksVertex.push_back({x1, y1 + offset, z});
    }
}

void Clock::makeButton() {
    float dh = 0.15;
    int centerIndex = bodyOutline.size() / 2;
    int startIndex, endIndex;
    startIndex = centerIndex - bodyOutline.size() / 6;
    endIndex = centerIndex + bodyOutline.size() / 6;

    /* left */
    Object::addRectangle(objectVertex, objectNormal,
        {bodyOutline[startIndex].x(), bodyOutline[startIndex].y(), -depth / 2},
        {bodyOutline[startIndex].x(), bodyOutline[startIndex].y(), depth / 2},
        {bodyOutline[startIndex].x(), bodyOutline[startIndex].y() + dh, depth / 2},
        {bodyOutline[startIndex].x(), bodyOutline[startIndex].y() + dh, -depth / 2}
    );
    for (int i = startIndex; i < endIndex; i++) {
        /* up */
        Object::addRectangle(objectVertex, objectNormal,
            {bodyOutline[i].x(), bodyOutline[i].y() + dh, -depth / 2},
            {bodyOutline[i].x(), bodyOutline[i].y() + dh, depth / 2},
            {bodyOutline[i + 1].x(), bodyOutline[i + 1].y() + dh, depth / 2},
            {bodyOutline[i + 1].x(), bodyOutline[i + 1].y() + dh, -depth / 2}
        );

        /* front */
        Object::addTriangle(objectVertex, objectNormal,
            {bodyOutline[i].x(), bodyOutline[i].y() + dh, depth / 2},
            {bodyOutline[startIndex].x(), bodyOutline[startIndex].y(), depth / 2},
            {bodyOutline[i + 1].x(), bodyOutline[i + 1].y() + dh, depth / 2}
        );

        /* back */
        Object::addTriangle(objectVertex, objectNormal,
            {bodyOutline[startIndex].x(), bodyOutline[startIndex].y(), -depth / 2},
            {bodyOutline[i].x(), bodyOutline[i].y() + dh, -depth / 2},
            {bodyOutline[i + 1].x(), bodyOutline[i + 1].y() + dh, -depth / 2}
        );
    }

    /* right */
    Object::addRectangle(objectVertex, objectNormal,
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y() + dh, -depth / 2},
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y() + dh, depth / 2},
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y(), depth / 2},
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y(), -depth / 2}
    );

    /* front */
    Object::addTriangle(objectVertex, objectNormal,
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y() + dh, depth / 2},
        {bodyOutline[startIndex].x(), bodyOutline[startIndex].y(), depth / 2},
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y(), depth / 2}
    );

    /* back */
    Object::addTriangle(objectVertex, objectNormal,
        {bodyOutline[startIndex].x(), bodyOutline[startIndex].y(), -depth / 2},
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y() + dh, -depth / 2},
        {bodyOutline[endIndex].x(), bodyOutline[endIndex].y(), -depth / 2}
    );
}

void Clock::makeTriangle() {
    float x0 = width / 2 - 0.2, x1 = width / 2 - 0.4;
    float y0 = 0.2 - height / 2, y1 = 0.4 - height / 2;
    float z0 = depth / 2, z1 = depth / 2 + 0.1;

    Object::addRectangle(objectVertex, objectNormal, {x0, y0, z1}, {x0, y0, z0}, {x0, y1, z0}, {x0, y1, z1});
    Object::addRectangle(objectVertex, objectNormal, {x0, y0, z0}, {x0, y0, z1}, {x1, y0, z1}, {x1, y0, z0});
    Object::addRectangle(objectVertex, objectNormal, {x1, y0, z0}, {x1, y0, z1}, {x0, y1, z1}, {x0, y1, z0});
    Object::addTriangle(objectVertex, objectNormal, {x0, y0, z1}, {x0, y1, z1}, {x1, y0, z1});
}
