// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "samplemodel.h"

using namespace ModelView;

namespace NodeEditor {

ModelEditorWidget::ModelEditorWidget(SampleModel*, QWidget* parent) : QWidget(parent) {}

void ModelEditorWidget::setModel(SampleModel*) {}

} // namespace NodeEditor
