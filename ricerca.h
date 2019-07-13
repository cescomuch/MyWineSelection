#ifndef RICERCA_H
#define RICERCA_H

#include "vinolistwidget.h"
#include "mycomboboxtipo.h"
#include <model.h>

#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QRadioButton>
#include <QLabel>
#include <QLCDNumber>


class Ricerca: public QWidget
{
    Q_OBJECT

private:
    QLabel *labelRicerca;
    QLabel *labelTag;

    QCheckBox *checkboxTipo;
    ComboBoxTipo *cercaPerTipo;

    QCheckBox *checkboxNome;
    QLineEdit *cercaPerNome;

    QCheckBox *checkboxNazione;
    QLineEdit *cercaPerNazione;

    QCheckBox *checkboxProduttore;
    QLineEdit *cercaPerProduttore;

    QCheckBox *checkboxColore;
    QLineEdit *cercaPerColore;

    QCheckBox *checkboxAnnata;
    QLineEdit *cercaPerAnnata;

    QCheckBox *checkboxPrezzo;
    QSlider *sliderPrezzo;
    QLCDNumber *lcdPrezzo;
    QRadioButton *prezzoMinore;
    QRadioButton *prezzoMaggiore;

    Model *modello;

    QPushButton *buttonCerca;
    QPushButton *buttonReset;
    QPushButton *buttonEliminaTrovato;

    VinoListWidget *listaVini;



public:
    Ricerca(QWidget* = nullptr);
    QLineEdit *getCercaPerNome() const;
    QLineEdit *getCercaPerNazione() const;
    QLineEdit *getCercaPerProduttore() const;
    QLineEdit *getCercaPerColore() const;
    QLineEdit *getCercaPerAnnata() const;
    QLCDNumber *getCercaPerPrezzo() const;
    ComboBoxTipo *getCercaPerTipo() const;

    QRadioButton *getRadioButtonPrezzoMinore() const;
    QRadioButton *getRadioButtonPrezzoMaggiore() const;

    QPushButton *getButtonCerca() const;
    QPushButton *getButtonReset() const;

    VinoListWidget *getListaVini() const;

    QPushButton *getButtonEliminaTrovato() const;

    QCheckBox *getCheckboxNome() const;
    QCheckBox *getCheckboxNazione() const;
    QCheckBox *getCheckboxProduttore() const;
    QCheckBox *getCheckboxColore() const;
    QCheckBox *getCheckboxAnnata() const;
    QCheckBox *getCheckboxPrezzo() const;
    QCheckBox *getCheckboxTipo() const;

private slots:
    void slotDisabilitaElementi() const;
    void slotRadioButtonMaggiore(bool) const;
    void slotRadioButtonMinore(bool) const;

public slots:
    void slotResetRicerca() const;

signals:
    void signalEliminaTuttiElementi(Model*);
};

#endif // RICERCA_H
