#include "vino.h"
#include "myexception.h"
#include "utils.h"

using namespace std;

//VINO (astratta)
Vino::Vino(string nome, string nazione, string regione, string produttore, string aggettivo, string colore, string img64, double prezzo,
           double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia ,int annata) : nome(nome), nazione(nazione),
           regione(regione), produttore(produttore), aggettivo(aggettivo), colore(colore), img64(img64), prezzo(prezzo), gradazioneAlcolica(gradazioneAlcolica),
           temperaturaSuggerita(temperaturaSuggerita), mlBottiglia(mlBottiglia), annata(annata) {}

Vino::Vino(const Vino& vino) : Vino(vino.nome, vino.nazione, vino.regione, vino.produttore, vino.aggettivo, vino.colore, vino.img64, vino.prezzo,
                                    vino.gradazioneAlcolica, vino.temperaturaSuggerita, vino.mlBottiglia, vino.annata) {}


bool Vino::operator==(const Vino& vino) const {
    return nome==vino.nome && nazione==vino.nazione && regione==vino.regione && produttore==vino.produttore
            && aggettivo==vino.aggettivo && colore==vino.colore && prezzo==vino.prezzo && gradazioneAlcolica==vino.gradazioneAlcolica
            && temperaturaSuggerita==vino.temperaturaSuggerita && mlBottiglia==vino.mlBottiglia && annata==vino.annata;}

bool Vino::operator!=(const Vino& vino) const {
    return !(*this==vino);}


//getters e setters
string Vino::getNome() const {return nome;}

string Vino::getNazione() const {return nazione;}

string Vino::getRegione() const {return regione;}

string Vino::getProduttore() const {return produttore;}

string Vino::getAggettivo() const {return aggettivo;}

string Vino::getColore() const {return colore;}

string Vino::getImg64() const {return img64;}

double Vino::getPrezzo() const {return prezzo;}

double Vino::getGradazioneAlcolica() const {return gradazioneAlcolica;}

int Vino::getTemperaturaSuggerita() const {return temperaturaSuggerita;}

int Vino::getMlBottiglia() const {return mlBottiglia;}

int Vino::getAnnata() const {return annata;}





void Vino::setNome(string nome) {this->nome=nome;}

void Vino::setNazione(string nazione) {this->nazione=nazione;}

void Vino::setRegione(string regione) {this->regione=regione;}

void Vino::setProduttore(string produttore) {this->produttore=produttore;}

void Vino::setAggettivo(string aggettivo) {this->aggettivo=aggettivo;}

void Vino::setColore(string colore) {this->colore=colore;}

void Vino::setImg64(string img64) {this->img64=img64;}

void Vino::setPrezzo(double prezzo) {this->prezzo=prezzo;}

void Vino::setGradazioneAlcolica(double gradazioneAlcolica) {this->gradazioneAlcolica=gradazioneAlcolica;}

void Vino::setTemperaturaSuggerita(int temperaturaSuggerita) {this->temperaturaSuggerita=temperaturaSuggerita;}

void Vino::setMlBottiglia(int mlBottiglia) {this->mlBottiglia=mlBottiglia;}

void Vino::setAnnata(int annata) {this->annata=annata;}


string Vino::getInfo() const {
    string str="\nVino "+getTipo()+":";
    return str.append("\n")
            .append("\n• Nome: " +getNome())
            .append("\n• Nazione: "+ getNazione())
            .append("\n• Regione: " + getRegione())
            .append("\n• Produttore: " + getProduttore())
            .append("\n• Descrizione: "+ getAggettivo())
            .append("\n• Colore: " + getColore())
            .append("\n• Prezzo: " + to_string(getPrezzo())).append(" €")
            .append("\n• Gradazione alcolica: " + to_string(getGradazioneAlcolica())).append("°")
            .append("\n• Temperatura suggerita: "+ to_string(getTemperaturaSuggerita())).append("°")
            .append("\n• ml bottiglia: " + to_string(getMlBottiglia())).append(" ml")
            .append("\n• Annata: " + to_string(getAnnata()));
}







//BARRICATO
VinoBarricato::VinoBarricato(string nome ,string nazione, string regione, string produttore, string aggettivo, string colore, string img64, double prezzo,
              double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia, int annata, string legno) :
              Vino(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata),
              legno(legno) {}

