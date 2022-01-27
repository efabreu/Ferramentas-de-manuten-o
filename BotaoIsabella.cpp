#include "BotaoIsabella.h"
//#include "mainwindow.h"

BotaoIsabella::BotaoIsabella(int digit, int digit2, QWidget *parent)
    : QPushButton(parent)
{
    myDigit = digit;
    myDigit2 = digit2;
    setMaximumSize(34,34);
    setFlat(0);
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

void BotaoIsabella::reemitClicked()
{
    emit clicked(myDigit, myDigit2);
}
