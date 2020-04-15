// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "reflwidgets.h"
#include "sldeditor.h"
#include "styleutils.h"
#include <QVBoxLayout>

//! ---------------------------------------------------------------------------

LayerCanvas::LayerCanvas(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Layer Canvas"));
}

//! ---------------------------------------------------------------------------

InstrumentEditor::InstrumentEditor(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Instrument Editor"));
}
