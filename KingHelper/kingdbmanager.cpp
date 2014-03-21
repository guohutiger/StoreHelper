#include "kingdbmanager.h"

KingDbManager::KingDbManager(QObject *parent) :
    QObject(parent)
{
    initDatebase();
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingDbManager::initDatebase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("datacore.db");
    m_db.setUserName("scott");
    m_db.setPassword("tiger");
    if(!m_db.open())
    {
        qDebug()<<"database open faild!";
        return;
    }
    QSqlQuery query;
    int iret = query.exec(createProductTable);
    printResult(query,iret);
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
int KingDbManager::addNewProductItem(productItem *newproduct)
{
    qDebug()<<newproduct->productName<<newproduct->productNamePY;
    int iRet = 0;
    QSqlQuery  query;
    iRet = query.prepare(insertnewproductitem);
    //query.bindValue(0,newproduct->productName);
    query.bindValue(1,newproduct->productName);
    query.bindValue(2,newproduct->productCode);
    query.bindValue(3,newproduct->productPrice);
    query.bindValue(4,newproduct->productUrl1);
    query.bindValue(5,newproduct->productUrl2);
    query.bindValue(6,newproduct->productUrl3);
    query.bindValue(7,newproduct->productImage);
    query.bindValue(8,newproduct->productDesc);
    query.bindValue(9,newproduct->productNamePY);
    query.exec();
    printResult(query,iRet);

    return iRet;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
QMap<QString,productItem>KingDbManager::getAllProductItems()
{
    QMap<QString,productItem> productItemsMap;
    int iRet = 0;
    QSqlQuery query;
    iRet = query.exec(getallproducts);
    while(query.next())
    {
        productItem item;
        item.productName = query.value(1).toString();
        item.productCode = query.value(2).toString();
        item.productPrice = query.value(3).toString();
        item.productUrl1 = query.value(4).toString();
        item.productUrl2 = query.value(5).toString();
        item.productUrl3 = query.value(6).toString();
        item.productImage = query.value(7).toString();
        item.productDesc  = query.value(8).toString();
        item.productNamePY= query.value(9).toString();
        productItemsMap.insert(item.productCode,item);
    }
    printResult(query,iRet);
    return productItemsMap;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingDbManager::printResult(QSqlQuery query,int iRet)
{
    if (1 != iRet)
    {
        qDebug()<<iRet<<"数据库操作失败!原因："<<query.lastError().text();
        qDebug()<<iRet<<"操作失败的sql语句："<<query.lastQuery();
    }
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
//QList<UserInfo> KingDbManager::getuserlistbypinyinhead(QString key)
//{
//    UserInfo usrinfo;
//    int iRet = 0;
//    QSqlQuery  query;
//    QString sqlsen = sql_get_userlist_by_pinyhead;
//    sqlsen.replace("?",key);
//    QList<UserInfo> userlist;
//    iRet = query.exec(sqlsen);
//    while(query.next())
//    {
//        usrinfo.userId = query.value(0).toInt();
//        usrinfo.depId = query.value(1).toInt();
//        usrinfo.userType = query.value(2).toInt();
//        usrinfo.position = query.value(3).toString();
//        usrinfo.job = query.value(4).toString();
//        usrinfo.userName = query.value(5).toString();
//        usrinfo.name = query.value(7).toString();
//        usrinfo.headUrl = query.value(8).toString();
//        usrinfo.signature = query.value(9).toString();
//        usrinfo.sex = query.value(10).toInt();
//        usrinfo.birthday = query.value(11).toString();
//        usrinfo.mobile = query.value(12).toString();
//        usrinfo.telephone = query.value(13).toString();
//        usrinfo.email = query.value(14).toString();
//        usrinfo.smsBalance = query.value(15).toInt();
//        usrinfo.mmsBalance = query.value(16).toInt();
//        usrinfo.onlineState = query.value(19).toInt();
//     userlist.append(usrinfo);
//    }
//    printResult(query,iRet);

//    return userlist;
//}
