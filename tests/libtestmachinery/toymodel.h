// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TOYMODEL_H
#define TOYMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/itempool.h>

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();
    SampleModel(std::shared_ptr<ModelView::ItemPool> pool);
};

} // namespace ToyItems

#endif // TOYMODEL_H
