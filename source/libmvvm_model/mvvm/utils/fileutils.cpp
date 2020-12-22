// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/utils/fileutils.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <stdexcept>

#ifdef ENABLE_FILESYSTEM
#include "mvvm/core/filesystem.h"
#endif

using namespace ModelView;

bool Utils::exists(const std::string& fileName)
{
#ifdef ENABLE_FILESYSTEM
    return std::filesystem::exists(fileName);
#else
    QFileInfo info(QString::fromStdString(fileName));
    return info.exists();
#endif
}

std::string Utils::join(const std::string& part1, const std::string& part2)
{
#ifdef ENABLE_FILESYSTEM
    auto path = std::filesystem::path(part1) / std::filesystem::path(part2);
    return path.string();
#else
    return part1 + std::string("/") + part2;
#endif
}

bool Utils::create_directory(const std::string& path)
{
#ifdef ENABLE_FILESYSTEM
    return std::filesystem::create_directory(path);
#else
    QDir dir(QString::fromStdString(path));
    return dir.mkpath(".");
#endif
}

bool Utils::remove(const std::string& path)
{
#ifdef ENABLE_FILESYSTEM
    return std::filesystem::remove(path);
#else
    QFile file(QString::fromStdString(path));
    return file.remove();
#endif
}

void Utils::remove_all(const std::string& path)
{
#ifdef ENABLE_FILESYSTEM
    std::filesystem::remove_all(path);
#else
    QDir dir(QString::fromStdString(path));
    if (dir.exists())
        dir.removeRecursively();
#endif
}

std::string Utils::base_name(const std::string& path)
{
#ifdef ENABLE_FILESYSTEM
    return std::filesystem::path(path).stem().string();
#else
    return QFileInfo(QString::fromStdString(path)).completeBaseName().toStdString();
#endif
}

std::vector<std::string> Utils::FindFiles(const std::string& dirname, const std::string& ext)
{
#ifdef ENABLE_FILESYSTEM
    std::vector<std::string> result;
    for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file() && entry.path().extension() == ext)
            result.push_back(entry.path().string());
    }
    return result;
#else
    std::vector<std::string> result;
    QDir dir(QString::fromStdString(dirname));
    if (dir.exists()) {
        QStringList filters = {QString::fromStdString("*" + ext)};
        for (auto entry : dir.entryList(filters)) {
            auto name = dir.filePath(entry);
            result.push_back(name.toStdString());
        }
    }
    return result;
#endif
}

std::string Utils::parent_path(const std::string& path)
{
#ifdef ENABLE_FILESYSTEM
    return std::filesystem::path(path).parent_path().string();
#else
    QFileInfo info(QString::fromStdString(path));
    return info.dir().path().toStdString();
#endif
}

bool Utils::is_empty(const std::string& path)
{
#ifdef ENABLE_FILESYSTEM
    return std::filesystem::is_empty(path);
#else
    QFileInfo info(QString::fromStdString(path));
    if (info.isDir()) {
        QDir dir(QString::fromStdString(path));
        return dir.isEmpty();
    }
    else {
        return info.size() == 0;
    }
    return false;
#endif
}
