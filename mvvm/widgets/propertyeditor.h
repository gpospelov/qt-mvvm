// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include "global.h"
#include <QWidget>
#include <memory>

class QTreeView;

namespace ModelView
{

class SessionItem;
class PropertyViewModel;
class ViewModelDelegate;

//! Editor factory for custom variants.

class CORE_EXPORT PropertyEditor : public QWidget
{
public:
    explicit PropertyEditor(QWidget* parent = nullptr);

    void setItem(SessionItem* item);

private:
    QTreeView* m_treeView;
    std::unique_ptr<PropertyViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
};

} // namespace ModelView

#endif // PROPERTYEDITOR_H
