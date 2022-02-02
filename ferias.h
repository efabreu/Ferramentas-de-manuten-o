#ifndef FERIAS_H
#define FERIAS_H

#include <QDialog>

namespace Ui {
class ferias;
}

class ferias : public QDialog
{
    Q_OBJECT

public:
    explicit ferias(QWidget *parent = nullptr);
    ~ferias();

private slots:
    void on_dateEdit_inicio_dateChanged(const QDate &date);

    void on_spinBox_duracao_valueChanged(int arg1);

    void lerArquivo(int sufixFunc, int anoBotao);

    void on_comboBox_funcionario_currentIndexChanged(int index);

    void escreveFerias(int posicaoDiaUm, int qDiasAno);

    void salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc);

    void on_pushButton_criarferias_clicked();

    void on_label_nome_2_windowIconTextChanged(const QString &iconText);

private:
    Ui::ferias *ui;

};

#endif // FERIAS_H
