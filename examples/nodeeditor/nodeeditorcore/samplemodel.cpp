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
    registerItem<ParticleLayoutItem>();
    registerItem<SphereItem>();
    registerItem<CylinderItem>();
    registerItem<TransformationItem>();
    registerItem<LatticeItem>();

    populateModel();

    setUndoRedoEnabled(true);
}

//! Inserts new item of given type at given position.

void SampleModel::insertConnectableItem(const std::string& itemType, double xpos, double ypos)
{
    if (auto item = dynamic_cast<ConnectableItem*>(insertNewItem(itemType)); item) {
        item->setX(xpos);
        item->setY(ypos);
    }
}

//! Populates the model with an exemplary hierarchical structure representing an initial node editor
//! content.

void SampleModel::populateModel()
{
    auto layout = insertItem<ParticleLayoutItem>();
    layout->setPos(490, 30);

    auto sphere = insertItem<SphereItem>(layout, {ParticleLayoutItem::T_PARTICLE, -1});
    sphere->setPos(250, 00);
    auto cylinder = insertItem<CylinderItem>(layout, {ParticleLayoutItem::T_PARTICLE, -1});
    cylinder->setPos(250, 200);
    auto transformation = insertItem<TransformationItem>(cylinder);
    transformation->setPos(60, 200);

    auto lattice = insertItem<LatticeItem>(layout, {ParticleLayoutItem::T_LATTICE, -1});
    lattice->setPos(250, 400);
}

} // namespace NodeEditor
