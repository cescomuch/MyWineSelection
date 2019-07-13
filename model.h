#ifndef MODEL_H
#define MODEL_H

#include <vino.h>
#include <container.h>

// classe che espone i metodi di Container<Vino*>

class Model {

private:
    Container<Vino*>* listaVini;
    Container<Vino*>* risultatiRicerca;

    string path;
    bool isDataSaved;

public:
    Model(string="../MyWineSelection/nuovi_dati.xml");
    ~Model();

    void push_back(Vino*);
    Vino* vinoAt(unsigned int);

    Container<Vino*>::iterator begin();
    Container<Vino*>::iterator end();
    Container<Vino*>::const_iterator cbegin() const;
    Container<Vino*>::const_iterator cend() const;

    unsigned int getDataSize() const;
    unsigned int getDataCapacity() const;

    void erase(unsigned int);
    void erase(unsigned int, unsigned int);
    void erase(Vino*);

    bool isDataEmpty() const;

    void clear();
    void save();
    void load();
    void setNewPath(string);
    bool getIsDataSaved() const;
    void setDataSaved(bool);


    //RICERCA
    Container<Vino*>::const_iterator ricerca_cbegin() const;
    Container<Vino*>::const_iterator ricerca_cend() const;

    unsigned int getRicercaSize() const;
    Vino* ricercaVinoAt(unsigned int);
    void resetRisultatiRicerca() const;
    void eliminaTrovati() const;

    //Filtri di ricerca scelti appositamente (i più significativi per un vino)
    void filterByTipo(string tipo) const;
    void filterByNome(string nome) const;
    void filterByNazione(string nazione) const;
    void filterByProduttore(string produttore) const;
    void filterByColore(string colore) const;
    void filterByAnnata(int annata) const;
    void filterByPrezzoMaggiore(double prezzo) const;
    void filterByPrezzoMinore(double prezzo) const;

};

#endif // MODELLO_H
