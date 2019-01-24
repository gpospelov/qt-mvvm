// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "global.h"
#include <QStandardItemModel>

namespace ModelView {

class SessionModel;

//! The view model to show content of our SessionModel in Qt views.

class CORE_EXPORT ViewModel : public QStandardItemModel {
public:
    ViewModel(QObject* parent = nullptr);

    void setSessionModel(SessionModel* model);

private:
    SessionModel* m_sessionModel;
};

}  // namespace ModelView

#endif // VIEWMODEL_H
