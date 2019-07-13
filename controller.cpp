#include "controller.h"
#include "utils.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>


using std::string;

Controller::Controller(Model* m, QWidget *parent) :
    QWidget(parent),
    modello(m),
    menu(new Menu(this)),
    layoutPrincipale(new QHBoxLayout(this)),
    catalogo(new Catalogo(this)),
    inserisci(new Inserisci(this)),
    dialogDettaglioVino(nullptr),
    ricerca(new Ricerca(this))
{

    setFixedSize(QSize(1000,1000));

    layoutPrincipale->setMenuBar(menu);

    layoutPrincipale->addWidget(catalogo);
    layoutPrincipale->addWidget(inserisci);
    layoutPrincipale->addWidget(ricerca);



    slotMostraInserisci();

    setLayout(layoutPrincipale);

    //CONNECT
    connect(catalogo->getButtonElimina(),SIGNAL(clicked()),this,SLOT(slotEliminaElemento()));
    connect(catalogo->getButtonElimina(),SIGNAL(clicked()),this,SLOT(slotResetRicerca()));
    connect(catalogo->getButtonElimina(),SIGNAL(clicked()),ricerca,SLOT(slotResetRicerca()));
    connect(catalogo->getButtonModifica(),SIGNAL(clicked()),this,SLOT(slotMostraModifica()));
    connect(catalogo->getListaVini(),SIGNAL(signalEliminaElementoDaLista(Vino*)),this,SLOT(slotEliminaDaModello(Vino*)));


    connect(inserisci->getButtonAggiungi(),SIGNAL(clicked()), this, SLOT(slotAggiungiElemento()));
    connect(inserisci->getButtonAggiungi(),SIGNAL(clicked()),this, SLOT(slotResetRicerca()));
    connect(inserisci->getButtonAggiungi(),SIGNAL(clicked()),ricerca,SLOT(slotResetRicerca()));

    connect(ricerca->getButtonCerca(),SIGNAL(clicked()),this,SLOT(slotRicerca()));
    connect(ricerca->getButtonEliminaTrovato(),SIGNAL(clicked()),this,SLOT(slotEliminaDaModello()));
    connect(ricerca->getButtonReset(),SIGNAL(clicked()), ricerca, SLOT(slotResetRicerca()));
    connect(ricerca->getButtonReset(),SIGNAL(clicked()), this, SLOT(slotResetRicerca()));

    slotCaricaDati();

}



Controller::~Controller() {modello->save();}


Model* Controller::getModello() {return modello;}









/*
 *
 *
 * SLOTS
 *
 *
*/




//DATI
void Controller::slotCaricaDati(){
    if(!modello->getIsDataSaved()){
        QMessageBox::StandardButton reply= QMessageBox::question(this,"Attenzione!","Ci sono modifiche che non sono state salvate, se clicchi Yes i dati verranno salvati nel file corrente.",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::No)
            return;
    }

    QString file= QFileDialog::getOpenFileName(
                this,
                tr("Scegli file"),
                "../MyWineSelection",
                "File XML(*.xml)"
                );
    if(file!=""){
        catalogo->getListaVini()->clear();
        ricerca->slotResetRicerca();
        modello->clear();

        modello->setNewPath(file.toStdString());
        modello->load();
        if(modello->getDataSize()==0){
            QMessageBox::warning(this,"Attenzione!","Il file del programma e' vuoto.");
        }
        else{
            for(unsigned int i=0; i<modello->getDataSize(); ++i)
                catalogo->getListaVini()->aggiungiVino(modello->vinoAt(i));

            modello->setDataSaved(true);
            slotMostraCatalogo();
            slotDatiCambiati(false);
        }
    }
}



void Controller::slotSalvaDati() const {
    if(!modello->getIsDataSaved()){
        modello->save();
        slotDatiCambiati(false);
    }
}


void Controller::slotDatiCambiati(bool b) const {menu->getSalva()->setEnabled(b);}









