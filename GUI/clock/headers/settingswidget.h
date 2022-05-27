#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QSlider>
#include <QSpacerItem>

class SettingsWidget : public QWidget {
    Q_OBJECT

public:
    SettingsWidget(QWidget *parent = nullptr);

signals:
    void projectionValueSet(bool value);
    void materialValueSet(const QString &value);
    void lightTypeValueSet(const QString &value);
    void lightPositionValueSet(int value);

private:
    QButtonGroup *projectionButtonGroup;
    QComboBox *materialComboBox;
    QButtonGroup *lightTypeButtonGroup;
    QSlider *lightPositionSlider;

    const QStringList materials = {"Emerald", "Pearl", "Ruby", "Bronze", "Chrome",
        "Copper", "Gold", "Silver", "White plastic", "Red plastic", "Green plastic",
        "Cyan plastic", "White rubber", "Yellow rubber"};
    const QStringList materialsRU = {"Изумруд", "Жемчуг", "Рубин", "Бронза", "Хром",
        "Медь", "Золото", "Серебро", "Белый пластик", "Красный пластик", "Зелёный пластик",
        "Голубой пластик", "Белая резина", "Жёлтая резина"};
    const QStringList lightTypes = {"Directional", "Point", "Spot"};
    const QStringList lightTypesRU = {"Направленный", "Точечный", "Прожекторный"};

};

#endif // SETTINGSWIDGET_H
