// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
#define MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H

#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show the content of SessionModel in Qt widgets. Represents two-column tree with
//! label/data, with one-to-one child/parent correspondence as in the original SessionModel. All
//! items (including hidden) are shown.

class MVVM_VIEWMODEL_EXPORT DefaultViewModel : public ViewModel {
    Q_OBJECT

public:
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
