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
#include <QObject>
#include <QStackedWidget>

class DesignerScene;
class DesignerWidgetFactory;
class InstrumentModel;
class SampleModel;
class FilterPropertyProxy;
class ApplicationModels;

//! sample designer interface
class SampleDesignerInterface : public QObject
{
    Q_OBJECT

public:
    SampleDesignerInterface(QObject *parent = 0) : QObject(parent){}
    virtual ~SampleDesignerInterface() { }

//    virtual DesignerScene *getScene() const = 0;
//    virtual DesignerView *getView() const = 0;

};


//! sample designer provide central window with graphic scene to drag and drop
class SampleDesigner: public SampleDesignerInterface
{
    Q_OBJECT

public:
    SampleDesigner(QWidget *parent = 0);
    virtual ~SampleDesigner();

    DesignerScene *getScene() const { return m_designerScene; }
    DesignerView *getView() const { return m_designerView; }

    QWidget *getCentralWidget() { return m_designerView; }

    void setModels(ApplicationModels* models);
    void setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy);

private:
    DesignerScene *m_designerScene; //! scene which holds all objects
    DesignerView *m_designerView;   //! graphical representation of scene with object
};



#endif // SAMPLEDESIGNER_H
