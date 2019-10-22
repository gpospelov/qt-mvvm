#include "google_test.h"
#include "DesignerScene.h"
#include "DesignerSceneUtils.h"
#include "ParticleLayoutItem.h"
#include "item_constants.h"
#include "LayerItems.h"
#include "LayerView.h"
#include "modelutils.h"
#include "MultiLayerView.h"
#include "SampleModel.h"

using namespace ModelView;

class TestDesignerSceneUtils : public ::testing::Test
{
public:
    TestDesignerSceneUtils();
    ~TestDesignerSceneUtils() override;

protected:
    QRectF makeFrame(QRectF bound);

    SampleModel model;
    std::unique_ptr<DesignerScene> scene;
};

TestDesignerSceneUtils::TestDesignerSceneUtils()
    : scene(std::make_unique<DesignerScene>(&model))
{
    model.clear();
}

TestDesignerSceneUtils::~TestDesignerSceneUtils() = default;

QRectF TestDesignerSceneUtils::makeFrame(QRectF bound)
{
    return QRectF(bound.left() - 0.1, bound.top() - 0.1, bound.width() + 0.2, bound.height() + 0.2);
}

TEST_F(TestDesignerSceneUtils, testTrivial)
{
    auto mlayer = model.insertNewItem(::Constants::MultiLayerType);
    auto view = dynamic_cast<MultiLayerView*>(scene->getViewForItem(mlayer));

    const auto [mview, row] = DesignerSceneUtils::nearestMultilayer(*view);
    EXPECT_FALSE(mview == view);
    EXPECT_EQ(mview, nullptr);
    EXPECT_EQ(row, -1);
}

TEST_F(TestDesignerSceneUtils, testSimple)
{
    auto mlayer = model.insertNewItem(::Constants::MultiLayerType);
    auto layer = model.insertNewItem(::Constants::LayerType, mlayer, MultiLayerItem::T_LAYERS);
    auto mview = dynamic_cast<MultiLayerView*>(scene->getViewForItem(mlayer));
    auto lview = dynamic_cast<LayerView*>(scene->getViewForItem(layer));

    const auto [candidate, row] = DesignerSceneUtils::nearestMultilayer(*lview);
    EXPECT_EQ(mview, candidate);
    EXPECT_EQ(row, 0);
}

TEST_F(TestDesignerSceneUtils, testHeadItems)
{
    const auto mlayer = model.insertItem<MultiLayerItem>();
    const auto layer = model.insertItem<LayerItem>(mlayer, MultiLayerItem::T_LAYERS);
    const auto layout = model.insertItem<ParticleLayoutItem>(layer, LayerItem::T_LAYOUTS);
    const auto layout_2 = model.insertItem<ParticleLayoutItem>();
    const auto mlayer_2 = model.insertItem<MultiLayerItem>();

    auto result = DesignerSceneUtils::headItems({mlayer, layer, layout, layout_2, mlayer_2});
    EXPECT_TRUE((result == QSet<SessionItem*>{mlayer, layout_2, mlayer_2}));

    result = DesignerSceneUtils::headItems({layer, layout, layout_2, mlayer_2});
    EXPECT_TRUE((result == QSet<SessionItem*>{layer, layout_2, mlayer_2}));

    result = DesignerSceneUtils::headItems({layout, layout_2, mlayer_2});
    EXPECT_TRUE((result == QSet<SessionItem*>{layout, layout_2, mlayer_2}));
}

TEST_F(TestDesignerSceneUtils, testMakeLookupTable)
{
    EXPECT_THROW(DesignerSceneUtils::makeLookupTable(nullptr, nullptr), std::runtime_error);

    const auto mlayer = model.insertItem<MultiLayerItem>();
    const auto layer = model.insertItem<LayerItem>(mlayer, MultiLayerItem::T_LAYERS);
    const auto layout = model.insertItem<ParticleLayoutItem>(layer, LayerItem::T_LAYOUTS);

    EXPECT_THROW(DesignerSceneUtils::makeLookupTable(mlayer, layout), std::runtime_error);

    SampleModel tmp;
    tmp.clear();

    SessionItem* copy = tmp.copyItem(mlayer, tmp.rootItem());
    auto result = DesignerSceneUtils::makeLookupTable(mlayer, copy);

    EXPECT_TRUE(result.find(mlayer) != result.end());
    EXPECT_TRUE(result.find(layer) != result.end());
    EXPECT_TRUE(result.find(layout) != result.end());
    EXPECT_EQ(result.size(),
              mlayer->childrenCount() + layer->childrenCount() + layout->childrenCount() + 1);
}

TEST_F(TestDesignerSceneUtils, testViewableItems)
{
    const auto mlayer = model.insertItem<MultiLayerItem>();
    const auto layer = model.insertItem<LayerItem>(mlayer, MultiLayerItem::T_LAYERS);
    const auto layout = model.insertItem<ParticleLayoutItem>(layer, LayerItem::T_LAYOUTS);

    QSet<SessionItem*> all_items;
    Utils::iterate(mlayer, [&all_items](SessionItem* item) { all_items.insert(item); });

    auto result =
        QSet<SessionItem*>::fromList(DesignerSceneUtils::viewableItems(all_items.toList()));
    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.find(mlayer) != result.end());
    EXPECT_TRUE(result.find(layer) != result.end());
    EXPECT_TRUE(result.find(layout) != result.end());
}
