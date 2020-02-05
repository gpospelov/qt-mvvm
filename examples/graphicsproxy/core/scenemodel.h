// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_SCENEMODEL_H
#define GRAPHICSPROXY_SCENEMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView
{
class ContainerItem;
}

//! Main application model with data for graphics scene.

class SceneModel : public ModelView::SessionModel
{
public:
    SceneModel();

    void update_data(double scale);

private:
    ModelView::ContainerItem* data_container();
    void init_model();
    void add_colormap();
};

#endif // GRAPHICSPROXY_SCENEMODEL_H
