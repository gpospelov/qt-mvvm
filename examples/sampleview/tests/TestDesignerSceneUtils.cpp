#include "google_test.h"
#include "DesignerScene.h"
#include "DesignerSceneUtils.h"
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
