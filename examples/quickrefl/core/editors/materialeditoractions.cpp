// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialeditoractions.h"

struct MaterialEditorActions::MaterialEditorActionsImpl {
};

MaterialEditorActions::MaterialEditorActions(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<MaterialEditorActionsImpl>())
{
}

MaterialEditorActions::~MaterialEditorActions() = default;
