// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/IView.h
//! @brief     Defines class IView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IVIEW_H
#define IVIEW_H

#include "DesignerHelper.h"
#include <QGraphicsObject>
#include <memory>

class SessionItem;

//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::IVIEW };

    IView(QGraphicsItem *parent = 0);
    virtual ~IView();

    int type() const;

    virtual void setParameterizedItem(SessionItem *item);

    virtual SessionItem *getItem();

    virtual void addView(IView *childView, int row = 0);

signals:
    void aboutToBeDeleted();

public slots:
    virtual void onChangedX();
    virtual void onChangedY();

protected:
    virtual void update_appearance();
    virtual void onPropertyChange(const QString &propertyName);
    virtual void onSiblingsChange();

    SessionItem *m_item;
};

inline int IView::type() const
{
    return TYPE;
}

inline SessionItem *IView::getItem()
{
    return m_item;
}

#endif // IVIEW_H
