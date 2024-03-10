#include <QPaintEvent>
#include <QTransform>
#include <QPolygonF>
#include <QPainter>
#include <QPointF>
#include <QtGui>
#include "Compass.h"


Compass::Compass(QWidget *parent)
    : QWidget{parent}
{}


void Compass::draw_frame(QPainter * painter)
{
    painter->drawRect(0, 0, this->width() - 1, this->height() - 1);
}


void Compass::draw_circuit(QPainter * painter)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(
        0 + this->padding,
        0 + this->padding,
        this->width() - this->padding * 2,
        this->height() - this->padding * 2
    );
    painter->setBrush(Qt::gray);
    painter->drawEllipse(
        0 + this->padding * 3,
        0 + this->padding * 3,
        this->width() - this->padding * 6,
        this->height() - this->padding * 6
    );
}


void Compass::draw_arrow(QPainter * painter)
{
    QPolygonF arrowUp, arrowDown;
    QPointF center = QPointF(this->width() / 2, this->height() / 2);
    // left-mid, top, right-mid
    arrowUp << QPointF(center.x() + this->padding / 2, center.y())
            << QPointF(center.x(), this->padding * 4)
            << QPointF(center.x() - this->padding / 2, center.y());
    // left-mid, bot, right-mid
    arrowDown << QPointF(center.x() + this->padding / 2, center.y())
              << QPointF(center.x(), this->height() - this->padding * 4)
              << QPointF(center.x() - this->padding / 2, center.y());
    arrowUp = QTransform().translate(center.x(), center.y()).rotate(this->corner).translate(-center.x(), -center.y()).map(arrowUp);
    arrowDown = QTransform().translate(center.x(), center.y()).rotate(this->corner).translate(-center.x(), -center.y()).map(arrowDown);

    painter->setBrush(Qt::blue);
    painter->drawPolygon(arrowUp);
    painter->setBrush(Qt::red);
    painter->drawPolygon(arrowDown);

    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(center, this->padding / 2, this->padding / 2);
}


void Compass::draw_division_scale(QPainter * painter)
{
    painter->setBrush(Qt::black);
    QPointF center = QPointF(this->width() / 2, this->height() / 2);
    QLine scale1(center.x(), this->padding * 3, center.x(), this->padding * 6);
    QLine scale2(center.x(), this->padding * 3, center.x(), this->padding * 5.5);
    QLine scale3(center.x(), this->padding * 3, center.x(), this->padding * 5);
    QLine scale4(center.x(), this->padding * 3, center.x(), this->padding * 4);
    for (int corner = 0; corner < 380; ++corner)
    {
        QLine line;
        if (corner % 90 == 0)        line = scale1;
        else if (corner % 45 == 0)   line = scale2;
        else if (corner % 5 == 0)    line = scale4;
        painter->drawLine(QTransform().translate(center.x(), center.y()).rotate(corner).translate(-center.x(), -center.y()).map(line));
        if (corner % 45 == 0)
            painter->drawLine(QTransform().translate(center.x(), center.y()).rotate(corner - 22.5).translate(-center.x(), -center.y()).map(scale3));
    }
}


void Compass::draw_char_sides(QPainter * painter)
{
    QPointF center = QPointF(this->width() / 2, this->height() / 2);

    QFont font = painter->font();
    font.setPixelSize(18);
    painter->setFont(font);

    QPoint top = QPoint(center.x() - 7, this->padding * 3 - 4),
        bot = QPoint(center.x() - 5, this->height() - this->padding - 4),
        left = QPoint(this->padding + 2, center.y() + 5),
        right = QPoint(this->height() - this->padding * 2 - 5, center.y() + 5);

    painter->drawText(left, QString::fromUtf8("W"));
    painter->drawText(top, QString::fromUtf8("N"));
    painter->drawText(right, QString::fromUtf8("E"));
    painter->drawText(bot, QString::fromUtf8("S"));
}


void Compass::set_corner(int corner)
{
    this->corner = corner;
    repaint();
}


void Compass::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    this->draw_frame(&painter);
    this->draw_circuit(&painter);
    this->draw_char_sides(&painter);
    this->draw_division_scale(&painter);
    this->draw_arrow(&painter);
    painter.end();
}
