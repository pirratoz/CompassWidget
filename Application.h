#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "Compass.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private:
    Compass *compass;

private:
    void init_slots();

private slots:
    void set_degrees(int degrees);

private:
    Ui::Application *ui;
};
#endif // APPLICATION_H
