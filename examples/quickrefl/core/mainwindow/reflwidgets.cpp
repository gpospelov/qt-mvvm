// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "reflwidgets.h"
#include "styleutils.h"
#include "SLDViewWidget.h"
#include <QVBoxLayout>

//! ---------------------------------------------------------------------------

LayerCanvas::LayerCanvas(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Layer Canvas"));
}

//! ---------------------------------------------------------------------------

SLDEditor::SLDEditor(class SLDViewWidget* sld_view, QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("SLD Editor"));
    auto layout = new QVBoxLayout;
    layout->addWidget(sld_view);
    setLayout(layout);
}

QSize SLDEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize SLDEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}


//! ---------------------------------------------------------------------------

InstrumentEditor::InstrumentEditor(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Instrument Editor"));
}
