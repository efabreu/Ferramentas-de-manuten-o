#ifndef JANELALEGENDA_H
#define JANELALEGENDA_H

#include <QDialog>

namespace Ui {
class janelaLegenda;
}

class janelaLegenda : public QDialog
{
    Q_OBJECT

public:
    explicit janelaLegenda(QWidget *parent = nullptr);
    ~janelaLegenda();

private:
    Ui::janelaLegenda *ui;
};

#endif // JANELALEGENDA_H
