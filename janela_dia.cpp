#include "janela_dia.h"
#include "ui_janela_dia.h"

#include <QDate>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QDateEdit>

//listas dos funcionarios
QStringList func = {0};
QStringList funcAnoAnt = {0};
QStringList funcAnoSeg = {0};

//datas para troca
QDate dataDia;
QDate dataTroca;

//variaveis globais
int funcionario;

Janela_Dia::Janela_Dia(QWidget *parent, int anoBotao, int posicaoBotao, int sufixFunc) :
    QDialog(parent),
    ui(new Ui::Janela_Dia)
{
    ui->setupUi(this);
    QPixmap trocaFolgaIcon(":/icones/Icons/trocaFolgaIcon.png");
    this->setWindowIcon(trocaFolgaIcon);
//    ui->lblDia_Btn->setText(QString::number(posicaoBotao));
//    ui->lblAno_Btn->setText(QString::number(anoBotao));
//    QDate data;
    dataDia = dataTroca = QDate(anoBotao, 1, 1).addDays(posicaoBotao);
    this->setWindowTitle("Dados do Dia: "+dataDia.toString("dd/MM/yyyy"));
    funcionario = sufixFunc;
    QString dataTexto = dataDia.toString("dd/MM/yyyy");
    ui->lblDia_Btn->setText(dataTexto);
    func = lerArquivo(sufixFunc, anoBotao);
    int qDiasAno = dataDia.daysInYear();
    ui->lblFunc_Btn->setText(func[qDiasAno]);
    funcAnoAnt = lerArquivo(sufixFunc, anoBotao-1);
    funcAnoSeg = lerArquivo(sufixFunc, anoBotao+1);
//    ui->lblFunc_Btn->setText(func[365]);
//    int verFolga = 0;
//    verFolga = func[posicaoBotao].toInt();

    QString stringVerif = func[posicaoBotao].at(0);
    int verifFolga = stringVerif.toInt();
    QPushButton * qPushButton = new QPushButton();

                    switch(verifFolga){
                        case 0: {  //dia de trabalho normal
                            ui->lblFolga->setText("Dia de trabalho");
                            ui->qLabel->setHidden(true);
                            ui->qDateEdit->setHidden(true);
                            ui->qCalendarWidget->setHidden(true);
                            break;
                        }
                        case 1: { //dia de folga normal
                            ui->lblFolga->setText("Folga");
                            qPushButton->setText("Trocar Folga");
                            qPushButton->setMaximumSize(300,30);
                            ui->qDateEdit->setDate(QDate::currentDate());
                            ui->qDateEdit->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
                            ui->qLabel->setText("Trocar para dia: ");
                            ui->qCalendarWidget->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
                            ui->lytTroca->addWidget(qPushButton);
                            connect(qPushButton, SIGNAL(clicked()), this, SLOT(onClick_qPushButton()));
                            break;
                        }
                        case 2:{ //dia de folga apos quinta
                            ui->lblFolga->setText("Folga extraordinária após quinta");
                            qPushButton->setText("Trocar Folga");
                            qPushButton->setMaximumSize(300,30);
                            ui->qDateEdit->setDate(QDate::currentDate());
                            ui->qDateEdit->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
                            ui->qLabel->setText("Trocar para dia: ");
                            ui->qCalendarWidget->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
                            ui->lytTroca->addWidget(qPushButton);
                            connect(qPushButton, SIGNAL(clicked()), this, SLOT(onClick_qPushButton()));
                            break;
                        }
                        case 3:{ //dia de trabalho troca
                            ui->lblFolga->setText("Dia de trabalho (Troca)");
                            ui->qLabel->setHidden(true);
                            ui->qDateEdit->setHidden(true);
                            ui->qCalendarWidget->setHidden(true);
                            break;
                        }
                        case 4:{ //dia de folga troca
                            ui->lblFolga->setText("Folga (Troca)");
                            qPushButton->setText("Trocar Folga");
                            qPushButton->setMaximumSize(300,30);
                            ui->qDateEdit->setDate(QDate::currentDate());
                            ui->qDateEdit->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
                            ui->qLabel->setText("Trocar para dia: ");
                            ui->qCalendarWidget->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
                            ui->lytTroca->addWidget(qPushButton);
                            connect(qPushButton, SIGNAL(clicked()), this, SLOT(onClick_qPushButton()));
                            break;
                        }
                        case 5:{ //dia de ferias
                            ui->lblFolga->setText("Férias");
                            ui->qLabel->setHidden(true);
                            ui->qDateEdit->setHidden(true);
                            ui->qCalendarWidget->setHidden(true);
                            break;
                        }
                        case 6:{ //dia de feriado ou folga adicional
                            ui->lblFolga->setText("Feriado ou folga extra");
                            ui->qLabel->setHidden(true);
                            ui->qDateEdit->setHidden(true);
                            ui->qCalendarWidget->setHidden(true);
                            break;
                        }

                    }


}

