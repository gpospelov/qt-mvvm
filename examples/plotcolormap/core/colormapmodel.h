// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COLORMAPMODEL_H
#define COLORMAPMODEL_H

#include "sessionmodel.h"

namespace ModelView
{
class ContainerItem;
}

/*!
@class ColorMapModel
@brief Main application model to demonstrate how to plot data.
*/

class ColorMapModel : public ModelView::SessionModel
{
public:
    ColorMapModel();

    void add_colormap();

private:
    ModelView::ContainerItem* data_container();
    void init_model();
};

#endif // COLORMAPMODEL_H
