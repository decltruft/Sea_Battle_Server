#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _users_table(new UsersTable)
    , _server(new SeaBattleServer)
{
    this->setFixedSize(516, 663);
    ui->setupUi(this);

    connect(_server, &SeaBattleServer::send_to_logger, this, &MainWindow::logs_reciever);

    ui->logger->setTextColor(Qt::black);
    ui->logger->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete _users_table;
    delete _server;
}

void MainWindow::logs_reciever(QString info)
{
    ui->logger->append(info);
}

void MainWindow::on_button_start_clicked()
{
    _server->start_server();
}


void MainWindow::on_button_stop_clicked()
{
    _server->stop_server();
}


void MainWindow::on_button_users_desk_clicked()
{
    _users_table->show();
}

