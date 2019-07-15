// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALTABLEVIEWMODEL_H
#define MATERIALTABLEVIEWMODEL_H

#include "abstractviewmodel.h"

namespace ModelView
{
class SessionItem;
class SessionModel;
} // namespace ModelView

class MaterialBaseItem;

/*!
@class MaterialTableViewModel
@brief View model to display content of MaterialModel in table like views.
*/

class MaterialTableViewModel : public ModelView::AbstractViewModel
{
public:
    MaterialTableViewModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);
    void setMaterialType(const std::string& material_type);
    std::string materialType() const { return m_material_type; }

    MaterialBaseItem* sessionItemFromRow(int row) const;

private:
    std::string m_material_type; //!< material type of the shown items
};

#endif //  MATERIALTABLEVIEWMODEL_H
