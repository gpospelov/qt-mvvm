// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEDESIGNER_H
#define SAMPLEDESIGNER_H

#include "DesignerScene.h"

class DesignerView;
class SampleModel;
class FilterPropertyProxy;
class ApplicationModels;
class QItemSelectionModel;

//! sample designer provide central window with graphic scene to drag and drop
class SampleViewController
{
public:
    SampleViewController(ApplicationModels* models);
    ~SampleViewController();

    DesignerScene& getScene() { return m_designerScene; }

    DesignerView* createDesignerView();

    void setSelectionModel(QItemSelectionModel* model, FilterPropertyProxy* proxy);

private:
    DesignerScene m_designerScene; //! scene which holds all objects
};



#endif // SAMPLEDESIGNER_H
