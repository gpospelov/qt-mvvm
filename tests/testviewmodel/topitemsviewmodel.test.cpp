// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/topitemsviewmodel.h"

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include "mvvm/model/sessionmodel.h"
#include <QSignalSpy>

using namespace ModelView;

//! Tests for TopItemsViewModel class.

class TopItemsViewModelTest : public ::testing::Test {
};

TEST_F(TopItemsViewModelTest, initialState)
{
    SessionModel model;
    TopItemsViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), model.rootItem());
}

//! Insert LayerItem in empty model.

TEST_F(TopItemsViewModelTest, insertLayerThenRemove)
{
    ToyItems::SampleModel model;
    TopItemsViewModel viewmodel(&model);

    QSignalSpy spyInsert(&viewmodel, &ViewModelBase::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &ViewModelBase::rowsRemoved);

    model.insertItem<ToyItems::LayerItem>();

    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);

    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyInsert.count(), 1);

    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(spyInsert.count(), 1);

    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 0);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 0);
}

//! Hidden LayerItem in a model. An item with setVisible(false) set shouldn't appear in a view
//! model. The current implementation is limited and respects this flag only if it was set before
//! the view model creation.

TEST_F(TopItemsViewModelTest, hidenLayerInModel)
{
    // the model with two layers, where one is invisible
    ToyItems::SampleModel model;
    auto layer0 = model.insertItem<ToyItems::LayerItem>();
    auto layer1 = model.insertItem<ToyItems::LayerItem>();
    layer0->setVisible(false);

    TopItemsViewModel viewmodel(&model);

    // TopItemsViewModel should see only one layer.
    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);
    auto layer1_index = viewmodel.index(0, 0, QModelIndex());
    EXPECT_EQ(viewmodel.sessionItemFromIndex(layer1_index), layer1);

    // The current implementation is somewhat limited: TopItemsViewModel doesn't listen for updates
    // in isVisible flag. If flag is set after the model creation, item still be visible.

    layer1->setVisible(false);

    // model still sees the layer
    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);
    layer1_index = viewmodel.index(0, 0, QModelIndex());
    EXPECT_EQ(viewmodel.sessionItemFromIndex(layer1_index), layer1);
}

//! Insert LayerItem in MultiLayer.

TEST_F(TopItemsViewModelTest, insertLayerInMultiLayerThenRemove)
{
    ToyItems::SampleModel model;
    TopItemsViewModel viewmodel(&model);

    QSignalSpy spyInsert(&viewmodel, &ViewModelBase::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &ViewModelBase::rowsRemoved);

    // inserting multilayer
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();

    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyInsert.count(), 1);

    // insert layer
    auto layer = model.insertItem<ToyItems::LayerItem>(multilayer);
    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyInsert.count(), 2);

    // checking their indices
    auto multilayer_index = viewmodel.index(0, 0, QModelIndex());
    auto layer_index = viewmodel.index(0, 0, multilayer_index);
    EXPECT_EQ(viewmodel.sessionItemFromIndex(multilayer_index), multilayer);
    EXPECT_EQ(viewmodel.sessionItemFromIndex(layer_index), layer);

    // checking row and columns
    EXPECT_EQ(viewmodel.rowCount(multilayer_index), 1);
    EXPECT_EQ(viewmodel.columnCount(multilayer_index), 2);
    EXPECT_EQ(viewmodel.rowCount(layer_index), 0);
    EXPECT_EQ(viewmodel.columnCount(layer_index), 0);

    // removing layer
    model.removeItem(multilayer, {"", 0});
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(spyInsert.count(), 2);
    EXPECT_EQ(viewmodel.rowCount(multilayer_index), 0);
    EXPECT_EQ(viewmodel.columnCount(multilayer_index), 0);
}

//! Insert LayerItem in MultiLayer while multilayer is root item. Then deleting multilayer.

TEST_F(TopItemsViewModelTest, multuLayerAsRooItem)
{
    ToyItems::SampleModel model;
    TopItemsViewModel viewmodel(&model);

    // setting up single multilayer playing the role
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    viewmodel.setRootSessionItem(multilayer);
    QSignalSpy spyInsert(&viewmodel, &ViewModelBase::rowsInserted);
    QSignalSpy spyRemove(&viewmodel, &ViewModelBase::rowsRemoved);

    // initial conditions
    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 0);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 0);
    EXPECT_EQ(viewmodel.sessionItemFromIndex(QModelIndex()), multilayer); // our new root

    // adding layer
    model.insertItem<ToyItems::LayerItem>(multilayer);
    EXPECT_EQ(viewmodel.rowCount(QModelIndex()), 1);
    EXPECT_EQ(viewmodel.columnCount(QModelIndex()), 2);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyInsert.count(), 1);

    // removing multilayer
    model.removeItem(model.rootItem(), {"", 0});
}
