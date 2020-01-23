// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALSELECTIONMODEL_H
#define MATERIALSELECTIONMODEL_H

#include <QItemSelectionModel>

namespace ModelView {
class AbstractViewModel;
}

class MaterialEditorActions;

//! Custom selection model for material view model (AbstractViewModel).
//! Reports clients about selected MaterialItem in material table and hides
//! QModelIndex related machinery.

class MaterialSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    MaterialSelectionModel(ModelView::AbstractViewModel* view_model, QObject *parent = nullptr);
    ~MaterialSelectionModel() = default;
};

#endif // MATERIALSELECTIONMODEL_H
