#ifndef ADICIONARTRABALHO_H
#define ADICIONARTRABALHO_H

#include <QDialog>

namespace Ui {
class adicionarTrabalho;
}

class adicionarTrabalho : public QDialog
{
    Q_OBJECT

public:
    explicit adicionarTrabalho(QWidget *parent = nullptr);
    ~adicionarTrabalho();

private slots:
    void on_calendarioWidget_clicked(const QDate &date);

    void on_dateEdit_userDateChanged(const QDate &date);

    QStringList lerArquivo(int sufixFunc, int anoBotao);

    void on_comboBox_funcionario_currentIndexChanged(int index);

    void salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc);

    void on_pushButton_criarTrabalho_clicked();

private:
    Ui::adicionarTrabalho *ui;
};

#endif // ADICIONARTRABALHO_H
