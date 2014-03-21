#include "kinghelpmain.h"
#include "kinghelpdef.h"
#include "ui_kinghelpmain.h"

//int oneAppOnly();
//HANDLE m_hEvent = NULL;

KingHelpMain::KingHelpMain(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    QPalette palette(QPalette::Background, QColor(94,148,162));
    setPalette(palette);
    setWindowIcon(QIcon(":/new/prefix1/resource/ico/tray.ico"));
    m_datacache = new  KingDataCache(this);
    m_tsObj = WoldTransitionSpell::instance();
    this->procodeEdit->setText(kingcommontools::fiveRandomSerialNumber());
    QRegExp reqexp("100000|([0-9]{0,5}[\.][0-9]{1,4})");
    this->propriceedit->setValidator(new QRegExpValidator(reqexp, this->propriceedit));
    m_searcheEdit = new SearchFrame(searchedit->x(),searchedit->height()+70,searchedit->width(),0,false,"",this);
    m_searcheEdit->hide();
    loadProductList();
    insertProductImage();
    createSysTray();
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::insertProductImage()
{
    QString strHtml = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head>\
    <meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body>\
    <p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><!--StartFragment-->\
    <img width = 250 height = 250 src=\"%1\" /><!--EndFragment--></p></body></html>").arg(":/new/prefix1/resource/test1.jpg");
    proimgedit->setHtml(strHtml);
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
KingHelpMain::~KingHelpMain()
{
   // delete ui;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::loadProductList()
{
    int index = 0;
    QSize itemSize;
    itemSize.setHeight(30);
    this->treeWidget->clear();

    QMap <QString,productItem>productsMap;
    productsMap = m_datacache->getAllProductItems();

    QMap <QString,productItem>::Iterator it = productsMap.begin();
    for(it ;it != productsMap.end();it++)
    {
        index+=1;
        kingWidgetItem* item = new kingWidgetItem(this->treeWidget,0);
        KingItemWidget *itemWidget = new KingItemWidget(this);
        item->setSizeHint(0, QSize(item->sizeHint(0).width(), 26));//设置行高
        item->itemId = it.value().productCode;
        itemWidget->setItemData(":/new/prefix1/resource/test1.jpg",it.value().productName,"该产品无相关描述");
        //item->setText(0,it.value().productCode);
        this->treeWidget->setItemWidget(item, 0, itemWidget);
        item->setSizeHint(0,itemSize);
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
void KingHelpMain::on_savebtn_clicked()
{
    int iRet = -1;
    int index = 0;
    QPalette tipcolor;
    productItem pitem;
    QString tipTxt = "";
    QString checklabeltxt = "";
    if(this->pronameedit->text().compare("") == 0)
    {
        index+=1;
        tipTxt  = "产品名称不建议为空!";
        checklabeltxt.append(QString::number(index)+"."+tipTxt +"\n");
        //this->pnamechecklabel->setPixmap(QPixmap(":/new/prefix1/resource/ico/warrning.ico"));
    }
    if(this->procodeEdit->text().compare("") == 0)
    {
         index+=1;
        tipTxt  = "产品编码不能为空!";
        checklabeltxt.append(QString::number(index)+"."+tipTxt +"\n");
    }
    if(this->propriceedit->text().compare("") == 0)
    {
         index+=1;
        tipTxt  = "产品价格不建议为空!";
        checklabeltxt.append(QString::number(index)+"."+tipTxt +"\n");
    }
    if(this->prourl1edit->text().compare("")== 0 && this->prourl2edit->text().compare("")== 0 &&this->prourl3edit->text().compare("")== 0 )
    {
        index+=1;
        tipTxt  = "产品地址不能为空!";
        checklabeltxt.append(QString::number(index)+"."+tipTxt +"\n");
    }
    if(tipTxt.compare("") != 0)
    {
        tipcolor.setColor(QPalette::WindowText,Qt::red);
        this->checkresultlabel->setPalette(tipcolor);
        this->checkresultlabel->setText(checklabeltxt);
        //QMessageBox::warning(this,"提示",tipTxt);
    }
    else
    {
        tipcolor.setColor(QPalette::WindowText,Qt::darkGreen);
        this->checkresultlabel->setPalette(tipcolor);
        pitem.productName = this->pronameedit->text();
        pitem.productCode = this->procodeEdit->text();
        pitem.productPrice= this->propriceedit->text();
        pitem.productUrl1 = this->prourl1edit->text();
        pitem.productUrl2 = this->prourl2edit->text();
        pitem.productUrl3 = this->prourl3edit->text();
        pitem.productDesc = "No describle";
        pitem.productNamePY = m_tsObj->TransitionSpell(pitem.productName);
        //pitem.productImage= this->proimgedit->text();

        tipTxt =kingcommontools::fiveRandomSerialNumber();
        this->pronameedit->clear();
        this->procodeEdit->setText(tipTxt);
        this->propriceedit->clear();
        this->prourl1edit->clear();
        this->prourl2edit->clear();
        this->prourl3edit->clear();
        this->proimgedit->clear();
        if (m_datacache)
        {
           iRet =  m_datacache->addNewProductItem(&pitem);
        }
        if(iRet == 1)
        {
            tipcolor.setColor(QPalette::WindowText,Qt::darkGreen);
            this->checkresultlabel->setPalette(tipcolor);
            this->checkresultlabel->setText("数据已保存！");
            loadProductList();
        }
        else
        {
            tipcolor.setColor(QPalette::WindowText,Qt::red);
            this->checkresultlabel->setPalette(tipcolor);
            this->checkresultlabel->setText("数据保存失败！");
        }
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
void KingHelpMain::on_addbtn_clicked()
{
     this->procodeEdit->setText(kingcommontools::fiveRandomSerialNumber());
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::on_updatebtn_clicked()
{

}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::on_sccutbtn_clicked()
{
    qDebug()<<"截图工具";
    m_screencut.show();
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::setupUi(QWidget *KingHelpMain)
{
    if (KingHelpMain->objectName().isEmpty())
        KingHelpMain->setObjectName(QString::fromUtf8("KingHelpMain"));
    KingHelpMain->resize(900, 700);
    KingHelpMain->setMinimumSize(QSize(900, 700));
    KingHelpMain->setMaximumSize(QSize(900, 700));
    QFont font;
    font.setStyleStrategy(QFont::PreferAntialias);
    KingHelpMain->setFont(font);
    KingHelpMain->setStyleSheet(QString::fromUtf8(""));
    KingHelpMain->setInputMethodHints(Qt::ImhNone);
    label_3 = new QLabel(KingHelpMain);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(40, 130, 60, 41));
    label_4 = new QLabel(KingHelpMain);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(40, 290, 61, 31));
    label = new QLabel(KingHelpMain);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(40, 63, 60, 31));
    label_2 = new QLabel(KingHelpMain);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(40, 100, 60, 31));
    label_6 = new QLabel(KingHelpMain);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(350, 10, 141, 41));
    label_6->setStyleSheet(QString::fromUtf8("font: 18pt \"Adobe Arabic\";"));
    pronameedit = new KingLineEdit(KingHelpMain);
    pronameedit->setObjectName(QString::fromUtf8("pronameedit"));
    pronameedit->setGeometry(QRect(110, 70, 321, 20));
    procodeEdit = new KingLineEdit(KingHelpMain);
    procodeEdit->setObjectName(QString::fromUtf8("procodeEdit"));
    procodeEdit->setGeometry(QRect(110, 100, 141, 20));
    QFont font1;
    font1.setBold(true);
    font1.setWeight(75);
    procodeEdit->setFont(font1);
    procodeEdit->setReadOnly(true);
    prourl1edit = new KingLineEdit(KingHelpMain);
    prourl1edit->setObjectName(QString::fromUtf8("prourl1edit"));
    prourl1edit->setGeometry(QRect(110, 140, 321, 20));
    treeWidget = new QTreeWidget(KingHelpMain);
    kingWidgetItem *__kingWidgetItem = new kingWidgetItem();
    __kingWidgetItem->setText(0, QString::fromUtf8("1"));
    treeWidget->setHeaderItem(__kingWidgetItem);
    treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
    treeWidget->setGeometry(QRect(480, 100, 411, 591));
    treeWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
    treeWidget->setContextMenuPolicy(Qt::NoContextMenu);
    treeWidget->setMidLineWidth(1);
    treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeWidget->setRootIsDecorated(true);
    treeWidget->setWordWrap(true);
    treeWidget->setHeaderHidden(true);
    treeWidget->header()->setVisible(false);
    treeWidget->header()->setCascadingSectionResizes(false);
    treeWidget->header()->setHighlightSections(false);
    treeWidget->header()->setMinimumSectionSize(21);
    treeWidget->header()->setStretchLastSection(true);
    addbtn = new QPushButton(KingHelpMain);
    addbtn->setObjectName(QString::fromUtf8("addbtn"));
    addbtn->setGeometry(QRect(140, 550, 75, 23));
    updatebtn = new QPushButton(KingHelpMain);
    updatebtn->setObjectName(QString::fromUtf8("updatebtn"));
    updatebtn->setGeometry(QRect(240, 550, 75, 23));
    sccutbtn = new QPushButton(KingHelpMain);
    sccutbtn->setObjectName(QString::fromUtf8("sccutbtn"));
    sccutbtn->setGeometry(QRect(340, 550, 75, 23));
    savebtn = new QPushButton(KingHelpMain);
    savebtn->setObjectName(QString::fromUtf8("savebtn"));
    savebtn->setGeometry(QRect(40, 550, 75, 23));
    propriceedit = new KingLineEdit(KingHelpMain);
    propriceedit->setObjectName(QString::fromUtf8("propriceedit"));
    propriceedit->setGeometry(QRect(300, 100, 131, 20));
    label_5 = new QLabel(KingHelpMain);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(260, 100, 41, 31));
    searchedit = new QComboBox(KingHelpMain);
    searchedit->setObjectName(QString::fromUtf8("searchedit"));
    searchedit->setGeometry(QRect(480, 70, 411, 22));
    searchedit->setEditable(true);
    label_7 = new QLabel(KingHelpMain);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(40, 170, 60, 41));
    prourl2edit = new KingLineEdit(KingHelpMain);
    prourl2edit->setObjectName(QString::fromUtf8("prourl2edit"));
    prourl2edit->setGeometry(QRect(110, 180, 321, 20));
    label_8 = new QLabel(KingHelpMain);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(40, 210, 60, 41));
    prourl3edit = new KingLineEdit(KingHelpMain);
    prourl3edit->setObjectName(QString::fromUtf8("prourl3edit"));
    prourl3edit->setGeometry(QRect(110, 220, 321, 20));
    label_9 = new QLabel(KingHelpMain);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(40, 250, 60, 41));
    prourl4edit = new KingLineEdit(KingHelpMain);
    prourl4edit->setObjectName(QString::fromUtf8("prourl4edit"));
    prourl4edit->setGeometry(QRect(110, 260, 321, 20));
    proimgedit = new QTextEdit(KingHelpMain);
    proimgedit->setObjectName(QString::fromUtf8("proimgedit"));
    proimgedit->setGeometry(QRect(40, 320, 391, 211));
    proimgedit->setFrameShape(QFrame::StyledPanel);
    proimgedit->setFrameShadow(QFrame::Sunken);
    label_10 = new QLabel(KingHelpMain);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(510, 9, 381, 51));
    label_10->setStyleSheet(QString::fromUtf8("font: 8pt \"Arial\";\n"
"color: rgb(0, 0, 255);"));
    label_10->setScaledContents(true);
    label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    label_10->setWordWrap(true);
    label_10->setOpenExternalLinks(true);
    pnamechecklabel = new QLabel(KingHelpMain);
    pnamechecklabel->setObjectName(QString::fromUtf8("pnamechecklabel"));
    pnamechecklabel->setGeometry(QRect(430, 70, 31, 21));
    ppricechecklabel = new QLabel(KingHelpMain);
    ppricechecklabel->setObjectName(QString::fromUtf8("ppricechecklabel"));
    ppricechecklabel->setGeometry(QRect(430, 100, 31, 21));
    label_13 = new QLabel(KingHelpMain);
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setGeometry(QRect(430, 140, 31, 21));
    purl1checklabel = new QLabel(KingHelpMain);
    purl1checklabel->setObjectName(QString::fromUtf8("purl1checklabel"));
    purl1checklabel->setGeometry(QRect(430, 140, 31, 21));
    purl2checklabel = new QLabel(KingHelpMain);
    purl2checklabel->setObjectName(QString::fromUtf8("purl2checklabel"));
    purl2checklabel->setGeometry(QRect(430, 180, 31, 21));
    purl3checklabel = new QLabel(KingHelpMain);
    purl3checklabel->setObjectName(QString::fromUtf8("purl3checklabel"));
    purl3checklabel->setGeometry(QRect(430, 220, 31, 21));
    purl4checklabel = new QLabel(KingHelpMain);
    purl4checklabel->setObjectName(QString::fromUtf8("purl4checklabel"));
    purl4checklabel->setGeometry(QRect(430, 260, 31, 21));
    imgchecklabel = new QLabel(KingHelpMain);
    imgchecklabel->setObjectName(QString::fromUtf8("imgchecklabel"));
    imgchecklabel->setGeometry(QRect(430, 510, 31, 21));
    groupBox = new QGroupBox(KingHelpMain);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(30, 580, 401, 111));
    checkresultlabel = new QLabel(groupBox);
    checkresultlabel->setObjectName(QString::fromUtf8("checkresultlabel"));
    checkresultlabel->setGeometry(QRect(3, 11, 391, 91));
    checkresultlabel->setScaledContents(true);
    checkresultlabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    checkresultlabel->setWordWrap(true);
    checkresultlabel->setMargin(5);
    checkresultlabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
    connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(slotTreeItemCicked(QTreeWidgetItem*,int)));
    connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(slotTreeItemDoubleCicked(QTreeWidgetItem*,int)));
    connect(searchedit,SIGNAL(editTextChanged(QString)),this,SLOT(slotSearchThisKey(QString)));


    retranslateUi(KingHelpMain);

    QMetaObject::connectSlotsByName(KingHelpMain);
} // setupUi

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::retranslateUi(QWidget *KingHelpMain)
{
    KingHelpMain->setWindowTitle(QApplication::translate("KingHelpMain", "KingHelpMain", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("KingHelpMain", "\351\223\276\346\216\245\345\234\260\345\235\2001\357\274\232", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("KingHelpMain", "\345\233\276\346\226\207\346\217\217\350\277\260\357\274\232", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("KingHelpMain", "\344\272\247\345\223\201\345\220\215\345\255\227\357\274\232", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("KingHelpMain", "\344\272\247\345\223\201\347\274\226\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("KingHelpMain", "\345\231\250\344\273\266\347\256\241\347\220\206\345\212\251\346\211\213", 0, QApplication::UnicodeUTF8));
    addbtn->setText(QApplication::translate("KingHelpMain", "\345\242\236\345\212\240", 0, QApplication::UnicodeUTF8));
    updatebtn->setText(QApplication::translate("KingHelpMain", "\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
    sccutbtn->setText("截图");
    savebtn->setText(QApplication::translate("KingHelpMain", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("KingHelpMain", "\344\273\267\346\240\274\357\274\232", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("KingHelpMain", "\351\223\276\346\216\245\345\234\260\345\235\2002\357\274\232", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("KingHelpMain", "\351\223\276\346\216\245\345\234\260\345\235\2003\357\274\232", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("KingHelpMain", "\351\223\276\346\216\245\345\234\260\345\235\2004\357\274\232", 0, QApplication::UnicodeUTF8));
    label_10->setText(QString());
    pnamechecklabel->setText(QString());
    ppricechecklabel->setText(QString());
    label_13->setText(QString());
    purl1checklabel->setText(QString());
    purl2checklabel->setText(QString());
    purl3checklabel->setText(QString());
    purl4checklabel->setText(QString());
    imgchecklabel->setText(QString());
    groupBox->setTitle(QApplication::translate("KingHelpMain", "\346\217\220\347\244\272\357\274\232", 0, QApplication::UnicodeUTF8));
    checkresultlabel->setText(QString());
} // retranslateUi

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::slotTreeItemCicked(QTreeWidgetItem*currItem,int index)
{
    kingWidgetItem *item = (kingWidgetItem *)currItem;
    qDebug()<<item->text(0)<<index<<item->itemId;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingHelpMain::slotTreeItemDoubleCicked(QTreeWidgetItem*currItem,int index)
{
//    kingWidgetItem *item = (kingWidgetItem *)currItem;
//    qDebug()<<item->text(0)<<index<<item->itemId;
}

void KingHelpMain::slotSearchThisKey(QString key)
{
    if(key.compare("")==0)
    {
        m_searcheEdit->hide();
    }
    else
    {
        m_searcheEdit->updateList(key);
        m_searcheEdit->show();
    }
}

void KingHelpMain::createSysTray()
{
    QIcon icon = QIcon(":/new/prefix1/resource/ico/tray.ico");
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(icon);
    m_trayIcon->setToolTip(tr("生命不息,奋斗不止！"));
    m_trayIcon->show();
    //createActions();
    //createTrayIcon();
    connect(m_trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void KingHelpMain::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick )//||reason == QSystemTrayIcon::Trigger)
    {
        if(this->isMinimized())
        {
        this->activateWindow();
        showNormal();
        }
        else if(this->isVisible())
        {
            this->showMinimized();
        }
    }
}
