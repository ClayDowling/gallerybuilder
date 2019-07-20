#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

namespace fs = std::experimental::filesystem;

std::string toPosixSlashes(fs::path src, bool instatic) {

    std::string posixurl;
    for(auto& el : src) {
        if (instatic || posixurl != "") posixurl += '/';
        posixurl += el.string();
    }

    return posixurl;

}

int main(int argc, char **argv)
{

    for(auto& p: fs::directory_iterator(argv[1])) {
        auto tp = p.path();
 
        fs::path url;
        bool instatic = false;
        for(auto& el: tp) {
            if (instatic) {
                url /= el;
            }
            if (el == "static") {
                instatic = true;
            }
        }
        if (instatic == false) {
            url = tp;
        }
 
        fs::path filename = tp.filename();
        filename.replace_extension("md");
        if (!fs::exists(filename)) {

            fs::file_time_type lastmod = last_write_time(tp);
            time_t cftime = decltype(lastmod)::clock::to_time_t(lastmod);
            struct tm* lt = localtime(&cftime);

            std::ofstream md(filename.string());
            md << "---" << std::endl
               << "title: " << tp.stem() << std::endl
               << "date:  \"" << lt->tm_year + 1900 << "-" 
                          << std::setfill('0') << std::setw(2) << lt->tm_mon 
                          << "-" << std::setfill('0') << std::setw(2) << lt->tm_mday << "\"" << std::endl
               << "image:   \"" << toPosixSlashes(url, instatic) << "\"" << std::endl
               << "---" << std::endl;

        }
    }

    return EXIT_SUCCESS;

}


