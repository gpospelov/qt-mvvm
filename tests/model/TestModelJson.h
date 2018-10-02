#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "modeljson.h"
#include "fileutils.h"
#include "modeljson.h"
#include "sessionitem.h"
#include <QFile>
#include <stdexcept>
#include <QJsonDocument>
#include <QJsonObject>

//! Set of tests to learn basic Qt/json manipulationx.

class TestModelJson : public ::testing::Test
{
public:
    ~TestModelJson();
    const std::string projectDir = "test_ModelJson";
};

TestModelJson::~TestModelJson() = default;

TEST_F(TestModelJson, writeModel)
{
    Utils::create_subdir(".", projectDir);

    QFile saveFile(QString::fromStdString(projectDir + "/save.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

    SessionModel model("MaterialModel");

    QJsonObject object;
    ModelJson::write(model, object);

    QJsonDocument saveDoc(object);
    saveFile.write(saveDoc.toJson());
}

TEST_F(TestModelJson, writeItems)
{
    Utils::create_subdir(".", projectDir);

    QFile saveFile(QString::fromStdString(projectDir + "/save2.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

    std::unique_ptr<SessionItem> parent(new SessionItem("MultiLayer"));
    parent->insertItem(-1, new SessionItem("Layer1"));
    parent->insertItem(-1, new SessionItem("Layer2"));
    parent->insertItem(-1, new SessionItem("Layer3"));

    QJsonObject object;
    ModelJson::write(parent.get(), object);

    QJsonDocument saveDoc(object);
    saveFile.write(saveDoc.toJson());
}
