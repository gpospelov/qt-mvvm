// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "layeritems.h"
#include "layerviewmodel.h"
#include "samplemodel.h"
#include "test_utils.h"
#include <QSignalSpy>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of LayerViewModel.

class LayerViewModelTest : public ::testing::Test
{
public:
    ~LayerViewModelTest();
};

LayerViewModelTest::~LayerViewModelTest() = default;

TEST_F(LayerViewModelTest, initialState)
{
    SampleModel model;
    LayerViewModel viewmodel(&model);

    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);
}

//! Checks signals while inserting LayerItem in empty model

TEST_F(LayerViewModelTest, insertLayer)
{
    SampleModel model;
    LayerViewModel viewmodel(&model);

    QSignalSpy spyRowsInserted(&viewmodel, &LayerViewModel::rowsInserted);
    QSignalSpy spyColumnsInserted(&viewmodel, &LayerViewModel::columnsInserted);
    QSignalSpy spyRowsRemoved(&viewmodel, &LayerViewModel::rowsRemoved);
    QSignalSpy spyColumnsRemoved(&viewmodel, &LayerViewModel::columnsRemoved);

    auto layer = model.insertItem<LayerItem>();
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 4);

    // checking ::rowInserted
    EXPECT_EQ(spyRowsInserted.count(), 1);
    QList<QVariant> arguments = spyRowsInserted.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);

    // checking ::columnInserted
    EXPECT_EQ(spyColumnsInserted.count(), 0);

    // checking ::spyRowsRemoved
    EXPECT_EQ(spyColumnsInserted.count(), 0);

    // checking ::spyRowsRemoved
    EXPECT_EQ(spyColumnsRemoved.count(), 0);

    // checking layout of ViewModel
    QModelIndexList selection = {viewmodel.index(0, 0), viewmodel.index(0, 1),
                                 viewmodel.index(0, 2), viewmodel.index(0, 3)};

    std::vector<SessionItem*> expected = {layer->getItem(LayerItem::P_NAME), nullptr,
                                          layer->getItem(LayerItem::P_MATERIAL),
                                          layer->getItem(LayerItem::P_THICKNESS)};
    EXPECT_EQ(Utils::ItemsFromIndex(selection), expected);
}

//! Checks signals while inserting MultiLayerItem in empty model.

TEST_F(LayerViewModelTest, inserMultitLayer)
{
    SampleModel model;
    LayerViewModel viewmodel(&model);

    QSignalSpy spyRowsInserted(&viewmodel, &LayerViewModel::rowsInserted);
    QSignalSpy spyColumnsInserted(&viewmodel, &LayerViewModel::columnsInserted);
    QSignalSpy spyRowsRemoved(&viewmodel, &LayerViewModel::rowsRemoved);
    QSignalSpy spyColumnsRemoved(&viewmodel, &LayerViewModel::columnsRemoved);

    auto multilayer = model.insertItem<MultiLayerItem>();
    EXPECT_EQ(viewmodel.rowCount(), 1);
    EXPECT_EQ(viewmodel.columnCount(), 4);

    // checking ::rowInserted
    EXPECT_EQ(spyRowsInserted.count(), 1);
    QList<QVariant> arguments = spyRowsInserted.takeFirst();
    EXPECT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);

    // checking ::columnInserted
    EXPECT_EQ(spyColumnsInserted.count(), 0);

    // checking ::spyRowsRemoved
    EXPECT_EQ(spyColumnsInserted.count(), 0);

    // checking ::spyRowsRemoved
    EXPECT_EQ(spyColumnsRemoved.count(), 0);

    // checking layout of ViewModel
    QModelIndexList selection = {viewmodel.index(0, 0), viewmodel.index(0, 1),
                                 viewmodel.index(0, 2), viewmodel.index(0, 3)};

    std::vector<SessionItem*> expected = {multilayer->getItem(MultiLayerItem::P_NAME),
                                          multilayer->getItem(MultiLayerItem::P_NREPETITIONS),
                                          nullptr, nullptr};
    EXPECT_EQ(Utils::ItemsFromIndex(selection), expected);

    // adding layer to the multilayer
    QModelIndex mlIndex = viewmodel.index(0, 0);
    model.insertItem<LayerItem>(multilayer);
    EXPECT_EQ(viewmodel.rowCount(mlIndex), 1);
    EXPECT_EQ(viewmodel.columnCount(mlIndex), 4);
}

//! Layout of LayerViewModel for two layer system.

TEST_F(LayerViewModelTest, twoLayerSystem)
{
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto top = model.insertItem<LayerItem>(multilayer);
    auto bottom = model.insertItem<LayerItem>(multilayer);

    LayerViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(multilayer);

    EXPECT_EQ(viewmodel.rowCount(), 2);
    EXPECT_EQ(viewmodel.columnCount(), 4); // name, Nr, material, thickness

    // check indexes in first row and their correspondance to top-layer related items
    QModelIndexList selection = {viewmodel.index(0, 0), viewmodel.index(0, 1),
                                 viewmodel.index(0, 2), viewmodel.index(0, 3)};
    std::vector<SessionItem*> expected = {top->getItem(LayerItem::P_NAME), nullptr,
                                          top->getItem(LayerItem::P_MATERIAL),
                                          top->getItem(LayerItem::P_THICKNESS)};
    EXPECT_EQ(Utils::ItemsFromIndex(selection), expected);

    // check indexes in first row and their correspondance to bottom-layer related items
    selection = {viewmodel.index(1, 0), viewmodel.index(1, 1), viewmodel.index(1, 2),
                 viewmodel.index(1, 3)};
    expected = {bottom->getItem(LayerItem::P_NAME), nullptr, bottom->getItem(LayerItem::P_MATERIAL),
                bottom->getItem(LayerItem::P_THICKNESS)};
    EXPECT_EQ(Utils::ItemsFromIndex(selection), expected);
}
