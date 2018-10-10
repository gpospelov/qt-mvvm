// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "test_utils.h"
#include "testconfig.h"
#include "fileutils.h"
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <string>

namespace {
void SaveDocument(const QJsonDocument& document, const QString& fileName);
}

void TestUtils::CreateTestDirectory(const QString& test_sub_dir)
{
    auto path = TestDirectoryPath(test_sub_dir);
    Utils::create_dir(path.toStdString());
}

QString TestUtils::TestDirectoryPath(const QString& test_sub_dir)
{
    return QString::fromStdString(TestConfig::TestOutputDir()) + "/" + test_sub_dir;
}

QString TestUtils::TestFileName(const QString& test_sub_dir, const QString& file_name)
{
    return TestDirectoryPath(test_sub_dir) + "/" + file_name;
}

void TestUtils::SaveJson(const QJsonObject& object, const QString& fileName)
{
    QJsonDocument document(object);
    SaveDocument(document, fileName);
}

void TestUtils::SaveJson(const QJsonArray& object, const QString& fileName)
{
    QJsonDocument document(object);
    SaveDocument(document, fileName);
}

namespace {

void SaveDocument(const QJsonDocument& document, const QString& fileName)
{
    QFile saveFile(fileName);

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestUtils::SaveDocument() -> Can't save file");

    saveFile.write(document.toJson());
}

}
