#ifndef KINGITEMWIDGET_H
#define KINGITEMWIDGET_H

#include <QWidget>

namespace Ui {
class KingItemWidget;
}

class KingItemWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit KingItemWidget(QWidget *parent = 0);
    ~KingItemWidget();
    void setItemData(QString img,QString title,QString desc);
    
private:
    Ui::KingItemWidget *ui;
};

#endif // KINGITEMWIDGET_H
