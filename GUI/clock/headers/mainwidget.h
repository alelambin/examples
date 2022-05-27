#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include "openglwidget.h"
#include "settingswidget.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);

private:
    OpenGLWidget *openGLWidget;
    SettingsWidget *settingsWidget;
    QTimer *timer;

};

#endif // MAINWIDGET_H
