#ifndef KINGDATACACHE_H
#define KINGDATACACHE_H

#include <QObject>
#include "kinghelpdef.h"
#include "kingdbmanager.h"

class KingDataCache : public QObject
{
    Q_OBJECT
public:
    explicit KingDataCache(QObject *parent = 0);
    int addNewProductItem(productItem*);
    QMap<QString,productItem>getAllProductItems();
private:
    KingDbManager *m_dbmanager;
    QMap<QString,productItem>m_productsMap;
    
signals:
    
public slots:
    
};

#endif // KINGDATACACHE_H
