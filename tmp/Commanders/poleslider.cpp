#include "poleslider.h"
#include "ui_poleslider.h"

PoleSlider::PoleSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoleSlider)
{
    ui->setupUi(this);
}

PoleSlider::~PoleSlider()
{
    delete ui;
}
