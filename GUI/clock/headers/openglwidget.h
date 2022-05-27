#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include <QInputEvent>
#include <QtMath>
#include <QDebug>
#include "clock.h"
#include "light.h"
#include "floor.h"

enum LightType {
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT
};

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

public slots:
    void changeProjection(bool value);
    void changeMaterial(const QString &value);
    void changeLightType(const QString &value);
    void changeLightPosition(int value);
    void timeUpdate();

private:
    void drawObject(QOpenGLShaderProgram *shaderProgram,
                    QVector<float> vertices, QVector<float> normals, GLenum mode);
    void drawObject(QOpenGLShaderProgram *shaderProgram,
                    QVector<float> vertices, GLenum mode);
    void initializeShaders(QOpenGLShaderProgram *shaderProgram, QString name);
    void logErrors(QOpenGLShaderProgram *shaderProgram, QString type);

    // for shader
    QOpenGLShaderProgram *clockShaderProgram, *floorShaderProgram, *lightShaderProgram, *depthShaderProgram;
    Clock *clock;
    Floor *floor;
    Light *light;
    QImage textureImage;
    QOpenGLFramebufferObject *depthBuffer;
    GLuint depthBufferHeight, depthBufferWidth;
    QVector2D aspectRatio;
    // for events
    QPoint mousePosition;
    float rotation[2];
    float viewAngle;
    // for settings
    bool isOrtho;
    QString materialName;
    LightType lightType;

};

#endif // OPENGLWIDGET_H
