#ifndef VMOTORCONTROLER_H
#define VMOTORCONTROLER_H
#include"config.h"
#include <QDialog>

class MainWindow;
class CKernel;
namespace Ui {
class VMotorControler;
}

class VMotorControler : public QDialog
{
    Q_OBJECT

public:
    explicit VMotorControler(MainWindow* mwin,CKernel* ker,QWidget *parent = 0);
    ~VMotorControler();
    void SliderRefresh();
    void LineEditRefresh();
    void ValueRefresh();
    void PoleRefresh();

    void ChangePole(QPushButton* button,int type);
    void Step_Init();


private slots:
    void on_pushButton_11_clicked();





    void on_PB_SPEEDRING_clicked();

    void on_PB_ANGLERING_clicked();

    void on_PB_GYRORING_clicked();

    void on_PB_SERVORING_clicked();

    void on_SD_KP_sliderMoved(int position);

    void on_SD_KI_sliderMoved(int position);

    void on_SD_KD_sliderMoved(int position);

    void on_SD_TARGET_sliderMoved(int position);

    void on_LE_KP_textEdited(const QString &arg1);

    void on_LE_KI_textEdited(const QString &arg1);

    void on_LE_KD_textEdited(const QString &arg1);

    void on_LE_TARGET_textEdited(const QString &arg1);

    void on_PB_PLUSKP_clicked();

    void on_PB_REDUCEKP_clicked();

    void on_PB_PLUSKI_clicked();

    void on_PB_REDUCEKI_clicked();

    void on_PB_PLUSKD_clicked();

    void on_PB_REDUCEKD_clicked();

    void on_PB_PLUSTARGET_clicked();

    void on_PB_REDUCETARGET_clicked();

    void on_PB_POLEKP_clicked();

    void on_PB_POLEKI_clicked();

    void on_PB_POLEKD_clicked();

    void on_PB_POLETARGET_clicked();

    void on_PB_SETKP_clicked();

    void on_PB_SETKI_clicked();

    void on_PB_SETKD_clicked();

    void on_PB_SETTARGET_clicked();




    void on_PB_RUNMOTOR_clicked();

    void on_PB_STOPMOTOR_clicked();

private:
    Ui::VMotorControler *ui;
    MainWindow* m_pMain;
    CKernel* m_pKer;
    float m_KpValue[4];
    float m_KiValue[4];
    float m_KdValue[4];
    float m_TargetValue[4];
    float m_MaxValue[4][4];
    int m_Mode;
    int m_Pole[4][4];
    float m_Step[4][4];
    unsigned int m_TypeHead[4][4];

};

#endif // VMOTORCONTROLER_H
