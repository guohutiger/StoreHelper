/*
* �ļ����ƣ�kkSearchFrame.cpp
* ժ   Ҫ����Ҫ����ʵ������������
*
* ��ǰ�汾��1.1
* ��   �ߣ�fangqi
* ������ڣ�
*
* ȡ���汾��1.0
* ԭ���� ��fangqi
* ������ڣ�
*/

#include "kingsearchedit.h"

/***********************************************************
* ����������fangqi
* �������ܣ��������캯��
* ����Ĳ�������˵��
* ���������pos_x:�����꣬pos_y:�����꣬width:��height:��
*			key:�����ؼ��֣�
*			parent:����ָ��
* �����������
* ����ֵ  ����
************************************************************/
SearchFrame::SearchFrame(int pos_x, int pos_y, int width, int height, bool isMain, QString key,QWidget *parent):
    QListWidget(parent), pos_x(pos_x), pos_y(pos_y), width(width), height(height), key(key), isMain(isMain)
{
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//���ù�����ÿ���ƶ����ٵĵ�λ
    this->setIconSize(QSize(21, 21));
    this->setFont(QFont("", 10));
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);

    //����QListView�ı���Ϊ��ɫ
    this->setStyleSheet("QListWidget{background-color:white}");

    if(true == isMain)
    {
        this->setGeometry(pos_x, pos_y, width, 133+6);
    }
    else
    {
        this->setGeometry(pos_x, pos_y, width, 133+6);
    }

    initData();
    addSearchDate();

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slotClicked(QListWidgetItem *)));

    //������ʽ
    this->setStyleSheet("QListWidget{border: 1px solid gray; background-color: white }"
                        "QListView::item:hover{background-color:rgba(222, 237, 248)}"
                        "QListView::item:selected{background-color:rgba(162, 209, 247)}");
}

/***********************************************************
* ����������fangqi
* �������ܣ���������������
* ����Ĳ�������˵��
* �����������
* �����������
* ����ֵ  ����
************************************************************/
SearchFrame::~SearchFrame()
{
}

/***********************************************************
* ����������fangqi
* �������ܣ������������б�
* ����Ĳ�������˵��
* ���������key�������ؼ���
* �����������
* ����ֵ  ��void
************************************************************/
void SearchFrame::updateList(QString key)
{
    this->key = key;

    //������нڵ�
    int rows = this->count();
    for(int i=0; i<rows; i++)
    {
        this->takeItem(i);
        --i;
        --rows;
    }
    this->setGeometry(pos_x, pos_y, width, 133+6);

    initData();
    addSearchDate();
}

/***********************************************************
* ����������fangqi
* �������ܣ���ʼ��һЩ����
* ����Ĳ�������˵��
* �����������
* �����������
* ����ֵ  ��void
************************************************************/
void SearchFrame::initData()
{
    userList.clear();
    depList.clear();

    //userList = netAppMgrInterface->FuzzySearchUser(key);
    //depList = netAppMgrInterface->getDepinfofromdb();
    UserInfo info;
    for(int index =0;index <key.toInt();index++)
    {
        qDebug()<<index;
          info.name = QString::number(index);
          info.userId = index;
          userList.append(info);
    }


    int maxNum;
    if(true == isMain)
    {
        maxNum = 16;
    }
    else
    {
        maxNum = 10;
    }

    int userNum = userList.size();
    if(userNum <= 5)
    {
        return ;
    }
    else if(userNum <= maxNum)
    {
        this->setGeometry(pos_x, pos_y, width, 26*userNum+6);
    }
    else
    {
        this->setGeometry(pos_x, pos_y, width, 26*maxNum+6);
    }
}

/***********************************************************
* ����������fangqi
* �������ܣ���������ʾ������ӽڵ�
* ����Ĳ�������˵��
* �����������
* �����������
* ����ֵ  ��void
************************************************************/
void SearchFrame::addSearchDate()
{
    kkMapId.clear();

    int userNum = userList.size();

    int maxShowNum;
    if(true == isMain)
    {
        maxShowNum = 16;
    }
    else
    {
        maxShowNum = 10;
    }

    int maxNum;
    if(userNum <= maxShowNum)
    {
        maxNum = userNum;
    }
    else if(userNum > maxShowNum)
    {
        maxNum = maxShowNum;
    }

    for(int i=0; i<maxNum; i++)
    {
        QString userName = userList.at(i).name;
        QString mobileNum = userList.at(i).mobile;

        //��ȡ����Ա���ڻ�������
        QString depName = "";
        foreach(DepInfo tmpDep, depList)
        {
            if(tmpDep.depId == userList.at(i).depId)
            {
                depName = tmpDep.depName;
            }
        }

        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(item->sizeHint().width(), 26));
        //��ʱ����ͷ����ͷ��ʱ��ʾ���ݵĿ���е�̫խ��
        item->setText(userName+"("+mobileNum+")--"+depName);

        kkMapId.insert(item, userList.at(i).userId);
    }
}

/***********************************************************
* ����������fangqi
* �������ܣ�ѡ���������������ڵ�ۺ���
* ����Ĳ�������˵��
* ���������tmpItem����ѡ�еĽڵ�
* �����������
* ����ֵ  ��void
************************************************************/
void SearchFrame::slotClicked(QListWidgetItem *tmpItem)
{
    int id = kkMapId.value(tmpItem);

    //ѡ����Ա
    emit signalClicked(id);
}

void SearchFrame::moveUp()
{
    int theNum = this->count();
    int theIndex = this->currentRow();
    if(-1==theIndex || 0==theNum)
    {
        return ;
    }
    else if(0 == theIndex)
    {
        this->setCurrentRow(theNum-1);
    }
    else
    {
        this->setCurrentRow(theIndex-1);
    }
}

void SearchFrame::moveDown()
{
    int theNum = this->count();
    int theIndex = this->currentRow();

    if(0 == theNum)
    {
        return ;
    }
    else if(-1==theIndex)
    {
        this->setCurrentRow(0);
    }
    else if(theNum-1 == theIndex)
    {
        this->setCurrentRow(0);
    }
    else
    {
        this->setCurrentRow(theIndex+1);
    }
}

void SearchFrame::moveEnter()
{
    int theIndex = this->currentRow();
    if(-1 != theIndex)
    {
        QListWidgetItem *tmpItem = this->currentItem();

        int theId = kkMapId.value(tmpItem);
        emit signalClicked(theId);
    }
}
