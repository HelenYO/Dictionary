#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void find_words();
    std::string get_file_string();
    void replaceAll(std::string& source, const std::string& from, const std::string& to);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
