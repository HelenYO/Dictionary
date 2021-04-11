#include "finder.h"

finder::finder(std::string path, std::string text_to_find)
{
    this->path = path;
    this->text_to_find = text_to_find;
}

finder::~finder() = default;

void finder::process()
{
    std::string file_content = get_file_string();

    std::string for_rex = text_to_find;
    replaceAll(for_rex, ".", "\\.");
    replaceAll(for_rex, "'", "\\'");

    std::regex rex((".*" + for_rex + ".*").c_str());

    std::sregex_iterator beg{ file_content.cbegin(), file_content.cend(), rex };
    std::sregex_iterator end{};
    std::string res;
    for (auto i = beg; i != end; ++i)
    {
        emit(add_to_list(QString::fromStdString(i->str())));
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
