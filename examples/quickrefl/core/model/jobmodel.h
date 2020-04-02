// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView
{
class Data1DItem;
class GraphViewportItem;
} // namespace ModelView

class JobItem;

//! Contains results of quick reflectometry simulations.
class JobModel : public ModelView::SessionModel
{
public:
    JobModel();

    ModelView::Data1DItem* sld_data() const;
    ModelView::GraphViewportItem* sld_viewport() const;

    ModelView::Data1DItem* specular_data() const;
    ModelView::GraphViewportItem* specular_viewport() const;

private:
    JobItem* job_item() const;
    void init_model();
};

#endif //  JOBMODEL_H
