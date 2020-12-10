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
#include <QSignalSpy>
#include <mvvm/model/itemutils.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of toy MultiLayer in the context of model and viewmodel.

class ToyParticleItemTest : public ::testing::Test
{
public:
    ~ToyParticleItemTest();
};

ToyParticleItemTest::~ToyParticleItemTest() = default;

//! Initial state.

TEST_F(ToyParticleItemTest, initialState)
{
    ToyItems::ParticleItem item;
    EXPECT_TRUE(item.isSinglePropertyTag(ToyItems::ParticleItem::P_POSITION));
    EXPECT_TRUE(item.isSinglePropertyTag(ToyItems::ParticleItem::P_SHAPES));
}

TEST_F(ToyParticleItemTest, TopLevelItems)
{
    ToyItems::SampleModel model;
    auto particle = model.insertItem<ToyItems::ParticleItem>();

    EXPECT_EQ(Utils::TopLevelItems(*model.rootItem()), std::vector<SessionItem*>({particle}));
    EXPECT_EQ(Utils::TopLevelItems(*particle), std::vector<SessionItem*>{});
}

TEST_F(ToyParticleItemTest, SinglePropertyItems)
{
    ToyItems::SampleModel model;
    auto particle = model.insertItem<ToyItems::ParticleItem>();

    EXPECT_EQ(Utils::TopLevelItems(*model.rootItem()), std::vector<SessionItem*>({particle}));

    EXPECT_EQ(Utils::SinglePropertyItems(*model.rootItem()), std::vector<SessionItem*>{});
    std::vector<SessionItem*> expected = {particle->getItem(ToyItems::ParticleItem::P_POSITION),
                                          particle->getItem(ToyItems::ParticleItem::P_SHAPES)};
    EXPECT_EQ(Utils::SinglePropertyItems(*particle), expected);
}
