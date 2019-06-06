#include "google_test.h"
#include "modelutils.h"
#include "toy_constants.h"
#include "toy_items.h"
#include "toy_models.h"

using namespace ModelView;

class TestModelUtils : public ::testing::Test
{
public:
    ~TestModelUtils();
};

TestModelUtils::~TestModelUtils() = default;

TEST_F(TestModelUtils, topItem)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::TopItem<>(&model), nullptr);
    EXPECT_EQ(Utils::TopItem<SessionItem>(&model), nullptr);
    EXPECT_EQ(Utils::TopItem<ToyItems::MultiLayerItem>(&model), nullptr);

    auto multilayer1 = model.insertNewItem(ToyItems::Constants::MultiLayerType);
    model.insertNewItem(ToyItems::Constants::MultiLayerType);

    EXPECT_EQ(Utils::TopItem<>(&model), multilayer1);
    EXPECT_EQ(Utils::TopItem<SessionItem>(&model), multilayer1);
    EXPECT_EQ(Utils::TopItem<ToyItems::MultiLayerItem>(&model), multilayer1);
}

TEST_F(TestModelUtils, topItems)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::TopItems<>(&model).size(), 0);
    EXPECT_EQ(Utils::TopItems<SessionItem>(&model).size(), 0);
    EXPECT_EQ(Utils::TopItems<ToyItems::MultiLayerItem>(&model).size(), 0);

    auto multilayer1 = dynamic_cast<ToyItems::MultiLayerItem*>(
        model.insertNewItem(ToyItems::Constants::MultiLayerType));
    auto particle = model.insertNewItem(ToyItems::Constants::ParticleType);
    auto multilayer2 = dynamic_cast<ToyItems::MultiLayerItem*>(
        model.insertNewItem(ToyItems::Constants::MultiLayerType));

    std::vector<SessionItem*> expected1 = {multilayer1, particle, multilayer2};
    EXPECT_EQ(Utils::TopItems<SessionItem>(&model), expected1);
    std::vector<ToyItems::MultiLayerItem*> expected2 = {multilayer1, multilayer2};
    EXPECT_EQ(Utils::TopItems<ToyItems::MultiLayerItem>(&model), expected2);
}

TEST_F(TestModelUtils, findItems)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::FindItems<>(&model).size(), 1); // because of rootItem
    EXPECT_EQ(Utils::FindItems<SessionItem>(&model).size(), 1); // because of rootItem
    EXPECT_EQ(Utils::FindItems<ToyItems::MultiLayerItem>(&model).size(), 0);

    auto multilayer1 = dynamic_cast<ToyItems::MultiLayerItem*>(
        model.insertNewItem(ToyItems::Constants::MultiLayerType));
    model.insertNewItem(ToyItems::Constants::ParticleType);
    auto multilayer2 = dynamic_cast<ToyItems::MultiLayerItem*>(
        model.insertNewItem(ToyItems::Constants::MultiLayerType));

    std::vector<ToyItems::MultiLayerItem*> expected2 = {multilayer1, multilayer2};
    EXPECT_EQ(Utils::FindItems<ToyItems::MultiLayerItem>(&model), expected2);

    // adding layers to multilayer
    auto layer1 = dynamic_cast<ToyItems::LayerItem*>(
        model.insertNewItem(ToyItems::Constants::LayerType, multilayer1));

    auto layer2 = dynamic_cast<ToyItems::LayerItem*>(
        model.insertNewItem(ToyItems::Constants::LayerType, multilayer2));

    std::vector<ToyItems::LayerItem*> expected3 = {layer1, layer2};
    EXPECT_EQ(Utils::FindItems<ToyItems::LayerItem>(&model), expected3);
}
