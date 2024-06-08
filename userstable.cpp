#include "userstable.h"
#include "ui_userstable.h"

UsersTable::UsersTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersTable)
{
    this->setFixedSize(730, 599);
    ui->setupUi(this);

    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("127.0.0.1");
    _db.setDatabaseName("./users_info.db");

    _query = new QSqlQuery(_db);
    _query->exec("CREATE TABLE UsersInformation(uname TEXT, password TEXT, email TEXT, wins INT, loses INT);");

    _model = new QSqlTableModel(this, _db);
    _model->setTable("UsersInformation");
    _model->select();

    ui->users_table->setModel(_model);
}

void UsersTable::show_table_model()
{

}

UsersTable::~UsersTable()
{
    delete ui;
}
