#include "inserisci.h"
#include "controller.h"

#include <QPushButton>
#include <qlabel.h>
#include <QString>
#include <QAction>
#include <iostream>
#include <qmessagebox.h>
#include <QFileDialog>
#include <QBuffer>



Inserisci::Inserisci(QWidget* p):
    QWidget (p),
    tipoVino(new ComboBoxTipo(this)),
    nome(new QLineEdit(this)),
    nazione(new QLineEdit(this)),
    regione(new QLineEdit(this)),
    produttore(new QLineEdit(this)),
    aggettivo(new QLineEdit(this)),
    colore(new QLineEdit(this)),
    prezzo(new QLineEdit(this)),
    gradazioneAlcolica(new QLineEdit(this)),
    temperaturaSuggerita(new QLineEdit(this)),
    mlBottiglia(new QLineEdit(this)),
    annata(new QLineEdit(this)),
    legno(new QLineEdit(this)),
    elementoAggiunto(new QLineEdit(this)),
    liquoreAggiunto(new QLineEdit(this)),
    pressione(new QLineEdit(this)),
    residuoZuccherino(new QLineEdit(this)),
    scegliFoto(new QLabel(this)),
    buttonScegliFoto(new QPushButton(this)),
    buttonAggiungi(new QPushButton("Aggiungi",this)),
    buttonAzzera(new QPushButton("Resetta valori",this))
{
    QVBoxLayout* form=new QVBoxLayout(this);

    form->addWidget(tipoVino);



    buttonScegliFoto->setText("Inserisci foto");
    QIcon i=QIcon(":/Immagini/choosefile.png");

    buttonScegliFoto->setIcon(i);
    buttonScegliFoto->setMaximumWidth(400);

    form->addWidget(buttonScegliFoto);
    form->addWidget(scegliFoto);



    nome->setPlaceholderText("Inserisci il nome");
    form->addWidget(nome);

    nazione->setPlaceholderText("Inserisci la nazione");
    form->addWidget(nazione);

    regione->setPlaceholderText("Inserisci la regione");
    form->addWidget(regione);

    produttore->setPlaceholderText("Inserisci il produttore");
    form->addWidget(produttore);

    aggettivo->setPlaceholderText("Inserisci un aggettivo");
    form->addWidget(aggettivo);

    colore->setPlaceholderText("Inserisci il colore");
    form->addWidget(colore);

    prezzo->setPlaceholderText("Inserisci il prezzo");
    form->addWidget(prezzo);

    gradazioneAlcolica->setPlaceholderText("Inserisci la gradazione alcolica");
    form->addWidget(gradazioneAlcolica);

    temperaturaSuggerita->setPlaceholderText("Inserisci la temperatura suggerita per il servizio");
    form->addWidget(temperaturaSuggerita);

    mlBottiglia->setPlaceholderText("Inserisci i ml del formato della bottiglia");
    form->addWidget(mlBottiglia);

    annata->setPlaceholderText("Inserisci l'annata");
    form->addWidget(annata);

    legno->setPlaceholderText("Inserisci il legno usato per le botti");
    form->addWidget(legno);

    elementoAggiunto->setPlaceholderText("Inserisci l'aroma aggiunto");
    form->addWidget(elementoAggiunto);

    liquoreAggiunto->setPlaceholderText("Inserisci il liquore aggiunto");
    form->addWidget(liquoreAggiunto);

    pressione->setPlaceholderText("Inserisci la pressione (bar)");
    form->addWidget(pressione);

    residuoZuccherino->setPlaceholderText("Inserisci il residuo zuccherino (%)");
    form->addWidget(residuoZuccherino);


   QHBoxLayout* b=new QHBoxLayout;
    b->addWidget(buttonAggiungi);
    b->addWidget(buttonAzzera);
    form->addItem(b);
    b->setSpacing(10);

    slotNascondiElementi(0);

    connect(tipoVino,SIGNAL(activated(int)),this,SLOT(slotNascondiElementi(int)));
    connect(buttonScegliFoto,SIGNAL(clicked()), this, SLOT(slotScegliImmagine()));
    connect(buttonAzzera,SIGNAL(clicked()),this,SLOT(slotAzzera()));

}


ComboBoxTipo *Inserisci::getScegliTipo() const {return tipoVino;}


void Inserisci::slotAzzera()const{

    nome->setText("");
    nazione->setText("");
    regione->setText("");
    produttore->setText("");
    aggettivo->setText("");
    colore->setText("");
    prezzo->setText("");
    gradazioneAlcolica->setText("");
    temperaturaSuggerita->setText("");
    mlBottiglia->setText("");
    annata->setText("");
    tipoVino->setCurrentIndex(0);
    scegliFoto->setText("");
    scegliFoto->clear();
    legno->setText("");
    elementoAggiunto->setText("");
    liquoreAggiunto->setText("");
    pressione->setText("");
    residuoZuccherino->setText("");

    nome->hide();
    nazione->hide();
    regione->hide();
    produttore->hide();
    aggettivo->hide();
    colore->hide();
    prezzo->hide();
    gradazioneAlcolica->hide();
    temperaturaSuggerita->hide();
    mlBottiglia->hide();
    annata->hide();
    scegliFoto->hide();
    buttonScegliFoto->hide();
    buttonAggiungi->hide();
    buttonAzzera->hide();
    legno->hide();
    elementoAggiunto->hide();
    liquoreAggiunto->hide();
    pressione->hide();
    residuoZuccherino->hide();
}



