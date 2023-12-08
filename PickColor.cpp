/************************************************************************/
/* email cfl997@163.com                                                 */
/************************************************************************/
#include "PickColor.h"
#include "ui_PickColor.h"
#include <qfile.h>
#include <QMouseEvent>
#include <QColor>
#include <QScreen>
#include <QPalette>
#include <QClipboard>
namespace Ui {
class PickColor;
}

struct PickColor::PrivateData
{
    bool GettingColor=false;
    QColor m_color=QColor(QString(u8"#404244"));
    void updateUi(bool ischange=true);
    Ui::PickColor ui;
    bool isPbPick=false;
    QString m_colorStr;
};
QString converRGB16HexStr(QColor _color) {
     //r的rgb转化为16进制
     QString redStr = QString("%1").arg(_color.red(),2,16,QChar('0'));
     //g的rgb转化为16进制
     QString greenStr = QString("%1").arg(_color.green(),2,16,QChar('0'));
     //b的rgb转化为16进制
     QString blueStr = QString("%1").arg(_color.blue(),2,16,QChar('0'));
     //a的alpha
     QString alphaStr=QString("%1").arg(_color.alpha(),2,16,QChar('0'));
     //将各rgb的拼接在一起形成#000000
     QString hexStr = "#"+redStr+greenStr+blueStr+alphaStr;
     //返回hexStr
     return hexStr;
     }


PickColor::PickColor(QWidget *parent) :
    MyDialog (parent),
    m_priv(new PrivateData)
{
    auto &d=*m_priv;
    d.ui.setupUi(this);

    QObject::connect(d.ui.pbClose,&QPushButton::clicked,this,[this](){
        close();
    });
    QObject::connect(d.ui.pbPick,&QPushButton::clicked,this,[&d]()
    {
        d.isPbPick=true;
    });
    QObject::connect(d.ui.pbCopy,&QPushButton::clicked,this,[&d](){
        QClipboard *clip = QApplication::clipboard();
        clip->setText(d.m_colorStr);
    });

        installEventFilter(this);
        d.updateUi();
}

PickColor::~PickColor()
{
    if(m_priv)
    {
        delete m_priv;
        m_priv=nullptr;
    }
}
bool PickColor::eventFilter(QObject *watched, QEvent *event)
{
    auto &d = *m_priv;
    if (event->type() == QEvent::Enter&&d.GettingColor == false)
    {
        setCursor(Qt::PointingHandCursor);
    }
    if (event->type() == QEvent::MouseButtonPress&& d.isPbPick)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->button() == Qt::LeftButton)
        {
            d.GettingColor = true;
            setCursor(Qt::CrossCursor);
            return true;
        }

    }
    else if (d.GettingColor == true && event->type() == QEvent::MouseMove)//实时颜色变化
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->button() != Qt::LeftButton && (mouseEvent->buttons() & Qt::LeftButton))
        {
            QPoint mouse_local_pos = QCursor::pos();
            QScreen *screen = QGuiApplication::primaryScreen();

            QPixmap pixmap = screen->grabWindow(0, mouse_local_pos.x(), mouse_local_pos.y(), 1, 1);
            d.m_color = pixmap.toImage().pixel(0, 0);
            d.updateUi();
            return true;
        }
    }
    else if (d.GettingColor == true && event->type() == QEvent::MouseButtonRelease)//最终选取
    {
        d.GettingColor = false;
        d.isPbPick=false;
        QPoint mouse_local_pos = QCursor::pos();
        QScreen *screen = QGuiApplication::primaryScreen();

        QPixmap pixmap = screen->grabWindow(0, mouse_local_pos.x(), mouse_local_pos.y(), 1, 1);
        d.m_color = pixmap.toImage().pixel(0, 0);
        //        emit sendColorPickData_end(d.m_color);

        d.updateUi();
        setCursor(Qt::ArrowCursor);
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void PickColor::PrivateData::updateUi(bool ischange)
{
    ui.dspR->setValue(m_color.red());
    ui.dspG->setValue(m_color.green());
    ui.dspB->setValue(m_color.blue());
    ui.dspA->setValue(m_color.alpha());

    ui.pbColor->setAutoFillBackground(true);
    ui.pbColor->setFlat(true);
    QPalette palette = ui.pbColor->palette();
    palette.setColor(QPalette::Button,m_color);
    ui.pbColor->setPalette(palette);

    m_colorStr=converRGB16HexStr(m_color);
    ui.le16->setText(m_colorStr);
//    ui.le16->setText(converRGB16HexStr(m_color));
}

