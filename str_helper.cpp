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

#include "str_helper.h"             // self

#include <sstream>                  // std::ostringstream

#include "utils/to_string_t.h"      // to_string()
#include "lang_tools/str_helper.h"  // to_string()

namespace product_db
{

std::ostream & StrHelper::write( std::ostream & os, const Product & l )
{
    os << "name '" << l.name << "' ";

    os << "templ ids: " << utils::to_string( l.template_ids ) << " ";

    os << "langs: ";

    for( auto & e : l.langs )
    {
        os << lang_tools::to_string( e ) << " ";
    }

    return os;
}

} // namespace product_db
