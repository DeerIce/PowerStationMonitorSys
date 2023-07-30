#ifndef CLIENT_H
#define CLIENT_H

#include "ui_client.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <random>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class QTcpSocket;
class QTimer;

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private slots:
    void readData();
    void updateSensorValues();

    void on_Connect_clicked();
    void on_Stable_clicked();
    void on_CriStable_clicked();
    void on_UnStable_clicked();

    void on_Alarm_clicked();

private:
    Ui::client *ui;
    QTcpSocket* tcpSocket;
    bool isConnected;

    QTimer *timer;
    // 用于生成随机数的引擎和分布
    std::default_random_engine generator;
    std::uniform_real_distribution<double> freqDistribution;
    std::uniform_real_distribution<double> voltageDistribution;
    std::uniform_real_distribution<double> currentDistribution;
    std::uniform_real_distribution<double> powerDistribution;
    double frequency;
    double voltage;
    double current;
    double power;
    int time;

    // 报警相关变量
    bool isAlarmTriggered;
    int alarmCounter, flashCounter;
    const int alarmThreshold = 5; // 报警触发阈值，5秒
    const double alarmPercentage = 0.07; // 报警百分比阈值，7%

    QVector<double> timeData;
    QVector<double> frequencyData[2];
    QVector<double> voltageData[2];
    QVector<double> currentData[2];
    QVector<double> powerData[2];

private:
    void change_range_rand_num(double range);
    void showEngineValues(QString Engine);
    void initPlot();
    void Plot(int index);
    void updateAxis();
    void setUi();
    void sendData(QString dataToSend);
    void Connect();

};
#endif // CLIENT_H
