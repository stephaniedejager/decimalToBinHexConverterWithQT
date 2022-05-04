#include "converterform.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLCDNumber>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QErrorMessage>

//constructor
ConverterForm::ConverterForm(QWidget *parent) : QWidget(parent)
{
    //Input field for GUI
    m_intEdit = new QLineEdit(this);

    //Buttons for GUI
    m_convertButton = new QPushButton("Convert");
    m_clearAllButton = new QPushButton("Clear All");

    //QLCDNumber display for GUI - binary display
    binaryDisplay = new QLCDNumber(8);
    binaryDisplay->setSegmentStyle(QLCDNumber::Flat);
    binaryDisplay->setMode(QLCDNumber::Bin);

    //QLCDNumber display for GUI - hexadecimal display
    hexaDisplay = new QLCDNumber(8);
    hexaDisplay->setSegmentStyle(QLCDNumber::Flat);
    hexaDisplay->setMode(QLCDNumber::Hex);

    //Labels for GUI
    QLabel* enterIntLabel = new QLabel("Enter an integer");
    QLabel* binaryLabel = new QLabel("Binary");
    QLabel* hexaLabel = new QLabel("Hexadecimal");

    //Vertical layout 1
    QVBoxLayout* vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(enterIntLabel);
    vlayout1->addWidget(binaryLabel);
    vlayout1->addWidget(hexaLabel);
    vlayout1->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //Vertical layout 2
    QVBoxLayout* vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(m_intEdit);
    vlayout2->addWidget(binaryDisplay);
    vlayout2->addWidget(hexaDisplay);
    vlayout2->addWidget(m_clearAllButton);

    //Vertical layout 3
    QVBoxLayout* vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(m_convertButton);
    vlayout3->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlayout3->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlayout3->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //Horizontal layout
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addLayout(vlayout1);
    hlayout->addLayout(vlayout2);
    hlayout->addLayout(vlayout3);

    //Connecting slots
    connect(m_convertButton, SIGNAL(clicked()), this, SLOT(process()));
    connect(m_clearAllButton, SIGNAL(clicked()), this, SLOT(clear()));

    this->setLayout(hlayout);
    this->setWindowTitle("Decimal to Bin/Hex Converter");
}

//Process validation checks and displays numbers in decimal and hexadecimal
void ConverterForm::process()
{
    inputFromGui =m_intEdit->text();
    decimalNum = inputFromGui.toInt();

    //Validates decimal number entered and
    //gives error message if value entered isn't valid
    QValidator* v = new QIntValidator(INT_MIN, INT_MAX, this);

    int pos =0;

    if(v->validate(inputFromGui,pos) != QValidator::Acceptable)
    {
        QErrorMessage intError(0);
        intError.showMessage("Please enter a valid integer");
        intError.exec();
        clear();
    }

    //Checks if there is an overflow in the number of digits displayed for the binary representation,
    //and gives error message if there is
    if(binaryDisplay->checkOverflow(decimalNum))
    {
        QErrorMessage overflowError(0);
        overflowError.showMessage("Overflow in the number of digits displayed for the binary representation");
        overflowError.exec();
        clear();
    }

    //Displays the integer entered as a binary and hexadecimal number with QLCDNumber
    binaryDisplay->display(decimalNum);
    hexaDisplay->display(decimalNum);

}

//Clears the integer input field and binary and hexadecimal displays on the GUI
void ConverterForm::clear()
{
    m_intEdit->clear();
    binaryDisplay->display(0);
    hexaDisplay->display(0);
}

