// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_TOPITEMSVIEWMODEL_H
#define MVVM_TOPITEMSVIEWMODEL_H

#include "defaultviewmodel.h"
#include <vector>

namespace ModelView {

//! View model to show content of SessionModel in Qt widgets.
//! Only top level items are shown, all property items are filtered out.

class CORE_EXPORT TopItemsViewModel : public DefaultViewModel {
public:
    TopItemsViewModel(SessionModel* model, QObject* parent = nullptr);

protected:
    std::vector<SessionItem*> item_children(const SessionItem* item) const override;

};

}  // namespace ModelView

#endif // MVVM_TOPITEMSVIEWMODEL_H
