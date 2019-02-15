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

class QStandardItem;

namespace ModelView
{

class SessionModel;
class SessionItem;
class ViewItem;

//! Base class for all view models to show content of  SessionModel in Qt views.

class CORE_EXPORT ViewModel : public QStandardItemModel
{
public:
    ViewModel(QObject* parent = nullptr);
    virtual ~ViewModel();

    void setSessionModel(SessionModel* model);

    std::vector<ViewItem*> findViews(SessionItem* item);

protected:
    SessionItem* rootSessionItem();
    QStandardItem* rootStandardItem();
    SessionModel* sessionModel();

    std::vector<QStandardItem*> findStandardViews(SessionItem* item);

private:
    virtual void init_view_model() = 0;
    virtual void onDataChange(SessionItem* item, int role);
    virtual void onRowInserted(SessionItem* parent, int row);
    virtual void onRowRemoved(SessionItem* parent, int row, std::string id);

    SessionModel* m_sessionModel;
};

} // namespace ModelView

#endif // VIEWMODEL_H
