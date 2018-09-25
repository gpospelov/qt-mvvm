#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include <QVariant>

class SessionItem {
public:
    SessionItem(QVariant variant);

private:
    QVariant m_data;
};

#endif
