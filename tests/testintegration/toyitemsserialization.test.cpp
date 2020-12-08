// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include <QJsonObject>
#include <mvvm/model/modelutils.h>
#include <mvvm/serialization/jsonmodelconverter.h>

using namespace ModelView;
using namespace ToyItems;

//! Testing serialization of ToyItems using json converters.

class ToyItemsSerializationTest : public ::testing::Test
{
public:
    ~ToyItemsSerializationTest();
};

ToyItemsSerializationTest::~ToyItemsSerializationTest() = default;

//! Checking ShapeGroupItem in a model.
//! Serialization/deserelization should give an item identical to original.

TEST_F(ToyItemsSerializationTest, defaultShapeGroupItemInModel)
{
    // model with single group item
    SampleModel model;
    auto group = model.insertItem<ShapeGroupItem>();

    // copy of model
    auto modelCopy = Utils::CreateCopy(model);
    auto groupCopy = modelCopy->topItem<ShapeGroupItem>();

    // basic properties in copied item should be the same
    EXPECT_EQ(group->currentIndex(), groupCopy->currentIndex());
    EXPECT_EQ(group->currentItem()->modelType(), groupCopy->currentItem()->modelType());
}

//! Checking ShapeGroupItem in a model.
//! Serialization/deserelization should give an item identical to original.

TEST_F(ToyItemsSerializationTest, modifiedShapeGroupItemInModel)
{
    SampleModel model;
    auto group = model.insertItem<ShapeGroupItem>();

    // modifying group item
    group->setCurrentType(ToyItems::Constants::AnysoPyramidItemType);
    group->children().at(0)->setProperty(CylinderItem::P_RADIUS, 42.0);
    group->children().at(1)->setProperty(SphereItem::P_RADIUS, 43.0);
    group->children().at(2)->setProperty(AnysoPyramidItem::P_LENGTH, 44.0);

    // creating copy
    auto modelCopy = Utils::CreateCopy(model);
    auto groupCopy = modelCopy->topItem<ShapeGroupItem>();

    // checking properties of
    EXPECT_EQ(groupCopy->currentIndex(), group->currentIndex());
    EXPECT_EQ(groupCopy->currentItem()->modelType(), group->currentItem()->modelType());
    EXPECT_EQ(groupCopy->children().at(0)->property<double>(CylinderItem::P_RADIUS), 42.0);
    EXPECT_EQ(groupCopy->children().at(1)->property<double>(SphereItem::P_RADIUS), 43.0);
    EXPECT_EQ(groupCopy->children().at(2)->property<double>(AnysoPyramidItem::P_LENGTH), 44.0);
}

//! Insert all supported items in a model and check that after serialization

TEST_F(ToyItemsSerializationTest, allItemsInAModel)
{
    SampleModel model;
    model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::LayerItem>();
    model.insertItem<ToyItems::ParticleItem>();
    model.insertItem<ToyItems::LatticeItem>();
    model.insertItem<ToyItems::SphereItem>();
    model.insertItem<ToyItems::CylinderItem>();
    model.insertItem<ToyItems::AnysoPyramidItem>();
    model.insertItem<ToyItems::ShapeGroupItem>();

    auto modelCopy = Utils::CreateCopy(model);
    EXPECT_EQ(model.rootItem()->childrenCount(), modelCopy->rootItem()->childrenCount());
}