VinoBarricato::VinoBarricato(const VinoBarricato& vb) : VinoBarricato(vb.getNome(), vb.getNazione(), vb.getRegione(), vb.getProduttore(),
                                                                      vb.getAggettivo(), vb.getColore(), vb.getImg64(), vb.getPrezzo(), vb.getGradazioneAlcolica(),
                                                                      vb.getTemperaturaSuggerita(),vb.getMlBottiglia(), vb.getAnnata(), vb.legno) {}

string VinoBarricato::getLegno() const {return legno;}

void VinoBarricato::setLegno(string legno) {this->legno=legno;}


VinoBarricato* VinoBarricato::clone() const {return new VinoBarricato(*this);}

bool VinoBarricato::operator==(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoBarricato*>(&vino);
    return tmp && Vino::operator==(vino) && legno==tmp->legno;

}
bool VinoBarricato::operator!=(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoBarricato*>(&vino);
    return !tmp || Vino::operator!=(vino) || legno!=tmp->legno;
}

string VinoBarricato::getTipo() const {return string("Barricato"); }

string VinoBarricato::getInfo()const {
    string str=Vino::getInfo();
    return str.append( "\n• Tipo legno: "+ getLegno())
            .append("\n");
}





//AROMATIZZATO
VinoAromatizzato::VinoAromatizzato(string nome ,string nazione, string regione,string produttore,string aggettivo,string colore, string img64,double prezzo,
              double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia, int annata, string elementoAggiunto) :
              Vino(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata),
              elementoAggiunto(elementoAggiunto) {}

VinoAromatizzato::VinoAromatizzato(const VinoAromatizzato& va) : VinoAromatizzato(va.getNome(), va.getNazione(), va.getRegione(), va.getProduttore(),
                                                                      va.getAggettivo(), va.getColore(),va.getImg64(), va.getPrezzo(), va.getGradazioneAlcolica(),
                                                                      va.getTemperaturaSuggerita(),va.getMlBottiglia(), va.getAnnata(), va.elementoAggiunto) {}

string VinoAromatizzato::getElementoAggiunto() const {return elementoAggiunto;}

void VinoAromatizzato::setElementoAggiunto(string elementoAggiunto) {this->elementoAggiunto=elementoAggiunto;}


VinoAromatizzato* VinoAromatizzato::clone() const {return new VinoAromatizzato(*this);}

bool VinoAromatizzato::operator==(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoAromatizzato*>(&vino);
    return tmp && Vino::operator==(vino) && elementoAggiunto==tmp->elementoAggiunto;

}
bool VinoAromatizzato::operator!=(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoAromatizzato*>(&vino);
    return !tmp || Vino::operator!=(vino) || elementoAggiunto!=tmp->elementoAggiunto;
}

string VinoAromatizzato::getTipo() const {return string("Aromatizzato");}


string VinoAromatizzato::getInfo() const {
    string str=Vino::getInfo();
    return str.append( "\n• Aroma aggiunto: "+ getElementoAggiunto())
            .append("\n");
}








//LIQUOROSO
VinoLiquoroso::VinoLiquoroso(string nome ,string nazione, string regione, string produttore, string aggettivo, string colore, string img64, double prezzo,
              double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia, int annata, string liquoreAggiunto) :
              Vino(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata),
              liquoreAggiunto(liquoreAggiunto) {}

VinoLiquoroso::VinoLiquoroso(const VinoLiquoroso& vl) : VinoLiquoroso(vl.getNome(), vl.getNazione(), vl.getRegione(), vl.getProduttore(),
                                                                      vl.getAggettivo(), vl.getColore(),vl.getImg64(), vl.getPrezzo(), vl.getGradazioneAlcolica(),
                                                                      vl.getTemperaturaSuggerita(),vl.getMlBottiglia(), vl.getAnnata(), vl.liquoreAggiunto) {}

string VinoLiquoroso::getLiquoreAggiunto() const {return liquoreAggiunto;}

void VinoLiquoroso::setLiquoreAggiunto(string liquoreAggiunto) {this->liquoreAggiunto=liquoreAggiunto;}


VinoLiquoroso* VinoLiquoroso::clone() const {return new VinoLiquoroso(*this);}

