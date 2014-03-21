#ifndef KINGWIDGETITEM_H
#define KINGWIDGETITEM_H

#include <QTreeWidgetItem>

class kingWidgetItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    explicit kingWidgetItem(QTreeWidget *parent = 0,int root = Type);

public:
    QString itemId;

    
signals:
    
public slots:
    
};

#endif // KINGWIDGETITEM_H
