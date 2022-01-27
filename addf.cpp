#include "addf.h"
#include "ui_addf.h"
#include <QFile>
#include <QDate>
#include <QMessageBox>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <QFileInfo>
#include <QDir>

using namespace std;

//inserir o mes
//QDate dataAtual = QDate::currentDate();
//int mes = dataAtual.month();
//int anoAtual = dataAtual.year();
//int ano = anoAtual;
//int bic = (ano % 4 == 0) ? 1 : 0;

// variaveis de folga
bool folgasf1 [365] = {0};
QStringList verifArquivo = {0};


addF::addF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addF)
{
    ui->setupUi(this);
    ui->cbx_numFunc->setItemData(0, 3); //funcionário 01, escala 4
    ui->cbx_numFunc->setItemData(1, 0); //funcionário 02, escala 1
    ui->cbx_numFunc->setItemData(2, 1); //funcionário 03, escala 2
    ui->cbx_numFunc->setItemData(3, 2); //funcionário 04, escala 3
    ui->cbx_numFunc->setItemData(4, 3); //funcionário 05, escala 4
    ui->cbx_numFunc->setItemData(5, 3); //funcionário 06, escala 4
    ui->cbx_numFunc->setItemData(6, 2); //funcionário 07, escala 3
    ui->cbx_numFunc->setItemData(7, 1); //funcionário 08, escala 2
    ui->cbx_numFunc->setItemData(8, 0); //funcionário 09, escala 1
    ui->cbx_numFunc->setItemData(9, 3); //funcionário 10, escala 4
    ui->cbx_numFunc->setCurrentIndex(10);
    ui->btn_criar->setDisabled(1);

    QDate dataAtual = QDate::currentDate();
    ui->spinBox_Ano->setRange(dataAtual.year()-1, dataAtual.year()+3);
    ui->spinBox_Ano->setValue(dataAtual.year());
    ui->spinBox_Escala->setRange(1,4);
    ui->spinBox_Escala->setValue(1);

    //QString local_2 = QDir::rootPath();
    QString local_2 = QCoreApplication::applicationDirPath();
    ui->diretorio->setText(local_2);

}

addF::~addF()
{
    delete ui;
}

void addF::on_btn_criar_clicked()
{
//    //variavel calculo ano bicesto
//    QDate dataAtual = QDate::currentDate();
//    int ano = dataAtual.year();
//    int bic = (ano % 4 == 0) ? 1 : 0;
//    int d_ano = 365 + bic;

//    for (int a = ano; a <= 2025; a += 1) {

//        // variaveis de arquivo
//        QString local = "H:/C++/Qt/Manutencao_ferramentas/";
//        QString pastaAno = QString::number(a) + "/";
//        QString nomeDoArquivo = "funcionario_";
//        int bicesto = ((a-1) % 4 == 0) ? 1 : 0;
//        int compensacao = ((a - dataAtual.year()) == 0) ? 0 : 1;

//        // variaveis QString
//        QString nome = ui->lEdit_nome->text();
//        QString equipe= ui->lEdit_equipe->text();

//        QVariant esc = ui->cbx_numFunc->currentData();
//        int escala = esc.toInt();
//        int sufixoFunc = ui->cbx_numFunc->currentIndex()+1;

//        if (arquivoExiste(local + pastaAno + nomeDoArquivo + QString::number(sufixoFunc))) {
//            QMessageBox::warning(this, "Arquivo", "Arquivo já Existe!");
//            break;
//            } else {
//                gravarMatriz(escala - 1 - (a - dataAtual.year()) - bicesto - compensacao, d_ano);
//                criaArquivo (local + pastaAno + nomeDoArquivo + QString::number(sufixoFunc), nome, equipe);
//            }

//    }

    //variavel calculo ano bicesto
    QDate dataAtual = QDate::currentDate();
    int ano = dataAtual.year();
    int bic = (ano % 4 == 0) ? 1 : 0;
    int d_ano = 365 + bic;

    // variaveis de arquivo
    int a = ui->spinBox_Ano->value();
    QString local = "H:/C++/Qt/Manutencao_ferramentas/";
    QString pastaAno = QString::number(a) + "/";
    QString pastaAnoAnterior = QString::number(a-1) + "/";
    QString nomeDoArquivo = "funcionario_";
    int escala;

    // variaveis QString
    QString nome = ui->lEdit_nome->text();
    QString equipe= ui->lEdit_equipe->text();

    int sufixoFunc = ui->cbx_numFunc->currentIndex()+1;
    if (arquivoExiste(local + pastaAnoAnterior + nomeDoArquivo + QString::number(sufixoFunc))) {
        escala = lerArquivo(local + pastaAnoAnterior + nomeDoArquivo + QString::number(sufixoFunc));
        } else {
        escala = ui->spinBox_Escala->value();
        }

    if (arquivoExiste(local + pastaAno + nomeDoArquivo + QString::number(sufixoFunc))) {
        QMessageBox::warning(this, "Arquivo", "Arquivo já Existe!");
        } else {
            gravarMatriz(escala, d_ano);
            criaArquivo (local + pastaAno + nomeDoArquivo + QString::number(sufixoFunc), nome, equipe);
        }

}


