#ifndef DETTAGLIOVINO_H
#define DETTAGLIOVINO_H

#include "vinolistitem.h"

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>




class DettaglioVino: public QDialog {
    Q_OBJECT

private:
    VinoListItem* itemVino;
    QPushButton* buttonClose;
    QPushButton* buttonSalvaModifica;
    Vino* vino;
    QLabel* immagine;
    QLineEdit* pathFoto;
    QPushButton* buttonScegliFoto;
    QTextEdit* prezzo;
    void setFoto(const QPixmap&);

public:
     DettaglioVino(VinoListItem*, QWidget* = nullptr);

public slots:
    void  slotSalvaModifica() const;
    void  slotFotoCambiata();
};

#endif // DETTAGLIOVINO_H
