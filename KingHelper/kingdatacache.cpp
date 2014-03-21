#include "kingdatacache.h"

KingDataCache::KingDataCache(QObject *parent) :
    QObject(parent)
{
    m_dbmanager = new KingDbManager(this);
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ��
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
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ��
**********************************************/
QMap<QString,productItem>KingDataCache::getAllProductItems()
{
    if(m_dbmanager)
    {
        m_productsMap =  m_dbmanager->getAllProductItems();
    }
    return m_productsMap;
}
