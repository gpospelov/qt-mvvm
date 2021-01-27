// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "toyitems.h"

#include "google_test.h"
#include "toymodel.h"
#include "mvvm/model/itemutils.h"
#include <QSignalSpy>

using namespace ModelView;

//! Tests of toy MultiLayer in the context of model and viewmodel.

class ToyParticleItemTest : public ::testing::Test {
};

//! Initial state.

TEST_F(ToyParticleItemTest, initialState)
{
    ToyItems::ParticleItem item;
    EXPECT_TRUE(Utils::IsSinglePropertyTag(item, ToyItems::ParticleItem::P_POSITION));
    EXPECT_TRUE(Utils::IsSinglePropertyTag(item, ToyItems::ParticleItem::P_SHAPES));
}

TEST_F(ToyParticleItemTest, TopLevelItems)
{
    ToyItems::SampleModel model;
    auto particle = model.insertItem<ToyItems::ParticleItem>();

    EXPECT_EQ(Utils::TopLevelItems(*model.rootItem()), std::vector<SessionItem*>({particle}));
    EXPECT_EQ(Utils::TopLevelItems(*particle), std::vector<SessionItem*>{});
}

TEST_F(ToyParticleItemTest, TopLevelItemsWhenHidden)
{
    ToyItems::SampleModel model;
    auto particle = model.insertItem<ToyItems::ParticleItem>();
    particle->setVisible(false);

    EXPECT_EQ(Utils::TopLevelItems(*model.rootItem()), std::vector<SessionItem*>({}));
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

TEST_F(ToyParticleItemTest, SinglePropertyItemsWhenPropertyHidden)
{
    ToyItems::SampleModel model;
    auto particle = model.insertItem<ToyItems::ParticleItem>();

    EXPECT_EQ(Utils::TopLevelItems(*model.rootItem()), std::vector<SessionItem*>({particle}));

    EXPECT_EQ(Utils::SinglePropertyItems(*model.rootItem()), std::vector<SessionItem*>{});

    particle->getItem(ToyItems::ParticleItem::P_POSITION)->setVisible(false);
    std::vector<SessionItem*> expected = {particle->getItem(ToyItems::ParticleItem::P_SHAPES)};
    EXPECT_EQ(Utils::SinglePropertyItems(*particle), expected);
}
