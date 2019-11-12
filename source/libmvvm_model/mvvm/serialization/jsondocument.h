// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONDOCUMENT_H
#define MVVM_SERIALIZATION_JSONDOCUMENT_H

#include <initializer_list>
#include <memory>
#include <mvvm/core/modeldocumentinterface.h>

namespace ModelView
{

class SessionModel;

/*!
@class JsonDocument
@brief Saves and restores list of SessionModel's to/from disk using json format.
*/

class CORE_EXPORT JsonDocument : public ModelDocumentInterface
{
public:
    JsonDocument(const std::initializer_list<SessionModel*>& models);
    ~JsonDocument() override;

    void save(const std::string& file_name) const override;
    void load(const std::string& file_name) override;

private:
    struct JsonDocumentImpl;
    std::unique_ptr<JsonDocumentImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_ITEMBACKUPSTRATEGY_H
