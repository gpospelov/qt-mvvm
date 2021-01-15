// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscenecontroller.h"
#include "graphicsscene.h"
#include "mvvm/model/sessionitem.h"
#include "sampleitems.h"
#include "samplemodel.h"

using namespace ModelView;

namespace NodeEditor {

GraphicsSceneController::GraphicsSceneController(SampleModel* model, GraphicsScene* scene)
    : ModelView::ModelListener<SampleModel>(model), m_scene(scene)
{
    setOnItemInserted([this](auto, auto) { m_scene->updateScene(); });

    auto on_about_to_remove = [this](SessionItem* parent, const TagRow& tagrow) {
        auto child = parent->getItem(tagrow.tag, tagrow.row);
        m_scene->removeViewForItem(dynamic_cast<ConnectableItem*>(child));
    };
    setOnAboutToRemoveItem(on_about_to_remove);
}

} // namespace NodeEditor
