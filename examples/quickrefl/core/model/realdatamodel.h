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
class RealDataContainer;
class DataGroupItem;
class RealDataStruct;

namespace ModelView
{
class SessionItem;
class GraphItem;
class GraphViewportItem;
} // namespace ModelView

//! The model to store imported reflectometry data.
class RealDataModel : public ModelView::SessionModel
{
public:
    RealDataModel();

    DataGroupItem* addDataToCollection(RealDataStruct data_struct, DataCollectionItem* data_node,
                                       DataGroupItem* data_group = nullptr);
    void removeAllDataFromCollection(DataCollectionItem* data_node);
    void removeDataFromCollection(std::vector<ModelView::SessionItem*> item_to_remove);
    std::vector<std::pair<std::string, std::string>> dataGroupNames() const;

    bool checkAllGroup(std::vector<ModelView::SessionItem*>& items) const;
    ModelView::GraphViewportItem* checkAllGraph(std::vector<ModelView::SessionItem*>& items) const;
    bool itemEditable(ModelView::SessionItem* item) const;
    bool dragEnabled(ModelView::SessionItem* item) const;
    bool dropEnabled(ModelView::SessionItem* item) const;
    bool dragDropItem(ModelView::SessionItem* item, ModelView::SessionItem* target, int row = -1);
    bool mergeItems(std::vector<ModelView::SessionItem*> items);

private:
    RealDataContainer* insertDataContainer();
    RealDataContainer* dataContainer() const;
    DataCollectionItem* insertDataCollection();
    DataGroupItem* insertDataGroup(DataCollectionItem* data_node);

    void addDataToGroup(DataGroupItem* data_group, RealDataStruct& data_struct);
    void removeDataFromGroup(ModelView::GraphItem* item);
};

#endif //  REALDATAMODEL_H