void addF::gravarMatriz(int escala, int d_ano)
{
    for (int i = escala; i <= d_ano; i += 4) {
        folgasf1 [i] = 1;
        int ano = ui->spinBox_Ano->value();
        QDate verifQuinta;
        verifQuinta.setDate(ano,1,1);
        verifQuinta = verifQuinta.addDays(i);
        if (verifQuinta.dayOfWeek() == 4){
            folgasf1 [i+1] = 1;
        }

    }
}




// função que verifica se o arquivo existe
bool addF::arquivoExiste(QString path) {
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void addF::criaArquivo(QString path, QString nome, QString equipe) {
    QFile arquivo (path);

    //variavel calculo ano bicesto
    QDate dataAtual = QDate::currentDate();
    int ano = dataAtual.year();
    int bic = (ano % 4 == 0) ? 1 : 0;
    int d_ano = 365 + bic;

    if (!arquivo.open(QFile::WriteOnly|QFile::Text))
            {
             QMessageBox::warning(this,"Problema!","Problemas na CRIAÇÃO do arquivo Funcionario");
            }else {
            QTextStream saida(&arquivo);
            for (int n = 0; n < d_ano; n++){
                QString texto = QString::number(folgasf1[n])+";";
                saida << texto;
                }
            saida << nome+";";
            saida << equipe+";";
            }
        QMessageBox::information(this,"Arquivo Criado", "O arquivo foi criado com sucesso!");
        arquivo.flush();
        arquivo.close();
        for (int i = 0; i <= d_ano; i += 1) {
            folgasf1 [i] = 0;
        }
}

void addF::removeArquivo(QString path) {
    QFile arquivo (path);

    //variavel calculo ano bicesto
    QDate dataAtual = QDate::currentDate();
    int ano = dataAtual.year();
    int bic = (ano % 4 == 0) ? 1 : 0;
    int d_ano = 365 + bic;

    if (!arquivo.open(QFile::WriteOnly|QFile::Text))
            {
             QMessageBox::warning(this,"Problema!","Problemas na REMOÇÃO do arquivo Funcionario");
            }else {
            arquivo.remove();
            }
        QMessageBox::information(this,"Arquivo Removido", "O arquivo foi removido com sucesso!");
        arquivo.flush();
        arquivo.close();
        for (int i = 0; i <= d_ano; i += 1) {
            folgasf1 [i] = 0;
        }
}

void addF::on_btn_remover_clicked()
{
    //variavel calculo ano bicesto
    QDate dataAtual = QDate::currentDate();
    int ano = dataAtual.year();

    for (int a = ano; a <= 2025; a += 1) {

        // variaveis de arquivo
        QString local = "H:/C++/Qt/Manutencao_ferramentas/";
        QString pastaAno = QString::number(a) + "/";
        QString nomeDoArquivo = "funcionario_";

        int sufixoFunc = ui->cbx_numFunc->currentIndex()+1;

        if (arquivoExiste(local + pastaAno + nomeDoArquivo + QString::number(sufixoFunc))) {
         removeArquivo (local + pastaAno + nomeDoArquivo + QString::number(sufixoFunc));
        } else {
            QMessageBox::warning(this, "Arquivo", "Arquivo não Existe!");
             }
    }
}


void addF::on_cbx_numFunc_currentIndexChanged(int index)
{
    ui->btn_criar->setEnabled(1);
}

int addF::lerArquivo(QString path) {
    QFile arquivo (path);

    //variavel calculo ano bicesto
    int ano = ui->spinBox_Ano->value()-1;
    QDate dataAtual;
    dataAtual.setDate(ano,1,1);
    int qDiasAno = dataAtual.daysInYear();
    int bic = (ano % 4 == 0) ? 1 : 0;
    int d_ano = 365 + bic;

    if (!arquivo.open(QFile::ReadOnly|QFile::Text))
            {
//             QMessageBox::warning(this,"Problema!","Problemas na CRIAÇÃO do arquivo Funcionario");
            }else {
                QTextStream entrada(&arquivo);
                QString texto = entrada.readAll();
                verifArquivo = texto.split(";");
                int dez31 = verifArquivo[qDiasAno].toInt();
                int dez30 = verifArquivo[qDiasAno-1].toInt();
                int dez29 = verifArquivo[qDiasAno-2].toInt();
                int dez28 = verifArquivo[qDiasAno-3].toInt();

                if (dez31 == 1){
                    arquivo.flush();
                    arquivo.close();
                    return 0;
                } if (dez30 == 1){
                    arquivo.flush();
                    arquivo.close();
                    return 1;
                } if (dez29 == 1){
                    arquivo.flush();
                    arquivo.close();
                    return 2;
                } if (dez28 == 1){
                    arquivo.flush();
                    arquivo.close();
                    return 3;
                }

            }
//        QMessageBox::information(this,"Arquivo Criado", "O arquivo foi criado com sucesso!");
//        arquivo.flush();
//        arquivo.close();
//        for (int i = 0; i <= d_ano; i += 1) {
//            folgasf1 [i] = 0;
//        }
}
