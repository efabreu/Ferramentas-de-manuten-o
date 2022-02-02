#ifndef JANELA_DIA_H
#define JANELA_DIA_H

#include <QDialog>

using namespace std;

namespace Ui {
class Janela_Dia;
}

class Janela_Dia : public QDialog
{
    Q_OBJECT

public:
    explicit Janela_Dia(QWidget *parent = nullptr, int anoBotao=0, int posicaoBotao=0, int sufixFunc=0);
    ~Janela_Dia();

private slots:
    void on_qCalendarWidget_clicked(const QDate &date);

    void onClick_qPushButton();

    void salvarArquivo(QStringList listaSalvar, int ano);

    void on_qDateEdit_userDateChanged(const QDate &date);

private:
    Ui::Janela_Dia *ui;
    QStringList lerArquivo(int sufixFunc, int anoBotao);
};

#endif // JANELA_DIA_H
