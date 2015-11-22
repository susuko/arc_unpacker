#pragma once

#include <string>
#include "io/file_stream.h"

namespace au {
namespace io {

    class File final
    {
    public:
        File(const io::path &name, const io::FileMode mode);
        File(const io::path &name, const bstr &data);
        File();
        ~File();
        bool has_extension();
        bool has_extension(const std::string &extension);
        void change_extension(const std::string &new_extension);
        void guess_extension();

        io::Stream &stream;
        io::path name;
    };

} }