#include "Application.h"
#include "ui_Application.h"
#include "Compass.h"


Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);
    init_slots();
    compass = new Compass(this);
    compass->setMinimumSize(180, 180);
    compass->move((this->width() - 180) / 2, 10);
}


Application::~Application()
{
    delete ui;
}


void Application::init_slots()
{
    connect(ui->SliderCompass, &QSlider::valueChanged, this, &Application::set_degrees);
}


void Application::set_degrees(int degrees)
{
    ui->LabelDegrees->setText(QString::fromUtf8("Degress: ") + QString::number(degrees));
    compass->set_corner(degrees);
}
