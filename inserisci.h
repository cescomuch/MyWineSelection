#ifndef INSERISCI_H
#define INSERISCI_H

#include "mycomboboxtipo.h"

#include <QComboBox>
#include <QFormLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <QLabel>


class Inserisci : public QWidget {
  Q_OBJECT
private:
    ComboBoxTipo *tipoVino;

    QLineEdit *nome;
    QLineEdit *nazione;
    QLineEdit *regione;
    QLineEdit *produttore;
    QLineEdit *aggettivo;
    QLineEdit *colore;
    QLineEdit *prezzo;
    QLineEdit *gradazioneAlcolica;
    QLineEdit *temperaturaSuggerita;
    QLineEdit *mlBottiglia;
    QLineEdit *annata;

    QLineEdit *legno;
    QLineEdit *elementoAggiunto;
    QLineEdit *liquoreAggiunto;
    QLineEdit *pressione;
    QLineEdit *residuoZuccherino;

    QLabel *scegliFoto;

    QPushButton *buttonScegliFoto;
    QPushButton *buttonAggiungi;
    QPushButton *buttonAzzera;

private slots:
    void slotAzzera() const;

public:
    Inserisci(QWidget * =nullptr);

    ComboBoxTipo* getScegliTipo() const;

    QLineEdit *getInserisciNome() const;
    QLineEdit *getInserisciNazione() const;
    QLineEdit *getInserisciRegione() const;
    QLineEdit *getInserisciProduttore() const;
    QLineEdit *getInserisciAggettivo() const;
    QLineEdit *getInserisciColore() const;
    QLineEdit *getInserisciPrezzo() const;
    QLineEdit *getInserisciGradazioneAlcolica() const;
    QLineEdit *getInserisciTemperaturaSuggerita() const;
    QLineEdit *getInserisciMlBottiglia() const;
    QLineEdit *getInserisciAnnata() const;


    QLineEdit *getInserisciLegno() const;
    QLineEdit *getInserisciElementoAggiunto() const;
    QLineEdit *getInserisciLiquoreAggiunto() const;
    QLineEdit *getInserisciPressione() const;
    QLineEdit *getInserisciResiduoZuccherino() const;

    QLabel *getScegliFoto() const;

    QPushButton *getButtonScegliFoto() const;
    QPushButton *getButtonAggiungi() const;

    void mostraWarningDialog(QWidget* = nullptr, QString ="") const;

public slots:
    void slotNascondiElementi(int) const;
    void slotScegliImmagine();
};

#endif // INSERISCI_H
