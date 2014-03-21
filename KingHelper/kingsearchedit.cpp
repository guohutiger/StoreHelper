/*
* 文件名称：kkSearchFrame.cpp
* 摘   要：主要用于实现搜索弹出框
*
* 当前版本：1.1
* 作   者：fangqi
* 完成日期：
*
* 取代版本：1.0
* 原作者 ：fangqi
* 完成日期：
*/

#include "kingsearchedit.h"

/***********************************************************
* 作者姓名：fangqi
* 函数介绍：搜索框构造函数
* 定义的参数含义说明
* 输入参数：pos_x:横坐标，pos_y:纵坐标，width:宽，height:高
*			key:搜索关键字，
*			parent:父类指针
* 输出参数：无
* 返回值  ：无
************************************************************/
SearchFrame::SearchFrame(int pos_x, int pos_y, int width, int height, bool isMain, QString key,QWidget *parent):
    QListWidget(parent), pos_x(pos_x), pos_y(pos_y), width(width), height(height), key(key), isMain(isMain)
{
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//设置滚动条每次移动多少的单位
    this->setIconSize(QSize(21, 21));
    this->setFont(QFont("", 10));
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);

    //设置QListView的背景为白色
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

    //设置样式
    this->setStyleSheet("QListWidget{border: 1px solid gray; background-color: white }"
                        "QListView::item:hover{background-color:rgba(222, 237, 248)}"
                        "QListView::item:selected{background-color:rgba(162, 209, 247)}");
}

/***********************************************************
* 作者姓名：fangqi
* 函数介绍：搜索框析构函数
* 定义的参数含义说明
* 输入参数：无
* 输出参数：无
* 返回值  ：无
************************************************************/
SearchFrame::~SearchFrame()
{
}

/***********************************************************
* 作者姓名：fangqi
* 函数介绍：更新搜索框列表
* 定义的参数含义说明
* 输入参数：key：搜索关键字
* 输出参数：无
* 返回值  ：void
************************************************************/
void SearchFrame::updateList(QString key)
{
    this->key = key;

    //清空所有节点
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
* 作者姓名：fangqi
* 函数介绍：初始化一些数据
* 定义的参数含义说明
* 输入参数：无
* 输出参数：无
* 返回值  ：void
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
* 作者姓名：fangqi
* 函数介绍：向搜索显示框里添加节点
* 定义的参数含义说明
* 输入参数：无
* 输出参数：无
* 返回值  ：void
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

        //获取该人员所在机构名称
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
        //暂时屏蔽头像，有头像时显示数据的宽度有点太窄了
        item->setText(userName+"("+mobileNum+")--"+depName);

        kkMapId.insert(item, userList.at(i).userId);
    }
}

/***********************************************************
* 作者姓名：fangqi
* 函数介绍：选择搜索输入框里面节点槽函数
* 定义的参数含义说明
* 输入参数：tmpItem：被选中的节点
* 输出参数：无
* 返回值  ：void
************************************************************/
void SearchFrame::slotClicked(QListWidgetItem *tmpItem)
{
    int id = kkMapId.value(tmpItem);

    //选中人员
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
