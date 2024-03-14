#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include"Serial/Serialer.h"
#include"bluetoothitem.h"
#include"BlueTooth/BlueTooth.h"
#include"vmotorcontroler.h"
#include<list>

class CKernel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool m_isConnect;
    explicit MainWindow(CKernel* ker,QWidget *parent = 0);
    ~MainWindow();
    void init();
    void RefreshCOM(QStringList PortList);
    void BLTConnecting(QBluetoothDeviceInfo info);
    void BLTConnected(QBluetoothDeviceInfo info);
    void BLTConnectedError();
    void BlueToothDevDiscovered(QBluetoothDeviceInfo info);
    void BlueToothDisConnect();
    void FinishSearch();
    void StartSearch();
    void BLTRecv(QByteArray content);
    QBluetoothDeviceInfo FindDev(QBluetoothAddress addr);
signals:
    void sig_SendText(QString);
    void sig_ConnectCOM(QString,int,int,int,int,int);
public slots:


private slots:
    void on_PB_SENDTEXT_COM_clicked();

    void on_PB_CONNECT_COM_clicked();

    void on_PB_SEARCHBLT_clicked();

    void on_PB_BLTBREAK_clicked();

    void on_PB_BLTSEND_clicked();

    void on_CB_BLTTEXTMODE_RECV_currentTextChanged(const QString &arg1);

    void on_CB_BLTTEXTMODE_SEND_currentTextChanged(const QString &arg1);

    void on_CB_BLTAPPEND_currentTextChanged(const QString &arg1);

    void on_PB_OPENVMOTOR_clicked();

private:
    Ui::MainWindow *ui;
    QLayout* m_pBlueToothLayout;
    QLayout* m_pBlueToothLayoutPair;
    list<BlueToothItem*> m_lstBLTitems;
    list<BlueToothItem*> m_lstBLTitemsPair;
    CKernel* m_pKer;
    VMotorControler* m_VMControler;
    QString m_SendMode;
    QString m_RecvMode;
    QString m_AppendMode;


};

#endif // MAINWINDOW_H
