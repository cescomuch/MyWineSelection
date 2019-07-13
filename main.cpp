#include <QApplication>
#include <QFile>
#include "controller.h"
#include "model.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    Controller w(new Model());


    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    a.setStyleSheet(style);


    w.show();

    a.setWindowIcon(QIcon(":Immagini/icon.png"));

    w.show();

    return a.exec();
}
