// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MockWidgets.h"
#include "google_test.h"
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/tagrow.h>
#include <mvvm/signals/modelmapper.h>

using namespace ModelView;
using ::testing::_;

//! Testing ModelMapper callbacks on basic model manipulations.

class ModelMapperTest : public ::testing::Test
{
public:
    ~ModelMapperTest();
};

ModelMapperTest::~ModelMapperTest() = default;

//! Setting item data and checking corresponding signal.

TEST(ModelMapperTest, onDataChange)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    EXPECT_CALL(widget, onItemInserted(_, _));
    auto item = model.insertItem<SessionItem>(model.rootItem());

    // expecting signal to be called once
    const int role = ItemDataRole::DATA;
    EXPECT_CALL(widget, onDataChange(item, role)).Times(1);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onItemAboutToBeRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onItemRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    model.setData(item, 42.0, ItemDataRole::DATA); // perform action

    // setting same data shouldn't trigger the signal
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onItemRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onItemAboutToBeRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    model.setData(item, 42.0, ItemDataRole::DATA); // perform action

    // setting new data through item
    EXPECT_CALL(widget, onDataChange(item, role)).Times(1);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onItemRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onItemAboutToBeRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    item->setData(43.0); // perform action
}

//! Inserting item and checking corresponding signals.

TEST(ModelMapperTest, onRowInserted)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    const TagRow expected_tagrow{model.rootItem()->defaultTag(), 0};
    EXPECT_CALL(widget, onItemInserted(model.rootItem(), expected_tagrow)).Times(1);
    EXPECT_CALL(widget, onItemRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onItemAboutToBeRemoved(_, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);

    // perform action
    model.insertItem<SessionItem>(model.rootItem(), expected_tagrow);
}

//! Inserting item and checking corresponding signals.

TEST(ModelMapperTest, onRowRemoved)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    const TagRow expected_tagrow{model.rootItem()->defaultTag(), 0};
    EXPECT_CALL(widget, onItemInserted(model.rootItem(), expected_tagrow)).Times(1);
    model.insertItem<SessionItem>(model.rootItem(), expected_tagrow);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(widget, onItemRemoved(model.rootItem(), expected_tagrow)).Times(1);
    EXPECT_CALL(widget, onItemAboutToBeRemoved(model.rootItem(), expected_tagrow)).Times(1);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    // perform action
    model.removeItem(model.rootItem(), expected_tagrow);
}

//! Testing signals on model destruction.

TEST(ModelMapperTest, onModelDestroyed)
{
    auto model = std::make_unique<SessionModel>();
    auto widget = std::make_unique<MockWidgetForModel>(model.get());

    EXPECT_CALL(*widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(*widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(*widget, onItemRemoved(_, _)).Times(0);
    EXPECT_CALL(*widget, onItemAboutToBeRemoved(_, _)).Times(0);
    EXPECT_CALL(*widget, onModelReset(_)).Times(0);
    EXPECT_CALL(*widget, onModelDestroyed(model.get())).Times(1);

    // perform action
    model.reset();
}

//! Testing signals on model destruction.

TEST(ModelMapperTest, onModelReset)
{
    auto model = std::make_unique<SessionModel>();
    auto widget = std::make_unique<MockWidgetForModel>(model.get());

    EXPECT_CALL(*widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(*widget, onItemInserted(_, _)).Times(0);
    EXPECT_CALL(*widget, onItemRemoved(_, _)).Times(0);
    EXPECT_CALL(*widget, onItemAboutToBeRemoved(_, _)).Times(0);
    EXPECT_CALL(*widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(*widget, onModelReset(model.get())).Times(1);

    // perform action
    model->clear();
}
