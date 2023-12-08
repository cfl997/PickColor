/************************************************************************/
/* email cfl997@163.com                                                 */
/************************************************************************/
#include "MyDialog.h"
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>

MyDialog::MyDialog(QWidget *parent):QDialog(parent, Qt::FramelessWindowHint)
{
}

bool MyDialog::eventFilter(QObject *watched, QEvent *event)
{
    return Super::eventFilter(watched,event);
}

void MyDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    QStyle *style = this->style();
    QRect active_area = this->rect();
    int titlebar_height = 0;

    // Titlebar.
    QStyleOptionTitleBar t_opt;
    t_opt.initFrom(this);

    titlebar_height = style->pixelMetric(QStyle::PM_TitleBarHeight, &t_opt, this);


    t_opt.rect = QRect(0, 0, this->width(), titlebar_height);
    t_opt.titleBarState = this->windowState();
    titlebarfont.setPixelSize(titlebarfontsize);

    t_opt.fontMetrics = QFontMetrics(titlebarfont);

    t_opt.text = t_opt.fontMetrics.elidedText(this->windowTitle(), Qt::ElideRight, t_opt.rect.width());
    style->drawComplexControl(QStyle::CC_TitleBar, &t_opt, &p, this);
    auto oldFont = p.font();
    p.setFont(titlebarfont);
    style->drawItemText(&p, t_opt.rect, Qt::AlignCenter, t_opt.palette, true, t_opt.text,
                        QPalette::WindowText);
    p.setFont(oldFont);

    // Background widget.
    active_area.setTopLeft(QPoint(0, titlebar_height));
    this->setContentsMargins(0, titlebar_height, 0, 0);

    QStyleOption w_opt;
    w_opt.initFrom(this);
    w_opt.rect = active_area;
    style->drawPrimitive(QStyle::PE_Widget, &w_opt, &p, this);
}


void MyDialog::mousePressEvent(QMouseEvent *event)
{
    int titlebar_height = 0;
    // Titlebar.
    QStyleOptionTitleBar t_opt;
    t_opt.initFrom(this);

    QStyle *style = this->style();
    titlebar_height = style->pixelMetric(QStyle::PM_TitleBarHeight, &t_opt, this);

    if (event->y() < titlebar_height)
    {
        m_moving = true;
    }
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MyDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_moving)
    {
        m_moving = false;
    }
}

void MyDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_moving)
    {
        move(event->globalX() - m_nMouseClick_X_Coordinate, event->globalY() - m_nMouseClick_Y_Coordinate);
    }
}
