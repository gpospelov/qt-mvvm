// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/factories/itemconverterfactory.h"

#include "google_test.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/itemcatalogue.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionitemdata.h"
#include "mvvm/model/sessionmodel.h"
#include <QJsonObject>

using namespace ModelView;

//! Checks converters generated by ItemFactoryConverter.

class ItemConverterFactoryTest : public ::testing::Test {
public:
    class TestItem : public CompoundItem {
    public:
        TestItem() : CompoundItem("TestItem")
        {
            setToolTip("compound");
            addProperty("Thickness", 42)->setToolTip("thickness")->setEditorType("abc");
        }
    };

    class TestModel : public SessionModel {
    public:
        TestModel() : SessionModel("TestModel")
        {
            auto catalogue = std::make_unique<ModelView::ItemCatalogue>();
            catalogue->registerItem<TestItem>();
            setItemCatalogue(std::move(catalogue));
        }
    };

    ItemConverterFactoryTest() : m_model(std::make_unique<TestModel>()) {}

    const ItemFactoryInterface* factory() const { return m_model->factory(); }

    std::unique_ptr<SessionModel> m_model;
};

//! Clone converter for simple property item.

TEST_F(ItemConverterFactoryTest, propertyItemCloneConverter)
{
    auto converter = CreateItemCloneConverter(factory());

    PropertyItem item;
    item.setToolTip("abc");

    auto object = converter->to_json(&item);
    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->toolTip(), std::string("abc"));
    EXPECT_EQ(reco->itemData()->roles(), item.itemData()->roles());
    EXPECT_TRUE(reco->identifier() == item.identifier()); // identifier preserved
}

//! Copy converter for simple property item.

TEST_F(ItemConverterFactoryTest, propertyItemCopyConverter)
{
    auto converter = CreateItemCopyConverter(factory());

    PropertyItem item;
    item.setToolTip("abc");

    auto object = converter->to_json(&item);
    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->toolTip(), std::string("abc"));
    EXPECT_EQ(reco->itemData()->roles(), item.itemData()->roles());
    EXPECT_FALSE(reco->identifier() == item.identifier()); // identifier has changed
}

//! Project converter for simple property item.
//! It preserves only identifier and data roles.

TEST_F(ItemConverterFactoryTest, propertyItemProjectConverter)
{
    auto converter = CreateItemProjectConverter(factory());

    PropertyItem item;
    item.setToolTip("abc");

    auto object = converter->to_json(&item);
    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->toolTip(), std::string());            // tooltips are not preserved
    EXPECT_TRUE(reco->identifier() == item.identifier()); // identifier preserved
}

//! Clone converter for simple property item.

TEST_F(ItemConverterFactoryTest, testItemCloneConverter)
{
    auto converter = CreateItemCloneConverter(factory());

    TestItem item;
    item.setToolTip("abc");

    auto object = converter->to_json(&item);
    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->toolTip(), std::string("abc")); // updated tooltip is preserved
    EXPECT_EQ(reco->itemData()->roles(), item.itemData()->roles());
    EXPECT_TRUE(reco->identifier() == item.identifier()); // identifier preserved
    EXPECT_EQ(reco->getItem("Thickness")->toolTip(), "thickness");
    EXPECT_EQ(reco->getItem("Thickness")->identifier(), item.getItem("Thickness")->identifier());
}

//! Clone converter for simple property item.
//! At this time

TEST_F(ItemConverterFactoryTest, testItemProjectConverter)
{
    auto converter = CreateItemProjectConverter(factory());

    TestItem item;
    item.setToolTip("abc");

    auto object = converter->to_json(&item);
    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->toolTip(), std::string("compound")); // initial tooltip exist
    EXPECT_EQ(reco->itemData()->roles(), item.itemData()->roles());
    EXPECT_TRUE(reco->identifier() == item.identifier()); // identifier preserved
    EXPECT_EQ(reco->getItem("Thickness")->toolTip(), "thickness");
    EXPECT_EQ(reco->getItem("Thickness")->identifier(), item.getItem("Thickness")->identifier());
}
