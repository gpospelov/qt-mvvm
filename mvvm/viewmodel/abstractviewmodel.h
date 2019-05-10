// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ABSTRACTVIEWMODEL_H
#define MVVM_ABSTRACTVIEWMODEL_H

#include "mvvm_global.h"
#include <QStandardItemModel>

class QStandardItem;

namespace ModelView
{

class SessionModel;
class SessionItem;
class ViewItem;

//! Base class for all view models to show content of  SessionModel in Qt views.

class CORE_EXPORT AbstractViewModel : public QStandardItemModel
{
public:
    AbstractViewModel(QObject* parent = nullptr);
    virtual ~AbstractViewModel();

    void setSessionModel(SessionModel* model);

    std::vector<ViewItem*> findViews(const SessionItem* item) const;

    SessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const SessionItem* item) const;

    void setRootSessionItem(SessionItem* item);

protected:
    SessionItem* rootSessionItem() const;
    QStandardItem* rootStandardItem() const;

    std::vector<QStandardItem*> findStandardViews(const SessionItem* item) const;

protected:
    virtual void init_view_model() = 0;
    virtual void onDataChange(SessionItem* item, int role);
    virtual void onRowInserted(SessionItem* parent, std::string tag, int row);
    virtual void onRowRemoved(SessionItem* parent, std::string tag, int row);
    virtual void onModelReset();

    SessionModel* m_sessionModel;
    SessionItem* m_rootItem;
};

} // namespace ModelView

#endif // MVVM_ABSTRACTVIEWMODEL_H
