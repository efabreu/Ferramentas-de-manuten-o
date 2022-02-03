#include "janelalegenda.h"
#include "ui_janelalegenda.h"

janelaLegenda::janelaLegenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::janelaLegenda)
{
    ui->setupUi(this);
    QPixmap legendaIcon(":/icones/Icons/legendaIcon.png");
    this->setWindowIcon(legendaIcon);
}

janelaLegenda::~janelaLegenda()
{
    delete ui;
}
