// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PROPERTYEDITOR_H
#define MVVM_PROPERTYEDITOR_H

#include <mvvm/model/mvvm_export.h>
#include <QWidget>
#include <memory>

class QTreeView;

namespace ModelView
{

class SessionItem;
class AbstractViewModel;
class ViewModelDelegate;

//! Standard property editor for SessionItem.
//! Shows property items, hides top level items and GroupItem internals.

class CORE_EXPORT PropertyEditor : public QWidget
{
public:
    explicit PropertyEditor(QWidget* parent = nullptr);
	~PropertyEditor() override;

    void setItem(SessionItem* item);

    QTreeView* treeView();

private:
    QTreeView* m_treeView;
    std::unique_ptr<AbstractViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
};

} // namespace ModelView

#endif // MVVM_PROPERTYEDITOR_H
