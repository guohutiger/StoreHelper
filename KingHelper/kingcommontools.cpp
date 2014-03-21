#include "kingcommontools.h"

kingcommontools::kingcommontools(QObject *parent) :
    QObject(parent)
{
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：/获取临时文件目录 eg:"C:\Users\win7\AppData\Local//pckk
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值 ：void
**********************************************/
QString kingcommontools::getkkTempleFilePath()
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    if (path.compare("") == 0)
    {
        qDebug()<<"获取临时数据目录失败!";
    }
    path = path + "\\kinghelper\\";
    path = path.replace("\\", "/");
    return path;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：获取一个随机数
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：返回一个带时间的序列号格式为14031318473951
**********************************************/
QString kingcommontools::fiveRandomSerialNumber()
{
    QString serials;
    int rands = qrand() % 79 + 10;
    serials = QDateTime::currentDateTime().toString("yyMMddhhmmss")+ QString::number(rands);

    return serials;
}

static WoldTransitionSpell *__db = NULL;

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值  ：
**********************************************/
WoldTransitionSpell *WoldTransitionSpell::instance()
{
    if(__db == NULL)
    {
        __db = new WoldTransitionSpell;
        //内存问题待优化
    }
    return __db;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值  ：
**********************************************/
void WoldTransitionSpell::releaseDB()
{
    if(__db != NULL)
    {
        delete __db;
        __db = NULL;
    }
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值  ：
**********************************************/
WoldTransitionSpell::WoldTransitionSpell(QObject *parent) :
QObject(parent)
{
    m_iDBState = 0;
    if(!loadDataInfo())
    {
        switch(m_iDBState)
        {
        case 1:
            qDebug() << "中文转拼音数据文件不存在";
            break;
        case 2:
            qDebug() << "中文转拼音数据文件打开失败";
            break;
        }
    }
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值  ：
**********************************************/
WoldTransitionSpell::~WoldTransitionSpell()
{
    releaseDB();
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值  ：
**********************************************/
bool WoldTransitionSpell::loadDataInfo()
{
    if (QSqlDatabase::database("pinyin").isValid())
    {
        return true;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "pinyin");
    QString fileName = "./resource/pinyin.db";
    QFile file(fileName );
    if(!file.exists() )
    {
        m_iDBState = 1;
        return false;
    }
    db.setDatabaseName(fileName);
    if (!db.open())
    {
        m_iDBState = 2;
        return false;
    }
    return true;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：void
* 输出参数：void
* 返回值  ：
**********************************************/
QChar WoldTransitionSpell::TransitionSpell(QString word)
{
    if(word.isEmpty() || word.isNull())
    {//如果输入汉字为空，返回一个空字符
        return QChar(' ');
    }
    if(word.at(0) >= 0 && word.at(0) < 128)
    {//如果输入的本身就是数字或者字母，则直接返回
        return word.at(0);
    }
    QSqlQuery query(QSqlDatabase::database("pinyin"));
    QString strQuery;
    strQuery = tr("select code from pinyin where name = '%1'")
        .arg(word);
    query.prepare(strQuery);
    if(!query.exec())
    {
        qDebug() <<"根据拼音模糊匹配查询未果!";
    }
    QChar x;
    while(query.next())
    {//获得查找到的结果
        x = query.value(0).toString().at(0);
    }
    return x;
}
