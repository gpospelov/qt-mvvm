// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleDesigner.h
//! @brief     Defines class SampleDesigner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEDESIGNER_H
#define SAMPLEDESIGNER_H

#include "DesignerScene.h"
#include "DesignerView.h"

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
    DesignerView& getView() { return m_designerView; }

    void setSelectionModel(QItemSelectionModel* model, FilterPropertyProxy* proxy);

private:
    DesignerScene m_designerScene; //! scene which holds all objects
    DesignerView m_designerView;   //! graphical representation of scene with object
};



#endif // SAMPLEDESIGNER_H
