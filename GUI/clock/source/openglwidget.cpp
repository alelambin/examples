#include "../headers/openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    clockShaderProgram = new QOpenGLShaderProgram(this);
    floorShaderProgram = new QOpenGLShaderProgram(this);
    lightShaderProgram = new QOpenGLShaderProgram(this);
    depthShaderProgram = new QOpenGLShaderProgram(this);

    clock = new Clock();
    floor = new Floor(15, -1.01);
    light = new Light({(float) (3.0 * qCos(M_PI / 4)), (float) (3.0 * qSin(M_PI / 4)), 0.0}, 0.1);

    textureImage = QImage(":/img/floorTexture.jpg");
    depthBufferHeight = depthBufferWidth = 1024;
    aspectRatio = {1, 1};

    rotation[0] = M_PI / 24;
    rotation[1] = 0;
    viewAngle = 3 * M_PI / 4;

    isOrtho = true;
    materialName = "Emerald";
    lightType = DIRECTIONAL_LIGHT;

    setFocusPolicy(Qt::StrongFocus);
}

OpenGLWidget::~OpenGLWidget() {
    delete clock;
    delete light;
    delete floor;
    delete depthBuffer;
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    initializeShaders(clockShaderProgram, "clock");
    initializeShaders(floorShaderProgram, "floor");
    initializeShaders(lightShaderProgram, "light");
    initializeShaders(depthShaderProgram, "depth");

    depthBuffer = new QOpenGLFramebufferObject(depthBufferWidth, depthBufferHeight, QOpenGLFramebufferObject::Depth);
}

void OpenGLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, (GLint)width, (GLint)height);
    if (width > height) {
        aspectRatio.setX(1.0 * width / height);
        aspectRatio.setY(1.0);
    } else {
        aspectRatio.setX(1.0);
        aspectRatio.setY(1.0 * height / width);
    }
}

