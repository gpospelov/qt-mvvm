// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef IVIEW_H
#define IVIEW_H

#include "DesignerHelper.h"
#include <QGraphicsObject>
#include <memory>

namespace ModelView {
    class SessionItem;
}

//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::IVIEW };
    static constexpr qreal basic_width = 200.0;
    static constexpr qreal basic_height = 30.0;

    IView(QGraphicsItem *parent = nullptr);
    ~IView() override;

    int type() const override { return TYPE; }

    virtual void subscribe(ModelView::SessionItem* item);
    void unsubscribe();

    ModelView::SessionItem* getItem() { return m_item; }

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
};

#endif // IVIEW_H
