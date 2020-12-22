// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/signals/modellistener.h"

#include "google_test.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionmodel.h"
#include <memory>

using namespace ModelView;

//! Tests of ModelListener class.

class ModelListenerTest : public ::testing::Test {
public:
    class TestListener : public ModelListener<SessionModel> {
    public:
        TestListener(SessionModel* model) : ModelListener(model) {}
    };
};

//! Initial state.

TEST_F(ModelListenerTest, initialState)
{
    SessionModel model;
    TestListener listener(&model);
    EXPECT_EQ(listener.model(), &model);
}

TEST_F(ModelListenerTest, onDataChange)
{
    auto model = std::make_unique<SessionModel>();
    auto listener = std::make_unique<TestListener>(model.get());

    int counter{0};
    auto on_data_change = [&counter](SessionItem*, int) { counter++; };
    listener->setOnDataChange(on_data_change);

    auto item = model->insertItem<PropertyItem>();
    item->setData(42.0);

    EXPECT_EQ(counter, 1);
}

//! Check that controller aware of item deletion.

TEST_F(ModelListenerTest, modelDeletedBeforeListener)
{
    auto model = std::make_unique<SessionModel>();
    auto listener = std::make_unique<TestListener>(model.get());

    EXPECT_EQ(listener->model(), model.get());

    model.reset();
    EXPECT_EQ(listener->model(), nullptr);
}

//! Checks that the listenerr can be deleted before the model.

TEST_F(ModelListenerTest, listenerDeletedBeforeTheModel)
{
    // create model and its listener
    auto model = std::make_unique<SessionModel>();
    auto listener = std::make_unique<TestListener>(model.get());

    // assign to data-changed event
    int counter{0};
    auto on_data_change = [&counter](SessionItem*, int) { counter++; };
    listener->setOnDataChange(on_data_change);

    // changing the data and checking the listener
    auto item = model->insertItem<PropertyItem>();
    item->setData(42.0);
    EXPECT_EQ(counter, 1);

    // deleting the listener and trying to change the data again
    listener.reset();
    item->setData(43.0);
    EXPECT_EQ(counter, 1);
}
