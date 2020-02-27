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
#include <vector>

namespace ModelView
{
class ViewModel;
} // namespace ModelView

class MaterialEditorActions;
class MaterialBaseItem;

//! Custom selection model for material view model (AbstractViewModel).
//! Reports clients about selected MaterialItem in material table and hides
//! QModelIndex related machinery.

class MaterialSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    MaterialSelectionModel(ModelView::ViewModel* view_model, QObject* parent = nullptr);
    ~MaterialSelectionModel() = default;

    std::vector<MaterialBaseItem*> selectedMaterials() const;
};

#endif // MATERIALSELECTIONMODEL_H