void Inserisci::slotNascondiElementi(int index)const
{
    switch (index) {
    case 1: //barricato
        nome->show();
        nazione->show();
        regione->show();
        produttore->show();
        aggettivo->show();
        colore->show();
        prezzo->show();
        gradazioneAlcolica->show();
        temperaturaSuggerita->show();
        mlBottiglia->show();
        annata->show();
        scegliFoto->show();
        buttonScegliFoto->show();
        buttonAggiungi->show();
        buttonAzzera->show();

        legno->show();

        elementoAggiunto->hide();
        liquoreAggiunto->hide();
        pressione->hide();
        residuoZuccherino->hide();
        break;

    case 2: //aromatizzato
        nome->show();
        nazione->show();
        regione->show();
        produttore->show();
        aggettivo->show();
        colore->show();
        prezzo->show();
        gradazioneAlcolica->show();
        temperaturaSuggerita->show();
        mlBottiglia->show();
        annata->show();
        scegliFoto->show();
        buttonScegliFoto->show();
        buttonAggiungi->show();
        buttonAzzera->show();

        elementoAggiunto->show();

        legno->hide();
        liquoreAggiunto->hide();
        pressione->hide();
        residuoZuccherino->hide();
        break;

    case 3://liquroso
        nome->show();
        nazione->show();
        regione->show();
        produttore->show();
        aggettivo->show();
        colore->show();
        prezzo->show();
        gradazioneAlcolica->show();
        temperaturaSuggerita->show();
        mlBottiglia->show();
        annata->show();
        scegliFoto->show();
        buttonScegliFoto->show();
        buttonAggiungi->show();
        buttonAzzera->show();

        liquoreAggiunto->show();

        elementoAggiunto->hide();
        legno->hide();
        pressione->hide();
        residuoZuccherino->hide();
        break;

    case 4://frizzante
        nome->show();
        nazione->show();
        regione->show();
        produttore->show();
        aggettivo->show();
        colore->show();
        prezzo->show();
        gradazioneAlcolica->show();
        temperaturaSuggerita->show();
        mlBottiglia->show();
        annata->show();
        scegliFoto->show();
        buttonScegliFoto->show();
        buttonAggiungi->show();
        buttonAzzera->show();

        pressione->show();

        elementoAggiunto->hide();
        liquoreAggiunto->hide();
        legno->hide();
        residuoZuccherino->hide();
        break;

    case 5://spumante
        nome->show();
        nazione->show();
        regione->show();
        produttore->show();
        aggettivo->show();
        colore->show();
        prezzo->show();
        gradazioneAlcolica->show();
        temperaturaSuggerita->show();
        mlBottiglia->show();
        annata->show();
        scegliFoto->show();
        buttonScegliFoto->show();
        buttonAggiungi->show();
        buttonAzzera->show();

        pressione->show();
        residuoZuccherino->show();

        legno->hide();
        elementoAggiunto->hide();
        liquoreAggiunto->hide();
        break;

    case 0: //nessun tipo di vino selezionato
        nome->hide();
        nazione->hide();
        regione->hide();
        produttore->hide();
        aggettivo->hide();
        colore->hide();
        prezzo->hide();
        gradazioneAlcolica->hide();
        temperaturaSuggerita->hide();
        mlBottiglia->hide();
        annata->hide();
        scegliFoto->hide();
        buttonScegliFoto->hide();
        buttonAggiungi->hide();
        buttonAzzera->hide();
        legno->hide();
        elementoAggiunto->hide();
        liquoreAggiunto->hide();
        pressione->hide();
        residuoZuccherino->hide();
        break;
    }
}




void Inserisci::slotScegliImmagine(){
    QString file= QFileDialog::getOpenFileName(
                this,
                tr("Choose image"),
                "../MyWineSelection/Immagini/.",
                "Image file (*.jpg)"
                );
        QFileInfo relativePath(file);

    if(file!=""){
        QImage im(file);
        QByteArray  array;
        QBuffer b(&array);

        im.save(&b,"JPG");
            scegliFoto->setPixmap(QPixmap::fromImage(im));
    }

}


QLineEdit *Inserisci::getInserisciNome() const {return nome;}

QLineEdit *Inserisci::getInserisciNazione() const {return nazione;}

QLineEdit *Inserisci::getInserisciRegione() const {return regione;}

QLineEdit *Inserisci::getInserisciProduttore() const {return produttore;}

QLineEdit *Inserisci::getInserisciAggettivo() const {return aggettivo;}

QLineEdit *Inserisci::getInserisciColore() const {return colore;}

QLineEdit *Inserisci::getInserisciPrezzo() const {return prezzo;}

QLineEdit *Inserisci::getInserisciGradazioneAlcolica() const {return gradazioneAlcolica;}

QLineEdit *Inserisci::getInserisciTemperaturaSuggerita() const {return temperaturaSuggerita;}

QLineEdit *Inserisci::getInserisciMlBottiglia() const {return mlBottiglia;}

QLineEdit *Inserisci::getInserisciAnnata() const {return annata;}

QLineEdit *Inserisci::getInserisciLegno() const {return legno;}

QLineEdit *Inserisci::getInserisciElementoAggiunto() const {return elementoAggiunto;}

QLineEdit *Inserisci::getInserisciLiquoreAggiunto() const {return liquoreAggiunto;}

QLineEdit *Inserisci::getInserisciPressione() const {return pressione;}

QLineEdit *Inserisci::getInserisciResiduoZuccherino() const {return residuoZuccherino;}






QLabel *Inserisci::getScegliFoto() const {return scegliFoto;}

QPushButton *Inserisci::getButtonScegliFoto() const {return buttonScegliFoto;}

QPushButton *Inserisci::getButtonAggiungi() const {return buttonAggiungi;}


void Inserisci::mostraWarningDialog(QWidget *p, QString what) const{
    QString str="Devi inserire il campo: ";
    str.append(what);
    QMessageBox::warning(p,"MyWineSelection",str);
}
