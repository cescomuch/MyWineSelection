#include "vinolistwidget.h"
#include <QScrollBar>

VinoListWidget::VinoListWidget(QWidget* p) : parent(p){
    setIconSize(QSize(350,350));
    addScrollBarWidget(new QScrollBar(Qt::Orientation::Vertical,parent), Qt::AlignRight);}


void VinoListWidget::aggiungiVino(Vino *vino){
    VinoListItem* item=new VinoListItem(vino, parent);
    addItem(item);}


VinoListItem *VinoListWidget::takeItem(int index){
    VinoListItem* p=static_cast<VinoListItem*>(QListWidget::takeItem(index));
    return p;}


VinoListItem* VinoListWidget::takeItem(Vino* daTogliere){
    bool trovato=false;
    VinoListItem* res=nullptr;
    for(int i=0; i<count()&& !trovato; ++i){
        VinoListItem* tmp=static_cast<VinoListItem*>(item(i));
        if(tmp->getItem()==daTogliere){
            res=static_cast<VinoListItem*>(takeItem(i));
            trovato=true;
        }
    }
    return res;}



VinoListItem* VinoListWidget::currentItem() const {
    return static_cast<VinoListItem*>(QListWidget::currentItem());}
