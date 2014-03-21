#ifndef KINGSCREENCUT_H
#define KINGSCREENCUT_H
#include <QtGui/QDialog>
#include <QSize>
#include <QPoint>
#include <QCursor>
#include <QColor>
#include <QAction>
#include <QMenu>
#include <QFile>
#include <QDebug>
#include <QClipboard>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QApplication>
#include <QInputDialog>
#include <QDateTime>
#include <qdesktopwidget.h>

//class QFile;
//class QPixmap;
//class QMenu;
//class QAction;
class KingScreenCut : public QDialog
{
    Q_OBJECT

public:
    struct posInfo
    {
        QPoint tlp,
                trp,
                blp,
                brp;
    };
    QPoint p1,p2;
    KingScreenCut(QWidget *parent = 0,QColor selectedColor=QColor(0,0,255),int quality=-1);
    ~KingScreenCut(){delete screen;delete fogPix;}
    QString fiveRandomSerialNumber();
    void reset();
private:
    QPixmap *screen,
            *fogPix;
    posInfo pos;
    bool rightPressed,
        leftPressed,
        done,
        pull;
    int moved;
    bool runOnce;
    bool bresize;
    bool showm;
    QColor sColor;
    QPoint start;
    QString fileName;
    QFile *file;
    QSize fullSize;
    QCursor cursor;
    QMenu *menu;
    QAction *saveAt,
            *closeAt,
            *saveTdb,
            *saveTob,
            *savedAt,
            *helpAt,
            *fixedSizeAt;
    int quality;
    QString savedFileName;

    void figPos(const QPoint&,const QPoint&);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyReleaseEvent(QKeyEvent *);
private slots:
    void saveImage();
    void saveBoard();
    void emitHelp();
    void saveImageTodb();
    void setMySize(int,int);
    void input();
    void inputSize(const QString &);
signals:
    void closed();
    void showHelp();
};

#endif // KINGSCREENCUT_H
