#ifndef SERVER_H
#define SERVER_H

#include "ui_server.h"
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class server; }
QT_END_NAMESPACE

class server : public QWidget
{
    Q_OBJECT

public:
    server(QWidget *parent = nullptr);
    ~server();

private slots:
    void newConnection();
    void receiveData();

private:
    Ui::server *ui;

    QTcpServer* tcpServer;
    QTcpSocket* clientSocket;

    QSqlDatabase database;
    QSqlQuery queryEngine1;
    QSqlQuery queryEngine2;

private:
    void createTable();
    void insertData(const QString& dataStr);
};
#endif // SERVER_H
