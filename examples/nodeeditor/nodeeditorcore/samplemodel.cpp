// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"

using namespace ModelView;

namespace NodeEditor {

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    registerItem<ParticleItem>();
    registerItem<TransformationItem>();

    populateModel();
}

//! Inserts new item of given type at given position.

void SampleModel::insertConnectableItem(const std::string& itemType, double xpos, double ypos)
{
    auto item = static_cast<ConnectableItem*>(insertNewItem(itemType));
    item->setX(xpos);
    item->setY(ypos);
}

//! Populates the model with

void SampleModel::populateModel()
{
    auto particleItem = insertItem<ParticleItem>();
    auto transformation = insertItem<TransformationItem>(particleItem);

    //    auto particleItem = insertItem<ParticleItem>();
    //    auto transformation = insertItem<TransformationItem>();
}

} // namespace NodeEditor
