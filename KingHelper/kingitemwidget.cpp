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
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ��
**********************************************/
KingItemWidget::~KingItemWidget()
{
    delete ui;
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ��
**********************************************/
void KingItemWidget::setItemData(QString img,QString title,QString desc)
{
   ui->itemDescLabel->setText(desc);
   ui->itemImgLabel->setPixmap(QPixmap(img));
   ui->itemTitleLabel->setText(title);
}
