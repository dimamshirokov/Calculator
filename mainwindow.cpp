#include "mainwindow.h"
#include "./ui_mainwindow.h"

double currentNumber;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Calculator");
    this->setWindowIcon(QIcon(":/res/images/calculator_icon-icons.com_72046.ico"));
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(onPushButtonDotClicked()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_oppositeSign, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_allClean, SIGNAL(clicked()), this, SLOT(onPushButtonAllClean()));
    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(onPushButtonEqualClicked()));
    connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_multiplication, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_addition, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_subtraction, SIGNAL(clicked()), this, SLOT(mathOperations()));
    ui->pushButton_division->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
    ui->pushButton_addition->setCheckable(true);
    ui->pushButton_subtraction->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitsNumbers()
{
    QPushButton *button = (QPushButton*)sender();
    QString newText;
    if(ui->result->text().contains(".") && button->text() == "0"){
        newText = (ui->result->text() + button->text());
    }else{
        double allNumbers = (ui->result->text() + button->text()).toDouble();\
        newText = QString::number(allNumbers, 'g', 15);
    }
    ui->result->setText(newText);
}

void MainWindow::onPushButtonDotClicked()
{
    if(!(ui->result->text().contains('.'))){
        ui->result->setText(ui->result->text() + ".");
    }
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton*)sender();
    double allNumbers;
    QString newText;
    if(button->text() == "+/-"){
        allNumbers = (ui->result->text()).toDouble();
        allNumbers *= (-1);
        newText = QString::number(allNumbers, 'g', 15);
        ui->result->setText(newText);
    }else if(button->text() == "%"){
        allNumbers = (ui->result->text()).toDouble();
        allNumbers /= 100;
        newText = QString::number(allNumbers, 'g', 15);
        ui->result->setText(newText);
    }
}

void MainWindow::onPushButtonAllClean()
{
    ui->pushButton_addition->setChecked(false);
    ui->pushButton_subtraction->setChecked(false);
    ui->pushButton_division->setChecked(false);
    ui->pushButton_multiplication->setChecked(false);
    ui->result->setText("0");
}

void MainWindow::onPushButtonEqualClicked()
{
    double labelNumber, secondNumber;
    QString newText;
    secondNumber = ui->result->text().toDouble();
    if(ui->pushButton_addition->isChecked()){
        labelNumber = currentNumber + secondNumber;
        newText = QString::number(labelNumber, 'g', 15);
        ui->result->setText(newText);
        ui->pushButton_addition->setChecked(false);
    }else if(ui->pushButton_subtraction->isChecked()){
        labelNumber = currentNumber - secondNumber;
        newText = QString::number(labelNumber, 'g', 15);
        ui->result->setText(newText);
        ui->pushButton_subtraction->setChecked(false);
    }else if(ui->pushButton_division->isChecked()){
        if(secondNumber == 0){
            ui->result->setText("0");
        }else{
            labelNumber = currentNumber / secondNumber;
            newText = QString::number(labelNumber, 'g', 15);
            ui->result->setText(newText);
        }
        ui->pushButton_division->setChecked(false);
    }else if(ui->pushButton_multiplication->isChecked()){
        labelNumber = currentNumber * secondNumber;
        newText = QString::number(labelNumber, 'g', 15);
        ui->result->setText(newText);
        ui->pushButton_multiplication->setChecked(false);
    }
}

void MainWindow::mathOperations()
{
    QPushButton *button = (QPushButton*)sender();
    button->setChecked(true);
    currentNumber = ui->result->text().toDouble();
    ui->result->setText("");
}
