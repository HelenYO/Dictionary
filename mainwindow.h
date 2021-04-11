#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "finder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_to_list(QString add);
    void finish_work();
    void update_progress();

private:
    void find_words();
    int preprocess_max_count();

private:
    Ui::MainWindow *ui;
    QThread* thread = nullptr;
    std::string path = "dict/words1.txt";
    int max_count;
};
#endif // MAINWINDOW_H