void OpenGLWidget::paintGL() {
    const float radius = 1.75;
    QVector3D cameraPosition = QVector3D(
        (radius * qCos(rotation[0])) * qCos(viewAngle),
        radius * qSin(rotation[0]),
        (radius * qCos(rotation[0])) * qSin(viewAngle)
    );

    QMatrix4x4 modelMatrix, viewMatrix, projectionMatrix;
    modelMatrix.rotate(rotation[1], {0.0, 1.0, 0.0});
    viewMatrix.lookAt(cameraPosition, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0});
    projectionMatrix.setToIdentity();
    if (isOrtho)
        projectionMatrix.ortho(
            -3.3 * aspectRatio.x(), 3.3 * aspectRatio.x(),
            -3.3 * aspectRatio.y(), 3.3 * aspectRatio.y(),
            -20, 20
        );
    else
        projectionMatrix.frustum(
            -0.75 * aspectRatio.x(), 0.75 * aspectRatio.x(),
            -0.75 * aspectRatio.y(), 0.75 * aspectRatio.y(),
            0.3, 20
        );

    QMatrix4x4 lightViewMatrix, lightProjectionMatrix;
    lightViewMatrix.lookAt(light->position(), {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0});
    lightProjectionMatrix.ortho(-10, 10, -10, 10, -10, 20);

    /* drawing to buffer */
    depthBuffer->bind();

    glViewport(0, 0, depthBufferWidth, depthBufferHeight);
    glClearColor(0.1, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    depthShaderProgram->bind();

    depthShaderProgram->setUniformValue("uLightModel", modelMatrix);
    depthShaderProgram->setUniformValue("uLightView", lightViewMatrix);
    depthShaderProgram->setUniformValue("uLightProjection", lightProjectionMatrix);

    drawObject(depthShaderProgram, clock->vertices(), clock->normals(), GL_TRIANGLES);
    drawObject(depthShaderProgram, floor->vertices(), GL_POLYGON);

    depthShaderProgram->release();
    depthBuffer->release();

    GLuint shadowTexture = depthBuffer->texture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowTexture);

    /* drawing to screen */
    glViewport(0, 0, width(), height());
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* clock drawing */
    clockShaderProgram->bind();

    clockShaderProgram->setUniformValue("uModel", modelMatrix);
    clockShaderProgram->setUniformValue("uView", viewMatrix);
    clockShaderProgram->setUniformValue("uProjection", projectionMatrix);

    clockShaderProgram->setUniformValue("uLightView", lightViewMatrix);
    clockShaderProgram->setUniformValue("uLightProjection", lightProjectionMatrix);

    QVector3D lightColor = QVector3D(1.0, 1.0, 1.0);
    clockShaderProgram->setUniformValue("uLightType", lightType);
    clockShaderProgram->setUniformValue("uLightInnerCut", (float) qCos(qDegreesToRadians(12.5)));
    clockShaderProgram->setUniformValue("uLightOuterCut", (float) qCos(qDegreesToRadians(17.5)));
    clockShaderProgram->setUniformValue("uLightColor", lightColor);
    clockShaderProgram->setUniformValue("uLightPosition", light->position());
    clockShaderProgram->setUniformValue("uCameraPosition", cameraPosition);

    Material material;
    try {
        material = Object::material(materialName);
    } catch(std::runtime_error &exception) {
        qDebug() << exception.what();
    }
    clockShaderProgram->setUniformValue("uMaterial.ambient", material.ambient);
    clockShaderProgram->setUniformValue("uMaterial.diffuse", material.diffuse);
    clockShaderProgram->setUniformValue("uMaterial.specular", material.specular);
    clockShaderProgram->setUniformValue("uMaterial.shininess", material.shininess * 128);

    drawObject(clockShaderProgram, clock->vertices(), clock->normals(), GL_TRIANGLES);

    clockShaderProgram->setUniformValue("uMaterial.ambient", QVector3D(0.0, 0.0, 0.0));
    clockShaderProgram->setUniformValue("uMaterial.diffuse", QVector3D(0.01, 0.01, 0.01));
    clockShaderProgram->setUniformValue("uMaterial.specular", QVector3D(0.5, 0.5, 0.5));
    clockShaderProgram->setUniformValue("uMaterial.shininess", 0.25f * 128);

    drawObject(clockShaderProgram, clock->hourArrow(), GL_LINE_LOOP);
    drawObject(clockShaderProgram, clock->minuteArrow(), GL_LINE_LOOP);
    drawObject(clockShaderProgram, clock->secondArrow(), GL_LINE_LOOP);
    drawObject(clockShaderProgram, clock->ticks(), GL_LINES);

    clockShaderProgram->release();

    /* floor drawing */
    floorShaderProgram->bind();

    floorShaderProgram->setUniformValue("uModel", QMatrix4x4());
    floorShaderProgram->setUniformValue("uView", viewMatrix);
    floorShaderProgram->setUniformValue("uProjection", projectionMatrix);

    floorShaderProgram->setUniformValue("uLightView", lightViewMatrix);
    floorShaderProgram->setUniformValue("uLightProjection", lightProjectionMatrix);

    floorShaderProgram->setUniformValue("uLightType", lightType);
    floorShaderProgram->setUniformValue("uLightInnerCut", (float) qCos(qDegreesToRadians(12.5)));
    floorShaderProgram->setUniformValue("uLightOuterCut", (float) qCos(qDegreesToRadians(17.5)));
    floorShaderProgram->setUniformValue("uLightColor", lightColor);
    floorShaderProgram->setUniformValue("uLightPosition", light->position());
    floorShaderProgram->setUniformValue("uCameraPosition", cameraPosition);

    QOpenGLTexture *texture = new QOpenGLTexture(textureImage);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    texture->setAutoMipMapGenerationEnabled(true);
    texture->bind(1);

    floorShaderProgram->setUniformValue("uShadowMap", GL_TEXTURE0 - GL_TEXTURE0);
    floorShaderProgram->setUniformValue("uTexture", GL_TEXTURE1 - GL_TEXTURE0);

    drawObject(floorShaderProgram, floor->vertices(), GL_POLYGON);
    texture->release();
    floorShaderProgram->release();
    delete texture;

    /* light drawing */
    lightShaderProgram->bind();

    lightShaderProgram->setUniformValue("uModel", QMatrix4x4());
    lightShaderProgram->setUniformValue("uView", viewMatrix);
    lightShaderProgram->setUniformValue("uProjection", projectionMatrix);

    lightShaderProgram->setUniformValue("uColor", lightColor);

    drawObject(lightShaderProgram, light->vertices(), GL_TRIANGLES);
    lightShaderProgram->release();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    mousePosition = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (qAbs(event->pos().y() - mousePosition.y()) >= qAbs(event->pos().x() - mousePosition.x())) {
        GLfloat angle = 0.1 / M_PI * (event->pos().y() - mousePosition.y());
        if (rotation[0] + angle > M_PI / 3)
            rotation[0] = M_PI / 3;
        else if (rotation[0] + angle < M_PI / 24)
            rotation[0] = M_PI / 24;
        else
            rotation[0] += angle;
    } else {
        rotation[1] += 1 / M_PI * (event->pos().x() - mousePosition.x());
    }
    mousePosition = event->pos();
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_A:
        case Qt::Key_Left:
            viewAngle += M_PI / 32;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            viewAngle -= M_PI / 32;
            break;
        default:
            break;
    }
    if (viewAngle > 2 * M_PI)
        viewAngle -= 2 * M_PI;
    if (viewAngle < 0)
        viewAngle += 2 * M_PI;
    update();
}

