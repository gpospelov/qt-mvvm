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

//! ---------------------------------------------------------------------------

LayerCanvas::LayerCanvas(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Layer Canvas"));
}

//! ---------------------------------------------------------------------------

SLDEditor::SLDEditor(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("SLD Editor"));
}

//! ---------------------------------------------------------------------------

ReflPlotWidget::ReflPlotWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Reflectivity plot"));
}

QSize ReflPlotWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize ReflPlotWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

//! ---------------------------------------------------------------------------

InstrumentEditor::InstrumentEditor(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Instrument Editor"));
}
