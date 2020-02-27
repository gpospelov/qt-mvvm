// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_ABSTRACTVIEWMODEL_H
#define MVVM_VIEWMODEL_ABSTRACTVIEWMODEL_H

//#include <QStandardItemModel>
//#include <memory>
//#include <mvvm/core/export.h>

#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{

class CORE_EXPORT AbstractViewModel : public ViewModel
{
public:
    AbstractViewModel(std::unique_ptr<RefViewModelController> controller,
                      QObject* parent = nullptr);
    ~AbstractViewModel();


};


//class SessionModel;
//class SessionItem;
//class ViewItem;
//class AbstractViewModelController;

///*!
//@class AbstractViewModel
//@brief Base class for all view models to show content of SessionModel in Qt views.

//AbstractViewModel is just a QStandardItemModel connected with SessionModel. On every
//insert/remove/data change in original SessionModel, AbstractViewModel gets notified
//and updates its content.

//Important details:

//AbstractViewModel is made of ViewItems, where each ViewItem represents some concrete data role
//of SessionItem.

//AbstractViewModel is not intended for insert/remove through QStandardItemModel interface.
//Everything should be done through SessionModel.

//AbstractViewModel uses simplified mechanism of syncronization with SessionModel.
//Every time some SessionItem is removed from SessionModel, in ViewModel we remove corersponding
//ViewItem _together_ with all its siblings, and then regenerate corresponding parent's branch.
//*/

//class CORE_EXPORT AbstractViewModel : public QStandardItemModel
//{
//public:
//    friend class AbstractViewModelController; // FIXME remove friendship
//    AbstractViewModel(std::unique_ptr<AbstractViewModelController> controller,
//                      QObject* parent = nullptr);
//    virtual ~AbstractViewModel();

//    void setSessionModel(SessionModel* model);

//    void setRootSessionItem(SessionItem* item);

//    void update();

//    SessionItem* sessionItemFromIndex(const QModelIndex& index) const;

//    QModelIndexList indexOfSessionItem(const SessionItem* item) const;

//    ViewItem* viewItemFromIndex(const QModelIndex& index) const;

//protected:
//    QStandardItem* rootViewItem() const;
//    SessionModel* sessionModel() const;
//    SessionItem* rootSessionItem() const;

//private:
//    // FIXME remove one of methods
//    std::vector<QStandardItem*> findStandardViews(const SessionItem* item) const;
//    std::vector<ViewItem*> findViews(const SessionItem* item) const;

//    std::unique_ptr<AbstractViewModelController> m_controller;
//};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_ABSTRACTVIEWMODEL_H
