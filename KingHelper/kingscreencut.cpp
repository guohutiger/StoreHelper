#include "kingscreencut.h"

KingScreenCut::KingScreenCut(QWidget *parent,QColor selectedColor,int quality)
    : QDialog(parent),quality(quality),sColor(selectedColor)
{
    saveTdb=new QAction(tr("保存到产品"),this);
    saveTdb->setIcon(QIcon(":/image/todb.png"));
    saveAt=new QAction(tr("保存到文件"),this);
    saveAt->setIcon(QIcon(":/image/save.png"));
    saveTob=new QAction(tr("保存到剪贴板"),this);
    saveTob->setIcon(QIcon(":/image/savetob.png"));
    closeAt=new QAction(tr("退出"),this);
    closeAt->setIcon(QIcon(":/image/quit.png"));
    helpAt=new QAction(tr("使用帮助"),this);
    helpAt->setIcon(QIcon(":/image/help.png"));
    fixedSizeAt=new QAction(tr("设置固定尺寸"),this);
    fixedSizeAt->setIcon(QIcon(":/image/fixedsize.png"));
    menu=new QMenu(tr("截图菜单"),this);
    menu->setStyleSheet("background-image:url(:/image/back.png);color:white");
    menu->addAction(saveTdb);
    menu->addAction(saveAt);
    menu->addAction(saveTob);
    menu->addSeparator();
    menu->addAction(fixedSizeAt);
    menu->addSeparator();
    menu->addAction(helpAt);
    menu->addSeparator();
    menu->addAction(closeAt);
    connect(saveAt,SIGNAL(triggered()),this,SLOT(saveImage()));
    connect(saveTob,SIGNAL(triggered()),this,SLOT(saveBoard()));
    connect(closeAt,SIGNAL(triggered()),this,SLOT(close()));
    connect(helpAt,SIGNAL(triggered()),this,SLOT(emitHelp()));
    connect(fixedSizeAt,SIGNAL(triggered()),this,SLOT(input()));
    connect(saveTdb,SIGNAL(triggered()),this,SLOT(saveImageTodb()));
    this->setMouseTracking(true);
    leftPressed=rightPressed=runOnce=done=pull=bresize=showm=false;
    fullSize=QApplication::desktop()->size();
    this->resize(fullSize);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    //this->hide();
    //获取了当前屏幕并存储在pixmap
    screen=new QPixmap(QPixmap::grabWindow(QApplication::desktop()->winId(),
                                           0,0,fullSize.width(),fullSize.height()));
    //新建一层朦胧屏幕
    fogPix=new QPixmap(*screen);
    QPixmap fog(fullSize.width(),fullSize.height());
    fog.fill(QColor(182,182,182,192));
    QPainter painter(fogPix);
    painter.drawPixmap(0,0,fog);
    painter.setPen(QPen(QColor(255,255,0)));
    painter.drawText(fullSize.width()/2-50,50,tr("如需使用帮助，请按F1"));
}

