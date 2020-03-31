// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef JOBITEM_H
#define JOBITEM_H

#include <mvvm/model/compounditem.h>

namespace ModelView {
class Data1DItem;
class GraphViewportItem;
}

//! Holds results of toy reflectivity simulation.

class JobItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_SLD_DATA = "P_SLD_DATA";
    static inline const std::string P_SLD_VIEWPORT = "P_SLD_VIEWPORT";
    static inline const std::string P_SPECULAR_DATA = "P_SPECULAR_DATA";
    static inline const std::string P_SPECULAR_VIEWPORT = "P_SPECULAR_VIEWPORT";

    JobItem();

    ModelView::Data1DItem* sld_data() const;
    ModelView::GraphViewportItem* sld_viewport() const;

    ModelView::Data1DItem* specular_data() const;
    ModelView::GraphViewportItem* specular_viewport() const;

private:
    void setup_graph(const std::string& data_tag, const std::string& viewport_tag);
};

#endif // JOBITEM_H
