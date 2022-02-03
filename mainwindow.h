#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addf.h"
#include "janela_dia.h"
#include "ferias.h"
#include "criarfolga.h"



using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onClick_qPushButton(int diaBotao, int sufixFunc);

    void on_pushButton_menos_clicked();

    void on_pushButton_mais_clicked();

    void on_actionAdd_Funcionario_triggered();

    void on_actionFerias_triggered();

    void on_actionAdicionar_Folga_triggered();

    void on_actionSair_triggered();

    void on_pushButton_clicked();

    void on_cBox_ano_currentIndexChanged(int index);

    void funcaoRefresh();


    void on_actionImprimir_triggered();

signals:

    void clicked(int diaBotao);

private:
    QString alterarMes(int mes);
    void criarDia(int qDiasMes);
    void modificaBotoes(int cDiasMes, int qDiasMes, int sufixFunc, QStringList funcionario, QLayout *layout1);
    void mostrarFolgas01(int cDiasMes, int qDiaMes, int sufixFunc);
    void mostrarDiasSem(int qDiaMes);
    void lerArquivo(int sufixFunc);
    void salvarArquivo();
    void abreJanelaDia(int anoBotao, int posicaoBotao, int sufixFunc);
    void limparLayoutEscala(QLayout *layout1);
    void limparLayoutCalendario();

    Ui::MainWindow *ui;
    addF *form02;
    ferias *form03;
    criarFolga *form04;

};
#endif // MAINWINDOW_H
