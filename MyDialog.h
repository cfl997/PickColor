#pragma once
#include <qdialog.h>

class MyDialog : public QDialog
{

	Q_OBJECT;
	Q_PROPERTY(QFont titlebarfont MEMBER titlebarfont NOTIFY titlebarChanged);
	Q_PROPERTY(int titlebarfontsize MEMBER titlebarfontsize NOTIFY titlebarChanged);
	Q_PROPERTY(QColor titlebarcolor MEMBER titlebarcolor NOTIFY titlebarChanged);

public:

	MyDialog(QWidget *parent=nullptr);
            using Super=QDialog;
signals:
	void titlebarChanged();
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event)override;
	virtual void paintEvent(QPaintEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event)override;
private:
	int m_nMouseClick_X_Coordinate;
	int m_nMouseClick_Y_Coordinate;
	bool m_moving = false;
	QFont titlebarfont;
	int titlebarfontsize = 16;
	QColor titlebarcolor;
};
