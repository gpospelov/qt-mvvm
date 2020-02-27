// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALTABLEWIDGET_H
#define MATERIALTABLEWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class ViewModel;
class ViewModelDelegate;
} // namespace ModelView

class QTableView;
class MaterialModel;
class QStyledItemDelegate;

/*!
@class MaterialTableWidget
@brief Shows content of material container in table-like view.
*/

class MaterialTableWidget : public QWidget
{
public:
    explicit MaterialTableWidget(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialTableWidget() override;

private:
    QTableView* m_material_table;
    std::unique_ptr<ModelView::ViewModel> view_model;
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // MATERIALTABLEWIDGET_H
