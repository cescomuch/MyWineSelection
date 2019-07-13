#include "ricerca.h"
#include "controller.h"

#include <qlabel.h>
#include <QMessageBox>



Ricerca::Ricerca(QWidget* p) :
    QWidget (p),

    labelRicerca(new QLabel("• Scegli che vincoli applicare alla ricerca \n",this)),
    labelTag(new QLabel("                  ",this)),

    checkboxTipo(new QCheckBox("Tipo",this)),
    cercaPerTipo(new ComboBoxTipo(this)),

    checkboxNome(new QCheckBox("Nome",this)),
    cercaPerNome(new QLineEdit(this)),

    checkboxNazione(new QCheckBox("Nazione",this)),
    cercaPerNazione(new QLineEdit(this)),

    checkboxProduttore(new QCheckBox("Produttore",this)),
    cercaPerProduttore(new QLineEdit(this)),

    checkboxColore(new QCheckBox("Colore",this)),
    cercaPerColore(new QLineEdit(this)),

    checkboxAnnata(new QCheckBox("Annata",this)),
    cercaPerAnnata(new QLineEdit(this)),

    checkboxPrezzo(new QCheckBox("Prezzo",this)),
    sliderPrezzo(new QSlider(Qt::Horizontal,this)),
    lcdPrezzo(new QLCDNumber(4)),
    prezzoMinore(new QRadioButton("(Minore di)",this)),
    prezzoMaggiore(new QRadioButton("(Maggiore di) ",this)),


    buttonCerca(new QPushButton("Cerca",this)),
    buttonReset(new QPushButton("Reset",this)),
    buttonEliminaTrovato(new QPushButton("Elimina trovati",this)),

    listaVini(new VinoListWidget(this))

