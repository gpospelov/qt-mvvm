// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LAYERTABLEWIDGET_H
#define LAYERTABLEWIDGET_H

#include "mvvm_global.h"
#include <QWidget>
#include <memory>

class QTreeView;
class CustomModelDelegate;
class ApplicationModels;

namespace ModelView
{
class AbstractViewModel;
class SessionItem;
} // namespace ModelView

/*!
@class LayerTableWidget
@brief Shows content of multi layer in a tree view in special "flat" form.
*/

class CORE_EXPORT LayerTableWidget : public QWidget
{
public:
    explicit LayerTableWidget(ApplicationModels* models, QWidget* parent = nullptr);
    ~LayerTableWidget() override;

private:
    std::unique_ptr<ModelView::AbstractViewModel> m_view_model;
    std::unique_ptr<CustomModelDelegate> m_delegate;
    QTreeView* m_tree_view;
};

#endif // LAYERTABLEWIDGET_H
