#include "kinglineedit.h"
#include "ui_kinglineedit.h"

KingLineEdit::KingLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    installEventFilter(this);
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：
**********************************************/
KingLineEdit::~KingLineEdit()
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
