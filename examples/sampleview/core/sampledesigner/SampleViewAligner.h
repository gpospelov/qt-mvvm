// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
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
    SampleViewAligner(DesignerScene* scene);

    void alignSample(ModelView::SessionItem* item, QPointF reference = QPointF(),
                     bool force_alignment = false);

    void smartAlign();
    void updateViews(const QModelIndex& parentIndex = QModelIndex());
    void updateForces();
    void calculateForces(IView* view);
    void advance();

private:
    QList<IView*> getConnectedViews(IView* view);

    DesignerScene* m_scene;
    QList<IView*> m_views; //!< list of all views which are subject to smart align
    QMap<IView*, QPointF> m_viewToPos;
};

#endif // SAMPLEVIEWALIGNER_H
