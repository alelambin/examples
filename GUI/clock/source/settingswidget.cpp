#include "../headers/settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {
    QLabel *projectionLabel = new QLabel("Проецирование:", this);
    projectionButtonGroup = new QButtonGroup(this);
    QRadioButton *projectionOrthoButton = new QRadioButton("Ортогональное", this);
    QRadioButton *projectionFrustumButton = new QRadioButton("Перспективное", this);
    projectionButtonGroup->addButton(projectionOrthoButton, 0);
    projectionButtonGroup->addButton(projectionFrustumButton, 1);
    projectionOrthoButton->setChecked(true);

    QLabel *materialLabel = new QLabel("Материал:", this);
    materialComboBox = new QComboBox(this);
    materialComboBox->addItems(materialsRU);

    QLabel *lightTypeLabel = new QLabel("Тип источника:", this);
    lightTypeButtonGroup = new QButtonGroup(this);
    QRadioButton *directionalLightButton = new QRadioButton(lightTypesRU[0], this);
    QRadioButton *pointLightButton = new QRadioButton(lightTypesRU[1], this);
    QRadioButton *spotLightButton = new QRadioButton(lightTypesRU[2], this);
    lightTypeButtonGroup->addButton(directionalLightButton, 0);
    lightTypeButtonGroup->addButton(pointLightButton, 1);
    lightTypeButtonGroup->addButton(spotLightButton, 2);
    directionalLightButton->setChecked(true);

    QLabel *lightPositionLabel = new QLabel("Положение источника света:", this);
    lightPositionSlider = new QSlider(Qt::Horizontal, this);
    lightPositionSlider->setMinimum(10);
    lightPositionSlider->setMaximum(80);
    lightPositionSlider->setValue(45);

    QVBoxLayout *layout = new QVBoxLayout(this);
    /* projection */
    layout->addWidget(projectionLabel);
    layout->addWidget(projectionOrthoButton);
    layout->addWidget(projectionFrustumButton);
    layout->addSpacerItem(new QSpacerItem(1, 30));
    /* material */
    layout->addWidget(materialLabel);
    layout->addWidget(materialComboBox);
    layout->addSpacerItem(new QSpacerItem(1, 30));
    /* light type */
    layout->addWidget(lightTypeLabel);
    layout->addWidget(directionalLightButton);
    layout->addWidget(pointLightButton);
    layout->addWidget(spotLightButton);
    layout->addSpacerItem(new QSpacerItem(1, 30));
    /* light position */
    layout->addWidget(lightPositionLabel);
    layout->addWidget(lightPositionSlider);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    connect(projectionButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
        [=] (QAbstractButton *button) {emit projectionValueSet(projectionButtonGroup->id(button) == 0);});
    connect(materialComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=] (int value) {emit materialValueSet(materials[value]);});
    connect(lightTypeButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
        [=] (QAbstractButton *button) {emit lightTypeValueSet(lightTypes[lightTypeButtonGroup->id(button)]);});
    connect(lightPositionSlider, QOverload<int>::of(&QSlider::valueChanged),
        [=] (int value) {emit lightPositionValueSet(value);});
}
