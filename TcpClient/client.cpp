#include "client.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    isConnected = false;
    ui->Connect->setText("Connect");

    timer = new QTimer(this);
    timer->start(1000);

    // 初始化随机数生成器和分布
    std::random_device rd;
    generator = std::default_random_engine(rd());
    freqDistribution = std::uniform_real_distribution<double>(49.0, 51.0);
    voltageDistribution = std::uniform_real_distribution<double>(218.0, 222.0);
    currentDistribution = std::uniform_real_distribution<double>(88, 92);

    time = 0;
    isAlarmTriggered = false;
    alarmCounter = 0;

    setUi();
    Connect();
    initPlot();
}

client::~client()
{
    delete ui;
    delete tcpSocket;
    delete timer;
}

void client::readData()
{
    QByteArray data = tcpSocket->readAll();

    //ui->Engine1->append("Received data: " + data);
}

void client::sendData(QString dataToSend)
{
    if (isConnected) {
        QByteArray sendDataBytes = dataToSend.toUtf8();
        tcpSocket->write(sendDataBytes);
    }
}

void client::updateSensorValues()
{
    timeData.append(time);
    time ++;
    showEngineValues("Engine1");
    showEngineValues("Engine2");

    // Alarm
    if (!isAlarmTriggered) {
        double freqChangePercentage = std::abs((frequency - 50) / 50);
        double voltageChangePercentage = std::abs((voltage - 220) / 220);
        double currentChangePercentage = std::abs((current - 90) / 90);

        if (freqChangePercentage > alarmPercentage || voltageChangePercentage > alarmPercentage || currentChangePercentage > alarmPercentage) {
            alarmCounter++;
        } else {
            alarmCounter = flashCounter = 0;
        }

        if (alarmCounter >= alarmThreshold) {
            isAlarmTriggered = true;
            ui->Alarm->setStyleSheet("background-color: red; font: 18pt \"Candara\"; border: 2px solid black; border-radius: 50px; padding: 10px;");
        }
    } else {
        if(flashCounter == 0){
            ui->Alarm->setStyleSheet("background-color: red; font: 18pt \"Candara\"; border: 2px solid black; border-radius: 50px; padding: 10px;");
            flashCounter++;
        } else {
            ui->Alarm->setStyleSheet("background-color: gray; font: 18pt \"Candara\"; border: 2px solid black; border-radius: 50px; padding: 10px;");
            flashCounter--;
        }
    }
}

void client::change_range_rand_num(double range){
    freqDistribution = std::uniform_real_distribution<double>(50.0*(1-range), 50.0*(1+range));
    voltageDistribution = std::uniform_real_distribution<double>(220.0*(1-range), 220.0*(1+range));
    currentDistribution = std::uniform_real_distribution<double>(90*(1-range), 90*(1+range));
};

void client::showEngineValues(QString Engine){
    // 生成随机数
    frequency = freqDistribution(generator);
    voltage = voltageDistribution(generator);
    current = currentDistribution(generator);
    power = voltage * current / 1000;

    // 固定字段宽度对齐数据
    QString freqStr = QString("Frequency: %1 Hz").arg(frequency, 10, 'f', 2, QChar(' '));
    QString voltageStr = QString("Voltage  : %1 V").arg(voltage, 10, 'f', 2, QChar(' '));
    QString currentStr = QString("Current  : %1 A").arg(current, 10, 'f', 2, QChar(' '));
    QString powerStr = QString("Power    : %1 KW").arg(power, 10, 'f', 2, QChar(' '));

    // 将参数标识为Engine1或Engine2
    QString dataToSend = (Engine == "Engine1") ? "Engine1," : "Engine2,";
    dataToSend += QString::number(frequency, 'f', 2) + "," + QString::number(voltage, 'f', 2) + ","
                + QString::number(current, 'f', 2) + "," + QString::number(power, 'f', 2) + "\n";
    sendData(dataToSend);

    if(Engine=="Engine1"){
        ui->Engine1->clear();
        ui->Engine1->append(freqStr);
        ui->Engine1->append(voltageStr);
        ui->Engine1->append(currentStr);
        ui->Engine1->append(powerStr);
        Plot(0);
        sendData("");
    }
    if(Engine=="Engine2"){
        ui->Engine2->clear();
        ui->Engine2->append(freqStr);
        ui->Engine2->append(voltageStr);
        ui->Engine2->append(currentStr);
        ui->Engine2->append(powerStr);
        Plot(1);
        sendData("");
    }
}

