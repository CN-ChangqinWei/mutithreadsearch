#ifndef POLESLIDER_H
#define POLESLIDER_H

#include <QWidget>

namespace Ui {
class PoleSlider;
}

class PoleSlider : public QWidget
{
    Q_OBJECT

public:
    explicit PoleSlider(QWidget *parent = 0);
    ~PoleSlider();

private:
    Ui::PoleSlider *ui;
};

#endif // POLESLIDER_H
