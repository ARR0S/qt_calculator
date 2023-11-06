#include <QApplication>
#include <QStyleFactory>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#212121")); // Цвет фона окна
    w.setPalette(palette);
    w.setStyleSheet(w.style);
    w.show();
    return a.exec();
}
