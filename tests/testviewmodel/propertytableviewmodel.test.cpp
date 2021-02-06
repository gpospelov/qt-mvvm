// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/propertytableviewmodel.h"

#include "google_test.h"
#include "toyitems.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/standarditems/vectoritem.h"
#include <QSignalSpy>
#include <QStandardItemModel>

using namespace ModelView;

class PropertyTableViewModelTest : public ::testing::Test {
};

TEST_F(PropertyTableViewModelTest, initialState)
{
    SessionModel model;
    PropertyTableViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), model.rootItem());
}

TEST_F(PropertyTableViewModelTest, baseItem)
{
    SessionModel model;
    model.insertItem<SessionItem>();

    PropertyTableViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(PropertyTableViewModelTest, propertyItem)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertItem<SessionItem>(parent, "universal_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");
    model.insertItem<SessionItem>(parent, "universal_tag");

    PropertyTableViewModel viewModel(&model);

    // one cell corresponding to single item at property_tag of our parent
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 1);

    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! VectorItem in a model.

TEST_F(PropertyTableViewModelTest, vectorItem)
{
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();

    PropertyTableViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    // switching to vectorItem and checking that it has 3 properties
    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! MultiLayer with layers, view model still looks to the RootItem.
//! No MultiLayer should be visible in table.

TEST_F(PropertyTableViewModelTest, multiLayerAndRootItem)
{
    SessionModel model;
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::LayerItem>(multilayer);
    model.insertItem<ToyItems::LayerItem>(multilayer);

    PropertyTableViewModel viewModel(&model);

    // ViewModel should be empty, since we are looking to RootItem.
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! MultiLayer with layers, multilayer is given as root index.

TEST_F(PropertyTableViewModelTest, multiLayer)
{
    SessionModel model;
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::LayerItem>(multilayer);
    model.insertItem<ToyItems::LayerItem>(multilayer);

    PropertyTableViewModel viewModel(&model);
    viewModel.setRootSessionItem(multilayer);

    EXPECT_EQ(viewModel.rowCount(), 2);    // two layers
    EXPECT_EQ(viewModel.columnCount(), 2); // layer thickness and color

    // add another layer
    model.insertItem<ToyItems::LayerItem>(multilayer);
    EXPECT_EQ(viewModel.rowCount(), 3);    // two layers
    EXPECT_EQ(viewModel.columnCount(), 2); // layer thickness and color

    // switching view model back to model's root, table should be empty
    viewModel.setRootSessionItem(model.rootItem());
    EXPECT_EQ(viewModel.rowCount(), 0);    // two layers
    EXPECT_EQ(viewModel.columnCount(), 0); // layer thickness and color
}

//! Check signaling of QStandardItemModel to learn from that.
//! Does insertion of row trigger columns-related signaling? Answer: no.

TEST_F(PropertyTableViewModelTest, standardItemModel)
{
    QStandardItemModel model;
    QStandardItem* parentItem = model.invisibleRootItem();

    QSignalSpy spyAboutInserInsert(&model, &ViewModelBase::rowsAboutToBeInserted);
    QSignalSpy spyInsert(&model, &ViewModelBase::rowsInserted);
    QSignalSpy spyAboutRemove(&model, &ViewModelBase::rowsAboutToBeRemoved);
    QSignalSpy spyRemove(&model, &ViewModelBase::rowsRemoved);
    QSignalSpy spyAboutReset(&model, &ViewModelBase::modelAboutToBeReset);
    QSignalSpy spyReset(&model, &ViewModelBase::modelReset);

    QList<QStandardItem*> items = {new QStandardItem("a"), new QStandardItem("b")};
    parentItem->insertRow(0, items);

    EXPECT_EQ(model.rowCount(), 1);
    EXPECT_EQ(model.columnCount(), 2);

    EXPECT_EQ(spyAboutInserInsert.count(), 1);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(spyAboutRemove.count(), 0);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 0);
    EXPECT_EQ(spyReset.count(), 0);

    QList<QVariant> arguments = spyInsert.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);
}

//! Initialize PropertyTableViewModel with empty SessionModel.
//! VectorItem in a model.

TEST_F(PropertyTableViewModelTest, insertItemSignaling)
{
    SessionModel model;
    PropertyTableViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);

    QSignalSpy spyAboutInserInsert(&viewModel, &ViewModelBase::rowsAboutToBeInserted);
    QSignalSpy spyInsert(&viewModel, &ViewModelBase::rowsInserted);
    QSignalSpy spyAboutRemove(&viewModel, &ViewModelBase::rowsAboutToBeRemoved);
    QSignalSpy spyRemove(&viewModel, &ViewModelBase::rowsRemoved);
    QSignalSpy spyAboutReset(&viewModel, &ViewModelBase::modelAboutToBeReset);
    QSignalSpy spyReset(&viewModel, &ViewModelBase::modelReset);
    QSignalSpy spyLayout(&viewModel, &ViewModelBase::layoutChanged);

    // inserting item
    model.insertItem<VectorItem>();
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    EXPECT_EQ(spyAboutInserInsert.count(), 1);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(spyAboutRemove.count(), 0);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 0);
    EXPECT_EQ(spyReset.count(), 0);

    // Checking that notification from PropertyTableViewModel::insertRow works,
    // when the model changes from columnsCount=0 to columdCount = 3
    EXPECT_EQ(spyLayout.count(), 1);

    QList<QVariant> arguments = spyInsert.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);

    arguments = spyAboutInserInsert.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 0);
    EXPECT_EQ(arguments.at(2).value<int>(), 0);

    spyLayout.takeFirst(); // clearing layout signal

    // inserting item
    model.insertItem<VectorItem>();
    EXPECT_EQ(viewModel.rowCount(), 2);
    EXPECT_EQ(viewModel.columnCount(), 3);

    EXPECT_EQ(spyAboutInserInsert.count(), 1);
    EXPECT_EQ(spyInsert.count(), 1);
    EXPECT_EQ(spyAboutRemove.count(), 0);
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyAboutReset.count(), 0);
    EXPECT_EQ(spyReset.count(), 0);
    EXPECT_EQ(spyLayout.count(), 0); // no second call for LayoutChange

    arguments = spyInsert.takeFirst();
    ASSERT_EQ(arguments.size(), 3); // QModelIndex &parent, int first, int last
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), QModelIndex());
    EXPECT_EQ(arguments.at(1).value<int>(), 1);
    EXPECT_EQ(arguments.at(2).value<int>(), 1);
}
