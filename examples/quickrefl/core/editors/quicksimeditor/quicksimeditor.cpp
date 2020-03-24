// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "quicksimeditor.h"
#include "styleutils.h"
#include <QVBoxLayout>
#include <mvvm/plotting/graphcanvas.h>

QuickSimEditor::QuickSimEditor(QWidget* parent)
    : QWidget(parent), graph_canvas(new ModelView::GraphCanvas)
{
    setWindowTitle(QString("Reflectivity plot"));
    auto layout = new QVBoxLayout;
    layout->addWidget(graph_canvas);
    setLayout(layout);
}

QSize QuickSimEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize QuickSimEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}
