// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jsondocument.h"
#include <vector>

using namespace ModelView;


struct JsonDocument::JsonDocumentImpl {
    std::vector<SessionModel*> models;

};

JsonDocument::JsonDocument(const std::initializer_list<ModelView::SessionModel*>& models)
    : p_impl(std::make_unique<JsonDocumentImpl>())
{

}

void JsonDocument::save(const std::string& file_name) const
{

}

void JsonDocument::load(const std::string& file_name)
{

}

JsonDocument::~JsonDocument() = default;
