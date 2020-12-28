// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscene.h"

namespace {
const double scene_origin_x{0.0};
const double scene_origin_y{0.0};
const QRectF default_scene_rect{QPointF{scene_origin_x, scene_origin_y}, QSizeF{800, 600}};
} // namespace

namespace NodeEditor {

GraphicsScene::GraphicsScene(SampleModel* model, QObject* parent)
    : QGraphicsScene(parent), m_model(model)
{
    setSceneRect(default_scene_rect);
}

GraphicsScene::~GraphicsScene() = default;

} // namespace NodeEditor
