#ifndef MENU_H
#define MENU_H

#include <qmenubar.h>
#include <qwidget.h>

class Menu : public QMenuBar {
    Q_OBJECT
    QWidget* parent;

    QMenu* menu;

    QAction* salva;
    QAction* carica;
    QAction* esci;

    QAction* catalogo;
    QAction* ricerca;
    QAction* inserisci;
public:
    Menu(QWidget* = nullptr);
    QMenu *getMenu() const;
    QAction *getSalva() const;
    QAction *getCarica() const;
    QAction *getEsci() const;
};

#endif // MENU_H
