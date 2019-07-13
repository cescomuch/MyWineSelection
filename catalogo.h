#ifndef CATALOGO_H
#define CATALOGO_H

#include "vinolistwidget.h"
#include "dettagliovino.h"

#include <QPushButton>
#include <QScrollBar>
#include <QVBoxLayout>


class Catalogo : public QWidget {
    Q_OBJECT
private:
    VinoListWidget *listaVini;
    QPushButton *buttonElimina;
    QPushButton* buttonModifica;
    DettaglioVino* dialogDettaglioVino;
    QWidget* parent;

public:
    Catalogo(QWidget * = nullptr);
    ~Catalogo();
    VinoListWidget *getListaVini() const;
    QPushButton *getButtonElimina() const;
    QPushButton *getButtonModifica() const;

public slots:
    void slotElementoSelezionato(bool=true) const;
    void slotRigaCambiata() const;

signals:
    void signalElementoSelezionato(bool=true) const;

};
#endif // CATALOGO_H
