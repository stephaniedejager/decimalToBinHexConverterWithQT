#ifndef CONVERTERFORM_H
#define CONVERTERFORM_H

#include <QtWidgets>
#include <QWidget>

class ConverterForm: public QWidget
{
    Q_OBJECT

public:
    //constructor
    ConverterForm(QWidget* parent =0);

private slots:
    //Process validation checks and displays numbers in decimal and hexadecimal
    void process();

    //Clears the integer input field and binary and hexadecimal displays on the GUI
    void clear();

private:
    //private data members
    QLineEdit* m_intEdit;
    QPushButton* m_convertButton;
    QPushButton* m_clearAllButton;
    QLCDNumber* binaryDisplay;
    QLCDNumber* hexaDisplay;

    //used for validation of input
    QString inputFromGui;

    //casted from QString inputFromGui and used as input for display
    int decimalNum;

};

#endif // CONVERTERFORM_H
