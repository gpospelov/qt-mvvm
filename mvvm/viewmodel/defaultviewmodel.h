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
#include <vector>

namespace ModelView
{

class ViewItem;


class CORE_EXPORT DefaultViewModel : public AbstractViewModel
{
public:
    DefaultViewModel(QObject* parent = nullptr);
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);

protected:
    void init_view_model() override;
    void onDataChange(SessionItem* item, int role) override;
    void onRowInserted(SessionItem* parent, std::string tag, int row) override;
    void onRowRemoved(SessionItem* parent, std::string tag, int row) override;

    void generate_children_views(SessionItem* parent);

    void update_model();
    virtual void iterate(const SessionItem* item, QStandardItem* parent);
    virtual std::vector<SessionItem*> item_children(const SessionItem* item) const;

};

} // namespace ModelView

#endif // MVVM_DEFAULTVIEWMODEL_H
