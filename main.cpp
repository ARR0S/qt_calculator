#include "Calculator.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#212121")); // Цвет фона окна
    w.setPalette(palette);
    w.setStyleSheet("background-color: #212121;");
    w.show();
    return a.exec();
}