{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QFormLayout* form= new QFormLayout();


    listaVini->setFixedSize(960,480);

    cercaPerTipo->setEnabled(false);
    cercaPerNome->setEnabled(false);
    cercaPerNazione->setEnabled(false);
    cercaPerProduttore->setEnabled(false);
    cercaPerColore->setEnabled(false);
    cercaPerAnnata->setEnabled(false);


    sliderPrezzo->setEnabled(false);
    sliderPrezzo->setRange(0,300);
    sliderPrezzo->setValue(0);
    lcdPrezzo->setSegmentStyle(QLCDNumber::Flat);
    prezzoMinore->setEnabled(false);
    prezzoMaggiore->setEnabled(false);




    cercaPerNome->setPlaceholderText("Cerca per nome");
    cercaPerNazione->setPlaceholderText("Cerca per nazione");
    cercaPerProduttore->setPlaceholderText("Cerca per produttore");
    cercaPerColore->setPlaceholderText("Cerca per colore");
    cercaPerAnnata->setPlaceholderText("Cerca per annata");


    form->addRow(checkboxTipo,cercaPerTipo);
    form->addRow(checkboxNome, cercaPerNome);
    form->addRow(checkboxNazione, cercaPerNazione);
    form->addRow(checkboxProduttore, cercaPerProduttore);
    form->addRow(checkboxColore, cercaPerColore);
    form->addRow(checkboxAnnata, cercaPerAnnata);

    form->addRow(checkboxPrezzo);
    form->addRow(prezzoMinore,prezzoMaggiore);
    form->addRow(labelTag,sliderPrezzo);
    form->addRow(labelTag,lcdPrezzo);

    form->addRow(labelTag,buttonCerca);

    mainLayout->addWidget(labelRicerca);
    mainLayout->addLayout(form);
    mainLayout->addWidget(listaVini);

    QHBoxLayout* hBox = new QHBoxLayout();
    mainLayout->addLayout(hBox);
    hBox->addWidget(buttonEliminaTrovato);
    hBox->addWidget(buttonReset);




    connect(checkboxTipo,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(checkboxNome,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(checkboxNazione,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(checkboxProduttore,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(checkboxColore,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(checkboxAnnata,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(checkboxPrezzo,SIGNAL(clicked(bool)),this,SLOT(slotDisabilitaElementi()));
    connect(sliderPrezzo,SIGNAL(valueChanged(int)),lcdPrezzo,SLOT(display(int)));
}




void Ricerca::slotResetRicerca() const {
    cercaPerTipo->setCurrentIndex(0);
    cercaPerNome->clear();
    cercaPerNazione->clear();
    cercaPerProduttore->clear();
    cercaPerColore->clear();
    cercaPerAnnata->clear();
    sliderPrezzo->setValue(0);

    listaVini->clear();
}



void Ricerca::slotDisabilitaElementi() const {
    checkboxTipo->isChecked()? cercaPerTipo->setEnabled(true) : cercaPerTipo->setEnabled(false);
    checkboxNome->isChecked()? cercaPerNome->setEnabled(true) : cercaPerNome->setEnabled(false);
    checkboxNazione->isChecked()? cercaPerNazione->setEnabled(true) : cercaPerNazione->setEnabled(false);
    checkboxProduttore->isChecked()? cercaPerProduttore->setEnabled(true) : cercaPerProduttore->setEnabled(false);
    checkboxColore->isChecked()? cercaPerColore->setEnabled(true) : cercaPerColore->setEnabled(false);
    checkboxAnnata->isChecked()? cercaPerAnnata->setEnabled(true) : cercaPerAnnata->setEnabled(false);

    if(checkboxPrezzo->isChecked()){
        prezzoMinore->setChecked(true);
        sliderPrezzo->setEnabled(true);
        prezzoMinore->setEnabled(true);
        prezzoMaggiore->setEnabled(true);
    }

    else{
        sliderPrezzo->setEnabled(false);
        prezzoMaggiore->setEnabled(false);
        prezzoMinore->setEnabled(false);
    }

}



void Ricerca::slotRadioButtonMaggiore(bool checked) const {prezzoMinore->setChecked(!checked);}

void Ricerca::slotRadioButtonMinore(bool checked) const {prezzoMaggiore->setChecked(!checked);}



ComboBoxTipo *Ricerca::getCercaPerTipo() const {return cercaPerTipo;}

QLineEdit *Ricerca::getCercaPerNome() const {return cercaPerNome;}

QLineEdit *Ricerca::getCercaPerNazione() const {return cercaPerNazione;}

QLineEdit *Ricerca::getCercaPerProduttore() const {return cercaPerProduttore;}

QLineEdit *Ricerca::getCercaPerColore() const {return cercaPerColore;}

QLineEdit *Ricerca::getCercaPerAnnata() const {return cercaPerAnnata;}

QLCDNumber *Ricerca::getCercaPerPrezzo() const {return lcdPrezzo;}




QPushButton *Ricerca::getButtonCerca() const {return buttonCerca;}

QPushButton *Ricerca::getButtonReset() const {return buttonReset;}

VinoListWidget *Ricerca::getListaVini() const {return listaVini;}

QPushButton *Ricerca::getButtonEliminaTrovato() const {return buttonEliminaTrovato;}

QCheckBox *Ricerca::getCheckboxTipo() const {return checkboxTipo;}

QCheckBox *Ricerca::getCheckboxNome() const {return checkboxNome;}

QCheckBox *Ricerca::getCheckboxNazione() const {return checkboxNazione;}

QCheckBox *Ricerca::getCheckboxProduttore() const {return checkboxProduttore;}

QCheckBox *Ricerca::getCheckboxColore() const {return checkboxColore;}

QCheckBox *Ricerca::getCheckboxAnnata() const {return checkboxAnnata;}

QCheckBox *Ricerca::getCheckboxPrezzo() const {return checkboxPrezzo;}

QRadioButton *Ricerca::getRadioButtonPrezzoMinore() const {return prezzoMinore;}

QRadioButton *Ricerca::getRadioButtonPrezzoMaggiore() const {return prezzoMaggiore;}
