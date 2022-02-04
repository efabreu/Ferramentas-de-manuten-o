#ifndef ADICIONAROBSERVACAO_H
#define ADICIONAROBSERVACAO_H

#include <QDialog>

namespace Ui {
class adicionarObservacao;
}

class adicionarObservacao : public QDialog
{
    Q_OBJECT

public:
    explicit adicionarObservacao(QWidget *parent = nullptr);
    ~adicionarObservacao();

private slots:
    void on_calendarioWidget_clicked(const QDate &date);

    void on_dateEdit_userDateChanged(const QDate &date);

    QStringList lerArquivo(int sufixFunc, int anoBotao);

    void on_comboBox_funcionario_currentIndexChanged(int index);

    void salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc);

    void on_pushButton_criarObservacao_clicked();

    void on_pushButton_criarObservao_clicked();

private:
    Ui::adicionarObservacao *ui;
};

#endif // ADICIONAROBSERVACAO_H
