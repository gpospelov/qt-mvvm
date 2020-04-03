// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importdataeditor.h"
#include <QLabel>
#include <QVBoxLayout>

ImportDataEditor::ImportDataEditor(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Hello World!"));
}
