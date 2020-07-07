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
#include <memory>
#include "tablemodel.h"
#include "particleviewmodel.h"

//class TableModel;
//class ParticleViewModel;

class BackEnd : public QObject
{
    Q_OBJECT

public:
    explicit BackEnd(QObject* parent = nullptr);
    ~BackEnd() override;

    Q_INVOKABLE TableModel* tableModel() const;
    Q_INVOKABLE ParticleViewModel* particleViewModel() const;

private:
    struct BackEndImpl;
    std::unique_ptr<BackEndImpl> p_impl;
};

#endif // MODELINQMLCORE_BACKEND_H