void client::initPlot() {
    //======= Voltage =======================================
    ui->Voltage->xAxis->setLabel("Time (s)");
    ui->Voltage->yAxis->setLabel("Voltage (V)");
    ui->Voltage->xAxis->setRange(0, 30); // 设置x轴范围
    ui->Voltage->yAxis->setRange(180, 250); // 设置y轴范围

    ui->Voltage->addGraph();
    ui->Voltage->graph(0)->setPen(QPen(Qt::blue, 2));
    ui->Voltage->addGraph();
    ui->Voltage->graph(1)->setPen(QPen(Qt::red, 2));

    // 添加图例
    ui->Voltage->legend->setVisible(true);
    ui->Voltage->legend->setFont(QFont("Helvetica", 9));
    ui->Voltage->legend->setRowSpacing(-3);

    // 设置图例项名称
    ui->Voltage->graph(0)->setName("Engine 1");
    ui->Voltage->graph(1)->setName("Engine 2");

    //======= Current =======================================
    ui->Current->xAxis->setLabel("Time (s)");
    ui->Current->yAxis->setLabel("Current (A)");
    ui->Current->xAxis->setRange(0, 30); // 设置x轴范围
    ui->Current->yAxis->setRange(80, 100); // 设置y轴范围

    ui->Current->addGraph();
    ui->Current->graph(0)->setPen(QPen(Qt::blue, 2));
    ui->Current->addGraph();
    ui->Current->graph(1)->setPen(QPen(Qt::red, 2));

    // 添加图例
    ui->Current->legend->setVisible(true);
    ui->Current->legend->setFont(QFont("Helvetica", 9));
    ui->Current->legend->setRowSpacing(-3);

    // 设置图例项名称
    ui->Current->graph(0)->setName("Engine 1");
    ui->Current->graph(1)->setName("Engine 2");

    //======= Frequency =======================================
    ui->Frequency->xAxis->setLabel("Time (s)");
    ui->Frequency->yAxis->setLabel("Frequency (Hz)");
    ui->Frequency->xAxis->setRange(0, 30); // 设置x轴范围
    ui->Frequency->yAxis->setRange(45, 55); // 设置y轴范围

    ui->Frequency->addGraph();
    ui->Frequency->graph(0)->setPen(QPen(Qt::blue, 2));
    ui->Frequency->addGraph();
    ui->Frequency->graph(1)->setPen(QPen(Qt::red, 2));

    // 添加图例
    ui->Frequency->legend->setVisible(true);
    ui->Frequency->legend->setFont(QFont("Helvetica", 9));
    ui->Frequency->legend->setRowSpacing(-3);

    // 设置图例项名称
    ui->Frequency->graph(0)->setName("Engine 1");
    ui->Frequency->graph(1)->setName("Engine 2");

    //======= Power =======================================
    ui->Power->xAxis->setLabel("Time (s)");
    ui->Power->yAxis->setLabel("Power (KW)");
    ui->Power->xAxis->setRange(0, 30); // 设置x轴范围
    ui->Power->yAxis->setRange(45, 55); // 设置y轴范围

    ui->Power->addGraph();
    ui->Power->graph(0)->setPen(QPen(Qt::blue, 2));
    ui->Power->addGraph();
    ui->Power->graph(1)->setPen(QPen(Qt::red, 2));

    // 添加图例
    ui->Power->legend->setVisible(true);
    ui->Power->legend->setFont(QFont("Helvetica", 9));
    ui->Power->legend->setRowSpacing(-3);

    // 设置图例项名称
    ui->Power->graph(0)->setName("Engine 1");
    ui->Power->graph(1)->setName("Engine 2");
}

void client::Plot(int index){
    voltageData[index].append(voltage);
    currentData[index].append(current);
    frequencyData[index].append(frequency);
    powerData[index].append(power);

    // Plot
    ui->Voltage->graph(index)->setData(timeData, voltageData[index]);
    updateAxis();
    ui->Voltage->replot();

    ui->Current->graph(index)->setData(timeData, currentData[index]);
    updateAxis();
    ui->Current->replot();

    ui->Frequency->graph(index)->setData(timeData, frequencyData[index]);
    updateAxis();
    ui->Frequency->replot();

    ui->Power->graph(index)->setData(timeData, powerData[index]);
    updateAxis();
    ui->Power->replot();
}

