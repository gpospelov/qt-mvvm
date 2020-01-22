// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "reflwidgets.h"

LayerEditor::LayerEditor(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(QString("Layer Editor"));
}

//! ---------------------------------------------------------------------------

LayerCanvas::LayerCanvas(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(QString("Layer Canvas"));
}

//! ---------------------------------------------------------------------------

SLDEditor::SLDEditor(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(QString("SLD Editor"));
}

//! ---------------------------------------------------------------------------

ReflPlotWidget::ReflPlotWidget(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(QString("Reflectivity plot"));
}


//! ---------------------------------------------------------------------------

InstrumentEditor::InstrumentEditor(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(QString("Instrument Editor"));
}
