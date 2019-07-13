#include "catalogo.h"

Catalogo::Catalogo(QWidget* p) :
    QWidget(p),

    listaVini(new VinoListWidget(this)),
    buttonElimina(new QPushButton("Elimina", this)),
    buttonModifica(new QPushButton("Modifica",this)),
    dialogDettaglioVino(nullptr)
{
    QVBoxLayout* vBox = new QVBoxLayout(this);
    buttonElimina->setEnabled(false);
    buttonModifica->setEnabled(false);
    vBox->addWidget(listaVini);
    listaVini->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(buttonModifica);
    hBox->addWidget(buttonElimina);

    vBox->addLayout(hBox);

    connect(listaVini, SIGNAL(currentRowChanged(int)), this, SLOT(slotElementoSelezionato()));
    connect(this, SIGNAL(signalElementoSelezionato(bool)), this,SLOT(slotElementoSelezionato(bool)));

}

Catalogo::~Catalogo() {
    delete listaVini;
    delete buttonElimina;
    delete buttonModifica;
}



QPushButton *Catalogo::getButtonElimina() const {return buttonElimina;}

QPushButton *Catalogo::getButtonModifica() const {return buttonModifica;}

VinoListWidget *Catalogo::getListaVini() const {return listaVini;}



//SLOTS
void Catalogo::slotElementoSelezionato(bool b) const {
    buttonElimina->setEnabled(b);
    buttonModifica->setEnabled(b);
}


void Catalogo::slotRigaCambiata() const {
    emit slotElementoSelezionato(true);
}
