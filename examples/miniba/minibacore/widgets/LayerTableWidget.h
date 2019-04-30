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

class QTableView;
class CustomModelDelegate;
class ApplicationModels;

namespace ModelView
{
class AbstractViewModel;
class SessionItem;
} // namespace ModelView

class CORE_EXPORT LayerTableWidget : public QWidget
{
public:
    explicit LayerTableWidget(ApplicationModels* models, QWidget* parent = nullptr);
    ~LayerTableWidget();

    void setItem(ModelView::SessionItem* container);

private:
    QTableView* m_view;
    std::unique_ptr<ModelView::AbstractViewModel> m_viewModel;
    std::unique_ptr<CustomModelDelegate> m_delegate;
};

#endif // LAYERTABLEWIDGET_H
