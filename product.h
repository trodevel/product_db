/*

Product DB - Product.

Copyright (C) 2018 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 8750 $ $Date:: 2018-03-12 #$ $Author: serge $

#ifndef LIB_PRODUCT_DB__PRODUCT_H
#define LIB_PRODUCT_DB__PRODUCT_H

#include <string>               // std::string
#include <set>                  // std::set

#include "lang_tools/language_enum.h"    // lang_tools::lang_e

#include "types.h"              // product_id_t

namespace product_db
{

struct Product
{
    std::string                 name;
    std::set<template_id_t>     template_ids;
    std::set<lang_tools::lang_e>    langs;
};

} // namespace product_db

#endif // LIB_PRODUCT_DB__PRODUCT_H
