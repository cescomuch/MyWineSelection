#ifndef VINOLISTWIDGET_H
#define VINOLISTWIDGET_H

#include "vinolistitem.h"
#include <QListWidget>
#include <QPushButton>


class VinoListWidget : public QListWidget {
    Q_OBJECT

    QWidget* parent;

public:
    VinoListWidget(QWidget* =nullptr);
    void aggiungiVino(Vino*);

    //Ridefinisco metodi di QListWidget
    VinoListItem* currentItem()const;
    VinoListItem* takeItem(int);
    VinoListItem* takeItem(Vino*);

signals:
    void  signalEliminaElementoDaLista(Vino*);
};

#endif // VINOLISTWIDGET_H
