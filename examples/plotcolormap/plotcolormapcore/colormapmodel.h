// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTCOLORMAPCORE_COLORMAPMODEL_H
#define PLOTCOLORMAPCORE_COLORMAPMODEL_H

#include "mvvm/model/sessionmodel.h"

namespace ModelView {
class ContainerItem;
}

namespace PlotColorMap {

//! Main application model to demonstrate how to plot data.

class ColorMapModel : public ModelView::SessionModel {
public:
    ColorMapModel();

    void update_data(double scale);

private:
    ModelView::ContainerItem* data_container();
    void init_model();
    void add_colormap();
};

} // namespace PlotColorMap

#endif // PLOTCOLORMAPCORE_COLORMAPMODEL_H
