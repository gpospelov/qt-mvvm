// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscenecontroller.h"
#include "samplemodel.h"
#include "graphicsscene.h"

namespace NodeEditor {

GraphicsSceneController::GraphicsSceneController(SampleModel* model, GraphicsScene* scene)
    : ModelView::ModelListener<SampleModel>(model)
    , m_scene(scene)
{
}

} // namespace NodeEditor


