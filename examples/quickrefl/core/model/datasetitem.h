// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DATASETITEM_H
#define DATASETITEM_H

#include <mvvm/model/compounditem.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <string>

namespace ModelView
{
class Data1DItem;
}

class TypeUnit;
class RealDataStruct;

// ----------------------------------------------------------------
//! This will hold the data for one particular type (and pair of intensity and axis units)
class DataGroupItem : public ModelView::GraphViewportItem
{
public:
    DataGroupItem();
    int itemCount() const;
};

// ----------------------------------------------------------------
//! This will hold all data grouped by types
class DataCollectionItem : public ModelView::CompoundItem
{
public:
    DataCollectionItem();
    void insertData(RealDataStruct& data_struct);
    DataGroupItem* getDataGroup(const std::string tag) const;

    inline static const std::string data_group_tag = "data_groups";
};

// ----------------------------------------------------------------
//! This will hold all the data1Ditems unordered
class RealDataContainer : public ModelView::ContainerItem
{
public:
    RealDataContainer();
};

#endif // DATASETITEM_H
