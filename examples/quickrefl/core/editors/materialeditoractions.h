// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALEDITORACTIONS_H
#define MATERIALEDITORACTIONS_H

#include <QObject>
#include <memory>

//! Handles user actions applied to material table.

class MaterialEditorActions : public QObject
{
    Q_OBJECT
public:
    MaterialEditorActions(QObject* parent = nullptr);
    ~MaterialEditorActions();

private:
    struct MaterialEditorActionsImpl;
    std::unique_ptr<MaterialEditorActionsImpl> p_impl;
};

#endif // MATERIALEDITORACTIONS_H
