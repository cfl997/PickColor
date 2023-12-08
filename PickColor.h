#ifndef PICKCOLOR_H
#define PICKCOLOR_H

#include <QDialog>
#include "MyDialog.h"


class PickColor : public MyDialog
{
    Q_OBJECT

public:
    explicit PickColor(QWidget *parent = nullptr);
    ~PickColor();

    virtual bool eventFilter(QObject *watched, QEvent *event)override;
private:

    struct PrivateData;
    PrivateData *m_priv;
};

#endif // PICKCOLOR_H
