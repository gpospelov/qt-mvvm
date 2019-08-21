#include "MockWidgets.h"
#include "google_test.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"

using namespace ModelView;
using ::testing::_;

//! Testing ModelMapper callbacks on basic model manipulations.

class TestModelMapper : public ::testing::Test
{
public:
    ~TestModelMapper();
};

TestModelMapper::~TestModelMapper() = default;

//! Setting item data and checking corresponding signal.

TEST(TestModelMapper, onDataChange)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    EXPECT_CALL(widget, onRowInserted(_, _, _));
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    // expecting signal to be called once
    const int role = ItemDataRole::DATA;
    EXPECT_CALL(widget, onDataChange(item, role)).Times(1);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowRemoved(_, _, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    model.setData(item, 42.0, ItemDataRole::DATA); // perform action

    // setting same data shouldn't trigger the signal
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowRemoved(_, _, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    model.setData(item, 42.0, ItemDataRole::DATA); // perform action

    // setting new data through item
    EXPECT_CALL(widget, onDataChange(item, role)).Times(1);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowRemoved(_, _, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    item->setData(43.0); // perform action
}

//! Inserting item and checking corresponding signals.

TEST(TestModelMapper, onRowInserted)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    const int expected_index(0);
    const std::string expected_tag("");
    EXPECT_CALL(widget, onRowInserted(model.rootItem(), expected_tag, expected_index)).Times(1);
    EXPECT_CALL(widget, onRowRemoved(_, _, _)).Times(0);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);

    // perform action
    model.insertNewItem(Constants::BaseType, model.rootItem(), expected_tag, 0);
}

//! Inserting item and checking corresponding signals.

TEST(TestModelMapper, onRowRemoved)
{
    SessionModel model;
    MockWidgetForModel widget(&model);

    const int expected_index(0);
    const std::string expected_tag("");
    EXPECT_CALL(widget, onRowInserted(model.rootItem(), expected_tag, expected_index)).Times(1);
    model.insertNewItem(Constants::BaseType, model.rootItem(), expected_tag, expected_index);

    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(widget, onRowRemoved(model.rootItem(), expected_tag, expected_index)).Times(1);
    EXPECT_CALL(widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(widget, onModelReset(_)).Times(0);
    // perform action
    model.removeItem(model.rootItem(), expected_tag, expected_index);
}

//! Testing signals on model destruction.

TEST(TestModelMapper, onModelDestroyed)
{
    std::unique_ptr<SessionModel> model = std::make_unique<SessionModel>();
    std::unique_ptr<MockWidgetForModel> widget = std::make_unique<MockWidgetForModel>(model.get());

    EXPECT_CALL(*widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(*widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(*widget, onRowRemoved(_, _, _)).Times(0);
    EXPECT_CALL(*widget, onModelReset(_)).Times(0);
    EXPECT_CALL(*widget, onModelDestroyed(model.get())).Times(1);

    // perform action
    model.reset();
}

//! Testing signals on model destruction.

TEST(TestModelMapper, onModelReset)
{
    std::unique_ptr<SessionModel> model = std::make_unique<SessionModel>();
    std::unique_ptr<MockWidgetForModel> widget = std::make_unique<MockWidgetForModel>(model.get());

    EXPECT_CALL(*widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(*widget, onRowInserted(_, _, _)).Times(0);
    EXPECT_CALL(*widget, onRowRemoved(_, _, _)).Times(0);
    EXPECT_CALL(*widget, onModelDestroyed(_)).Times(0);
    EXPECT_CALL(*widget, onModelReset(model.get())).Times(1);

    // perform action
    model->clear();
}
