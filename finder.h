#ifndef FINDER_H
#define FINDER_H

#include <QCommonStyle>

#include <fstream>
#include <regex>
#include <iostream>


class finder : public QObject
{
    Q_OBJECT

public:
    finder(std::string path, std::string text_to_find, bool mod_letters);
    ~finder();

private:
    void replaceAll(std::string& source, const std::string& from, const std::string& to);
    std::string get_file_string();

public slots:
    void process();

signals:
    void add_to_list(QString add);

    void finished();

private:
    std::string path;
    std::string text_to_find;
    bool is_mod_letters;
};

#endif // FINDER_H
