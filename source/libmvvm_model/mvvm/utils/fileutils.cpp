// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/utils/fileutils.h>
#include <QDir>
#include <QFileInfo>
#include <stdexcept>

using namespace ModelView;

void Utils::create_dir(const std::string& dir_name)
{
    if (Utils::exists(dir_name))
        Utils::removeRecursively(dir_name);

    Utils::create_subdir(".", dir_name);
}

bool Utils::exists(const std::string& fileName)
{
    QFileInfo info(QString::fromStdString(fileName));
    return info.exists();
}

void Utils::create_subdir(const std::string& parentName, const std::string& subdirName)
{
    QString subdir = QString::fromStdString(subdirName);
    QDir projectDir(QString::fromStdString(parentName));
    if (!projectDir.exists(subdir)) {
        if (!projectDir.mkdir(subdir))
            throw std::runtime_error("GUIHelpers::createSubdir() -> Error. Can't create '"
                                     + subdirName + "' in parent directory '" + parentName + "'.");
    }
}

bool Utils::removeRecursively(const std::string& dirname)
{
    QDir dir(QString::fromStdString(dirname));

    if (!dir.exists())
        throw std::runtime_error("ProjectUtils::removeRecursively() -> Error. Non existing "
                                 "directory '"
                                 + dirname + "'.");

    return dir.removeRecursively();
}
