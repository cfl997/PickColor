/************************************************************************/
/* email cfl997@163.com                                                 */
/************************************************************************/
#include "PickColor.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":theme/my.qss");
    if( file.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(file.readAll());
        a.setStyleSheet(style);
        file.close();
    }
    else
    {
       qDebug("Open failed");
    }

    PickColor w;
    w.show();

    return a.exec();
}
