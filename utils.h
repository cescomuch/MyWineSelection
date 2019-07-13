#ifndef UTILS_H
#define UTILS_H

#include <QPixmap>
#include<iostream>
#include <myexception.h>

using std::string;


/*
 * Classe per utilizzare la codifica a 64bit delle immagini
 */
class Img64{
public:
    Img64();
    static std::string getRawData(const QImage&);
    static QPixmap getImage(const std::string&);
};



/*
 * Due funzioni di utilità per la ricerca case sensitive di stringhe
 */
bool caseSensitiveToLower(unsigned char a, unsigned char b);
bool caseSensitive(std::string const& a, std::string const& b);



#endif // UTILS_H
