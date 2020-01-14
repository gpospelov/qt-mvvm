// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IVIEW_H
#define IVIEW_H

#include "DesignerHelper.h"
#include <QGraphicsObject>
#include <memory>

namespace ModelView
{
class SessionItem;
}

//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
    Q_OBJECT
public:
    static constexpr qreal basic_width = 200.0;
    static constexpr qreal basic_height = 30.0;

    IView(QGraphicsItem* parent, int view_type);
    ~IView() override;

    int type() const override final { return m_view_type; }

    virtual void subscribe(ModelView::SessionItem* item);
    void unsubscribe();

    ModelView::SessionItem* getItem() const { return m_item; }

    virtual void addView(IView* childView) = 0;

    // slots:
    void onChangedX();
    void onChangedY();

signals:
    void aboutToBeDeleted();

protected:
    virtual void update_appearance();
    virtual void onPropertyChange(const std::string& propertyName);

private:
    ModelView::SessionItem* m_item;
    int m_view_type;
};

#endif // IVIEW_H
