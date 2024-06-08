#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "userstable.h"
#include "seabattleserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void logs_reciever(QString);

private slots:
    void on_button_start_clicked();
    void on_button_stop_clicked();
    void on_button_users_desk_clicked();

private:
    Ui::MainWindow *ui;    
    UsersTable* _users_table;

    SeaBattleServer* _server;
};
#endif // MAINWINDOW_H
