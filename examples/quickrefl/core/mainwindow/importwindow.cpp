// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importwindow.h"
#include "applicationmodels.h"
#include "importdataeditor.h"
#include <QVBoxLayout>

ImportWindow::ImportWindow(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), models(models)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new ImportDataEditor(models->realDataModel()));
}
