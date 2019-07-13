#include "utils.h"

#include <QBuffer>
#include <QByteArray>

Img64::Img64() {}

std::string Img64::getRawData(const QImage &q){
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    q.save(&buffer, "PNG");

    return QString(byteArray.toBase64()).toStdString();}


QPixmap Img64::getImage(const std::string &i){
    QImage* image=new QImage;
    QByteArray array=QByteArray(i.data());
    image->loadFromData(QByteArray::fromBase64(array), "PNG");

    QPixmap p=QPixmap::fromImage(*image);

    return p.scaled(400,400,Qt::AspectRatioMode::KeepAspectRatio);} //modifica in caso le dimensioni








bool caseSensitiveToLower(unsigned char a, unsigned char b){
    return std::tolower(a) == std::tolower(b);}


bool caseSensitive(std::string const& a, std::string const& b){
    if (a.length()==b.length()) {
        return std::equal(b.begin(), b.end(),
                           a.begin(), caseSensitiveToLower);}
    else {
        return false;
    }
}




