// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <mvvm/utils/fileutils.h>
#include <stdexcept>

#ifndef DISABLE_FILESYSTEM
#include <mvvm/core/filesystem.h>
#endif

using namespace ModelView;

bool Utils::exists(const std::string& fileName)
{
#ifdef DISABLE_FILESYSTEM
    QFileInfo info(QString::fromStdString(fileName));
    return info.exists();
#else
    return std::filesystem::exists(fileName);
#endif
}

std::string Utils::join(const std::string& part1, const std::string& part2)
{
#ifdef DISABLE_FILESYSTEM
    return part1 + std::string("/") + part2;
#else
    auto path = std::filesystem::path(part1) / std::filesystem::path(part2);
    return path.string();
#endif
}

bool Utils::create_directory(const std::string& path)
{
#ifdef DISABLE_FILESYSTEM
    QDir dir(QString::fromStdString(path));
    return dir.mkpath(".");
#else
    return std::filesystem::create_directory(path);
#endif
}

bool Utils::remove(const std::string& path)
{
#ifdef DISABLE_FILESYSTEM
    QFile file(QString::fromStdString(path));
    return file.remove();
#else
    return std::filesystem::remove(path);
#endif
}

void Utils::remove_all(const std::string& path)
{
#ifdef DISABLE_FILESYSTEM
    QDir dir(QString::fromStdString(path));
    if (dir.exists())
        dir.removeRecursively();
#else
    std::filesystem::remove_all(path);
#endif
}

#include <QDebug>
std::vector<std::string> Utils::FindFiles(const std::string& dirname, const std::string& ext)
{
#ifdef DISABLE_FILESYSTEM
    qDebug() << "1.1";
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
#else
    qDebug() << "1.2";
    std::vector<std::string> result;
    for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file() && entry.path().extension() == ext)
            result.push_back(entry.path().string());
    }
    return result;
#endif
}
