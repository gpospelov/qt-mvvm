// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "customplotsceneadapter.h"
#include "qcustomplot.h"


using namespace ModelView;

CustomPlotSceneAdapter::CustomPlotSceneAdapter(QCustomPlot* custom_plot)
{

}

CustomPlotSceneAdapter::~CustomPlotSceneAdapter()
{
}

double CustomPlotSceneAdapter::toSceneX(double customplot_x) const
{
    return customplot_x;
}

double CustomPlotSceneAdapter::toSceneY(double customplot_y) const
{
    return customplot_y;
}

double CustomPlotSceneAdapter::fromSceneX(double scene_x) const
{
    return scene_x;
}

double CustomPlotSceneAdapter::fromSceneY(double scene_y) const
{
    return scene_y;
}
