#ifndef KINGCOMMONTOOLS_H
#define KINGCOMMONTOOLS_H

#include <QFile>
#include <QDebug>
#include <QObject>
#include <QDateTime>
#include <kingdbmanager.h>
#include <qdesktopservices.h>

class WoldTransitionSpell : public QObject
{
    Q_OBJECT
public:
    static WoldTransitionSpell *instance();

    static void releaseDB();

    ~WoldTransitionSpell();

    QChar TransitionSpell(QString word);

    bool loadDataInfo();

protected:
    explicit WoldTransitionSpell(QObject *parent = 0);

private:
    int m_iDBState;
};


class kingcommontools : public QObject
{
    Q_OBJECT
public:
    explicit kingcommontools(QObject *parent = 0);

    static QString getkkTempleFilePath();
    static QString fiveRandomSerialNumber();
    
signals:
    
public slots:
    
};

#endif // KINGCOMMONTOOLS_H
