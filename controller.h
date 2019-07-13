#ifndef WIDGET_H
#define WIDGET_H

#include "inserisci.h"
#include "ricerca.h"
#include "catalogo.h"
#include "model.h"
#include "menu.h"

#include <QWidget>
#include <QVBoxLayout>


class Controller : public QWidget{
    Q_OBJECT
private:
    Model* modello;

    Menu* menu;
    QHBoxLayout* layoutPrincipale;
    Catalogo* catalogo;
    Inserisci* inserisci;
    DettaglioVino* dialogDettaglioVino;
    Ricerca* ricerca;

public:
    Controller(Model*, QWidget * = nullptr);
    ~Controller();
    Model* getModello();

public slots:
    void slotCaricaDati();
    void slotAggiungiElemento();
    void slotMostraModifica();
    void slotRicerca();
    void slotEliminaElemento() const;
    void slotResetRicerca() const;
    void slotSalvaDati() const;
    void slotDatiCambiati(bool) const;
    void slotEliminaDaModello(Vino*) const;
    void slotEliminaDaModello() const;
    void slotMostraCatalogo() const;
    void slotMostraRicerca() const;
    void slotMostraInserisci() const;
};

#endif // WIDGET_H
