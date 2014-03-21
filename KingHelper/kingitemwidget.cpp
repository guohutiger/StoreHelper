#include "kingitemwidget.h"
#include "ui_kingitemwidget.h"

KingItemWidget::KingItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KingItemWidget)
{
    ui->setupUi(this);
   // ui->itemImgLabel->resize(ui->itemImgLabel->width(),this->height());
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
KingItemWidget::~KingItemWidget()
{
    delete ui;
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
void KingItemWidget::setItemData(QString img,QString title,QString desc)
{
   ui->itemDescLabel->setText(desc);
   ui->itemImgLabel->setPixmap(QPixmap(img));
   ui->itemTitleLabel->setText(title);
}
