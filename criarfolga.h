#ifndef CRIARFOLGA_H
#define CRIARFOLGA_H

#include <QDialog>

namespace Ui {
class criarFolga;
}

class criarFolga : public QDialog
{
    Q_OBJECT

public:
    explicit criarFolga(QWidget *parent = nullptr);
    ~criarFolga();

private slots:
    void on_calendarioWidget_clicked(const QDate &date);

    void on_dateEdit_userDateChanged(const QDate &date);

    QStringList lerArquivo(int sufixFunc, int anoBotao);

    void on_comboBox_funcionario_currentIndexChanged(int index);

    void salvarArquivo(int sufixFunc, int anoBotao, QStringList listaFunc);

    void on_pushButton_criarFolga_clicked();

private:
    Ui::criarFolga *ui;
};

#endif // CRIARFOLGA_H
