// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/modelutils.h"

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"

using namespace ModelView;

class ModelUtilsTest : public ::testing::Test {
};

TEST_F(ModelUtilsTest, topItem)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::TopItem<>(&model), nullptr);
    EXPECT_EQ(Utils::TopItem<SessionItem>(&model), nullptr);
    EXPECT_EQ(Utils::TopItem<ToyItems::MultiLayerItem>(&model), nullptr);

    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::MultiLayerItem>();

    EXPECT_EQ(Utils::TopItem<>(&model), multilayer1);
    EXPECT_EQ(Utils::TopItem<SessionItem>(&model), multilayer1);
    EXPECT_EQ(Utils::TopItem<ToyItems::MultiLayerItem>(&model), multilayer1);
}

TEST_F(ModelUtilsTest, topItems)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::TopItems<>(&model).size(), 0);
    EXPECT_EQ(Utils::TopItems<SessionItem>(&model).size(), 0);
    EXPECT_EQ(Utils::TopItems<ToyItems::MultiLayerItem>(&model).size(), 0);

    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    auto particle = model.insertItem<ToyItems::ParticleItem>();
    auto multilayer2 = model.insertItem<ToyItems::MultiLayerItem>();

    std::vector<SessionItem*> expected1 = {multilayer1, particle, multilayer2};
    EXPECT_EQ(Utils::TopItems<SessionItem>(&model), expected1);
    std::vector<ToyItems::MultiLayerItem*> expected2 = {multilayer1, multilayer2};
    EXPECT_EQ(Utils::TopItems<ToyItems::MultiLayerItem>(&model), expected2);
}

TEST_F(ModelUtilsTest, findItems)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::FindItems<>(&model).size(), 1);            // because of rootItem
    EXPECT_EQ(Utils::FindItems<SessionItem>(&model).size(), 1); // because of rootItem
    EXPECT_EQ(Utils::FindItems<ToyItems::MultiLayerItem>(&model).size(), 0);

    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::ParticleItem>();
    auto multilayer2 = model.insertItem<ToyItems::MultiLayerItem>();

    std::vector<ToyItems::MultiLayerItem*> expected2 = {multilayer1, multilayer2};
    EXPECT_EQ(Utils::FindItems<ToyItems::MultiLayerItem>(&model), expected2);

    // adding layers to multilayer
    auto layer1 = model.insertItem<ToyItems::LayerItem>(multilayer1);
    auto layer2 = model.insertItem<ToyItems::LayerItem>(multilayer2);

    std::vector<ToyItems::LayerItem*> expected3 = {layer1, layer2};
    EXPECT_EQ(Utils::FindItems<ToyItems::LayerItem>(&model), expected3);
}

TEST_F(ModelUtilsTest, CreateCopy)
{
    ToyItems::SampleModel model;
    auto layer = model.insertItem<ToyItems::LayerItem>();
    layer->setProperty(ToyItems::LayerItem::P_THICKNESS, 42.0);

    auto modelCopy = Utils::CreateCopy<ToyItems::SampleModel>(model);
    auto layerCopy = modelCopy->topItem<ToyItems::LayerItem>();
    EXPECT_EQ(layerCopy->property<double>(ToyItems::LayerItem::P_THICKNESS), 42.0);

    // Copied model has unique identifiers
    EXPECT_FALSE(model.rootItem()->identifier() == modelCopy->rootItem()->identifier());
    EXPECT_FALSE(layerCopy->identifier() == layer->identifier());
}

TEST_F(ModelUtilsTest, CreateClone)
{
    ToyItems::SampleModel model;
    auto layer = model.insertItem<ToyItems::LayerItem>();
    layer->setProperty(ToyItems::LayerItem::P_THICKNESS, 42.0);

    auto modelCopy = Utils::CreateClone<ToyItems::SampleModel>(model);
    auto layerCopy = modelCopy->topItem<ToyItems::LayerItem>();
    EXPECT_EQ(layerCopy->property<double>(ToyItems::LayerItem::P_THICKNESS), 42.0);

    // Copied model has unique identifiers
    EXPECT_TRUE(layerCopy->identifier() == layer->identifier());

    // root item by current conveniton still has unique identifier event for cloned model
    // probably for the uniformity this has to be changed, and test below changed to EXPECT_TRUE
    // This will require change in JsonModelConverter
    EXPECT_FALSE(model.rootItem()->identifier() == modelCopy->rootItem()->identifier());
}

TEST_F(ModelUtilsTest, DeleteItemFromModel)
{
    ToyItems::SampleModel model;

    auto item = model.insertItem<SessionItem>();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    Utils::DeleteItemFromModel(item);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
}

TEST_F(ModelUtilsTest, MoveItemUp)
{
    ToyItems::SampleModel model;

    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer0 = model.insertItem<ToyItems::LayerItem>(multilayer);
    auto layer1 = model.insertItem<ToyItems::LayerItem>(multilayer);
    auto layer2 = model.insertItem<ToyItems::LayerItem>(multilayer);

    std::vector<SessionItem*> expected = {layer0, layer1, layer2};

    // original layout
    EXPECT_EQ(multilayer->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);

    // moving top layer up doesn't change the order
    Utils::MoveUp(layer0);
    EXPECT_EQ(multilayer->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);

    // moving bottom layer up does change the order
    Utils::MoveUp(layer2);
    expected = {layer0, layer2, layer1};
    EXPECT_EQ(multilayer->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);
}

TEST_F(ModelUtilsTest, MoveItemDown)
{
    ToyItems::SampleModel model;

    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer0 = model.insertItem<ToyItems::LayerItem>(multilayer);
    auto layer1 = model.insertItem<ToyItems::LayerItem>(multilayer);
    auto layer2 = model.insertItem<ToyItems::LayerItem>(multilayer);

    std::vector<SessionItem*> expected = {layer0, layer1, layer2};

    // original layout
    EXPECT_EQ(multilayer->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);

    // moving bottom layer down doesn't change the order
    Utils::MoveDown(layer2);
    EXPECT_EQ(multilayer->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);

    // moving top layer down doesn't change the order
    Utils::MoveDown(layer0);
    expected = {layer1, layer0, layer2};
    EXPECT_EQ(multilayer->getItems(ToyItems::MultiLayerItem::T_LAYERS), expected);
}
