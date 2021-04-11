#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <regex>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("Dictionary"));
    ui->pushButton->setEnabled(true);
    ui->progressBar->setValue(0);
//    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
//    ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->listWidget->clear();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::find_words);

    }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::find_words()
{
    ui->label->clear();
    ui->label->setText("search is started");


    QString text_to_find = ui->lineEdit->text();


    std::string file_content = get_file_string();
    std::string for_rex = text_to_find.toStdString();
    replaceAll(for_rex, ".", "\\.");
    replaceAll(for_rex, "'", "\\'");
    std::regex rex((".*" + for_rex + ".*").c_str());

    std::sregex_iterator beg{ file_content.cbegin(), file_content.cend(), rex };
    std::sregex_iterator end{};
    std::string res;
    for (auto i = beg; i != end; ++i)
    {
        ui->listWidget->addItem(QString::fromStdString(i->str()));
    }
}


std::string MainWindow::get_file_string() {
    std::ifstream ifs("/Users/elena/Desktop/JB/dict/words2.txt");
    return std::string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
}


void MainWindow::replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}
