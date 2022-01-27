#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BotaoIsabella.h"
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <QTextStream>
#include <QComboBox>
#include <QString>
#include <QDate>
#include <QFile>
#include <QMessageBox>



//inserir o mes
QDate dataAtual = QDate::currentDate();
int mes = dataAtual.month();
int anoAtual = dataAtual.year();
int ano = anoAtual;
int bic = (ano % 4 == 0) ? 1 : 0;

//inserir o mes
int posicaoBotao = 0;

//listas dos funcionarios
QStringList func1 = {0};
QStringList func2 = {0};
QStringList func3 = {0};
QStringList func4 = {0};
QStringList func5 = {0};
QStringList func6 = {0};
QStringList func7 = {0};
QStringList func8 = {0};
QStringList func9 = {0};
QStringList func10 = {0};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cBox_ano->setCurrentText(QString::number(anoAtual));
    for(int n = 1; n <= 10; n++){
    lerArquivo(n);
    }
    ui->lbl_mes->setText(alterarMes(mes));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// cria os dias do mes
void MainWindow::criarDia(int qDiasMes)
{
    QLayoutItem * child;
    while ((child = ui->horizontalLayout->takeAt(0))!=0) {
        delete child->widget();
        delete child;
    }

    //ui->horizontalLayout->destroyed();
//    QHBoxLayout * qHBoxLayout = new QHBoxLayout();



    for (int i = 0; i < qDiasMes; i++){

        QPushButton * qPushButton = new QPushButton();
        qPushButton->setText(QString::number(i+1));
        qPushButton->setMaximumSize(34,34);
        qPushButton->setFlat(0);
        qPushButton->setStyleSheet("background-color: rgb(154, 205, 50);");
        ui->horizontalLayout->addWidget(qPushButton);
        }
//    ui->horizontalLayout->addItem(qHBoxLayout);
}


