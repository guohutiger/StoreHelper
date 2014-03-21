/*
* �ļ����ƣ�kkSearchFrame.h
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

#ifndef KKSEARCHFRAME_H
#define KKSEARCHFRAME_H

#include <QListWidget>
#include <QStringListModel>
#include <QMap>
#include <QDebug>

//������Ϣ�ṹ
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
    int         userId;         //�û�ID
    int         depId;          //����ID
    int         userType;       //�û�����
    int         onlineState;    //����״̬0�˳� 1 ���� 2æµ 3�뿪 4����
    QString 	userName;		//��¼����
    QString     name;			//�û���
    QString     headUrl;		//ͷ���ַ
    QString     signature;		//ǩ��
    int		    sex;			//0Ů  1��
    QString     birthday;		//����
    QString 	mobile;			//�ֻ�
    QString     telephone;		//�칫�绰
    QString     qq;				//����˺�
    QString     email;			//��������
    QString     msn;			//
    int         smsBalance;     //���
    int         mmsBalance;     //���
    QString     position;		//ְλ
    QString     job;			//��λ
    QString     pinyin;			//ƴ����д
    int         opertype;       //��������

}UserInfo;
//#include "netappmgrinterface.h"
//#include "kkMainWindow.h"

class NetAppMgrInterface;

//������������
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

    //���ڴ洢����ƥ�����Ա�б�
    QList<UserInfo > userList;
    //���ڴ洢�����б�
    QList<DepInfo > depList;
    //�ڵ���ID��ӳ��
    QMap<QListWidgetItem *, int > kkMapId;
    //��˶���
    NetAppMgrInterface *netAppMgrInterface;

    //��ʼ������
    void initData();
    //��ʾ������Ľ��
    void addSearchDate();

protected:

private slots:
    //�ڵ����¼�
    void slotClicked(QListWidgetItem * );

signals:
    //ѡ����ԱID
    void signalClicked(int );

};


#endif // KKSEARCHFRAME_H
