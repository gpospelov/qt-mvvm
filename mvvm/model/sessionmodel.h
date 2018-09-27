// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QVariant>
class SessionItem;

class SessionModel
{
public:
    SessionModel();
    virtual ~SessionModel();

    SessionItem* insertNewItem(SessionItem* parent = nullptr, int row = -1);

    SessionItem* rootItem() const;

    QVariant data(SessionItem* item) const;

    bool setData(SessionItem* item, const QVariant& value);

private:
    void createRootItem();

    SessionItem* m_root_item;
};

#endif
