#ifndef KINGDBMANAGER_H
#define KINGDBMANAGER_H

#include <QDebug>
#include <QObject>
#include <QSqlError>
#include <QDateTime>
#include <QSqlQuery>
#include "kinghelpdef.h"
#include <QSqlDatabase>

class KingDbManager : public QObject
{
    Q_OBJECT
public:
    explicit KingDbManager(QObject *parent = 0);

    int addNewProductItem(productItem *newproduct);

    QMap<QString,productItem> getAllProductItems();

protected:
    QSqlDatabase m_db;
    void initDatebase();
    void printResult(QSqlQuery query,int iRet);
    
signals:
    
public slots:
    
};

#endif // KINGDBMANAGER_H
