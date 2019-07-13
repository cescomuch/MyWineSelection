#include "vinolistitem.h"
#include "utils.h"

#include <QByteArray>

VinoListItem::VinoListItem(Vino* i, QWidget* p) : item(i), parent(p) {aggiorna();}

void VinoListItem::aggiorna(){
    QPixmap q=Img64::getImage(item->getImg64());
    setIcon(q);

    setText(QString::fromStdString(item->getInfo()));}

Vino* VinoListItem::getItem() const {return item;}
