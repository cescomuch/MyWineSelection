#include "model.h"
#include "utils.h"

#include <QSaveFile>
#include <QXmlStreamReader>
#include <QFile>

#include <myexception.h>
#include <QDebug>

using std::cerr;
using std::endl;


Model::Model(string p):
    listaVini(new Container<Vino*>(2)),
    risultatiRicerca(new Container<Vino*>(2)),
    path(p),
    isDataSaved(true) {}

Model::~Model(){
    for(unsigned int i=0; i<listaVini->getSize(); ++i)
        delete listaVini->at(i);

    delete risultatiRicerca;
}

void Model::push_back(Vino* vi){
    listaVini->push_back(vi);
    if(!(*risultatiRicerca == *listaVini))
        *risultatiRicerca=*listaVini;

    isDataSaved=false;
}


Vino* Model::vinoAt(unsigned int index){
    isDataSaved=false;
    return listaVini->at(index);
}


Container<Vino*>::iterator Model::begin(){
    isDataSaved=false;
    return  listaVini->begin();
}

Container<Vino*>::iterator Model::end(){
    isDataSaved=false;
    return listaVini->end();
}

Container<Vino*>::const_iterator Model::cbegin() const {return listaVini->cbegin();}

Container<Vino*>::const_iterator Model::cend() const {return listaVini->cend();}


unsigned int Model::getDataSize() const {return listaVini->getSize();}

unsigned int Model::getDataCapacity() const {return listaVini->getCapacity();}


void Model::erase(unsigned int index ){
    isDataSaved=false;
    listaVini->erase(index);
}

void Model::erase(unsigned int start, unsigned int end){
    isDataSaved=false;
    listaVini->erase(start,end);
}

 void Model::erase(Vino* it){
    isDataSaved=false;
     listaVini->erase(it);
}



bool Model::isDataEmpty() const {return listaVini->isEmpty();}


void Model::clear(){
    isDataSaved=false;
    for(unsigned int i=0; i<listaVini->getSize(); ++i)
        delete listaVini->at(i);

    listaVini->clear();
    risultatiRicerca->clear();
}


