#include "../headers/mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    openGLWidget = new OpenGLWidget(this);
    settingsWidget = new SettingsWidget(this);
    settingsWidget->setFixedWidth(200);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(settingsWidget);
    layout->addWidget(openGLWidget);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), openGLWidget, SLOT(timeUpdate()));
    timer->start(100);

    connect(settingsWidget, SIGNAL(projectionValueSet(bool)), openGLWidget, SLOT(changeProjection(bool)));
    connect(settingsWidget, SIGNAL(materialValueSet(const QString &)), openGLWidget, SLOT(changeMaterial(const QString &)));
    connect(settingsWidget, SIGNAL(lightTypeValueSet(const QString &)), openGLWidget, SLOT(changeLightType(const QString &)));
    connect(settingsWidget, SIGNAL(lightPositionValueSet(int)), openGLWidget, SLOT(changeLightPosition(int)));
}
