// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewAligner.cpp
//! @brief     Implements class SampleViewAligner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleViewAligner.h"
#include "DesignerScene.h"
#include "IView.h"
#include "SampleModel.h"
#include "item_constants.h"
#include <mvvm/model/sessionitem.h>
#include <QModelIndex>

using namespace ModelView;

SampleViewAligner::SampleViewAligner(DesignerScene *scene)
    : m_scene(scene)
{
    Q_ASSERT(m_scene);
}


//! Spring based implified algorithm for smart alignment
void SampleViewAligner::smartAlign()
{
    m_views.clear();
    updateViews();
    updateForces();
    advance();
}


//! Forms list of all views which are subject for smart alignment (i.e. views
//! which do not have parent view)
void SampleViewAligner::updateViews(const QModelIndex & parentIndex)
{
    /*SampleModel *sampleModel = m_scene->getSampleModel();
    for( int i_row = 0; i_row < sampleModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = sampleModel->index( i_row, 0, parentIndex );
         IView *view = getViewForIndex(itemIndex);
         if(view && !view->parentObject()) {
            m_views.append(view);
         }
         updateViews( itemIndex);
     }*/
}


//! Calculates forces acting on all views for smart alignment
void SampleViewAligner::updateForces()
{
    m_viewToPos.clear();
    for(IView *view : m_views) {
        calculateForces(view);
    }
}


//! Calculates forces acting on single view (simplified force directed spring algorithm)
//! and deduce new position of views.
void SampleViewAligner::calculateForces(IView *view)
{
    qreal xvel = 0;
    qreal yvel = 0;

    // repulsive forces which are pushing items away

    double weight1(200.0);
    for(IView *other : m_views) {
        QPointF vec = view->mapToItem(other, other->boundingRect().center());
        qreal dx = view->boundingRect().center().x() - vec.x();
        qreal dy = view->boundingRect().center().y() - vec.y();
        double l = (dx * dx + dy * dy);
        if (l > 0) {
            xvel -= (dx * weight1) / l;
            yvel -= (dy * weight1) / l;
        }
    }
    // attracting forces which are pulling views together
    double weight2(100.0);
    for(IView *other : getConnectedViews(view)) {
        QPointF vec = view->mapToItem(other, other->boundingRect().center());
        qreal dx = view->boundingRect().center().x() - vec.x();
        qreal dy = view->boundingRect().center().y() - vec.y();
        xvel += dx/weight2;
        yvel += dy/weight2;
    }
    QPointF newPos = view->pos() + QPointF(xvel, yvel);
    m_viewToPos[view] = newPos;
}


//! Applies calculated positions to views
void SampleViewAligner::advance()
{
    for(IView *view : m_views) {
        view->setPos(m_viewToPos[view]);
    }
}


//! Returns list of views connected with given view for the subsequent force calculation.
//!
//! Weirdness of given function is due to the fact, that, for example, ParticleLayout view
//! should interact not with Layer view, but with its parent - MultiLayer view.
//! Similarly, MultiLayer is not interacting with its Layers, but directly with the ParticleLayout.
QList<IView *> SampleViewAligner::getConnectedViews(IView *view)
{
    QList<IView *> result;

    SessionItem *itemOfView = view->getItem();

    QList<SessionItem *> connected_items;

    if(itemOfView->parent()->modelType() == ::Constants::LayerType) {
        // e.g. we are dealing here with ParticleLayout, so we will use directly MultiLayer to interact with
        connected_items.append(itemOfView->parent()->parent());
    } else {
        connected_items.append(itemOfView->parent());
    }
    if(itemOfView->modelType() == ::Constants::MultiLayerType) {
        // MultiLayer will not interact with its Layers, but with they children, e.g. with ParticleLayouts
        for(auto child : itemOfView->children()) {
            auto grand_children = child->children();
            std::for_each(grand_children.begin(), grand_children.end(),
                [&connected_items](auto child) { connected_items.append(child); });
        }
    } else {
        auto children = itemOfView->children();
        std::for_each(children.begin(), children.end(),
            [&connected_items](auto child) { connected_items.append(child); });
    }
    for(auto item : connected_items) {
        IView *view = m_scene->getViewForItem(item);
        if(view) {
            result.append(view);
        }
    }
    return result;
}


//! Aligns sample starting from reference point.
//! If force_alignment=false, view's position will be changed only if it has Null coordinate,
//! if force_alignment=true the position will be changed anyway.
//! Position of View which has parent item (like Layer) will remain unchainged.
void SampleViewAligner::alignSample(SessionItem* item, QPointF reference, bool force_alignment)
{
    if (!item)
        return;

    if (IView* view = m_scene->getViewForItem(item)) {
        if ((force_alignment || view->pos().isNull()) && !view->parentObject())
            view->setPos(reference);

        reference = view->parentObject() ? view->mapToScene(view->pos()) : view->pos();
    }

    int child_counter = 0;
    for (auto child: item->children()) {
        IView* view = m_scene->getViewForItem(child);
        if (!view)
            continue;
        QPointF child_reference = reference + QPointF(-150, 150*child_counter++);
        alignSample(child, child_reference, force_alignment);
    }
}
