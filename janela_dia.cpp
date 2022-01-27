#include "janela_dia.h"
#include "ui_janela_dia.h"

#include <QDate>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QDateEdit>

//listas dos funcionarios
QStringList func = {0};

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
//    ui->lblDia_Btn->setText(QString::number(posicaoBotao));
//    ui->lblAno_Btn->setText(QString::number(anoBotao));
//    QDate data;
    dataDia = dataTroca = QDate(anoBotao, 1, 1).addDays(posicaoBotao);
    funcionario = sufixFunc;
    QString dataTexto = dataDia.toString("dd/MM/yyyy");
    ui->lblDia_Btn->setText(dataTexto);
    lerArquivo(sufixFunc, anoBotao);
//    ui->lblFunc_Btn->setText(func[365]);
//    int verFolga = 0;
//    verFolga = func[posicaoBotao].toInt();
    if (func[posicaoBotao].at(0) == QString::number(1)) {
        ui->lblFolga->setText("Folga");
        QPushButton * qPushButton = new QPushButton();
        qPushButton->setText("Trocar Folga");
        qPushButton->setMaximumSize(300,30);
//        qPushButton->setFlat(0);
//        qPushButton->setStyleSheet("background-color: rgb(154, 205, 50);");
        ui->qDateEdit->setDate(QDate::currentDate());
        ui->qDateEdit->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));
        ui->qLabel->setText("Trocar para dia: ");
        ui->qCalendarWidget->setDateRange(dataDia.addDays(-60),dataDia.addDays(60));

        ui->lytTroca->addWidget(qPushButton);
        connect(qPushButton, SIGNAL(clicked()), this, SLOT(onClick_qPushButton()));

    } else {
        ui->lblFolga->setText("Dia de trabalho");
        ui->qLabel->setHidden(true);
        ui->qDateEdit->setHidden(true);
        ui->qCalendarWidget->setHidden(true);
    }

}

Janela_Dia::~Janela_Dia()
{
    delete ui;
}

// lê arquivos e escreve em listas
void Janela_Dia::lerArquivo(int sufixFunc, int anoBotao)
{
    // variaveis de arquivo
    QString local = "H:/C++/Qt/Manutencao_ferramentas/";
    QString pastaAno = QString::number(anoBotao) + "/";
    QString nomeDoArquivo = "funcionario_"+QString::number(sufixFunc);
    QFile arquivo (local + pastaAno + nomeDoArquivo);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text))
    {
    QMessageBox::warning(this,"Problema!","nao existe arquivo funcionario "+QString::number(sufixFunc));
    ui->lblFunc_Btn->setText("Não existe");

    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        func = texto.split(";");
        ui->lblFunc_Btn->setText(func[365]);

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
    func[posicaoDe] = QString::number(0)+"T("+dataTroca.toString("dd/MM")+")";
    func[posicaoPara] = QString::number(1)+"T("+dataDia.toString("dd/MM") +")";

    salvarArquivo();
    QMessageBox::warning(this,"Trocar","Do dia " + dataDia.toString() + " para " + dataTroca.toString());
    Janela_Dia::close();
}

void Janela_Dia::salvarArquivo()
{
    // variaveis de arquivo
    QString local = "H:/C++/Qt/Manutencao_ferramentas/";
    QString pastaAno = QString::number(dataDia.year()) + "/";
    QString nomeDoArquivo = "funcionario_"+QString::number(funcionario);
    QFile arquivo (local + pastaAno + nomeDoArquivo);

    if (!arquivo.open(QFile::WriteOnly|QFile::Text))
            {
             QMessageBox::warning(this,"Problema!","Problemas na CRIAÇÃO do arquivo Teste");
            }else {
            QTextStream saida(&arquivo);
            for (int n = 0; n < 368; n++){
                QString texto = func[n]+";";
                saida << texto;
                }
        arquivo.flush();
        arquivo.close();
    }

}
