// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELINQMLCORE_BACKEND_H
#define MODELINQMLCORE_BACKEND_H

#include <QObject>
#include <QString>
#include <qqml.h>

class TableModel;

class BackEnd : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit BackEnd(QObject *parent = nullptr);

    Q_INVOKABLE TableModel* tableModel() const;

private:
    TableModel* m_tableModel{nullptr};
};

#endif // MODELINQMLCORE_BACKEND_H



