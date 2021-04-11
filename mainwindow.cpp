#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <QThread>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("Dictionary"));
    ui->pushButton->setEnabled(true);
    max_count = preprocess_max_count();
    ui->progressBar->setMaximum(max_count);
    ui->progressBar->setValue(0);
    ui->listWidget->clear();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::find_words);
    ui->checkBox->setChecked(false);
    }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::find_words()
{
    ui->label->clear();
    ui->label->setText("search is started");
    ui->pushButton->setEnabled(false);
    ui->listWidget->clear();
    ui->progressBar->setValue(0);

    std::string text_to_find = ui->lineEdit->text().toStdString();

    thread = new QThread;
    auto *worker = new finder(path, text_to_find, ui->checkBox->isChecked(), max_count);
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(add_to_list(QString)), this, SLOT(add_to_list(QString)));
    connect(worker, SIGNAL(finished()), this, SLOT(finish_work()));
    connect(worker, SIGNAL(update_progress_bar()), this, SLOT(update_progress()));

    thread->start();
}

void MainWindow::add_to_list(QString add) {
    ui->listWidget->addItem(add);
}

void MainWindow::finish_work()
{
    ui->pushButton->setEnabled(true);
    ui->label->setText("finished");
    ui->progressBar->setValue(ui->progressBar->maximum());
}

void MainWindow::update_progress()
{
    ui->progressBar->setValue(ui->progressBar->value() + max_count/20);
}

int MainWindow::preprocess_max_count()
{
    QDir dir = QDir::currentPath();
    std::ifstream fin(dir.canonicalPath().toStdString() + "/../../../../" + path, std::ios::binary);
    std::string text;
    int count = 0;
    while (!fin.eof())
    {
         std::getline(fin, text);
         count++;
    }
    ui->label->setText("ready!");
    return count;
}
