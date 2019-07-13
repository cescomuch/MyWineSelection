#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <QString>
#include <iostream>

class MyException {
private:
    QString what;
public:
    MyException(QString w): what(w){}

    QString getWhat() const{return what;}
    void printError()const {std::cout<<"L'errore e': "<<getWhat().toStdString();}
};

#endif // MYEXCEPTION_H
