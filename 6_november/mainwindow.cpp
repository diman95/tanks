#include <QtGui>

 #include "mainwindow.h"

 RenderArea::RenderArea(const QPainterPath &path, QWidget *parent)
     : QWidget(parent), path(path)
 {
     penWidth = 1;
     rotationAngle = 0;
     setBackgroundRole(QPalette::Base);
 }

 QSize RenderArea::minimumSizeHint() const
 {
     return QSize(500, 500);
 }

 QSize RenderArea::sizeHint() const
 {
     return QSize(500, 500);
 }

 void RenderArea::setFillRule(Qt::FillRule rule)
 {
     path.setFillRule(rule);
     update();
 }

 void RenderArea::setFillGradient(const QColor &color1, const QColor &color2)
 {
     fillColor1 = color1;
     fillColor2 = color2;
     update();
 }

 void RenderArea::setPenWidth(int width)
 {
     penWidth = width;
     update();
 }

 void RenderArea::setPenColor(const QColor &color)
 {
     penColor = color;
     update();
 }

 void RenderArea::setRotationAngle(int degrees)
 {
     rotationAngle = degrees;

     update();
 }
 void RenderArea::setRotationAngle2(int degrees)
 {
     rotationAngle = degrees % 360;
     update();
 }
 void RenderArea::setVrachenie()
 {
     for(int i=0; i<=100; i++) setRotationAngle2(i);
     update();
 }

 void RenderArea::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     painter.scale(width() / 100.0, height() / 100.0);
     painter.translate(50.0, 50.0);
     painter.rotate(-rotationAngle);
     painter.translate(-50.0, -50.0);

     painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
     QLinearGradient gradient(0, 0, 0, 100);
     gradient.setColorAt(0.0, fillColor1);
     gradient.setColorAt(1.0, fillColor2);
     painter.setBrush(gradient);
     painter.drawPath(path);
 }
