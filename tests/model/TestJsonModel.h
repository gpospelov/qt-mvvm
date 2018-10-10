#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "fileutils.h"
#include "jsonmodel.h"
#include "sessionitem.h"
#include "testconfig.h"
#include <QFile>
#include <stdexcept>
#include <QJsonDocument>
#include <QJsonObject>

//! Set of tests to learn basic Qt/json manipulationx.

class TestJsonModel : public ::testing::Test
{
public:
    ~TestJsonModel();
    std::string projectDir() const {
        return TestConfig::TestOutputDir() + "/" + "test_ModelJson";
    }
};

TestJsonModel::~TestJsonModel() = default;

TEST_F(TestJsonModel, writeModel)
{
    JsonModel converter;

    Utils::create_subdir(".", projectDir());

    QFile saveFile(QString::fromStdString(projectDir() + "/save.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

    SessionModel model("MaterialModel");

    QJsonObject object;
    converter.write(model, object);

    QJsonDocument saveDoc(object);
    saveFile.write(saveDoc.toJson());
}

TEST_F(TestJsonModel, writeItems)
{
    JsonModel converter;

    Utils::create_subdir(".", projectDir());

    QFile saveFile(QString::fromStdString(projectDir() + "/save2.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

    std::unique_ptr<SessionItem> parent(new SessionItem("MultiLayer"));
    parent->insertItem(-1, new SessionItem("Layer1"));
    parent->insertItem(-1, new SessionItem("Layer2"));
    parent->insertItem(-1, new SessionItem("Layer3"));

    QJsonObject object;
    converter.write(parent.get(), object);

    QJsonDocument saveDoc(object);
    saveFile.write(saveDoc.toJson());
}
