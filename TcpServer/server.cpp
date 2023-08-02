#include "server.h"

server::server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::server)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &server::newConnection);
    tcpServer->listen(QHostAddress::Any, 8080);

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("running_state.db");

    if (database.open())    createTable();
}

server::~server()
{
    delete ui;
}

void server::newConnection()
{
    clientSocket = tcpServer->nextPendingConnection();
    if (clientSocket) {
        connect(clientSocket, &QTcpSocket::readyRead, this, &server::receiveData);
    }
}

void server::receiveData()
{
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    QString dataStr = QString::fromUtf8(data);
    QStringList dataList = dataStr.split(',');
    ui->stateBrowser->append(dataStr);

    if (dataList.size() == 5) {
        QString engineType = dataList[0];
        QString frequency = dataList[1];
        QString voltage = dataList[2];
        QString current = dataList[3];
        QString power = dataList[4];

        if (engineType == "Engine1") {
            QString insertQuery = "INSERT INTO engine1_table (frequency, voltage, current, power) VALUES (:frequency, :voltage, :current, :power)";
            queryEngine1.prepare(insertQuery);
            queryEngine1.bindValue(":frequency", frequency.toDouble());
            queryEngine1.bindValue(":voltage", voltage.toDouble());
            queryEngine1.bindValue(":current", current.toDouble());
            queryEngine1.bindValue(":power", power.toDouble());

            if (!queryEngine1.exec()) {
                qDebug() << "Error: Failed to insert data into Engine1 table - " << queryEngine1.lastError().text();
            }
        } else if (engineType == "Engine2") {
            QString insertQuery = "INSERT INTO engine2_table (frequency, voltage, current, power) VALUES (:frequency, :voltage, :current, :power)";
            queryEngine2.prepare(insertQuery);
            queryEngine2.bindValue(":frequency", frequency.toDouble());
            queryEngine2.bindValue(":voltage", voltage.toDouble());
            queryEngine2.bindValue(":current", current.toDouble());
            queryEngine2.bindValue(":power", power.toDouble());

            if (!queryEngine2.exec()) {
                qDebug() << "Error: Failed to insert data into Engine2 table - " << queryEngine2.lastError().text();
            }
        }
    }
}

void server::createTable()
{
    QSqlQuery queryEngine1;
    QSqlQuery queryEngine2;

    QString createTableQueryEngine1 = "CREATE TABLE IF NOT EXISTS engine1_table ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "frequency REAL,"
                                      "voltage REAL,"
                                      "current REAL,"
                                      "power REAL"
                                      ")";

    QString createTableQueryEngine2 = "CREATE TABLE IF NOT EXISTS engine2_table ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "frequency REAL,"
                                      "voltage REAL,"
                                      "current REAL,"
                                      "power REAL"
                                      ")";

    if (!queryEngine1.exec(createTableQueryEngine1)) {
        qDebug() << "Error: Failed to create Engine1 table - " << queryEngine1.lastError().text();
    }

    if (!queryEngine2.exec(createTableQueryEngine2)) {
        qDebug() << "Error: Failed to create Engine2 table - " << queryEngine1.lastError().text();
    }

    this->queryEngine1=queryEngine1;
    this->queryEngine2=queryEngine2;
}
