#include <QDebug>

#include "seabattleserver.h"

SeaBattleServer::SeaBattleServer(QWidget* parent) :
    QWidget(parent)
  , _server(nullptr)
  , _next_block_size(0)
{

}

SeaBattleServer::~SeaBattleServer()
{
    stop_server();
}

void SeaBattleServer::start_server()
{
    _server = new QTcpServer(this);
    if(!_server->listen(QHostAddress::Any, _port))
    {
        const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
        QString message = "[ " + dateTime + " ]" + "  Не удалось запустить сервер!";
        emit send_to_logger(message);

        _server->close();
        return;
    }
    const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
    QString message = "[ " + dateTime + " ]" + "  Сервер запущен!";
    emit send_to_logger(message);

    connect(_server, &QTcpServer::newConnection, this, &SeaBattleServer::slotNewConnection);
}

void SeaBattleServer::stop_server()
{
    if(nullptr == _server)
        return;

    _server->close();
    delete _server;
    _server = nullptr;

    const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
    QString message = "[ " + dateTime + " ]" + "  Сервер остановлен!";
    emit send_to_logger(message);
}

void SeaBattleServer::slotNewConnection()
{
    QTcpSocket* clients_socket = _server->nextPendingConnection();

    connect(clients_socket, &QTcpSocket::disconnected, clients_socket, &QTcpSocket::deleteLater);
    connect(clients_socket, &QTcpSocket::readyRead, this, &SeaBattleServer::slotReadClient);

    send_to_client(clients_socket, "You have been connected!");

    const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
    QString message = "[ " + dateTime + " ]" + "  Новый клиент подключился!";
    emit send_to_logger(message);
}

void SeaBattleServer::slotReadClient()
{
    QTcpSocket *clients_socket = (QTcpSocket*)sender();
    QDataStream in(clients_socket);
    in.setVersion(QDataStream::Qt_6_2);

    if(QDataStream::Status::Ok != in.status())
    {
        const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
        QString message = "[ " + dateTime + " ]" + "  Ошибка потока данных!";
        emit send_to_logger(message);
        return;
    }

    for(;;)
    {
        if(_next_block_size == 0)
        {
            qDebug() << "block size == 0\n";
            if(clients_socket->bytesAvailable() < 2)
            {
                break;
            }
            in >> _next_block_size;
        }

        if(clients_socket->bytesAvailable() < _next_block_size)
        {
            break;
        }

        QString str;
        in >> str;
        _next_block_size = 0;

        const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
        QString message = "[ " + dateTime + " ]" + str;
        emit send_to_logger(message);

        QString server_response = "hs:wrongcmd";
        QRegularExpression rx("(cl:)(\\w+:)(.+)");

        auto match = rx.match(str);
        if(match.hasMatch())
        {
            if(match.captured(2) == "enter:")
            {
                server_response = handle_enter_req(str);
            }
            else if(match.captured(2) =="recov:")
            {
                server_response = handle_password_recov_req(str);
            }
            else if(match.captured(2) =="reg:")
            {
                server_response = handle_registration_req(str);
            }
            else if(match.captured(2) =="set:")
            {
                server_response = handle_settings_req(str);
            }
        }
        send_to_client(clients_socket, server_response);
    }
}

void SeaBattleServer::send_to_client(QTcpSocket* sock, const QString& request)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);

    if(QDataStream::Status::Ok != out.status())
    {
        const QString dateTime = QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy");
        QString message = "[ " + dateTime + " ]" + "  Ошибка потока данных!";
        emit send_to_logger(message);
        return;
    }

    out << quint16(0) << request;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    sock->write(arrBlock);
}

QString SeaBattleServer::handle_enter_req(QString req)
{
    QRegularExpression rx("(cl:)(\\w+:)(.+):(.+)");
    auto match = rx.match(req);
    if(match.hasMatch())
    {
        if(1)
        {
            return QString("hs:enter:accept");
        }
        else if(2)
        {
            return QString("hs:enter:wrongpass");
        }
        else if(3)
        {
            return QString("hs:enter:wronguname");
        }
    }
}

QString SeaBattleServer::handle_password_recov_req(QString req)
{
    QRegularExpression rx("(cl:)(\\w+:)(.+):(.+):(.+)");
    auto match = rx.match(req);
    if(match.hasMatch())
    {
        if(1)
        {
            return QString("hs:recov:accept");
        }
        else if(2)
        {
            return QString("hs:recov:wronguname");
        }
        else if(3)
        {
            return QString("hs:recov:wrongemail");
        }
    }
}

QString SeaBattleServer::handle_registration_req(QString req)
{
    QRegularExpression rx("(cl:)(\\w+:)(.+):(.+):(.+)");
    auto match = rx.match(req);
    if(match.hasMatch())
    {
        if(1)
        {
            return QString("hs:reg:accept");
        }
        else if(2)
        {
            return QString("hs:reg:unameisusing");
        }
        else
        {
            return QString("hs:reg:emailisusing");
        }
    }
}

QString SeaBattleServer::handle_settings_req(QString req)
{
    QRegularExpression rx("(cl:)(\\w+:)(\\w+:)(.+)");
    auto match = rx.match(req);
    if(match.hasMatch())
    {
        if(match.captured(3) == "changeuname:")
        {
            QRegularExpression rx_u("(cl:)(\\w+:)(\\w+:)(.+):(.+)");
            auto match_u = rx_u.match(req);
            if(match.hasMatch())
            {
                if(1)
                {
                    return QString("hs:set:changeuname:accept");
                }
                else
                {
                    return QString("hs:set:changeuname:unameisusing");
                }
            }
        }
        else if(match.captured(3) == "changeemail:")
        {
            QRegularExpression rx_e("(cl:)(\\w+:)(\\w+:)(.+):(.+)");
            auto match_e = rx_e.match(req);
            if(match.hasMatch())
            {
                if(1)
                {
                    return QString("hs:set:changeemail:accept");
                }
                else
                {
                    return QString("hs:set:changeemail:emailisusing");
                }
            }
        }
        else if(match.captured(3) == "changepass:")
        {
            QRegularExpression rx_p("(cl:)(\\w+:)(\\w+:)(.+):(.+)");
            auto match_p = rx_p.match(req);
            if(match.hasMatch())
            {
                if(1)
                {
                    return QString("hs:set:changepass:accept");
                }
            }
        }
        else if(match.captured(3) == "removeacc:")
        {
            QRegularExpression rx_r("(cl:)(\\w+:)(\\w+:)(.+)");
            auto match_r = rx_r.match(req);
            if(match.hasMatch())
            {
                if(1)
                {
                    return QString("hs:set:removeacc:hbremoved");
                }
            }
        }
    }
}
