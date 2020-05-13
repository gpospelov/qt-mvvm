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
    void addDataToNode(DataCollectionItem* data_set_item, RealDataStruct data_struct);
};

#endif //  REALDATAMODEL_H
