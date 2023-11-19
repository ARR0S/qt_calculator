#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    QFile styleFile(":/Calculator/StyleSheet.css");
    styleFile.open(QFile::ReadOnly | QFile::Text);
    QString style = styleFile.readAll();
    styleFile.close();
    a.setStyleSheet(style);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#212121")); // Цвет фона окна
    w.setPalette(palette);
    w.show();
    return a.exec();
}