void OpenGLWidget::changeProjection(bool value) {
    isOrtho = value;
    update();
}

void OpenGLWidget::changeMaterial(const QString &value) {
    materialName = value;
    update();
}

void OpenGLWidget::changeLightType(const QString &value) {
    if (value.toLower() == "directional")
        lightType = DIRECTIONAL_LIGHT;
    else if (value.toLower() == "point")
        lightType = POINT_LIGHT;
    else if (value.toLower() == "spot")
        lightType = SPOT_LIGHT;
    else
        qDebug() << "ERROR: Wrong light type";
    update();
}

void OpenGLWidget::changeLightPosition(int value) {
    float lightAngle = M_PI / 180 * value;
    light->setPosition({
        (float) (3.0 * qCos(lightAngle)),
        (float) (3.0 * qSin(lightAngle)),
        0.0
    });
    update();
}

void OpenGLWidget::timeUpdate() {
    clock->updateTime();
    update();
}

void OpenGLWidget::drawObject(QOpenGLShaderProgram *shaderProgram,
                              QVector<float> vertices, QVector<float> normals, GLenum mode) {
    shaderProgram->setAttributeArray("aPosition", vertices.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("aNormal", normals.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("aPosition");
    shaderProgram->enableAttributeArray("aNormal");

    glDrawArrays(mode, 0, vertices.size() / 3);

    shaderProgram->disableAttributeArray("aPosition");
    shaderProgram->disableAttributeArray("aNormal");
}

void OpenGLWidget::drawObject(QOpenGLShaderProgram *shaderProgram, QVector<float> vertices, GLenum mode) {
    shaderProgram->setAttributeArray("aPosition", vertices.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("aPosition");

    glDrawArrays(mode, 0, vertices.size() / 3);

    shaderProgram->disableAttributeArray("aPosition");
}

void OpenGLWidget::initializeShaders(QOpenGLShaderProgram *shaderProgram, QString name) {
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/" + name + ".vert"))
        logErrors(shaderProgram, "Vertex");
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/" + name + ".frag"))
        logErrors(shaderProgram, "Fragment");
    if (!shaderProgram->link())
        logErrors(shaderProgram, "Program");
    for (auto shader : shaderProgram->shaders())
        glDeleteShader(shader->shaderId());
}

void OpenGLWidget::logErrors(QOpenGLShaderProgram *shaderProgram, QString type) {
    if (type != "Program") {
        const char *log = QString("ERROR: " + type + " shader not succesfully compiled").toLatin1();
        qDebug() << log;
        qDebug() << shaderProgram->log();
    } else {
        const char *log = QString("ERROR: " + type + " shader not succesfully linked").toLatin1();
        qDebug() << log;
        qDebug() << shaderProgram->log();
    }
}
