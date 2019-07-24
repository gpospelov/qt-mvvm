// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewAligner.h
//! @brief     Defines class SampleViewAligner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEVIEWALIGNER_H
#define SAMPLEVIEWALIGNER_H

#include <QMap>
#include <QModelIndex>
#include <QPointF>

class DesignerScene;
class IView;

namespace ModelView
{
    class SessionItem;
}


//! Makes alignment of sample droped on graphics scene.
//! Implements additional algorithm for smart alignment.
class SampleViewAligner
{
public:
    SampleViewAligner(DesignerScene *scene);

    void alignSample(ModelView::SessionItem* item, QPointF reference = QPointF(),
                     bool force_alignment = false);

    void smartAlign();
    void updateViews(const QModelIndex & parentIndex = QModelIndex());
    void updateForces();
    void calculateForces(IView *view);
    void advance();

private:
    QList<IView *> getConnectedViews(IView *view);

    DesignerScene *m_scene;
    QList<IView *> m_views; //!< list of all views which are subject to smart align
    QMap<IView *, QPointF> m_viewToPos;
};


#endif // SAMPLEVIEWALIGNER_H

