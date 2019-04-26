// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALTABLEMODEL_H
#define MATERIALTABLEMODEL_H

#include "defaultviewmodel.h"
#include "mvvm_global.h"

namespace ModelView
{
class SessionModel;
class SessionItem;
} // namespace ModelView

//! View model to display content of MaterialModel in table like views.

class CORE_EXPORT MaterialTableModel : public ModelView::DefaultViewModel
{
public:
    MaterialTableModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);

protected:
    std::vector<ModelView::SessionItem*>
    item_children(const ModelView::SessionItem* item) const override;
};

#endif //  MATERIALTABLEMODEL_H