void Model::save(){

    QSaveFile file(QString::fromStdString(path));
    if(!file.open(QIODevice::WriteOnly)) {
        throw MyException("Errore");
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("NON MODIFICARE A MANO QUESTO FILE!!!!");

    writer.writeStartElement("root");                                // <root>

    auto it=cbegin();
    while(it!=cend()) {
        const Vino* toSave = *it;
        const QString tipo=QString::fromStdString(toSave->getTipo());
        writer.writeEmptyElement(tipo);


        writer.writeAttribute("nome",QString::fromStdString(toSave->getNome()));
        writer.writeAttribute("nazione",QString::fromStdString(toSave->getNazione()));
        writer.writeAttribute("regione",QString::fromStdString(toSave->getRegione()));
        writer.writeAttribute("produttore",QString::fromStdString(toSave->getProduttore()));
        writer.writeAttribute("aggettivo",QString::fromStdString(toSave->getAggettivo()));
        writer.writeAttribute("colore",QString::fromStdString(toSave->getColore()));
        writer.writeAttribute("img64",QString::fromStdString(toSave->getImg64()));
        writer.writeAttribute("prezzo",QString("%1").arg((toSave->getPrezzo())));
        writer.writeAttribute("gradazioneAlcolica",QString("%1").arg(toSave->getGradazioneAlcolica()));
        writer.writeAttribute("temperaturaSuggerita",QString("%1").arg(toSave->getTemperaturaSuggerita()));
        writer.writeAttribute("mlBottiglia",QString("%1").arg(toSave->getMlBottiglia()));
        writer.writeAttribute("annata",QString("%1").arg(toSave->getAnnata()));

        if(tipo=="Barricato"){
            const VinoBarricato* barricato = static_cast<const VinoBarricato*>(toSave);
            writer.writeAttribute("legno",QString::fromStdString(barricato->getLegno()));}

        else if(tipo=="Aromatizzato"){
            const VinoAromatizzato* aromatizzato = static_cast<const VinoAromatizzato*>(toSave);
            writer.writeAttribute("elementoAggiunto",QString::fromStdString(aromatizzato->getElementoAggiunto()));}

        else if(tipo=="Liquoroso"){
            const VinoLiquoroso* liquoroso = static_cast<const VinoLiquoroso*>(toSave);
            writer.writeAttribute("liquoreAggiunto",QString::fromStdString(liquoroso->getLiquoreAggiunto()));}

        else if(tipo=="Frizzante"){
            const VinoFrizzante* frizzante = static_cast<const VinoFrizzante*>(toSave);
            writer.writeAttribute("pressione",QString("%1").arg(frizzante->getPressione()));}

        else if(tipo=="Spumante"){
            const Spumante* spumante = static_cast<const Spumante*>(toSave);
            writer.writeAttribute("pressione",QString("%1").arg(spumante->getPressione()));
            writer.writeAttribute("residuoZuccherino",QString("%1").arg(spumante->getResiduoZuccherino()));}

        if (writer.hasError()){
            throw MyException("Errore salvataggio");
        }

        ++it;
    }

    writer.writeEndElement();
    writer.writeEndDocument();
    isDataSaved=true;
    file.commit();
}

void Model::load(){

    QFile file(QString::fromStdString(path));

    if(!file.open(QIODevice::ReadOnly)){
        throw MyException("Errorre in apertura del file.");
    }

    QXmlStreamReader reader(&file);
    if(reader.readNextStartElement()){
        if(reader.name()=="root"){
            while(reader.readNextStartElement()){
                const QXmlStreamAttributes att=reader.attributes();

                string nome=att.hasAttribute("nome")? att.value("nome").toString().toStdString(): "";
                string nazione=att.hasAttribute("nazione")? att.value("nazione").toString().toStdString(): "";
                string regione=att.hasAttribute("regione")? att.value("regione").toString().toStdString(): "";
                string produttore=att.hasAttribute("produttore")? att.value("produttore").toString().toStdString(): "";
                string aggettivo=att.hasAttribute("aggettivo")? att.value("aggettivo").toString().toStdString(): "";
                string colore=att.hasAttribute("colore")? att.value("colore").toString().toStdString(): "";
                string img64=att.hasAttribute("img64")? att.value("img64").toString().toStdString(): "";
                double prezzo=att.hasAttribute("prezzo")? att.value("prezzo").toDouble(): 0.00;
                double gradazioneAlcolica=att.hasAttribute("gradazioneAlcolica")? att.value("gradazioneAlcolica").toDouble(): 0.00;
                int temperaturaSuggerita=att.hasAttribute("temperaturaSuggerita")? att.value("temperaturaSuggerita").toInt(): 0;
                int mlBottiglia=att.hasAttribute("mlBottiglia")? att.value("mlBottiglia").toInt(): 0;
                int annata=att.hasAttribute("annata")? att.value("annata").toInt(): 0;



                Vino* toPush=nullptr;

                if(reader.name()=="Barricato"){

                    string legno= att.hasAttribute("legno")? att.value("legno").toString().toStdString():"";

                    toPush= new VinoBarricato(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,
                                              gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,legno);

                }else if(reader.name()=="Aromatizzato"){

                    string elementoAggiunto= att.hasAttribute("elementoAggiunto")? att.value("elementoAggiunto").toString().toStdString():"";

                    toPush= new VinoAromatizzato(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,
                                              gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,elementoAggiunto);

                }else if(reader.name()=="Liquoroso"){

                    string liquoreAggiunto= att.hasAttribute("liquoreAggiunto")? att.value("liquoreAggiunto").toString().toStdString():"";

                    toPush= new VinoLiquoroso(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,
                                              gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,liquoreAggiunto);

                }else if(reader.name()=="Frizzante"){

                    double pressione= att.hasAttribute("pressione")? att.value("pressione").toDouble():0;

                    toPush= new VinoFrizzante(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,
                                              gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,pressione);

                }else if(reader.name()=="Spumante"){

                    double pressione= att.hasAttribute("pressione")? att.value("pressione").toDouble():0;
                    double residuoZuccherino= att.hasAttribute("residuoZuccherino")? att.value("residuoZuccherino").toDouble():0;


                    toPush= new Spumante(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,
                                              gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata,pressione,residuoZuccherino);
                }


                if(toPush!= nullptr){
                    push_back(toPush);
                }
                else throw MyException("Errore caricamento file!");

                if(!reader.isEndDocument())
                    reader.skipCurrentElement();
            }
        }
    }
    file.close();
    isDataSaved=true;
}

void Model::setNewPath(std::string str){
    path=str;
    delete listaVini;
    isDataSaved=false;
    listaVini=new Container<Vino*>;
}


bool Model::getIsDataSaved() const {return isDataSaved;}

void Model::setDataSaved(bool b) {isDataSaved=b;}








//RICERCA

Container<Vino*>::const_iterator Model::ricerca_cbegin() const {return risultatiRicerca->cbegin();}

Container<Vino*>::const_iterator Model::ricerca_cend() const {return risultatiRicerca->cend();}

unsigned int Model::getRicercaSize() const {return risultatiRicerca->getSize();}

Vino *Model::ricercaVinoAt(unsigned int index){
    return risultatiRicerca->at(index);}


void Model::resetRisultatiRicerca() const {
    if(!(*risultatiRicerca == *listaVini))
        *risultatiRicerca = *listaVini;}


void Model::eliminaTrovati() const {
    for(auto it = ricerca_cbegin(); it != ricerca_cend(); ++it){
        listaVini->erase(*it);
        delete (*it);}

    resetRisultatiRicerca();
}



void Model::filterByTipo(string tipo) const {
     for(auto it =ricerca_cbegin() ; it != ricerca_cend(); ++it){
        if(tipo != (*it)->getTipo()){
            risultatiRicerca->erase(*it);
            --it;
        }
    }
}


void Model::filterByNome(string nome) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it){
        if(!(caseSensitive(nome,(*it)->getNome()))){
            risultatiRicerca->erase(*it);
            --it;
        }
    }

}

void Model::filterByNazione(string nazione) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it){
        if(!(caseSensitive(nazione,(*it)->getNazione()))){
            risultatiRicerca->erase(*it);
            --it;
        }
    }

}


void Model::filterByProduttore(string produttore) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it){
       if(!(caseSensitive(produttore,(*it)->getProduttore()))){
            risultatiRicerca->erase(*it);
            --it;
        }
    }

}

void Model::filterByColore(string colore) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it){
        if(!(caseSensitive(colore,(*it)->getColore()))){
            risultatiRicerca->erase(*it);
            --it;
        }
    }

}


void Model::filterByAnnata(int annata) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it)
        if(annata != (*it)->getAnnata()){
            risultatiRicerca->erase(*it);
            --it;
        }

}


void Model::filterByPrezzoMaggiore(double prezzo) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it)
        if(((*it)->getPrezzo()<=prezzo)){
            risultatiRicerca->erase(*it);
            --it;
        }

}

void Model::filterByPrezzoMinore(double prezzo) const {
    for(auto it= risultatiRicerca->cbegin(); it!= risultatiRicerca->cend(); ++it)
        if(((*it)->getPrezzo()>=prezzo)){
            risultatiRicerca->erase(*it);
            --it;
        }

}

