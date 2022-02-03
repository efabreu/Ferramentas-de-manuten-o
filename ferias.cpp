#include "ferias.h"
#include "ui_ferias.h"
#include <QFile>
#include <QMessageBox>

QDate dataInicio;
QDate dataFinal;
QStringList funcAnoInicial;
QStringList funcAnoSeguinte;

ferias::ferias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ferias)
{
    ui->setupUi(this);
    QPixmap addFeriasIcon(":/icones/Icons/addFeriasIcon.png");
    this->setWindowIcon(addFeriasIcon);
    ui->dateEdit_inicio->setDate(QDate::currentDate());
    ui->spinBox_duracao->setRange(5,30);
    ui->comboBox_funcionario->setCurrentIndex(-1);
    ui->pushButton_criarferias->setDisabled(1);

}

ferias::~ferias()
{
    delete ui;
}

void ferias::on_dateEdit_inicio_dateChanged(const QDate &date)
{
    dataInicio = ui->dateEdit_inicio->date();
    dataFinal = dataInicio.addDays(ui->spinBox_duracao->value()-1);
    ui->label_fim_data->setText(dataFinal.toString("dd/MM/yyyy"));
    lerArquivo(ui->comboBox_funcionario->currentIndex()+1,dataInicio.year());
}


void ferias::on_spinBox_duracao_valueChanged(int arg1)
{
    on_dateEdit_inicio_dateChanged(ui->dateEdit_inicio->date());
}

// lê arquivos e escreve em listas
void ferias::lerArquivo(int sufixFunc, int anoBotao)
{
    // variaveis de arquivo
    QString local = "M:/Técnica/01- MANUTENÇÃO_INSTALAÇÕES/2 - MINAS ARENA/3 - MANUTENÇÃO PREVENTIVAS/Escala 3.1/DADOS ESCALAS/";
    QString pastaAno = QString::number(anoBotao) + "/";
    QString pastaAnoSeguinte = QString::number(anoBotao+1) + "/";
    QString nomeDoArquivo = "funcionario_"+QString::number(sufixFunc);
    QFile arquivo (local + pastaAno + nomeDoArquivo);

    // le arquivo do ano um
    if (!arquivo.open(QFile::ReadOnly|QFile::Text))
    {
//    QMessageBox::warning(this,"Problema!","nao existe arquivo funcionario "+QString::number(sufixFunc));
    ui->label_nome_2->setText("Não existe");

    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        funcAnoInicial = texto.split(";");
        int qDiasAno = QDate::currentDate().daysInYear();
        ui->label_nome_2->setText(funcAnoInicial[qDiasAno]);

    }
    arquivo.flush();
    arquivo.close();

    // le arquivo do ano seguinte
    QFile arquivo2 (local + pastaAnoSeguinte + nomeDoArquivo);
    if (!arquivo2.open(QFile::ReadOnly|QFile::Text))
    {
//    QMessageBox::warning(this,"Problema!","nao existe arquivo funcionario "+QString::number(sufixFunc));
    ui->label_nome_2->setText("Não existe");

    }else{
        QTextStream entrada(&arquivo2);
        QString texto = entrada.readAll();
        funcAnoSeguinte = texto.split(";");
    }
    arquivo2.flush();
    arquivo2.close();
}

void ferias::on_comboBox_funcionario_currentIndexChanged(int index)
{
    on_dateEdit_inicio_dateChanged(ui->dateEdit_inicio->date());
    if (ui->label_nome_2->text() != "Não existe") {
        ui->pushButton_criarferias->setEnabled(1);
    } else {
        ui->pushButton_criarferias->setDisabled(1);
    }
}

void ferias::escreveFerias(int posicaoDiaUm, int qDiasAno)
{
    int qtdFerias = ui->spinBox_duracao->value();
    int qtdFeriasAux = qDiasAno - posicaoDiaUm;

    if (qtdFeriasAux > qtdFerias){
        qtdFeriasAux = qtdFerias-1;
    }
    for (int i = 0; i <= qtdFeriasAux; i += 1) {
            funcAnoInicial [posicaoDiaUm+i-1] = "5Férias";;


    }if (qtdFeriasAux < qtdFerias){
        qtdFeriasAux = qtdFerias - qtdFeriasAux -1;
            for (int i = 0; i < qtdFeriasAux; i += 1) {
            funcAnoSeguinte [i] = "5Férias";
        }

    }
}

void ferias::salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc)
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

void ferias::on_pushButton_criarferias_clicked()
{
    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this,"Prosseguir?","Deseja incluir férias para "+ui->label_nome_2->text()+" do dia "
                          +dataInicio.toString("dd/MM/yy")+" até "+dataFinal.toString("dd/MM/yy")+"?",QMessageBox::Yes|QMessageBox::No);
    if (resposta == QMessageBox::Yes) {
        escreveFerias(dataInicio.dayOfYear(),dataInicio.daysInYear());
        if (dataInicio.daysInYear() - dataInicio.dayOfYear() >= ui->spinBox_duracao->value()){
            salvarArquivo(ui->comboBox_funcionario->currentIndex()+1,dataInicio.year(),funcAnoInicial);
            }else{
                 salvarArquivo(ui->comboBox_funcionario->currentIndex()+1,dataInicio.year(),funcAnoInicial);
                 salvarArquivo(ui->comboBox_funcionario->currentIndex()+1,dataFinal.year(),funcAnoSeguinte);
                }
        ferias::close();
    }else{

    }
}


void ferias::on_label_nome_2_windowIconTextChanged(const QString &iconText)
{
//    if (ui->label_nome_2->text() != "Não existe") {
//        ui->pushButton_criarferias->setEnabled(1);
//    }
}