void KingScreenCut::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::yellow);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawPixmap(0,0,*fogPix);
    QPainter painterInfo(this);
    if(pos.tlp.x()!=pos.brp.x()&&
            pos.tlp.y()!=pos.brp.y())
    {
        QPoint zPoint(1,1);

        painterInfo.setPen(QPen(sColor));
        painterInfo.drawRect(QRect(pos.tlp-zPoint,pos.brp));
        painterInfo.drawRect(pos.tlp.x()-3,pos.tlp.y()-3,3,3);
        painterInfo.drawRect(pos.trp.x(),pos.trp.y()-3,3,3);
        painterInfo.drawRect(pos.blp.x()-3,pos.blp.y()+1,3,3);
        painterInfo.drawRect(pos.brp.x()+1,pos.brp.y()+1,3,3);

        painterInfo.drawRect((pos.tlp.x()+pos.trp.x())/2-2,
                             (pos.tlp.y()-4),3,3);
        painterInfo.drawRect(pos.tlp.x()-4,
                             (pos.tlp.y()+pos.blp.y())/2-2,3,3);
        painterInfo.drawRect(pos.trp.x()+1,
                             (pos.trp.y()+pos.brp.y())/2-2,3,3);
        painterInfo.drawRect((pos.blp.x()+pos.brp.x())/2-2,
                             pos.blp.y()+1,3,3);
        painterInfo.drawPixmap(pos.tlp,
                               screen->copy(QRect(pos.tlp,pos.brp)));
        painterInfo.setBrush(QBrush(QColor(200,200,200,165)));
        painterInfo.setPen(QPen(QColor(200,200,200,165)));
        painterInfo.drawRect(pos.tlp.x(),pos.tlp.y()>=40?
                                 pos.tlp.y()-40:pos.tlp.y(),150,40);
        painterInfo.setPen(QPen(Qt::black));
        painterInfo.drawText(pos.tlp.x()+10,
                            pos.tlp.y()>=40?pos.tlp.y()-25:pos.tlp.y()+15,
                             tr("截图开始坐标(%1,%2)").arg(QString::number(pos.tlp.x()),
                                                     QString::number(pos.tlp.y())));
        painterInfo.drawText(pos.tlp.x()+10,
                             pos.tlp.y()>=40?pos.tlp.y()-10:pos.tlp.y()+30,
                             tr("截图尺寸大小(%1,%2)").arg(QString::number(pos.brp.x()-pos.tlp.x()),
                                                     QString::number(pos.brp.y()-pos.tlp.y())));
    }
    else
    {
        cursor.setShape(Qt::ArrowCursor);
        this->setCursor(cursor);
    }
}
void KingScreenCut::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        leftPressed=true;
        if(!(e->globalPos().x()>pos.tlp.x()&&
             e->globalPos().y()>pos.tlp.y()&&
             e->globalPos().x()<pos.brp.x()&&
             e->globalPos().y()<pos.brp.y())&&
                !(e->globalPos().x()>=pos.tlp.x()-5&&
                  e->globalPos().x()<=pos.tlp.x()-1&&
                  e->globalPos().y()>=pos.tlp.y()-5&&
                  e->globalPos().y()<=pos.tlp.y()-1)&&
                !(e->globalPos().x()>=pos.trp.x()+1&&
                  e->globalPos().x()<=pos.trp.x()+5&&
                  e->globalPos().y()<=pos.trp.y()+1&&
                  e->globalPos().y()>=pos.trp.y()-5)&&
                !(e->globalPos().x()>=pos.blp.x()-5&&
                  e->globalPos().x()<=pos.blp.x()-1&&
                  e->globalPos().y()<=pos.blp.y()+5&&
                  e->globalPos().y()>=pos.blp.y()+1)&&
                !(e->globalPos().x()>=pos.brp.x()+1&&
                  e->globalPos().x()<=pos.brp.x()+5&&
                  e->globalPos().y()>=pos.brp.y()+1&&
                  e->globalPos().y()<=pos.brp.y()+5)&&
                !((e->globalPos().x()>=(pos.tlp.x()+pos.trp.x())/2-2&&
                   e->globalPos().x()<=(pos.tlp.x()+pos.trp.x())/2+2&&
                   e->globalPos().y()<=pos.tlp.y()-1&&
                   e->globalPos().y()>=pos.tlp.y()-4))&&
                !(e->globalPos().x()>=pos.tlp.x()-4&&
                  e->globalPos().x()<=pos.tlp.x()-1&&
                  e->globalPos().y()>=(pos.tlp.y()+pos.blp.y())/2-2&&
                  e->globalPos().y()<=(pos.tlp.y()+pos.blp.y())/2+2)&&
                !(e->globalPos().x()>=(pos.blp.x()+pos.brp.x())/2-2&&
                 e->globalPos().x()<=(pos.blp.x()+pos.brp.x())/2+2&&
                 e->globalPos().y()>=pos.blp.y()+1&&
                 e->globalPos().y()<=pos.blp.y()+4)&&
                !(e->globalPos().x()>=pos.trp.x()+1&&
                                e->globalPos().x()<=pos.trp.x()+4&&
                                e->globalPos().y()>=(pos.trp+pos.brp).y()/2-2&&
                                e->globalPos().y()<=(pos.trp+pos.brp).y()/2+2)) //不在所选的区域内
        {
            p1=e->globalPos();
            done=false;
        }
        if((e->globalPos().x()>pos.tlp.x()&&
            e->globalPos().y()>pos.tlp.y()&&
            e->globalPos().x()<pos.brp.x()&&
            e->globalPos().y()<pos.brp.y()))
        {
            pull=true;
        }
        if(e->globalPos().x()>=pos.tlp.x()-5&&
                e->globalPos().x()<=pos.tlp.x()-1&&
                e->globalPos().y()>=pos.tlp.y()-5&&
                e->globalPos().y()<=pos.tlp.y()-1)
        {
            bresize=true;
            moved=1;
        }
        if(e->globalPos().x()>=pos.trp.x()+1&&
                e->globalPos().x()<=pos.trp.x()+5&&
                e->globalPos().y()<=pos.trp.y()+1&&
                e->globalPos().y()>=pos.trp.y()-5)
        {
            bresize=true;
            moved=2;
        }
        if(e->globalPos().x()>=pos.blp.x()-5&&
                e->globalPos().x()<=pos.blp.x()-1&&
                e->globalPos().y()<=pos.blp.y()+5&&
                e->globalPos().y()>=pos.blp.y()+1)
        {
            bresize=true;
            moved=3;
        }
        if(e->globalPos().x()>=pos.brp.x()+1&&
                e->globalPos().x()<=pos.brp.x()+5&&
                e->globalPos().y()>=pos.brp.y()+1&&
                e->globalPos().y()<=pos.brp.y()+5)
        {
            bresize=true;
            moved=4;
        }
        if(e->globalPos().x()>=(pos.tlp.x()+pos.trp.x())/2-2&&
                e->globalPos().x()<=(pos.tlp.x()+pos.trp.x())/2+2&&
                e->globalPos().y()<=pos.tlp.y()-1&&
                e->globalPos().y()>=pos.tlp.y()-4)
        {
            bresize=true;
            moved=5;
        }
        if(e->globalPos().x()>=pos.tlp.x()-4&&
                e->globalPos().x()<=pos.tlp.x()-1&&
                e->globalPos().y()>=(pos.tlp.y()+pos.blp.y())/2-2&&
                e->globalPos().y()<=(pos.tlp.y()+pos.blp.y())/2+2)
        {
            bresize=true;
            moved=6;
        }
        if(e->globalPos().x()>=(pos.blp.x()+pos.brp.x())/2-2&&
                e->globalPos().x()<=(pos.blp.x()+pos.brp.x())/2+2&&
                e->globalPos().y()>=pos.blp.y()+1&&
                e->globalPos().y()<=pos.blp.y()+4)
        {
            bresize=true;
            moved=8;
        }
        if(e->globalPos().x()>=pos.trp.x()+1&&
                e->globalPos().x()<=pos.trp.x()+4&&
                e->globalPos().y()>=(pos.trp+pos.brp).y()/2-2&&
                e->globalPos().y()<=(pos.trp+pos.brp).y()/2+2)
        {
            bresize=true;
            moved=7;
        }
    }
    else if(e->button()==Qt::RightButton)
    {
        if(!(e->globalPos().x()>pos.tlp.x()&&
             e->globalPos().y()>pos.tlp.y()&&
             e->globalPos().x()<pos.brp.x()&&
             e->globalPos().y()<pos.brp.y())&&
                !(e->globalPos().x()>=pos.tlp.x()-5&&
                  e->globalPos().x()<=pos.tlp.x()-1&&
                  e->globalPos().y()>=pos.tlp.y()-5&&
                  e->globalPos().y()<=pos.tlp.y()-1)&&
                !(e->globalPos().x()>=pos.trp.x()+1&&
                  e->globalPos().x()<=pos.trp.x()+5&&
                  e->globalPos().y()<=pos.trp.y()+1&&
                  e->globalPos().y()>=pos.trp.y()-5)&&
                !(e->globalPos().x()>=pos.blp.x()-5&&
                  e->globalPos().x()<=pos.blp.x()-1&&
                  e->globalPos().y()<=pos.blp.y()+5&&
                  e->globalPos().y()>=pos.blp.y()+1)&&
                !(e->globalPos().x()>=pos.brp.x()+1&&
                  e->globalPos().x()<=pos.brp.x()+5&&
                  e->globalPos().y()>=pos.brp.y()+1&&
                  e->globalPos().y()<=pos.brp.y()+5)&&
                !(e->globalPos().x()>=(pos.tlp.x()+pos.trp.x())/2-2&&
                  e->globalPos().x()<=(pos.tlp.x()+pos.trp.x())/2+2&&
                  e->globalPos().y()<=pos.tlp.y()-1&&
                  e->globalPos().y()>=pos.tlp.y()-4)&&
                !(e->globalPos().x()>=pos.tlp.x()-4&&
                  e->globalPos().x()<=pos.tlp.x()-1&&
                  e->globalPos().y()>=(pos.tlp.y()+pos.blp.y())/2-2&&
                  e->globalPos().y()<=(pos.tlp.y()+pos.blp.y())/2+2)&&
                !(e->globalPos().x()>=(pos.blp.x()+pos.brp.x())/2-2&&
                 e->globalPos().x()<=(pos.blp.x()+pos.brp.x())/2+2&&
                 e->globalPos().y()>=pos.blp.y()+1&&
                 e->globalPos().y()<=pos.blp.y()+4)&&
                !(e->globalPos().x()>=pos.trp.x()+1&&
                                e->globalPos().x()<=pos.trp.x()+4&&
                                e->globalPos().y()>=(pos.trp+pos.brp).y()/2-2&&
                                e->globalPos().y()<=(pos.trp+pos.brp).y()/2+2)) //不在所选的区域内
        {
            this->reset();
            done=false;
            leftPressed=false;
            rightPressed=false;
            runOnce=false;
            bresize=false;
            pull=false;
            showm=false;
            this->update();
        }
        else
        {
            showm=true;
        }
    }
}
void KingScreenCut::mouseMoveEvent(QMouseEvent *e)
{
    if(leftPressed)
    {
        if(!done)
        {
            p2.setX(e->globalPos().x());
            p2.setY(e->globalPos().y());
            this->figPos(p1,p2);
            this->update();
        }
        if(bresize)
        {
            if(moved==1)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if(pos.tlp.x()+(e->globalPos().x()-start.x())<pos.brp.x()&&
                        pos.tlp.y()+(e->globalPos().y()-start.y())<pos.brp.y())
                {
                    pos.tlp.setX(pos.tlp.x()+(e->globalPos().x()-start.x()));
                    pos.tlp.setY(pos.tlp.y()+(e->globalPos().y()-start.y()));
                    this->figPos(pos.tlp,pos.brp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved==2)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if(pos.trp.x()+(e->globalPos().x()-start.x())>pos.blp.x()&&
                        pos.trp.y()+(e->globalPos().y()-start.y())<pos.blp.y())
                {
                    pos.trp.setX(pos.trp.x()+(e->globalPos().x()-start.x()));
                    pos.trp.setY(pos.trp.y()+(e->globalPos().y()-start.y()));
                    this->figPos(pos.trp,pos.blp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved==3)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if(pos.blp.x()+(e->globalPos().x()-start.x())<pos.trp.x()&&
                       pos.blp.y()+(e->globalPos().y()-start.y())>pos.trp.y())
                {
                    pos.blp.setX(pos.blp.x()+(e->globalPos().x()-start.x()));
                    pos.blp.setY(pos.blp.y()+(e->globalPos().y()-start.y()));
                    this->figPos(pos.blp,pos.trp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved==4)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if(pos.brp.x()+(e->globalPos().x()-start.x())>pos.tlp.x()&&
                        pos.brp.y()+(e->globalPos().y()-start.y())>pos.tlp.y())
                {
                    pos.brp.setX(pos.brp.x()+(e->globalPos().x()-start.x()));
                    pos.brp.setY(pos.brp.y()+(e->globalPos().y()-start.y()));
                    this->figPos(pos.brp,pos.tlp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved==5)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if(pos.tlp.y()+(e->globalPos().y()-start.y())<pos.blp.y())
                {
                    pos.tlp.setY(pos.tlp.y()+(e->globalPos().y()-start.y()));
                    this->figPos(pos.tlp,pos.brp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved==6)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if((pos.tlp.x()+(e->globalPos()-start).x())<pos.brp.x())
                {
                    pos.tlp.setX(pos.tlp.x()+(e->globalPos().x()-start.x()));
                    this->figPos(pos.tlp,pos.brp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved==8)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if(pos.blp.y()+(e->globalPos().y()-start.y())>pos.tlp.y())
                {
                    pos.blp.setY(pos.blp.y()+(e->globalPos().y()-start.y()));
                    this->figPos(pos.blp,pos.trp);
                }
                start=e->globalPos();
                this->update();
            }
            else if(moved=7)
            {
                if(!runOnce)
                {
                    start=e->globalPos();
                    runOnce=true;
                }
                if((pos.trp.x()+(e->globalPos()-start).x())>pos.blp.x())
                {
                    pos.trp.setX(pos.trp.x()+(e->globalPos().x()-start.x()));
                    this->figPos(pos.trp,pos.blp);
                }
                start=e->globalPos();
                this->update();
            }
        }
        if(pull)
        {
            if(!runOnce)
            {
                start=e->globalPos();
                runOnce=true;
            }
            if(pos.tlp.x()+e->globalPos().x()-start.x()>0&&
                    pos.tlp.x()+e->globalPos().x()-start.x()<=fullSize.width()&&
                    pos.tlp.y()+e->globalPos().y()-start.y()>0&&
                    pos.tlp.y()+e->globalPos().y()-start.y()<=fullSize.height()&&
                    pos.brp.x()+e->globalPos().x()-start.x()>=0&&
                    pos.brp.x()+e->globalPos().x()-start.x()<fullSize.width()&&
                    pos.brp.y()+e->globalPos().y()-start.y()>=0&&
                    pos.brp.y()+e->globalPos().y()-start.y()<=fullSize.height())
            {
                pos.tlp+=(e->globalPos()-start);
                pos.brp+=(e->globalPos()-start);
                this->figPos(pos.tlp,pos.brp);
            }
            else if(pos.tlp.x()+e->globalPos().x()-start.x()<=0&&
                    pos.blp.y()+e->globalPos().y()-start.y()<=fullSize.height()&&
                    pos.tlp.y()+e->globalPos().y()-start.y()>=0)//左边
            {
                pos.tlp.setX(0);
                pos.tlp.setY(pos.tlp.y()+e->globalPos().y()-start.y());
                pos.brp.setX(pos.brp.x()-pos.blp.x());
                pos.brp.setY(pos.brp.y()+e->globalPos().y()-start.y());
                this->figPos(pos.tlp,pos.brp);
            }
            else if(pos.tlp.y()+e->globalPos().y()-start.y()<=0&&
                    pos.tlp.x()+e->globalPos().x()-start.x()>=0&&
                    pos.trp.x()+e->globalPos().x()-start.x()<=fullSize.width())//上
            {
                pos.tlp.setY(0);
                pos.tlp.setX(pos.tlp.x()+e->globalPos().x()-start.x());
                pos.brp.setX(pos.brp.x()+e->globalPos().x()-start.x());
                pos.brp.setY(pos.tlp.y()+pos.blp.y()-pos.trp.y());
                this->figPos(pos.tlp,pos.brp);
            }
            else if(pos.brp.x()+e->globalPos().x()-start.x()>=fullSize.width()&&
                    pos.trp.y()+e->globalPos().y()-start.y()>=0&&
                    pos.brp.y()+e->globalPos().y()-start.y()<=fullSize.height())//右
            {
                pos.brp.setX(fullSize.width());
                pos.brp.setY(pos.brp.y()+e->globalPos().y()-start.y());
                pos.tlp.setX(fullSize.width()-(pos.trp.x()-pos.blp.x()));
                pos.tlp.setY(pos.tlp.y()+e->globalPos().y()-start.y());
                this->figPos(pos.tlp,pos.brp);
            }
            else if(pos.brp.y()+e->globalPos().y()-start.y()>=fullSize.height()&&
                    pos.brp.x()+e->globalPos().x()-start.x()<=fullSize.width()&&
                    pos.blp.x()+e->globalPos().x()-start.x()>=0)//下
            {
                pos.brp.setY(fullSize.height());
                pos.brp.setX(pos.brp.x()+e->globalPos().x()-start.x());
                pos.tlp.setX(pos.tlp.x()+e->globalPos().x()-start.x());
                pos.tlp.setY(pos.brp.y()-(pos.blp.y()-pos.trp.y()));
                this->figPos(pos.tlp,pos.brp);
            }
            start=e->globalPos();
            this->update();
        }

    }
    else
    {
        if(e->globalPos().x()>=pos.tlp.x()-5&&
                e->globalPos().x()<=pos.tlp.x()-1&&
                e->globalPos().y()>=pos.tlp.y()-5&&
                e->globalPos().y()<=pos.tlp.y()-1)
        {
            cursor.setShape(Qt::SizeFDiagCursor);
            this->setCursor(cursor);
        }
        else if((e->globalPos().x()>pos.tlp.x()&&
                 e->globalPos().y()>pos.tlp.y()&&
                 e->globalPos().x()<pos.brp.x()&&
                 e->globalPos().y()<pos.brp.y()))
        {
            cursor.setShape(Qt::SizeAllCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=pos.trp.x()+1&&
                e->globalPos().x()<=pos.trp.x()+5&&
                e->globalPos().y()<=pos.trp.y()+1&&
                e->globalPos().y()>=pos.trp.y()-5)
        {
            cursor.setShape(Qt::SizeBDiagCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=pos.blp.x()-5&&
                e->globalPos().x()<=pos.blp.x()-1&&
                e->globalPos().y()<=pos.blp.y()+5&&
                e->globalPos().y()>=pos.blp.y()+1)
        {
            cursor.setShape(Qt::SizeBDiagCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=pos.brp.x()+1&&
                e->globalPos().x()<=pos.brp.x()+5&&
                e->globalPos().y()>=pos.brp.y()+1&&
                e->globalPos().y()<=pos.brp.y()+5)
        {
            cursor.setShape(Qt::SizeFDiagCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=(pos.tlp.x()+pos.trp.x())/2-2&&
                e->globalPos().x()<=(pos.tlp.x()+pos.trp.x())/2+2&&
                e->globalPos().y()<=pos.tlp.y()-1&&
                e->globalPos().y()>=pos.tlp.y()-4)
        {
            cursor.setShape(Qt::SizeVerCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=pos.tlp.x()-4&&
                e->globalPos().x()<=pos.tlp.x()-1&&
                e->globalPos().y()>=(pos.tlp.y()+pos.blp.y())/2-2&&
                e->globalPos().y()<=(pos.tlp.y()+pos.blp.y())/2+2)
        {
            cursor.setShape(Qt::SizeHorCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=(pos.blp.x()+pos.brp.x())/2-2&&
                e->globalPos().x()<=(pos.blp.x()+pos.brp.x())/2+2&&
                e->globalPos().y()>=pos.blp.y()+1&&
                e->globalPos().y()<=pos.blp.y()+4)
        {
            cursor.setShape(Qt::SizeVerCursor);
            this->setCursor(cursor);
        }
        else if(e->globalPos().x()>=pos.trp.x()+1&&
                e->globalPos().x()<=pos.trp.x()+4&&
                e->globalPos().y()>=(pos.trp+pos.brp).y()/2-2&&
                e->globalPos().y()<=(pos.trp+pos.brp).y()/2+2)
        {
            cursor.setShape(Qt::SizeHorCursor);
            this->setCursor(cursor);
        }
        else
        {
            QCursor cursor;
            cursor.setShape(Qt::ArrowCursor);
            this->setCursor(cursor);
        }

    }

    if(rightPressed)
    {

    }
}
void KingScreenCut::mouseReleaseEvent(QMouseEvent *e)
{
    leftPressed=false;
    runOnce=false;
    done=true;
    bresize=false;
    pull=false;
    if(e->button()==Qt::RightButton)
    {
        if(!(e->globalPos().x()>pos.tlp.x()&&
             e->globalPos().y()>pos.tlp.y()&&
             e->globalPos().x()<pos.brp.x()&&
             e->globalPos().y()<pos.brp.y())&&
                !(e->globalPos().x()>=pos.tlp.x()-5&&
                  e->globalPos().x()<=pos.tlp.x()-1&&
                  e->globalPos().y()>=pos.tlp.y()-5&&
                  e->globalPos().y()<=pos.tlp.y()-1)&&
                !(e->globalPos().x()>=pos.trp.x()+1&&
                  e->globalPos().x()<=pos.trp.x()+5&&
                  e->globalPos().y()<=pos.trp.y()+1&&
                  e->globalPos().y()>=pos.trp.y()-5)&&
                !(e->globalPos().x()>=pos.blp.x()-5&&
                  e->globalPos().x()<=pos.blp.x()-1&&
                  e->globalPos().y()<=pos.blp.y()+5&&
                  e->globalPos().y()>=pos.blp.y()+1)&&
                !(e->globalPos().x()>=pos.brp.x()+1&&
                  e->globalPos().x()<=pos.brp.x()+5&&
                  e->globalPos().y()>=pos.brp.y()+1&&
                  e->globalPos().y()<=pos.brp.y()+5))
        {}
        else
        {
            if(showm)
            {
                menu->exec(e->globalPos());
            }
        }
    }
    rightPressed=false;
    showm=false;
    //cursor.setShape(Qt::ArrowCursor);
    //this->setCursor(cursor);
}
void KingScreenCut::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Left:
        if(pos.tlp.x()-1>=0)
        {
            pos.tlp.setX(pos.tlp.x()-1);
            pos.brp.setX(pos.brp.x()-1);
        }
        break;
    case Qt::Key_Right:
        if(pos.blp.x()+1<=fullSize.width())
        {
            pos.tlp.setX(pos.tlp.x()+1);
            pos.brp.setX(pos.brp.x()+1);
            this->figPos(pos.tlp,pos.brp);
        }
        break;
    case Qt::Key_Up:
        if(pos.tlp.y()-1>=0)
        {
            pos.tlp.setY(pos.tlp.y()-1);
            pos.brp.setY(pos.brp.y()-1);
            this->figPos(pos.tlp,pos.brp);
        }
        break;
    case Qt::Key_Down:
        if(pos.brp.y()+1<=fullSize.height())
        {
            pos.tlp.setY(pos.tlp.y()+1);
            pos.brp.setY(pos.brp.y()+1);
            this->figPos(pos.tlp,pos.brp);
        }
        break;
    case Qt::Key_Enter:
        this->saveImage();
        break;
    case Qt::Key_Escape:
        this->close();
        this->destroy();
        emit closed();
        break;
    case Qt::Key_Space:
        this->saveBoard();
    default:
        break;
    }
    this->update();
}
void KingScreenCut::saveImage()
{
    QString tmpTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    QString slcStr;
    QPoint end=pos.brp;
    end.setX(end.x()-1);
    end.setY(end.y()-1);
    fileName=QFileDialog::getSaveFileName(this,tr("保存截图"),
                                              "HP"+tmpTime,
                                              tr("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)"),&slcStr);
    if(slcStr.left(3)=="JPG")
    {
        if(fileName.right(3)!="jpg")
        {
            fileName+=".jpg";
        }
    }
    if(slcStr.left(3)=="PNG")
    {
        if(fileName.right(3)!="png")
        {
            fileName+=".png";
        }
    }
    if(slcStr.left(3)=="BMP")
    {
        if(fileName.right(3)!="bmp")
        {
            fileName+=".bmp";
        }
    }
    if(!fileName.isEmpty())
    {
        file=new QFile(fileName);
    }
    else
        return;
    QFileInfo fileInfo(fileName);
    savedFileName = fileName;
    QString ext=fileInfo.suffix();
    if(file->open(QIODevice::WriteOnly))
    {
        screen->copy(QRect(pos.tlp,end)).save(file,ext.toStdString().c_str(),quality);
        qDebug()<<ext;
        file->close();
    }
    delete file;
    this->close();
}

void KingScreenCut::saveImageTodb()
{
    QString tmpTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    QString slcStr;
    QPoint end=pos.brp;
    end.setX(end.x()-1);
    end.setY(end.y()-1);
    fileName = "HP"+tmpTime+".png";
    if(!fileName.isEmpty())
    {
        file=new QFile(fileName);
    }
    else
        return;
    QFileInfo fileInfo(fileName);
    savedFileName = fileName;
    QString ext=fileInfo.suffix();
    if(file->open(QIODevice::WriteOnly))
    {
        screen->copy(QRect(pos.tlp,end)).save(file,ext.toStdString().c_str(),quality);
        qDebug()<<ext;
        file->close();
    }
    if(savedFileName.compare("") != 0)
    {
        qDebug()<< savedFileName;
    }
    delete file;
    this->close();
}
void KingScreenCut::saveBoard()
{
    QApplication::clipboard()->setImage(screen->copy(QRect(pos.tlp,pos.brp)).toImage());
    this->close();
}
void KingScreenCut::reset()
{
    QPoint zeroP(0,0);
    pos.blp=zeroP;
    pos.brp=zeroP;
    pos.tlp=zeroP;
    pos.trp=zeroP;
}
void KingScreenCut::figPos(const QPoint& p1,const QPoint& p2)
{
    if(p1.x()<p2.x()&&
            p1.y()<p2.y())
    {
        pos.tlp=p1;
        pos.trp.setX(p2.x());
        pos.trp.setY(p1.y());
        pos.blp.setX(p1.x());
        pos.blp.setY(p2.y());
        pos.brp=p2;
    }
    else if(p1.x()>p2.x()&&
            p1.y()<p2.y())
    {
        pos.tlp.setX(p2.x());
        pos.tlp.setY(p1.y());
        pos.trp=p1;
        pos.blp=p2;
        pos.brp.setX(p1.x());
        pos.brp.setY(p2.y());
    }
    else if(p1.x()<p2.x()&&
            p1.y()>p2.y())
    {
        pos.tlp.setX(p1.x());
        pos.tlp.setY(p2.y());
        pos.trp=p2;
        pos.brp=p1;
        pos.brp.setX(p2.x());
        pos.brp.setY(p1.y());
    }
    else if(p1.x()>p2.x()&&
            p1.y()>p2.y())
    {
        pos.tlp=p2;
        pos.trp.setX(p1.x());
        pos.trp.setY(p2.y());
        pos.blp.setX(p2.x());
        pos.blp.setY(p1.y());
        pos.brp=p1;
    }
}
void KingScreenCut::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton&&
            (e->globalPos().x()>pos.tlp.x()&&
             e->globalPos().y()>pos.tlp.y()&&
             e->globalPos().x()<pos.brp.x()&&
             e->globalPos().y()<pos.brp.y()))
    {
        this->saveBoard();
        this->saveImageTodb();
    }
}
void KingScreenCut::emitHelp()
{
    emit showHelp();
}
void KingScreenCut::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_F1:
        emit emitHelp();
        break;
    default:
        QDialog::keyReleaseEvent(e);
        break;
    }
}
void KingScreenCut::setMySize(int n1, int n2)
{
    if(n1!=0)
    {
        if(pos.tlp.x()+n1>=fullSize.width())
        {
            pos.brp.setX(fullSize.width());
        }
        else
        {
            pos.brp.setX(pos.tlp.x()+n1);
        }
        this->figPos(pos.tlp,pos.brp);
        this->update();
    }
    if(n2!=0)
    {
        if(pos.tlp.y()+n2>=fullSize.height())
        {
            pos.brp.setY(fullSize.height());
        }
        else
        {
            pos.brp.setY(pos.tlp.y()+n2);
        }
        this->figPos(pos.tlp,pos.brp);
        this->update();
    }
}
void KingScreenCut::inputSize(const QString& customSize)
{
    if (customSize.split("x").size() != 2)
        return;
    setMySize(customSize.split("x").at(0).toInt(),customSize.split("x").at(1).toInt());
}

void KingScreenCut::input()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("设置固定尺寸"),
        tr("固定尺寸:"), QLineEdit::Normal,
        "500x500", &ok);
    if (ok && !text.isEmpty())
        inputSize(text);
}

/**********************************************
* 作者姓名：郭虎
* 函数介绍：获取一个随机数
* 定义的参数含义说明
* 输入参数：int userId
* 输出参数：void
* 返回值  ：返回一个带时间的序列号格式为2013051911486089546
**********************************************/
QString KingScreenCut::fiveRandomSerialNumber()
{
    QString serials;
    int rands = qrand() % (8990 - 1000) + 1000;
    serials = QDateTime::currentDateTime().toString("yyyyMMddhhmmss")+ QString::number(rands);

    return serials;
}
