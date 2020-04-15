// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SLDEDITORACTIONS_H
#define SLDEDITORACTIONS_H

#include <QObject>
#include <memory>

class SLDElementModel;

//! Handles user actions applied to SLDEditor.
//! Belongs to SLDEditor.

class SLDEditorActions : public QObject
{
    Q_OBJECT
public:
    SLDEditorActions(SLDElementModel* sld_element_model, QObject* parent = nullptr);
    ~SLDEditorActions();

private:
    struct SLDEditorActionsImpl;
    std::unique_ptr<SLDEditorActionsImpl> p_impl;
};

#endif // SLDEDITORACTIONS_H
