#include "criarfolga.h"
#include "ui_criarfolga.h"
#include <QFile>
#include <QMessageBox>

QDate dataSelecionada;
QStringList listaFuncionario;

criarFolga::criarFolga(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::criarFolga)
{
    ui->setupUi(this);
    QPixmap addFolgaIcon(":/icones/Icons/addFolgaIcon.png");
    this->setWindowIcon(addFolgaIcon);
    ui->calendarioWidget->setSelectedDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_funcionario->setCurrentIndex(-1);
    ui->pushButton_criarFolga->setDisabled(1);

}

criarFolga::~criarFolga()
{
    delete ui;
}

void criarFolga::on_calendarioWidget_clicked(const QDate &date)
{
    ui->dateEdit->setDate(date);
    dataSelecionada = date;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    listaFuncionario = lerArquivo(sufixFunc,dataSelecionada.year());
}


void criarFolga::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->calendarioWidget->setSelectedDate(date);
    dataSelecionada = date;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    listaFuncionario = lerArquivo(sufixFunc,dataSelecionada.year());
}

// lê arquivos e escreve em listas
QStringList criarFolga::lerArquivo(int sufixFunc, int anoBotao)
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
        ui->pushButton_criarFolga->setDisabled(1);
        arquivo.flush();
        arquivo.close();
        return lista;

    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        lista = texto.split(";");
        ui->label_Nome->setText(lista[dataSelecionada.daysInYear()]);
        ui->label_Equipe->setText(lista[dataSelecionada.daysInYear()+1]);
        ui->pushButton_criarFolga->setEnabled(1);
        return lista;
    }
    arquivo.flush();
    arquivo.close();

}

void criarFolga::on_comboBox_funcionario_currentIndexChanged(int index)
{
    listaFuncionario = lerArquivo(index+1,dataSelecionada.year());
}

void criarFolga::salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc)
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


void criarFolga::on_pushButton_criarFolga_clicked()
{
    int posicaoDia = dataSelecionada.dayOfYear()-1;
    int sufixFunc = ui->comboBox_funcionario->currentIndex()+1;
    if (listaFuncionario[posicaoDia].at(0) != QString::number(0)){
        QMessageBox::warning(this,"Problema!","O funcionário já está de folga no dia selecionado.");
        return;
    }
    listaFuncionario[posicaoDia] = "6F";
    salvarArquivo(sufixFunc, dataSelecionada.year(), listaFuncionario);
    QMessageBox::information(this,"Folga adicionada","Folga adicionada no dia "+dataSelecionada.toString("dd/MM/yy")+" com sucesso!");
    criarFolga::close();
}

