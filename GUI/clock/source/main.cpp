#include <QApplication>
#include <QIcon>
#include "../headers/mainwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWidget mainWidget;
    mainWidget.resize(800, 600);
    mainWidget.setWindowTitle("clock");
    mainWidget.setWindowIcon(QIcon(":/img/icon.png"));
    mainWidget.show();

    return a.exec();
}
