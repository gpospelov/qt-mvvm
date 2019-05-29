// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LAYERTABLEMODEL_H
#define LAYERTABLEMODEL_H

#include "defaultviewmodel.h"
#include "mvvm_global.h"

namespace ModelView
{
class SessionModel;
class SessionItem;
} // namespace ModelView

//! View model to display content of MultiLayerItem in table like views.

class CORE_EXPORT LayerTableModel : public ModelView::DefaultViewModel
{
public:
    LayerTableModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);
};

#endif //  LAYERTABLEMODEL_H
