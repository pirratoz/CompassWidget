#ifndef COMPASS_H
#define COMPASS_H

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>


class Compass : public QWidget
{
    Q_OBJECT
public:
    explicit Compass(QWidget *parent = nullptr);

public:
    int padding = 10;
    int corner = 0;

private:
    void draw_frame(QPainter * painter);
    void draw_circuit(QPainter * painter);
    void draw_char_sides(QPainter * painter);
    void draw_arrow(QPainter * painter);
    void draw_division_scale(QPainter * painter);

protected:
    void paintEvent(QPaintEvent * event);

public:
    void set_corner(int corner);
};

#endif // COMPASS_H
