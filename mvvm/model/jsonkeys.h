// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONKEYS_H
#define JSONKEYS_H

#include <QString>

//! @file Contains collection of constants that represent json keys.

namespace json
{

const QString variantTypeKey = "type";
const QString variantValueKey = "value";

const QString invalid_type_name = "invalid";
const QString int_type_name = "int";
const QString string_type_name = "std::string";

}

#endif
