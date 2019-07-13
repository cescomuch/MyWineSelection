#include "menu.h"

Menu::Menu(QWidget* p) :
    parent(p),
    menu(new QMenu("File", this)),
    salva( new QAction("Salva file", menu)),
    carica( new QAction("Carica file", menu)),
    esci(new QAction("Esci", menu)),
    catalogo(new QAction("Catalogo",p)),
    ricerca( new QAction("Cerca",p)),
    inserisci(new QAction("Inserisci",p))
{

    QList<QAction*> actionList;
    actionList.push_back(salva);
    actionList.push_back(carica);
    actionList.push_back(esci);

    menu->addActions(actionList);
    actionList.clear();

    addMenu(menu);
    addAction(catalogo);
    addAction(inserisci);
    addAction(ricerca);


    connect(salva,SIGNAL(triggered()),parent,SLOT(slotSalvaDati()));
    connect(carica,SIGNAL(triggered()),parent, SLOT(slotCaricaDati()));
    connect(esci,SIGNAL(triggered()),parent,SLOT(close()));
    connect(catalogo, SIGNAL(triggered()), parent,SLOT(slotMostraCatalogo()));
    connect(inserisci, SIGNAL(triggered()), parent,SLOT(slotMostraInserisci()));
    connect(ricerca, SIGNAL(triggered()), parent,SLOT(slotMostraRicerca()));

}

QMenu *Menu::getMenu() const {return menu;}

QAction *Menu::getSalva() const {return salva;}

QAction *Menu::getCarica() const {return carica;}

QAction *Menu::getEsci() const {return esci;}
