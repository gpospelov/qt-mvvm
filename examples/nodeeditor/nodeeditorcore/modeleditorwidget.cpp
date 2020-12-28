// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "graphicsscene.h"
#include "graphicsview.h"
#include "samplemodel.h"
#include <QHBoxLayout>

using namespace ModelView;

namespace NodeEditor {

ModelEditorWidget::ModelEditorWidget(SampleModel*, QWidget* parent)
    : QWidget(parent)
    , m_graphicsScene(new GraphicsScene(this))
    , m_graphicsView(new GraphicsView(m_graphicsScene, this))
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_graphicsView);
}

void ModelEditorWidget::setModel(SampleModel*) {}

} // namespace NodeEditor
