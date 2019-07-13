#include "mycomboboxtipo.h"

ComboBoxTipo::ComboBoxTipo(QWidget* parent):
    QComboBox (parent)
{
    addItem("Seleziona il tipo di vino");
    addItem("Barricato");
    addItem("Aromatizzato");
    addItem("Liquoroso");
    addItem("Frizzante");
    addItem("Spumante");
}