void client::updateAxis(){
    if (timeData.size() > 30){
        ui->Voltage->xAxis->setRange(timeData.last() - 30, timeData.last());
        ui->Current->xAxis->setRange(timeData.last() - 30, timeData.last());
        ui->Frequency->xAxis->setRange(timeData.last() - 30, timeData.last());
        ui->Power->xAxis->setRange(timeData.last() - 30, timeData.last());
    } else {
        ui->Voltage->xAxis->setRange(0, timeData.last());
        ui->Current->xAxis->setRange(0, timeData.last());
        ui->Frequency->xAxis->setRange(0, timeData.last());
        ui->Power->xAxis->setRange(0, timeData.last());
    }

    double min, max;
    // 调整 Y 轴的显示范围
    min = *std::min_element(voltageData[0].begin(), voltageData[0].end());
    max = *std::max_element(voltageData[0].begin(), voltageData[0].end());
    ui->Voltage->yAxis->setRange(min - 20, max + 20);

    min = *std::min_element(currentData[0].begin(), currentData[0].end());
    max = *std::max_element(currentData[0].begin(), currentData[0].end());
    ui->Current->yAxis->setRange(min - 20, max + 20);

    min = *std::min_element(frequencyData[0].begin(), frequencyData[0].end());
    max = *std::max_element(frequencyData[0].begin(), frequencyData[0].end());
    ui->Frequency->yAxis->setRange(min - 10, max + 10);

    min = *std::min_element(powerData[0].begin(), powerData[0].end());
    max = *std::max_element(powerData[0].begin(), powerData[0].end());
    ui->Power->yAxis->setRange(min - 5, max + 5);
}

void client::setUi(){
    ui->Engine1->setStyleSheet("font: 14pt \"Consolas\"; "
                               "border: 2px solid black; "
                               "border-color: rgb(79, 170, 255);");
    ui->Engine2->setStyleSheet("font: 14pt \"Consolas\"; "
                               "border: 2px solid black; "
                               "border-color: rgb(79, 170, 255);");

    ui->Alarm->setGeometry(800, 150, 100, 100);
    ui->Alarm->setStyleSheet("background-color: gray; "
                             "font: 18pt \"Candara\"; "
                             "border: 2px solid black; "
                             "border-radius: 50px; "
                             "padding: 10px;");
}

void client::Connect(){
    connect(tcpSocket, &QTcpSocket::readyRead, this, &client::readData);
    connect(timer, &QTimer::timeout, this, &client::updateSensorValues);
}

void client::on_Connect_clicked()
{
    // Get ip and port
    QString ipAddress = ui->IP->text();
    int port = ui->Port->text().toInt();

    if (!isConnected) {
        tcpSocket->connectToHost(ipAddress, port);

        if (tcpSocket->waitForConnected(5000)) {
            //ui->Engine1->append("Connected！");
            ui->Connect->setText("Disconnect");
            isConnected = true;
        } else {
            //ui->Engine1->append("Fail to connect：" + tcpSocket->errorString());
        }
    } else {
        // if isConnected，then Disconnect
        tcpSocket->disconnectFromHost();
        ui->Connect->setText("Connect");
        isConnected = false;
    }
}

void client::on_Stable_clicked()
{
    ui->Stable->setStyleSheet("font: 75 20pt \"Consolas\"; color: #1d8aff;");
    ui->CriStable->setStyleSheet("font: 75 20pt \"Consolas\";");
    ui->UnStable->setStyleSheet("font: 75 20pt \"Consolas\";");

    change_range_rand_num(0.02);
}

void client::on_CriStable_clicked()
{
    ui->CriStable->setStyleSheet("font: 75 20pt \"Consolas\"; color: #1d8aff;");
    ui->Stable->setStyleSheet("font: 75 20pt \"Consolas\";");
    ui->UnStable->setStyleSheet("font: 75 20pt \"Consolas\";");

    change_range_rand_num(0.05);
}

void client::on_UnStable_clicked()
{
    ui->UnStable->setStyleSheet("font: 75 20pt \"Consolas\"; color: #1d8aff;");
    ui->Stable->setStyleSheet("font: 75 20pt \"Consolas\";");
    ui->CriStable->setStyleSheet("font: 75 20pt \"Consolas\";");

    change_range_rand_num(0.2);
}

void client::on_Alarm_clicked()
{
    // 取消报警状态
    isAlarmTriggered = false;
    alarmCounter = 0;
    ui->Alarm->setStyleSheet("background-color: gray; "
                             "font: 18pt \"Candara\"; "
                             "border: 2px solid black; "
                             "border-radius: 50px; "
                             "padding: 10px;");
}
