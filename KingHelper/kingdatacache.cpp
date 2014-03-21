#include "kingdatacache.h"

KingDataCache::KingDataCache(QObject *parent) :
    QObject(parent)
{
    m_dbmanager = new KingDbManager(this);
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
int KingDataCache::addNewProductItem(productItem *newproduct)
{
    if(m_dbmanager)
    {
        return m_dbmanager->addNewProductItem(newproduct);
    }
    return -1;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
QMap<QString,productItem>KingDataCache::getAllProductItems()
{
    if(m_dbmanager)
    {
        m_productsMap =  m_dbmanager->getAllProductItems();
    }
    return m_productsMap;
}
