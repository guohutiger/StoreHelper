#ifndef KINGLINEEDIT_H
#define KINGLINEEDIT_H

#include <QDebug>
#include <QClipboard>
#include <QLineEdit>

class KingLineEdit : public QLineEdit
{
    Q_OBJECT
    
public:
    explicit KingLineEdit(QWidget *parent = 0);
    ~KingLineEdit();

public slots:
    bool eventFilter(QObject *,QEvent *);    //◊¢“‚’‚¿Ô
    
};

#endif // KINGLINEEDIT_H
