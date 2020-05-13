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
#include <mvvm/standarditems/graphviewportitem.h>
#include <string>

namespace ModelView
{
    class ContainerItem;
}

// ----------------------------------------------------------------
//! Convenience data transfer header information
struct TypeUnit
{
    std::string type;
    std::pair<std::string,std::string> unit_pair;
};

// ----------------------------------------------------------------
//! Convenience data transfer structure
struct RealDataStruct 
{
public:
    std::string type;
    std::string name;

    std::vector<double> axis;
    std::string axis_name;
    std::string axis_unit;

    std::vector<double> data;
    std::string data_name;
    std::string data_unit;
};

// ----------------------------------------------------------------
//! This will hold the data for one particular type (and pair of intensity and axis units) 
class DataGroupItem : public ModelView::GraphViewportItem
{
public:
    static inline const std::string P_DATA = "P_DATA";
    DataGroupItem(TypeUnit &type_unit);
    void insertData(RealDataStruct& data_struct);
    int itemCount() const;

};

// ----------------------------------------------------------------
//! This will hold all data grouped by types
class DataCollectionItem : public ModelView::CompoundItem
{
public:
    DataCollectionItem();
    void insertData(RealDataStruct& data_struct);

private:
    DataGroupItem* hasTypeUnit(TypeUnit& type_unit) const;
    DataGroupItem* addTypeUnit(TypeUnit& type_unit);

private:
    const std::string data_group_tag = "data_groups";
};

#endif // DATASETITEM_H
