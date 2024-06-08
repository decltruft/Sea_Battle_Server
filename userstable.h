#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QWidget>

#include <QtSql>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class UsersTable;
}

class UsersTable : public QWidget
{
    Q_OBJECT

public:
    explicit UsersTable(QWidget *parent = nullptr);
    ~UsersTable();

public:
    void show_table_model();

public slots:


signals:


private:
    Ui::UsersTable *ui;

    QSqlDatabase _db;

    QSqlQuery* _query;
    QSqlTableModel* _model;
};

#endif // USERSTABLE_H
