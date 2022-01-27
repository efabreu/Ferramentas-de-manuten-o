#ifndef BOTAOISABELLA_H
#define BOTAOISABELLA_H


#include <QPushButton>
#include <QWidget>


#endif // BOTAOISABELLA_H

class BotaoIsabella : public QPushButton
    {
        Q_OBJECT
    public:
        BotaoIsabella(int digit, int digit2, QWidget *parent);

    signals:
        void clicked(int digit, int digit2);

    private slots:
        void reemitClicked();

    private:
        int myDigit;
        int myDigit2;
    };


