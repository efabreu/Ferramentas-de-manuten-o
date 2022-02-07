#include "adicionartrabalho.h"
#include "ui_adicionartrabalho.h"
#include <QFile>
#include <QMessageBox>

QDate dataSelecionadaTrabalho;
QStringList listaFuncionarioTrabalho;

adicionarTrabalho::adicionarTrabalho(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adicionarTrabalho)
{
    ui->setupUi(this);    QPixmap addObsIcon(":/icones/Icons/obsIcon.png");
    this->setWindowIcon(addObsIcon);
    ui->calendarioWidget->setSelectedDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_funcionario->setCurrentIndex(-1);
    ui->pushButton_criarTrabalho->setDisabled(1);
}

adicionarTrabalho::~adicionarTrabalho()
{
    delete ui;
}

void adicionarTrabalho::on_calendarioWidget_clicked(const QDate &date)
{
    ui->dateEdit->setDate(date);
    dataSelecionadaTrabalho = date;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    listaFuncionarioTrabalho = lerArquivo(sufixFunc,dataSelecionadaTrabalho.year());
}


void adicionarTrabalho::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->calendarioWidget->setSelectedDate(date);
    dataSelecionadaTrabalho = date;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    listaFuncionarioTrabalho = lerArquivo(sufixFunc,dataSelecionadaTrabalho.year());
}

// lê arquivos e escreve em listas
QStringList adicionarTrabalho::lerArquivo(int sufixFunc, int anoBotao)
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
        ui->label_Nome->setText("Não existe");
        ui->label_Equipe->setText("Não existe");
        ui->pushButton_criarTrabalho->setDisabled(1);
        arquivo.flush();
        arquivo.close();
        return lista;

    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        lista = texto.split(";");
        ui->label_Nome->setText(lista[dataSelecionadaTrabalho.daysInYear()]);
        ui->label_Equipe->setText(lista[dataSelecionadaTrabalho.daysInYear()+1]);
        ui->pushButton_criarTrabalho->setEnabled(1);
        return lista;
    }
    arquivo.flush();
    arquivo.close();

}

void adicionarTrabalho::on_comboBox_funcionario_currentIndexChanged(int index)
{
    listaFuncionarioTrabalho = lerArquivo(index+1,dataSelecionadaTrabalho.year());
}

void adicionarTrabalho::salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc)
{
    // variaveis de arquivo
    QString local = "M:/Técnica/01- MANUTENÇÃO_INSTALAÇÕES/2 - MINAS ARENA/3 - MANUTENÇÃO PREVENTIVAS/Escala 3.1/DADOS ESCALAS/";
    QString pastaAno = QString::number(anoBotao) + "/";
    QString nomeDoArquivo = "funcionario_"+QString::number(sufixFunc);
    QFile arquivo (local + pastaAno + nomeDoArquivo);

    if (!arquivo.open(QFile::WriteOnly|QFile::Text))
            {
             QMessageBox::warning(this,"Problema!","Problemas na CRIAÇÃO do arquivo Teste");
            }else {
            QTextStream saida(&arquivo);
            for (int n = 0; n < 368; n++){
                QString texto = listaFunc[n]+";";
                saida << texto;
                }
        arquivo.flush();
        arquivo.close();
    }

}

void adicionarTrabalho::on_pushButton_criarTrabalho_clicked()
{
    int posicaoDia = dataSelecionadaTrabalho.dayOfYear()-1;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    QString observacao = ui->plainTextEdit_obs->toPlainText();
    if (listaFuncionarioTrabalho[posicaoDia].at(0) == QString::number(0) || listaFuncionarioTrabalho[posicaoDia].at(0) == QString::number(3)){
        QMessageBox::warning(this,"Problema!","Favor selecionar um dia de folga.");
        return;
    }
    listaFuncionarioTrabalho[posicaoDia] = "0T"+observacao;
    salvarArquivo(sufixFunc, dataSelecionadaTrabalho.year(), listaFuncionarioTrabalho);
    QMessageBox::information(this,"Observação adicionada","Dia de trabalho adicionado no dia "+dataSelecionadaTrabalho.toString("dd/MM/yy")+" com sucesso!");
    adicionarTrabalho::close();
}

