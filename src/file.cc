#include <boost/filesystem.hpp>
#include <string>
#include "buffered_io.h"
#include "file.h"
#include "file_io.h"

File::File(const std::string path, const FileIOMode mode)
    : io(*new FileIO(path, mode)), name(path)
{
}

File::File() : io(*new BufferedIO)
{
}

File::~File()
{
    delete &io;
}

void File::change_extension(const std::string new_extension)
{
    auto path = boost::filesystem::path(name);
    if (path.filename() == "." || path.filename() == ".." || path.stem() == "")
        return;
    path.replace_extension(new_extension);
    name = path.string();
}

void File::guess_extension()
{
    std::vector<std::pair<std::string, std::string>> definitions
    {
        { "b", std::string("abmp", 4) }, //QLiE
        { "imoavi", std::string("IMOAVI", 6) }, //QLiE
        { "png", std::string("\x89PNG", 4) },
        { "bmp", std::string("BM", 2) },
        { "wav", std::string("RIFF", 4) },
        { "ogg", std::string("OggS", 4) },
        { "jpeg", std::string("\xff\xd8\xff", 3) },
    };

    size_t old_pos = io.tell();
    for (auto &def : definitions)
    {
        const std::string ext = def.first;
        const std::string magic = def.second;
        io.seek(0);
        if (io.size() < magic.size()) continue;
        if (io.read(magic.size()) != magic) continue;
        change_extension(ext);
        io.seek(old_pos);
        return;
    }
    io.seek(old_pos);
}