// mostrar dias de folga de cada escala - funcionario 01
void MainWindow::mostrarFolgas01(int cDiasMes, int qDiasMes, int sufixFunc)
{

        switch(sufixFunc){
            QLayoutItem * child;
                case 1:
                    while ((child = ui->hlyt_funcionari01->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 2:
                    while ((child = ui->hlyt_funcionari02->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 3:
                    while ((child = ui->hlyt_funcionari03->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 4:
                    while ((child = ui->hlyt_funcionari04->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 5:
                    while ((child = ui->hlyt_funcionari05->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 6:
                    while ((child = ui->hlyt_funcionari06->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 7:
                    while ((child = ui->hlyt_funcionari07->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 8:
                    while ((child = ui->hlyt_funcionari08->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 9:
                    while ((child = ui->hlyt_funcionari09->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
                case 10:
                    while ((child = ui->hlyt_funcionari10->takeAt(0))!=0) {
                        delete child->widget();
                        delete child;
                    }
                    break;
            }

        for (int i =cDiasMes-1; i < cDiasMes+qDiasMes-1 ; i++ ) {
            BotaoIsabella * qPushButton = new BotaoIsabella(i, sufixFunc, this);
            connect(qPushButton, SIGNAL(clicked(int, int)), this, SLOT(onClick_qPushButton(int, int)));



            switch(sufixFunc){
                    case 1:
                    if (func1[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari01->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari01->addWidget(qPushButton);
                            if (func1[i].at(0) == QString::number(1)){
                                qPushButton->setText(func1[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func1[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f1->setText(func1[365]);
                            ui->lbl_e1->setText(func1[366]);
                            break;
                    }

                    case 2:
                    if (func2[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari02->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari02->addWidget(qPushButton);
                            if (func2[i].at(0) == QString::number(1)){
                                qPushButton->setText(func2[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func2[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f2->setText(func2[365]);
                            ui->lbl_e2->setText(func2[366]);
                            break;
                    }

                    case 3:
                    if (func3[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari03->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari03->addWidget(qPushButton);
                            if (func3[i].at(0) == QString::number(1)){
                                qPushButton->setText(func3[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func3[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f3->setText(func3[365]);
                            ui->lbl_e3->setText(func3[366]);
                            break;
                    }

                    case 4:
                    if (func4[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari04->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari04->addWidget(qPushButton);
                            if (func4[i].at(0) == QString::number(1)){
                                qPushButton->setText(func4[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func4[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f4->setText(func4[365]);
                            ui->lbl_e4->setText(func4[366]);
                            break;
                    }

                    case 5:
                    if (func5[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari05->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari05->addWidget(qPushButton);
                            if (func5[i].at(0) == QString::number(1)){
                                qPushButton->setText(func5[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func5[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f5->setText(func5[365]);
                            ui->lbl_e5->setText(func5[366]);
                            break;
                    }

                    case 6:
                    if (func6[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari06->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari06->addWidget(qPushButton);
                            if (func6[i].at(0) == QString::number(1)){
                                qPushButton->setText(func6[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func6[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f6->setText(func6[365]);
                            ui->lbl_e6->setText(func6[366]);
                            break;
                    }

                    case 7:
                    if (func7[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari07->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari07->addWidget(qPushButton);
                            if (func7[i].at(0) == QString::number(1)){
                                qPushButton->setText(func7[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func7[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f7->setText(func7[365]);
                            ui->lbl_e7->setText(func7[366]);
                            break;
                    }
                    case 8:
                    if (func8[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari08->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari08->addWidget(qPushButton);
                            if (func8[i].at(0) == QString::number(1)){
                                qPushButton->setText(func8[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func8[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f8->setText(func8[365]);
                            ui->lbl_e8->setText(func8[366]);
                            break;
                    }

                    case 9:
                    if (func9[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari09->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari09->addWidget(qPushButton);
                            if (func9[i].at(0) == QString::number(1)){
                                qPushButton->setText(func9[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func9[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f9->setText(func9[365]);
                            ui->lbl_e9->setText(func9[366]);
                            break;
                    }

                    case 10:
                    if (func10[0] == "NAOEXISTE") {
                        ui->hlyt_funcionari10->addWidget(qPushButton);
                        qPushButton->setText("Funcionário não declarado em arquivo!");
                        qPushButton->setFixedWidth(800);
                        qPushButton->setFlat(1);
                        return ;
                    } else{
                            ui->hlyt_funcionari10->addWidget(qPushButton);
                            if (func10[i].at(0) == QString::number(1)){
                                qPushButton->setText(func10[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(255, 0, 0);}");
                            }else{
                                qPushButton->setText(func10[i].mid(1,-1));
                                qPushButton->setStyleSheet("QPushButton{font-size: 8px;font-family: Arial"
                                                           ";color: rgb(0, 0, 0);background-color: rgb(247, 247, 247);}");
                                }
                            ui->lbl_f10->setText(func10[365]);
                            ui->lbl_e10->setText(func10[366]);
                            break;
                    }

            }

        }
}

void MainWindow::mostrarDiasSem(int qDiasMes)
{
    QLayoutItem * child;
    while ((child = ui->hlyt_diasSem->takeAt(0))!=0) {
        delete child->widget();
        delete child;
    }

    for (int i = 1; i <= qDiasMes; i++){
        QString diasSem [] {" ","S","T","Q","Q","S","S","D"};
        QDate diaUm(ano, mes, i);
        int diaSemana = diaUm.dayOfWeek();

        QPushButton * qPushButton = new QPushButton();
        qPushButton->setText(diasSem[diaSemana]);
        qPushButton->setMaximumSize(34,34);
        qPushButton->setFlat(0);
        if ((diaSemana==6) | (diaSemana==7)){
            qPushButton->setStyleSheet("background-color: rgb(255, 0, 0);");
        }else{
            qPushButton->setStyleSheet("background-color: rgb(192, 192, 192);");
            }
        ui->hlyt_diasSem->addWidget(qPushButton);
        }

}


QString MainWindow::alterarMes(int mes)
{
    QString nomeDoMes;


        switch(mes){

                case 1:
                    nomeDoMes = "Janeiro";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(1,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
                case 2:
                    nomeDoMes = "Fevereiro";
                    criarDia(28+bic);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(32,28+bic,n);
                    }
                    mostrarDiasSem(28+bic);
                    break;
                case 3:
                    nomeDoMes = "Março";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(60+bic,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
                case 4:
                    nomeDoMes = "Abril";
                    criarDia(30);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(91+bic,30,n);
                    }
                    mostrarDiasSem(30);
                    break;
                case 5:
                    nomeDoMes = "Maio";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(121+bic,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
                case 6:
                    nomeDoMes = "Junho";
                    criarDia(30);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(152+bic,30,n);
                    }
                    mostrarDiasSem(30);
                    break;
                case 7:
                    nomeDoMes = "Julho";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(182+bic,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
                case 8:
                    nomeDoMes = "Agosto";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(213+bic,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
                case 9:
                    nomeDoMes = "Setembro";
                    criarDia(30);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(244+bic,30,n);
                    }
                    mostrarDiasSem(30);
                    break;
                case 10:
                    nomeDoMes = "Outubro";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(274+bic,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
                case 11:
                    nomeDoMes = "Novembro";
                    criarDia(30);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(305+bic,30,n);
                    }
                    mostrarDiasSem(30);
                    break;
                case 12:
                    nomeDoMes = "Dezembro";
                    criarDia(31);
                    for(int n = 1; n <= 10; n++){
                    mostrarFolgas01(335+bic,31,n);
                    }
                    mostrarDiasSem(31);
                    break;
//                default:
//                    cout << "O valor digitado nao corresponde a um mes do ano!" << endl;
            }
    return nomeDoMes;
}

void MainWindow::on_pushButton_menos_clicked()
{
    if (mes > 1) {
    mes--;
    ui->lbl_mes->setText(alterarMes(mes));
    }else {

    }

}

void MainWindow::on_pushButton_mais_clicked()
{
    if (mes < 12) {
    mes++;
    ui->lbl_mes->setText(alterarMes(mes));
    }else {
        }
}

void MainWindow::on_actionAdd_Funcionario_triggered()
{
    form02 = new addF(this);
    form02->exec();

    for(int n = 1; n <= 10; n++){
    lerArquivo(n);
    }
    mes = dataAtual.month();
    alterarMes(mes);
}

void MainWindow::onClick_qPushButton(int diaBotao, int sufixFunc)
{
//    QLayoutItem * child;
//    while ((child = ui->hlyt_campoDia->takeAt(0))!=0) {
//        delete child->widget();
//        delete child;
//        }
//    QLabel * qLabel = new QLabel;
//    qLabel->setText("Folga?");
//    QComboBox * qComboBox = new QComboBox;
//    qComboBox->addItem("SIM",1);
//    qComboBox->addItem("NÃO",0);
//    ui->hlyt_campoDia->addWidget(qLabel);
//    ui->hlyt_campoDia->addWidget(qComboBox);
//    int diaBotao = 20;
    abreJanelaDia(ano, diaBotao, sufixFunc);
}

// lê arquivos e escreve em listas
void MainWindow::lerArquivo(int sufixFunc)
{
    // variaveis de arquivo
    QString local = "H:/C++/Qt/Manutencao_ferramentas/";
    QString pastaAno = ui->cBox_ano->currentText()+"/";
    QString nomeDoArquivo = "funcionario_"+QString::number(sufixFunc);
    QFile arquivo (local + pastaAno + nomeDoArquivo);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text))
    {
//    QMessageBox::warning(this,"Problema!","nao existe arquivo funcionario"+QString::number(sufixFunc));
    switch(sufixFunc){
            case 1:
                func1[0] = "NAOEXISTE";
                break;
            case 2:
                func2[0] = "NAOEXISTE";
                break;
            case 3:
                func3[0] = "NAOEXISTE";
                break;
            case 4:
                func4[0] = "NAOEXISTE";
                break;
            case 5:
                func5[0] = "NAOEXISTE";
                break;
            case 6:
                func6[0] = "NAOEXISTE";
                break;
            case 7:
                func7[0] = "NAOEXISTE";
                break;
            case 8:
                func8[0] = "NAOEXISTE";
                break;
            case 9:
                func9[0] = "NAOEXISTE";
                break;
            case 10:
                func10[0] = "NAOEXISTE";
                break;
        }
    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        switch(sufixFunc){
                case 1:
                    func1 = texto.split(";");
                    break;
                case 2:
                    func2 = texto.split(";");
                    break;
                case 3:
                    func3 = texto.split(";");
                    break;
                case 4:
                    func4 = texto.split(";");
                    break;
                case 5:
                    func5 = texto.split(";");
                    break;
                case 6:
                    func6 = texto.split(";");
                    break;
                case 7:
                    func7 = texto.split(";");
                    break;
                case 8:
                    func8 = texto.split(";");
                    break;
                case 9:
                    func9 = texto.split(";");
                    break;
                case 10:
                    func10 = texto.split(";");
                    break;
            }

    }
    arquivo.flush();
    arquivo.close();
}

void MainWindow::salvarArquivo()
{
    // variaveis de arquivo
    QString local = "H:/C++/Qt/Manutencao_ferramentas/";
    QString nomeDoArquivo = "teste";

    QFile arquivo (local + nomeDoArquivo);
    if (!arquivo.open(QFile::WriteOnly|QFile::Text))
            {
             QMessageBox::warning(this,"Problema!","Problemas na CRIAÇÃO do arquivo Teste");
            }else {
            QTextStream saida(&arquivo);
            for (int n = 0; n < 368; n++){
                QString texto = func1[n]+";";
                saida << texto;
                }
        arquivo.flush();
        arquivo.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    salvarArquivo();
}


void MainWindow::on_cBox_ano_currentIndexChanged(int index)
{
    for(int n = 1; n <= 10; n++){
    lerArquivo(n);
    }
    mes = 1;
    ui->lbl_mes->setText(alterarMes(mes));
    QString anoQstr = ui->cBox_ano->currentText();
    ano = anoQstr.toInt();
    bic = (ano % 4 == 0) ? 1 : 0;
}

void MainWindow::abreJanelaDia(int anoBotao, int posicaoBotao, int sufixFunc)
{
    Janela_Dia form3(this, anoBotao, posicaoBotao, sufixFunc);
    form3.exec();
    lerArquivo(sufixFunc);
    mes = QDate(anoBotao, 1, 1).addDays(posicaoBotao).month();
    alterarMes(mes);
}

//void MainWindow::clicked()
//{

//}