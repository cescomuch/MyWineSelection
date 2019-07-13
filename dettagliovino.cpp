#include "inserisci.h"
#include "dettagliovino.h"
#include "utils.h"
#include "vino.h"

#include <QLabel>
#include <QFormLayout>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QBuffer>


void DettaglioVino::setFoto(const QPixmap &p) {immagine->setPixmap(p);}

DettaglioVino::DettaglioVino(VinoListItem* v, QWidget* parent):
    itemVino(v),
    buttonClose(new QPushButton("Chiudi senza salvare",parent)),
    buttonSalvaModifica( new QPushButton("Salva modifiche",parent)),
    vino(v->getItem()),
    immagine(new QLabel(parent)),
    pathFoto(new QLineEdit("Aggiorna foto")),
    buttonScegliFoto(new QPushButton()),
    prezzo(new QTextEdit(parent))
{

    setFixedSize(QSize(700,700));



    pathFoto->setEnabled(false);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* fotoLayout = new QHBoxLayout();



    prezzo->setText(QString::number(vino->getPrezzo()));
    mainLayout->addWidget(new QLabel("Nuovo prezzo: "));
    mainLayout->addWidget(prezzo);



    fotoLayout->addWidget(pathFoto);
    fotoLayout->addWidget(buttonScegliFoto);


    mainLayout->addLayout(fotoLayout);
    buttonScegliFoto->setIcon(QIcon(":/Immagini/choosefile.png"));
    buttonScegliFoto->setFixedSize(QSize(50,40));

    setFoto(Img64::getImage(itemVino->getItem()->getImg64()));
    mainLayout->addWidget(immagine);

    QHBoxLayout* btnLayout= new QHBoxLayout();
    btnLayout->addWidget(buttonSalvaModifica);
    btnLayout->addWidget(buttonClose);


    mainLayout->addLayout(btnLayout);


    setLayout(mainLayout);
    setModal(true);


    connect(buttonClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(buttonSalvaModifica,SIGNAL(clicked()),this,SLOT(slotSalvaModifica()));
    connect(buttonScegliFoto,SIGNAL(clicked()),this,SLOT(slotFotoCambiata()));
    connect(buttonSalvaModifica,SIGNAL(clicked()), this,SLOT(close()));

}


void DettaglioVino::slotSalvaModifica()const{
    vino->setPrezzo(prezzo->toPlainText().toDouble());

    if(pathFoto->text().toStdString()!=vino->getImg64()){
        vino->setImg64(Img64::getRawData(immagine->pixmap()->toImage()));
        itemVino->aggiorna();}
}



void DettaglioVino::slotFotoCambiata(){
    QString file=QFileDialog::getOpenFileName(
                this,
                tr("Scegli file"),
                "./MyWineSelection/Immagini/",
                "Image file (*.jpg)"
                );


        if(file!=""){
            setFoto(QPixmap(file));
        }
}
