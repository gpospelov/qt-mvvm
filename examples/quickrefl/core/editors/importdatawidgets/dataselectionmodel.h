// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DATASELECTIONMODEL_H
#define DATASELECTIONMODEL_H

#include <QItemSelectionModel>
#include <vector>

namespace ModelView
{
class ViewModel;
class SessionItem;
} // namespace ModelView

//! Custom selection model for data view model (AbstractViewModel).

class DataSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    DataSelectionModel(ModelView::ViewModel* view_model, QObject* parent = nullptr);
    ~DataSelectionModel() = default;

    void selectItem(ModelView::SessionItem* item);
    void selectItems(std::vector<ModelView::SessionItem*> items);

    std::vector<ModelView::SessionItem*> selectedItems() const;

    const ModelView::ViewModel* viewModel() const;
};

#endif // DATASELECTIONMODEL_H
