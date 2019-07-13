#ifndef VINO_H
#define VINO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using std::string;

class Vino {
private:
    string nome;
    string nazione;
    string regione;
    string produttore;
    string aggettivo;
    string colore;
    string img64;
    double prezzo;
    double gradazioneAlcolica;
    int temperaturaSuggerita;
    int mlBottiglia;
    int annata;

public:
    //costruttori,operatori,metodi virtuali
    Vino(string nome, string nazione, string regione, string produttore, string aggettivo, string colore, string img64,
         double prezzo, double gradazioneAlcolica, int temperaturaSuggerita, int mlBottiglia, int annata);
    Vino(const Vino&);
    virtual Vino& operator=(const Vino&) = delete; //rompo la regola dei 3 non permettendo assegnazione, ma permetto Vino* x=y.clone();

    virtual Vino* clone() const =0;
    virtual bool operator==(const Vino&) const;
    virtual bool operator!=(const Vino&) const;
    virtual ~Vino() =default;

    virtual string getTipo() const =0;
    virtual string getInfo() const;

    //getters
    string getNome() const;
    string getNazione() const;
    string getRegione() const;
    string getProduttore() const;
    string getAggettivo() const;
    string getColore() const;
    string getImg64() const;
    double getPrezzo() const;
    double getGradazioneAlcolica() const;
    int getTemperaturaSuggerita() const;
    int getMlBottiglia() const;
    int getAnnata() const;


    //setters
    void setNome(string nome);
    void setNazione(string nazione);
    void setRegione(string regione);
    void setProduttore(string produttore);
    void setAggettivo(string aggettivo);
    void setColore(string colore);
    void setImg64(string img64);
    void setPrezzo(double prezzo);
    void setGradazioneAlcolica(double gradazioneAlcolica);
    void setTemperaturaSuggerita(int temperaturaSuggerita);
    void setMlBottiglia(int mlBottiglia);
    void setAnnata(int annata);
};






//Non-astratta
class VinoBarricato: public Vino{
private:
    string legno; //tipo di legno usato
public:
    //costruttori
    VinoBarricato(string nome="No name" ,string nazione="No name", string regione="No name", string produttore="No name", string aggettivo="No name", string colore="No name", string img64="No name",
                  double prezzo=0, double gradazioneAlcolica=0, int temperaturaSuggerita=0, int mlBottiglia=0, int annata=0, string legno="No name");
    VinoBarricato(const VinoBarricato& vb);

    //get e set
    string getLegno() const;
    void setLegno(string legno);

    //virtual stuff
    VinoBarricato* clone() const;
    bool operator==(const Vino&) const;
    bool operator!=(const Vino&) const;

    string getTipo() const;
    string getInfo() const;
};






//Non-astratta
class VinoAromatizzato: public Vino{
private:
    string elementoAggiunto;
public:
    //costruttori
    VinoAromatizzato(string nome="No name" ,string nazione="No name" , string regione="No name", string produttore="No name", string aggettivo="No name", string colore="No name", string img64="No name",
                     double prezzo=0, double gradazioneAlcolica=0, int temperaturaSuggerita=0, int mlBottiglia=0, int annata=0, string elementoAggiunto="No name");
    VinoAromatizzato(const VinoAromatizzato& va);

    //get e set
    string getElementoAggiunto() const;
    void setElementoAggiunto(string elementoAggiunto);

    //virtual stuff
    VinoAromatizzato* clone() const;
    bool operator==(const Vino&) const;
    bool operator!=(const Vino&) const;


    string getTipo() const;
    string getInfo() const;
};






//Non-astratta
class VinoLiquoroso: public Vino{
    string liquoreAggiunto;
public:
    //costruttori
    VinoLiquoroso(string nome="No name" ,string nazione="No name", string regione="No name", string produttore="No name", string aggettivo="No name", string colore="No name", string img64="No name",
                  double prezzo=0, double gradazioneAlcolica=0, int temperaturaSuggerita=0, int mlBottiglia=0, int annata=0, string liquoreAggiunto="No name");
    VinoLiquoroso(const VinoLiquoroso& vl);

    //get e set
    string getLiquoreAggiunto() const;
    void setLiquoreAggiunto(string liquoreAggiunto);

    //virtual stuff
    VinoLiquoroso* clone() const;
    bool operator==(const Vino&) const;
    bool operator!=(const Vino&) const;

    string getTipo() const;
    string getInfo() const;
};








//Non-astratta
class VinoFrizzante: public Vino{
private:
    double pressione; //espressa in BAR (tra 1 e 2,5 per i frizzanti, maggiore di 3 per gli spuamanti)
public:
    //costruttori
    VinoFrizzante(string nome="No name" ,string nazione="No name", string regione="No name", string produttore="No name", string aggettivo="No name", string colore="No name", string img64="No name",
                 double prezzo=0, double gradazioneAlcolica=0, int temperaturaSuggerita=0, int mlBottiglia=0,
                 int annata=0, double pressione=0);
    VinoFrizzante(const VinoFrizzante& vf);

    //get e set
    double getPressione() const;
    void setPressione(double pressione);

    //virtual stuff
    VinoFrizzante* clone() const;
    bool operator==(const Vino&) const;
    bool operator!=(const Vino&) const;

    string getTipo() const;
    string getInfo() const;
};







//Non-astratta
class Spumante: public VinoFrizzante{
private:
    double residuoZuccherino; //espresso in percentuale; 1=100%, quindi è un numero compreso tra 0 e 1
public:
    //costruttori
    Spumante(string nome="No name" ,string nazione="No name", string regione="No name", string produttore="No name", string aggettivo="No name", string colore="No name", string img64="No name",
                 double prezzo=0, double gradazioneAlcolica=0, int temperaturaSuggerita=0, int mlBottiglia=0,
                 int annata=0, double pressione=0, double residuoZuccherino=0);
    Spumante(const Spumante& sp);

    //get e set
    double getResiduoZuccherino() const;
    void setResiduoZuccherino(double residuoZuccherino);

    //virtual stuff
    Spumante* clone() const;
    bool operator==(const Vino&) const;
    bool operator!=(const Vino&) const;

    string getTipo() const;
    string getInfo() const;

};


#endif // VINO_H
