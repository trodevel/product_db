/*

String Helper. Provides to_string() function.

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

// $Revision: 8770 $ $Date:: 2018-03-16 #$ $Author: serge $

#ifndef LIB_PRODUCT_DB__STR_HELPER_H
#define LIB_PRODUCT_DB__STR_HELPER_H

#include <string>

#include "product.h"        // Product

namespace product_db
{

class StrHelper
{
public:
    static std::ostream & write( std::ostream & os, const Product & l );
};

} // namespace phonebook

#endif // LIB_PRODUCT_DB__STR_HELPER_H
