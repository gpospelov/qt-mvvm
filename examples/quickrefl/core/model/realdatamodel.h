// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef REALDATAMODEL_H
#define REALDATAMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

class DataCollectionItem;
class RealDataStruct;
class TypeUnit;
class DataGroupItem;

namespace ModelView
{
class SessionItem;
}

//! The model to store imported reflectometry data.
class RealDataModel : public ModelView::SessionModel
{
public:
    RealDataModel();
    DataCollectionItem* insertDataNode();
    void addDataToNode(DataCollectionItem* data_node, RealDataStruct data_struct);

private:
    DataGroupItem* hasTypeUnit(DataCollectionItem* data_node, TypeUnit& type_unit) const;
    DataGroupItem* addGroupItem(DataCollectionItem* data_node);
    void addDataToGroup(DataGroupItem* data_group, RealDataStruct& data_struct);

};

#endif //  REALDATAMODEL_H
