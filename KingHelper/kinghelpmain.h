#ifndef KINGHELPMAIN_H
#define KINGHELPMAIN_H

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QTextEdit>
#include <QTreeWidget>
#include <QMessageBox>
#include "kinglineedit.h"
#include "kingitemwidget.h"
#include "kingdatacache.h"
#include "kingwidgetitem.h"
#include "kingsearchedit.h"
#include <QSystemTrayIcon>
#include <kingcommontools.h>
#include "kingscreencut.h"

//namespace Ui {
//class KingHelpMain;
//}

class KingHelpMain : public QWidget
{
    Q_OBJECT
    
public:
    explicit KingHelpMain(QWidget *parent = 0);
    ~KingHelpMain();

protected:
        void createSysTray();
        void loadProductList();
        void insertProductImage();
        void setupUi(QWidget *widget);
        void retranslateUi(QWidget *widget);

private slots:
        void on_savebtn_clicked();

        void on_addbtn_clicked();

        void on_updatebtn_clicked();

        void on_sccutbtn_clicked();

        void slotSearchThisKey(QString key);

        void iconActivated(QSystemTrayIcon::ActivationReason);

        void slotTreeItemCicked(QTreeWidgetItem*,int);

        void slotTreeItemDoubleCicked(QTreeWidgetItem*,int);

private:
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_6;
    KingLineEdit *pronameedit;
    KingLineEdit *procodeEdit;
    KingLineEdit *prourl1edit;
    QTreeWidget *treeWidget;
    QPushButton *addbtn;
    QPushButton *updatebtn;
    QPushButton *sccutbtn;
    QPushButton *savebtn;
    KingLineEdit *propriceedit;
    QLabel *label_5;
    QComboBox *searchedit;
    QLabel *label_7;
    KingLineEdit *prourl2edit;
    QLabel *label_8;
    KingLineEdit *prourl3edit;
    QLabel *label_9;
    KingLineEdit *prourl4edit;
    QTextEdit *proimgedit;
    QLabel *label_10;
    QLabel *pnamechecklabel;
    QLabel *ppricechecklabel;
    QLabel *label_13;
    QLabel *purl1checklabel;
    QLabel *purl2checklabel;
    QLabel *purl3checklabel;
    QLabel *purl4checklabel;
    QLabel *imgchecklabel;
    QGroupBox *groupBox;
    QLabel *checkresultlabel;
    //Ui::KingHelpMain *ui;
    KingDataCache *m_datacache;
    SearchFrame *m_searcheEdit;
    WoldTransitionSpell *m_tsObj;
    QSystemTrayIcon *m_trayIcon;
    KingScreenCut   m_screencut ;
};

#endif // KINGHELPMAIN_H
