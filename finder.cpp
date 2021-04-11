#include "finder.h"
#include "QDir"

finder::finder(std::string path, std::string text_to_find, bool mod_letters, int max_count)
{
    QDir dir = QDir::currentPath();
    this->path = dir.canonicalPath().toStdString() + "/../../../../" + path;
    this->text_to_find = text_to_find;
    this->is_mod_letters = mod_letters;
    this->max_count = max_count;
}

finder::~finder() = default;

void finder::process()
{
    std::string for_rex = text_to_find;
    replaceAll(for_rex, ".", "\\.");
    replaceAll(for_rex, "'", "\\'");

    std::regex rex;
    if(!is_mod_letters)
    {
        rex = (".*" + for_rex + ".*").c_str();
    }
    else
    {
        std::string tmp = "";
        for(int i = 0; i < for_rex.size(); i++)
        {
            tmp += for_rex[i];
            if (for_rex[i] == '\\') continue;
            tmp += ".*";
        }
        rex = (".*" + tmp).c_str();
    }

    std::ifstream fin(path, std::ios::binary);
    std::string text;
    std::cmatch m;
    char prev = '$';
    int count = max_count/20;
    while (!fin.eof())
    {
         std::getline(fin, text);
         if (std::regex_match(text.c_str(), m, rex)) {
             emit(add_to_list(QString::fromStdString(text)));
         }
         count--;
         if(count == 0) {
             emit(update_progress_bar());
             count = max_count/20;
         }
    }
    emit finished();
}

std::string finder::get_file_string() {
    std::ifstream ifs(path);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
}

void finder::replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    newString += source.substr(lastPos);

    source.swap(newString);
}