bool VinoLiquoroso::operator==(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoLiquoroso*>(&vino);
    return tmp && Vino::operator==(vino) && liquoreAggiunto==tmp->liquoreAggiunto;

}
bool VinoLiquoroso::operator!=(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoLiquoroso*>(&vino);
    return !tmp || Vino::operator!=(vino) || liquoreAggiunto!=tmp->liquoreAggiunto;
}

string VinoLiquoroso::getTipo() const { return string("Liquoroso"); }

string VinoLiquoroso::getInfo() const {
    string str=Vino::getInfo();
    return str.append( "\n• Liquore aggiunto: "+ getLiquoreAggiunto())
            .append("\n");
}











//FRIZZANTE
VinoFrizzante::VinoFrizzante(string nome ,string nazione, string regione, string produttore,string aggettivo,string colore, string img64, double prezzo,
              double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia, int annata, double pressione) :
              Vino(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,gradazioneAlcolica,temperaturaSuggerita,mlBottiglia,annata),
              pressione(pressione) {}

VinoFrizzante::VinoFrizzante(const VinoFrizzante& vf) : VinoFrizzante(vf.getNome(), vf.getNazione(), vf.getRegione(), vf.getProduttore(),
                                                                      vf.getAggettivo(),vf.getColore(),vf.getImg64(), vf.getPrezzo(), vf.getGradazioneAlcolica(),
                                                                      vf.getTemperaturaSuggerita(),vf.getMlBottiglia(), vf.getAnnata(), vf.pressione) {}

double VinoFrizzante::getPressione() const {return pressione;}

void VinoFrizzante::setPressione(double pressione) {this->pressione=pressione;}

bool VinoFrizzante::operator==(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoFrizzante*>(&vino);
    return tmp && Vino::operator==(vino) && pressione==tmp->pressione;

}

VinoFrizzante* VinoFrizzante::clone() const {return new VinoFrizzante(*this);}


bool VinoFrizzante::operator!=(const Vino& vino) const {
    auto tmp=dynamic_cast<const VinoFrizzante*>(&vino);
    return !tmp || Vino::operator!=(vino) || pressione!=tmp->pressione;
}

string VinoFrizzante::getTipo() const { return string("Frizzante"); }

string VinoFrizzante::getInfo() const {
    string str=Vino::getInfo();
    return str.append( "\n• Pressione: "+ to_string(getPressione())).append(" bar")
            .append("\n");
}









//SPUMANTE
Spumante::Spumante(string nome ,string nazione, string regione, string produttore, string aggettivo, string colore, string img64, double prezzo,
              double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia, int annata, double pressione,
              double residuoZuccherino) : VinoFrizzante(nome,nazione,regione,produttore,aggettivo,colore,img64,prezzo,gradazioneAlcolica,
              temperaturaSuggerita,mlBottiglia,annata,pressione), residuoZuccherino(residuoZuccherino) {}

Spumante::Spumante(const Spumante& sp) : Spumante (sp.getNome(), sp.getNazione(), sp.getRegione(), sp.getProduttore(), sp.getAggettivo(),sp.getColore(), sp.getImg64(),
                                                   sp.getPrezzo(), sp.getGradazioneAlcolica(), sp.getTemperaturaSuggerita(),sp.getMlBottiglia(),
                                                   sp.getAnnata(), sp.getPressione(),sp.residuoZuccherino) {}

double Spumante::getResiduoZuccherino() const {return residuoZuccherino;}

void Spumante::setResiduoZuccherino(double residuoZuccherino) {this->residuoZuccherino=residuoZuccherino;}

Spumante* Spumante::clone() const {return new Spumante(*this);}

bool Spumante::operator==(const Vino& vino) const {
    auto tmp=dynamic_cast<const Spumante*>(&vino);
    return tmp && VinoFrizzante::operator==(vino) && residuoZuccherino==tmp->residuoZuccherino;

}
bool Spumante::operator!=(const Vino& vino) const {
    auto tmp=dynamic_cast<const Spumante*>(&vino);
    return !tmp || VinoFrizzante::operator!=(vino) || residuoZuccherino!=tmp->residuoZuccherino;
}


string Spumante::getTipo() const {return string("Spumante");}

string Spumante::getInfo() const {
    string str=Vino::getInfo();
    return str.append("\n• Pressione: " + to_string(getPressione())).append(" bar")
    .append("\n• Residuo zuccherino: "+ to_string(getResiduoZuccherino())).append("%")
            .append("\n");
}

