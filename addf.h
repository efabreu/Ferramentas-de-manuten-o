#ifndef ADDF_H
#define ADDF_H

#include <QDialog>


namespace Ui {
class addF;
}

class addF : public QDialog
{
    Q_OBJECT

public:
    explicit addF(QWidget *parent = nullptr);
    ~addF();


private slots:
    void on_btn_criar_clicked();


    void on_btn_remover_clicked();

    void on_cbx_numFunc_currentIndexChanged(int index);

private:
    Ui::addF *ui;
    bool arquivoExiste(QString path);
    void criaArquivo(QString path, QString nome, QString equipe);
    void removeArquivo(QString path);
    void gravarMatriz(int escala, int d_ano);
    int lerArquivo(QString path);
};

#endif // ADDF_H