//ELIMINAZIONI
void Controller::slotEliminaElemento() const {
    if(catalogo->getListaVini()->count() && catalogo->getListaVini()->currentItem()!= nullptr){
        VinoListItem* item = catalogo->getListaVini()->takeItem(catalogo->getListaVini()->currentRow());
        modello->erase(item->getItem());
        delete item;
        catalogo->getListaVini()->reset();
        slotDatiCambiati(true);
    }
}

void Controller::slotEliminaDaModello(Vino* vi) const {
    modello->erase(vi);
    delete vi;
    ricerca->slotResetRicerca();
    slotDatiCambiati(true);
}

void Controller::slotEliminaDaModello() const {
    for(; ricerca->getListaVini()->count()!=0;){
        VinoListItem* itemDaRicerca= ricerca->getListaVini()->takeItem(0);
        VinoListItem* itemDaVisualizza=catalogo->getListaVini()->takeItem(itemDaRicerca->getItem());
        delete  itemDaRicerca;
        delete  itemDaVisualizza;
    }
    modello->eliminaTrovati();
    slotDatiCambiati(true);
}








//RICERCA
void Controller::slotRicerca(){
    slotResetRicerca();
    ricerca->getListaVini()->clear();
    if(modello->getDataSize()==0){
        QMessageBox::warning(this, "Attenzione!","Non sono presenti vini nel catalogo per poter fare la ricerca.");
    } else {
        if(ricerca->getCheckboxTipo()->isChecked())
           modello->filterByTipo(ricerca->getCercaPerTipo()->currentText().toStdString());

        if(ricerca->getCheckboxNome()->isChecked())
            modello->filterByNome( ricerca->getCercaPerNome()->text().toStdString());

        if(ricerca->getCheckboxNazione()->isChecked())
            modello->filterByNazione(ricerca->getCercaPerNazione()->text().toStdString());

        if(ricerca->getCheckboxProduttore()->isChecked())
            modello->filterByProduttore(ricerca->getCercaPerProduttore()->text().toStdString());

        if(ricerca->getCheckboxColore()->isChecked())
            modello->filterByColore(ricerca->getCercaPerColore()->text().toStdString());

        if(ricerca->getCheckboxAnnata()->isChecked())
            modello->filterByAnnata(ricerca->getCercaPerAnnata()->text().toInt());

        if(ricerca->getCheckboxPrezzo()->isChecked()){
            if(ricerca->getRadioButtonPrezzoMinore()->isChecked())
                modello->filterByPrezzoMinore(ricerca->getCercaPerPrezzo()->intValue());
            else
                modello->filterByPrezzoMaggiore(ricerca->getCercaPerPrezzo()->intValue());
        }

//finita ricerca
        if(modello->getRicercaSize()==0){
               QMessageBox::warning(this, "Informazione",
                                    "Non ci sono vini che corrispondono ai parametri di ricerca.");
        } else {
            for(auto it = modello->ricerca_cbegin(); it != modello->ricerca_cend(); ++it)
                ricerca->getListaVini()->aggiungiVino(*it);
        }

    }
}



void Controller::slotResetRicerca() const {modello->resetRisultatiRicerca();}










//MODIFICA
void Controller::slotMostraModifica() {
    VinoListItem* cat=catalogo->getListaVini()->currentItem();

    if(dialogDettaglioVino!=nullptr)
        delete dialogDettaglioVino;
    dialogDettaglioVino=new DettaglioVino(cat,this);
    dialogDettaglioVino->show();
    slotDatiCambiati(true);
}









