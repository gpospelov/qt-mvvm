#include <gtest/gtest.h>
#include "fileutils.h"
#include "testconfig.h"
#include <QFile>
#include <stdexcept>
#include <QJsonDocument>
#include <QJsonObject>

//! Set of tests to learn basic Qt/json manipulationx.

class TestJsonBasics : public ::testing::Test
{
public:
    ~TestJsonBasics();
    std::string projectDir() const {
        return TestConfig::TestOutputDir() + "/" + "test_JsonBasics";
    }
};

TestJsonBasics::~TestJsonBasics() = default;

TEST_F(TestJsonBasics, singleVariant)
{
    Utils::create_subdir(".", projectDir());

    QFile saveFile(QString::fromStdString(projectDir() + "/save.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

    QJsonObject object;
    object["type"] = "double";
    object["role"] = 0;
    object["value"] = 42.0;

    QJsonDocument saveDoc(object);
    saveFile.write(saveDoc.toJson());
}
