// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "test_utils.h"
#include "testconfig.h"
#include <mvvm/utils/fileutils.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/serialization/jsonconverterinterfaces.h>
#include <mvvm/serialization/jsonutils.h>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include <filesystem>

using namespace ModelView;

namespace {
void SaveDocument(const QJsonDocument& document, const QString& fileName);
}

void TestUtils::CreateTestDirectory(const std::string &test_sub_dir)
{
    auto path = TestDirectoryPath(test_sub_dir);
    if(!Utils::exists(path))
        Utils::create_dir(path);
}

QString TestUtils::TestDirectoryPath(const QString& test_sub_dir)
{
    return QString::fromStdString(TestConfig::TestOutputDir()) + "/" + test_sub_dir;
}

std::string TestUtils::TestDirectoryPath(const std::string& test_sub_dir)
{
    auto result = std::filesystem::path(TestConfig::TestOutputDir()) / test_sub_dir;
    return result.string();
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

QString TestUtils::JsonToString(const QJsonObject& object)
{
    QJsonDocument document(object);
    return QString(document.toJson(QJsonDocument::Compact));
}

QString TestUtils::ModelToJsonString(SessionModel& model)
{
    return QString::fromStdString(JsonUtils::ModelToJsonString(model));
}

QJsonDocument TestUtils::LoadJson(const QString& fileName)
{
    QFile jsonFile(fileName);

    if (!jsonFile.open(QIODevice::ReadOnly))
        throw std::runtime_error("TestUtils::LoadJson() -> Can't read file");

    return QJsonDocument().fromJson(jsonFile.readAll());
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



