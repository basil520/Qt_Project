#include <QApplication>
#include <QDesktopWidget>


#include "src/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    const QDesktopWidget* desktop = QApplication::desktop();
    MainWindow mw;
    mw.move((desktop->width() - mw.width()) / 2, (desktop->height() - mw.height()) / 2);
    mw.show();
    return QApplication::exec();
}