//INSERISCI
void Controller::slotAggiungiElemento(){
    try {

        int indiceTipo=inserisci->getScegliTipo()->currentIndex();

        if(indiceTipo==0) throw MyException("Tipo Vino");

        string nome=inserisci->getInserisciNome()->text().toStdString();
        string nazione=inserisci->getInserisciNazione()->text().toStdString();
        string regione=inserisci->getInserisciRegione()->text().toStdString();
        string produttore=inserisci->getInserisciProduttore()->text().toStdString();
        string aggettivo=inserisci->getInserisciAggettivo()->text().toStdString();
        string colore=inserisci->getInserisciColore()->text().toStdString();
        double prezzo=inserisci->getInserisciPrezzo()->text().toDouble();
        double gradazioneAlcolica=inserisci->getInserisciGradazioneAlcolica()->text().toDouble();
        int temperaturaSuggerita=inserisci->getInserisciTemperaturaSuggerita()->text().toInt();
        int mlBottiglia=inserisci->getInserisciMlBottiglia()->text().toInt();
        int annata=inserisci->getInserisciAnnata()->text().toInt();




        if(nome.empty()) throw MyException("Nome");
        if(nazione.empty()) throw MyException("Nazione");
        if(regione.empty()) throw MyException("Regione");
        if(produttore.empty()) throw MyException("Produttore");
        if(aggettivo.empty()) throw MyException("Aggettivo");
        if(colore.empty()) throw MyException("Colore");


        if(prezzo==0.00) throw MyException("Prezzo");
        if(gradazioneAlcolica==0.00) throw MyException("Gradazione alcolica");
        if(temperaturaSuggerita==0) throw MyException("Temperatura suggerita");
        if(mlBottiglia==0) throw MyException("ml bottiglia");
        if(annata==0) throw MyException("Annata");

        Vino* toPush=nullptr;

        string img64=Img64::getRawData(inserisci->getScegliFoto()->pixmap()->toImage());
        if(img64.empty()) throw MyException("Scegliere la foto");


        switch (indiceTipo) {
        case 1:
            toPush= new VinoBarricato(nome,nazione,regione,produttore,aggettivo,colore,img64,
                                      prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,
                                      inserisci->getInserisciLegno()->text().toStdString());

            if(inserisci->getInserisciLegno()->text().toStdString().empty()) throw MyException("Legno");

            break;

        case 2:
            toPush= new VinoAromatizzato(nome,nazione,regione,produttore,aggettivo,colore,img64,
                                      prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,
                                      inserisci->getInserisciElementoAggiunto()->text().toStdString());

            if(inserisci->getInserisciElementoAggiunto()->text().toStdString().empty()) throw MyException("Aroma aggiunto");

            break;

        case 3:
            toPush= new VinoLiquoroso(nome,nazione,regione,produttore,aggettivo,colore,img64,
                                      prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,
                                      inserisci->getInserisciLiquoreAggiunto()->text().toStdString());

            if(inserisci->getInserisciLiquoreAggiunto()->text().toStdString().empty()) throw MyException("Liquore aggiunto");

            break;

        case 4:
            toPush= new VinoFrizzante(nome,nazione,regione,produttore,aggettivo,colore,img64,
                                      prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,
                                      inserisci->getInserisciPressione()->text().toDouble());

            if(inserisci->getInserisciPressione()->text().toDouble() == 0.00) throw MyException("Pressione");

            break;
        case 5:
            toPush= new Spumante(nome,nazione,regione,produttore,aggettivo,colore,img64,
                                      prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,
                                      inserisci->getInserisciPressione()->text().toDouble(),inserisci->getInserisciResiduoZuccherino()->text().toDouble());

            if(inserisci->getInserisciPressione()->text().toDouble() == 0.00) throw MyException("Pressione");
            if(inserisci->getInserisciResiduoZuccherino()->text().toDouble() == 0.00) throw MyException("Residuo zuccherino");

            break;
        default:
            throw MyException("Tipo di vino");

        }


        if(toPush!= nullptr){
            modello->push_back(toPush);
            catalogo->getListaVini()->aggiungiVino(toPush);
            slotDatiCambiati(true);
            QMessageBox::information(this,"Conferma", "Il vino e' stato inserito correttamente");
        }

    } catch (MyException ex) {
        inserisci->mostraWarningDialog(this,ex.getWhat());
    }
}









//HIDE AND SHOW
void Controller::slotMostraCatalogo() const{
    catalogo->show();
    ricerca->hide();
    inserisci->hide();
}
void Controller::slotMostraRicerca() const{
    catalogo->hide();
    ricerca->show();
    inserisci->hide();
}
void Controller::slotMostraInserisci() const{
    catalogo->hide();
    ricerca->hide();
    inserisci->show();
}
