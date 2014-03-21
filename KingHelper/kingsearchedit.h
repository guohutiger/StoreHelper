/*
* 文件名称：kkSearchFrame.h
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

#ifndef KKSEARCHFRAME_H
#define KKSEARCHFRAME_H

#include <QListWidget>
#include <QStringListModel>
#include <QMap>
#include <QDebug>

//机构信息结构
typedef struct DepInfo
{
    int depId;
    int parentId;
    int smsBalance;
    int mmsBalance;
    QString updateTime;
    QString depName;
    int opertype;

}DepInfo;

typedef struct UserInfo
{
    UserInfo()
    {
        userId = -1;
        depId  = -1;
        userType = -1;
        onlineState = -1;
        sex = -1;
        smsBalance = -1;
        mmsBalance = -1;
        opertype = -1;
    }
    int         userId;         //用户ID
    int         depId;          //机构ID
    int         userType;       //用户类型
    int         onlineState;    //在线状态0退出 1 在线 2忙碌 3离开 4隐身
    QString 	userName;		//登录名称
    QString     name;			//用户名
    QString     headUrl;		//头像地址
    QString     signature;		//签名
    int		    sex;			//0女  1男
    QString     birthday;		//生日
    QString 	mobile;			//手机
    QString     telephone;		//办公电话
    QString     qq;				//企鹅账号
    QString     email;			//电子邮箱
    QString     msn;			//
    int         smsBalance;     //余额
    int         mmsBalance;     //余额
    QString     position;		//职位
    QString     job;			//岗位
    QString     pinyin;			//拼音简写
    int         opertype;       //操作类型

}UserInfo;
//#include "netappmgrinterface.h"
//#include "kkMainWindow.h"

class NetAppMgrInterface;

//搜索弹出框类
class SearchFrame : public QListWidget
{
    Q_OBJECT
public:
    explicit SearchFrame(int pos_x, int pos_y, int width, int height, bool isMain, QString key, QWidget *parent=0);
    ~SearchFrame();

    void updateList(QString );

    void moveUp();
    void moveDown();
    void moveEnter();

private:
    int pos_x;
    int pos_y;
    int width;
    int height;
    QString key;

    bool isMain;

    //用于存储返回匹配的人员列表
    QList<UserInfo > userList;
    //用于存储机构列表
    QList<DepInfo > depList;
    //节点与ID的映射
    QMap<QListWidgetItem *, int > kkMapId;
    //后端对象
    NetAppMgrInterface *netAppMgrInterface;

    //初始化数据
    void initData();
    //显示搜索后的结果
    void addSearchDate();

protected:

private slots:
    //节点点击事件
    void slotClicked(QListWidgetItem * );

signals:
    //选中人员ID
    void signalClicked(int );

};


#endif // KKSEARCHFRAME_H
