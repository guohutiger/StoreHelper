#include "kinglineedit.h"
#include "ui_kinglineedit.h"

KingLineEdit::KingLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    installEventFilter(this);
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ��
**********************************************/
KingLineEdit::~KingLineEdit()
{
}

/**********************************************
* ��������������
* �������ܣ�
* ����Ĳ�������˵��
* ���������int userId
* ���������void
* ����ֵ  ��
**********************************************/
bool KingLineEdit::eventFilter(QObject *watched, QEvent *event)
{
  if (event->type()==QEvent::MouseButtonDblClick)
  {
      if(text().compare("")!= 0)
      {
         QClipboard *clipboard = QApplication::clipboard();
         clipboard->setText(text());
      }
  }
  else if (event->type()==QEvent::FocusOut)
  {
    this->selectionStart();
  }
 return QWidget::eventFilter(watched,event);
}
