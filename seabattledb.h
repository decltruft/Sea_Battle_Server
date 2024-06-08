#ifndef SEABATTLEDB_H
#define SEABATTLEDB_H

#include <QObject>

class SeaBattleDB : public QObject
{
    Q_OBJECT
public:
    explicit SeaBattleDB(QObject *parent = nullptr);

signals:

};

#endif // SEABATTLEDB_H
