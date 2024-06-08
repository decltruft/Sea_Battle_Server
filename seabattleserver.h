#ifndef SEABATTLESERVER_H
#define SEABATTLESERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QRegularExpression>

#include "server_commands.h"
#include "seabattledb.h"

class SeaBattleServer : public QWidget
{
    Q_OBJECT

public:
    SeaBattleServer(QWidget* parent = 0);
    virtual ~SeaBattleServer();

signals:
    void send_to_logger(QString);

public slots:
    void start_server();
    void stop_server();

    virtual void slotNewConnection();
    void slotReadClient();

private:
    const size_t _port = 7878;
    QTcpServer*  _server;

    qint16 _next_block_size;

    void send_to_client(QTcpSocket* sock, const QString& request);

    QString handle_enter_req(QString);
    QString handle_password_recov_req(QString);
    QString handle_registration_req(QString);
    QString handle_settings_req(QString);
};

#endif // SEABATTLESERVER_H
