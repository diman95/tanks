#include <QtGui>
#include <math.h>
#include "mainwindow.h"
#include "window.h"
#include <QMouseEvent>

 const float Pi = 3.14159f;

 Window::Window()
 {
     QPainterPath rectPath;
     rectPath.moveTo(20.0, 30.0);
     rectPath.lineTo(80.0, 30.0);
     rectPath.lineTo(80.0, 70.0);
     rectPath.lineTo(20.0, 70.0);
     rectPath.closeSubpath();

     QPainterPath starPath;
     starPath.moveTo(90, 50);
     for (int i = 1; i < 5; ++i) {
         starPath.lineTo(50 + 40 * cos(0.8 * i * Pi),
                         50 + 40 * sin(0.8 * i * Pi));
     }
     starPath.closeSubpath();    void setRotationAngle(int degrees);


     renderAreas = new RenderArea(starPath);


     fillRuleComboBox = new QComboBox;
     fillRuleComboBox->addItem(tr("Odd Even"), Qt::OddEvenFill);
     fillRuleComboBox->addItem(tr("Winding"), Qt::WindingFill);

     fillRuleLabel = new QLabel(tr("Fill &Rule:"));
     fillRuleLabel->setBuddy(fillRuleComboBox);

     fillColor1ComboBox = new QComboBox;
     populateWithColors(fillColor1ComboBox);
     fillColor1ComboBox->setCurrentIndex(
             fillColor1ComboBox->findText("mediumslateblue"));

     fillColor2ComboBox = new QComboBox;
     populateWithColors(fillColor2ComboBox);
     fillColor2ComboBox->setCurrentIndex(
             fillColor2ComboBox->findText("cornsilk"));

     fillGradientLabel = new QLabel(tr("&Fill Gradient:"));
     fillGradientLabel->setBuddy(fillColor1ComboBox);

     fillToLabel = new QLabel(tr("to"));
     fillToLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

     penWidthSpinBox = new QSpinBox;
     penWidthSpinBox->setRange(0, 20);

     penWidthLabel = new QLabel(tr("&Pen Width:"));
     penWidthLabel->setBuddy(penWidthSpinBox);

     penColorComboBox = new QComboBox;
     populateWithColors(penColorComboBox);
     penColorComboBox->setCurrentIndex(
             penColorComboBox->findText("darkslateblue"));

     penColorLabel = new QLabel(tr("Pen &Color:"));
     penColorLabel->setBuddy(penColorComboBox);

     rotationAngleSpinBox = new QSpinBox;
     rotationAngleSpinBox->setRange(0, 359);
     rotationAngleSpinBox->setWrapping(true);
     rotationAngleSpinBox->setSuffix("\xB0");

     rotationAngleLabel = new QLabel(tr("&Rotation Angle:"));
     rotationAngleLabel->setBuddy(rotationAngleSpinBox);

     connect(fillRuleComboBox, SIGNAL(activated(int)),
             this, SLOT(fillRuleChanged()));
     connect(fillColor1ComboBox, SIGNAL(activated(int)),
             this, SLOT(fillGradientChanged()));
     connect(fillColor2ComboBox, SIGNAL(activated(int)),
             this, SLOT(fillGradientChanged()));
     //connect(penColorComboBox, SIGNAL(activated(int)),
       //      this, SLOT(penColorChanged()));

     //for (int i = 0; i < NumRenderAreas; ++i) {
         connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
                 renderAreas, SLOT(setVrachenie()));

         connect(rotationAngleSpinBox, SIGNAL(valueChanged(int)),
                 renderAreas, SLOT(setVrachenie()));
     //}
    //renderAreas->setRotationAngle2(17);
     //mouseMoveEvent();
     //QMouseEvent.x();
     QGridLayout *topLayout = new QGridLayout;
     //for (int i = 0; i < NumRenderAreas; ++i)
         topLayout->addWidget(renderAreas, 0, 0);

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addLayout(topLayout, 0, 0, 1, 4);
     mainLayout->addWidget(rotationAngleLabel, 5, 0);
     mainLayout->addWidget(rotationAngleSpinBox, 5, 1, 1, 3);
     setLayout(mainLayout);

     fillRuleChanged();
     fillGradientChanged();
     penColorChanged();
     penWidthSpinBox->setValue(2);

     //setRotationAngle(17);
     //for (int i=0; i<=150; i++){

     //}
     //RenderArea::setRotationAngle(17);

    setWindowTitle(tr("Painter Paths"));
 }

 void Window::fillRuleChanged()
 {
     Qt::FillRule rule = (Qt::FillRule)currentItemData(fillRuleComboBox).toInt();

     //for (int i = 0; i < NumRenderAreas; ++i)
         renderAreas->setFillRule(rule);
 }

 void Window::fillGradientChanged()
 {
     QColor color1 = qvariant_cast<QColor>(currentItemData(fillColor1ComboBox));
     QColor color2 = qvariant_cast<QColor>(currentItemData(fillColor2ComboBox));

     //for (int i = 0; i < NumRenderAreas; ++i)
         renderAreas->setFillGradient(color1, color2);
 }

 void Window::penColorChanged()
 {
     QColor color = qvariant_cast<QColor>(currentItemData(penColorComboBox));

     //for (int i = 0; i < NumRenderAreas; ++i)
         renderAreas->setPenColor(color);
 }

 void Window::populateWithColors(QComboBox *comboBox)
 {
     QStringList colorNames = QColor::colorNames();
     foreach (QString name, colorNames)
         comboBox->addItem(name, QColor(name));
 }

 QVariant Window::currentItemData(QComboBox *comboBox)
 {
     return comboBox->itemData(comboBox->currentIndex());
 }
