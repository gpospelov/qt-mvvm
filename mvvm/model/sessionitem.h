// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include <QVariant>
#include <vector>
#include "mvvm_types.h"

class SessionModel;

class SessionItem {
    friend class SessionModel;
public:
    SessionItem(const model_type& modelType = {});
    virtual ~SessionItem();

    model_type modelType() const;

    bool setData(QVariant data);

    QVariant data() const;

    SessionModel* model() const;

    SessionItem* parent() const;

    int childrenCount() const;

    bool insertItem(int row, SessionItem* item);

    std::vector<SessionItem*> children() const;

    SessionItem* childAt(int row) const;

    int rowOfChild(SessionItem* child) const;

    SessionItem* takeRow(int row);

private:
    void setParent(SessionItem* parent);
    void setModel(SessionModel* model);
    void childDeleted(SessionItem* child);

    QVariant m_data;
    SessionItem* m_parent;
    SessionModel* m_model;
    std::vector<SessionItem*> m_children;
    model_type m_modelType;
};

#endif
