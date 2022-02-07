#include "adicionarobservacao.h"
#include "ui_adicionarobservacao.h"
#include <QFile>
#include <QMessageBox>

QDate dataSelecionadaObs;
QStringList listaFuncionarioObs;

adicionarObservacao::adicionarObservacao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adicionarObservacao)
{
    ui->setupUi(this);
    QPixmap addObsIcon(":/icones/Icons/obsIcon.png");
    this->setWindowIcon(addObsIcon);
    ui->calendarioWidget->setSelectedDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_funcionario->setCurrentIndex(-1);
    ui->pushButton_criarObservao->setDisabled(1);
}

adicionarObservacao::~adicionarObservacao()
{
    delete ui;
}

void adicionarObservacao::on_calendarioWidget_clicked(const QDate &date)
{
    ui->dateEdit->setDate(date);
    dataSelecionadaObs = date;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    listaFuncionarioObs = lerArquivo(sufixFunc,dataSelecionadaObs.year());
}


void adicionarObservacao::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->calendarioWidget->setSelectedDate(date);
    dataSelecionadaObs = date;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    listaFuncionarioObs = lerArquivo(sufixFunc,dataSelecionadaObs.year());
}

// lê arquivos e escreve em listas
QStringList adicionarObservacao::lerArquivo(int sufixFunc, int anoBotao)
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
        ui->pushButton_criarObservao->setDisabled(1);
        arquivo.flush();
        arquivo.close();
        return lista;

    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        lista = texto.split(";");
        ui->label_Nome->setText(lista[dataSelecionadaObs.daysInYear()]);
        ui->label_Equipe->setText(lista[dataSelecionadaObs.daysInYear()+1]);
        ui->pushButton_criarObservao->setEnabled(1);
        return lista;
    }
    arquivo.flush();
    arquivo.close();

}

void adicionarObservacao::on_comboBox_funcionario_currentIndexChanged(int index)
{
    listaFuncionarioObs = lerArquivo(index+1,dataSelecionadaObs.year());
}

void adicionarObservacao::salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc)
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


void adicionarObservacao::on_pushButton_criarObservacao_clicked()
{
//    int posicaoDia = dataSelecionadaObs.dayOfYear()-1;
//    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
//    QString observacao = ui->plainTextEdit_obs->toPlainText();
//    if (listaFuncionarioObs[posicaoDia].at(0) != QString::number(0)){
//        QMessageBox::warning(this,"Problema!","O funcionário já está de folga no dia selecionado.");
//        return;
//    }
//    listaFuncionarioObs[posicaoDia] = "7Obs"+observacao;
//    salvarArquivo(sufixFunc, dataSelecionadaObs.year(), listaFuncionarioObs);
//    QMessageBox::information(this,"Folga adicionada","Folga adicionada no dia "+dataSelecionadaObs.toString("dd/MM/yy")+" com sucesso!");
//    adicionarObservacao::close();
}

void adicionarObservacao::on_pushButton_criarObservao_clicked()
{
    int posicaoDia = dataSelecionadaObs.dayOfYear()-1;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    QString observacao = ui->plainTextEdit_obs->toPlainText();
    if (listaFuncionarioObs[posicaoDia].at(0) != QString::number(0)){
        QMessageBox::warning(this,"Problema!","Não é possível adicionar observação em dia de folga.");
        return;
    }
    listaFuncionarioObs[posicaoDia] = "7Obs"+observacao;
    salvarArquivo(sufixFunc, dataSelecionadaObs.year(), listaFuncionarioObs);
    QMessageBox::information(this,"Observação adicionada","Observação adicionada no dia "+dataSelecionadaObs.toString("dd/MM/yy")+" com sucesso!");
    adicionarObservacao::close();
}