Janela_Dia::~Janela_Dia()
{
    delete ui;
}

// lê arquivos e escreve em listas
QStringList Janela_Dia::lerArquivo(int sufixFunc, int anoBotao)
{
    QStringList lista = {0};
    // variaveis de arquivo
    QString local = "M:/Técnica/01- MANUTENÇÃO_INSTALAÇÕES/2 - MINAS ARENA/3 - MANUTENÇÃO PREVENTIVAS/Escala 3.1/DADOS ESCALAS/";
    QString pastaAno = QString::number(anoBotao) + "/";
    QString nomeDoArquivo = "funcionario_"+QString::number(sufixFunc);
    // le arquivo ano atual
    QFile arquivo (local + pastaAno + nomeDoArquivo);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text))
    {
//    QMessageBox::warning(this,"Problema!","nao existe arquivo funcionario "+QString::number(sufixFunc));
//    ui->lblFunc_Btn->setText("Não existe");
        lista [0] = "Não existe";
        arquivo.flush();
        arquivo.close();
        return lista;

    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        lista = texto.split(";");
        return lista;
    }
    arquivo.flush();
    arquivo.close();

}

void Janela_Dia::on_qCalendarWidget_clicked(const QDate &date)
{
    dataTroca = date;
    ui->qDateEdit->setDate(date);
}

void Janela_Dia::onClick_qPushButton()
{
    int posicaoDe = dataDia.dayOfYear() - 1;
    int posicaoPara = dataTroca.dayOfYear() - 1;
    int anoDe = dataDia.year();
    int anoPara = dataTroca.year();
    func[posicaoDe] = QString::number(3)+"T("+dataTroca.toString("dd/MM")+")";
    if (funcAnoAnt[0] == "Não existe" && anoDe - anoPara == 1 ) {
        QMessageBox::warning(this,"Problema!","Não existe arquivo para dia destino da folga.");
        return;
    }
    if (funcAnoSeg[0] == "Não existe" && anoDe - anoPara == -1 ) {
        QMessageBox::warning(this,"Problema!","Não existe arquivo para dia destino da folga.");
        return;
    }
    switch (anoDe - anoPara){
        case 0:
            func[posicaoPara] = QString::number(4)+"T("+dataDia.toString("dd/MM") +")";
            break;
        case -1:
            funcAnoSeg[posicaoPara] = QString::number(4)+"T("+dataDia.toString("dd/MM") +")";
            break;
        case 1:
            funcAnoAnt[posicaoPara] = QString::number(4)+"T("+dataDia.toString("dd/MM") +")";
            break;
        }

//    func[posicaoPara] = QString::number(4)+"T("+dataDia.toString("dd/MM") +")";

    salvarArquivo(func, anoDe);
    if (anoDe < anoPara){
        salvarArquivo(funcAnoSeg, anoPara);
    }
    if (anoDe > anoPara){
        salvarArquivo(funcAnoAnt, anoPara);
    }
    QMessageBox::warning(this,"Trocar","Do dia " + dataDia.toString("dd/MM/yyyy") + " para " + dataTroca.toString("dd/MM/yyyy"));
    Janela_Dia::close();
}

void Janela_Dia::salvarArquivo(QStringList listaSalvar, int ano)
{
    // variaveis de arquivo
    QString local = "M:/Técnica/01- MANUTENÇÃO_INSTALAÇÕES/2 - MINAS ARENA/3 - MANUTENÇÃO PREVENTIVAS/Escala 3.1/DADOS ESCALAS/";
    QString pastaAno = QString::number(ano) + "/";
    QString nomeDoArquivo = "funcionario_"+QString::number(funcionario);
    QFile arquivo (local + pastaAno + nomeDoArquivo);

    if (!arquivo.open(QFile::WriteOnly|QFile::Text))
            {
             QMessageBox::warning(this,"Problema!","Problemas na CRIAÇÃO do arquivo Teste");
            }else {
            QTextStream saida(&arquivo);
            for (int n = 0; n < 368; n++){
                QString texto = listaSalvar[n]+";";
                saida << texto;
                }
        arquivo.flush();
        arquivo.close();
    }

}

void Janela_Dia::on_qDateEdit_userDateChanged(const QDate &date)
{
    ui->qCalendarWidget->setSelectedDate(date);
    dataTroca = date;

}

