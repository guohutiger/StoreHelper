#include "kingcommontools.h"

kingcommontools::kingcommontools(QObject *parent) :
    QObject(parent)
{
}

/**********************************************
* ��������������
* �������ܣ�/��ȡ��ʱ�ļ�Ŀ¼ eg:"C:\Users\win7\AppData\Local//pckk
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ ��void
**********************************************/
QString kingcommontools::getkkTempleFilePath()
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    if (path.compare("") == 0)
    {
        qDebug()<<"��ȡ��ʱ����Ŀ¼ʧ��!";
    }
    path = path + "\\kinghelper\\";
    path = path.replace("\\", "/");
    return path;
}

/**********************************************
* ��������������
* �������ܣ���ȡһ�������
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ������һ����ʱ������кŸ�ʽΪ14031318473951
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
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ  ��
**********************************************/
WoldTransitionSpell *WoldTransitionSpell::instance()
{
    if(__db == NULL)
    {
        __db = new WoldTransitionSpell;
        //�ڴ�������Ż�
    }
    return __db;
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ  ��
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
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ  ��
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
            qDebug() << "����תƴ�������ļ�������";
            break;
        case 2:
            qDebug() << "����תƴ�������ļ���ʧ��";
            break;
        }
    }
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ  ��
**********************************************/
WoldTransitionSpell::~WoldTransitionSpell()
{
    releaseDB();
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ  ��
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
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������void
* ���������void
* ����ֵ  ��
**********************************************/
QChar WoldTransitionSpell::TransitionSpell(QString word)
{
    if(word.isEmpty() || word.isNull())
    {//������뺺��Ϊ�գ�����һ�����ַ�
        return QChar(' ');
    }
    if(word.at(0) >= 0 && word.at(0) < 128)
    {//�������ı���������ֻ�����ĸ����ֱ�ӷ���
        return word.at(0);
    }
    QSqlQuery query(QSqlDatabase::database("pinyin"));
    QString strQuery;
    strQuery = tr("select code from pinyin where name = '%1'")
        .arg(word);
    query.prepare(strQuery);
    if(!query.exec())
    {
        qDebug() <<"����ƴ��ģ��ƥ���ѯδ��!";
    }
    QChar x;
    while(query.next())
    {//��ò��ҵ��Ľ��
        x = query.value(0).toString().at(0);
    }
    return x;
}
