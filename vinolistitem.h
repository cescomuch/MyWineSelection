#ifndef VINOLISTITEM_H
#define VINOLISTITEM_H

#include <QListWidgetItem>
#include <vino.h>

//Ridefinisco metodi ereditati da QListWidgetItem e implemento void aggiorna();
class VinoListItem : public QListWidgetItem{
private:
    Vino *item;
    QWidget* parent;
public:
    VinoListItem(Vino*, QWidget* = nullptr);
    Vino* getItem() const;
    void aggiorna();
};
#endif // VINOLISTITEM_H
