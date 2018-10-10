#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "jsonmodel.h"
#include "sessionitem.h"
#include "test_utils.h"
#include <QJsonObject>
#include <QJsonArray>

//! Checks SessionModel class and its ability to convert SessionItem trees to json objects and back.

class TestJsonModel : public ::testing::Test
{
public:
    ~TestJsonModel();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

TestJsonModel::~TestJsonModel() = default;
const QString TestJsonModel::test_dir = "test_JsonModel";

//! Checks the validity of json object representing item tree.

TEST_F(TestJsonModel, isValidTree)
{
    JsonModel converter;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter.is_valid(object));

    // it also should contain array
    object[JsonModel::modelKey] = "abc";
    object[JsonModel::itemsKey] = 42; // incorrect
    EXPECT_FALSE(converter.is_valid(object));

    // correctly constructed
    object[JsonModel::itemsKey] = QJsonArray();
    EXPECT_TRUE(converter.is_valid(object));
}

//! Check single item (no children) without the data.

TEST_F(TestJsonModel, singleItem)
{
    const QString model_type("MultiLayer");

    JsonModel converter;
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));

    QJsonObject object;
    converter.write(parent.get(), object);

    EXPECT_EQ(object[JsonModel::modelKey], model_type);
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 0);
}



//TEST_F(TestJsonModel, writeItems)
//{
//    JsonModel converter;

//    std::unique_ptr<SessionItem> parent(new SessionItem("MultiLayer"));
//    parent->insertItem(-1, new SessionItem("Layer1"));
//    parent->insertItem(-1, new SessionItem("Layer2"));
//    parent->insertItem(-1, new SessionItem("Layer3"));

//    QJsonObject object;
//    converter.write(parent.get(), object);

//    // saving to file
//    auto fileName = TestUtils::TestFileName(test_dir, "model.json");
//    TestUtils::SaveJson(object, fileName);
//}

//TEST_F(TestJsonModel, writeModel)
//{
//    JsonModel converter;

//    Utils::create_subdir(".", projectDir());

//    QFile saveFile(QString::fromStdString(projectDir() + "/save.json"));

//    if (!saveFile.open(QIODevice::WriteOnly))
//        throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

//    SessionModel model("MaterialModel");

//    QJsonObject object;
//    converter.write(model, object);

//    QJsonDocument saveDoc(object);
//    saveFile.write(saveDoc.toJson());
//}
