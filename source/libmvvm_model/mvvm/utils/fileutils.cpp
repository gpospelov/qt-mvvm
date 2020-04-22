// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDir>
#include <QFileInfo>
#include <mvvm/utils/fileutils.h>
#include <mvvm/core/filesystem.h>
#include <stdexcept>

using namespace ModelView;

bool Utils::exists(const std::string& fileName)
{
    QFileInfo info(QString::fromStdString(fileName));
    return info.exists();
}

std::string Utils::join(const std::string& part1, const std::string& part2)
{
    auto path = std::filesystem::path(part1) / std::filesystem::path(part2);
    return path.string();
}

bool Utils::create_directory(const std::string& path)
{
    return std::filesystem::create_directory(path);
}

bool Utils::remove(const std::string& path)
{
    return std::filesystem::remove(path);
}

void Utils::remove_all(const std::string& path)
{
    std::filesystem::remove_all(path);
}

std::vector<std::string> Utils::FindFiles(const std::string& dirname, const std::string& ext)
{
    std::vector<std::string> result;
    for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file() && entry.path().extension() == ext)
            result.push_back(entry.path().string());
    }
    return result;
}
