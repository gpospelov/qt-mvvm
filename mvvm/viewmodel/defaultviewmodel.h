// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DEFAULTVIEWMODEL_H
#define MVVM_DEFAULTVIEWMODEL_H

#include "abstractviewmodel.h"

namespace ModelView
{

class CORE_EXPORT DefaultViewModel : public AbstractViewModel
{
public:
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_DEFAULTVIEWMODEL_H
