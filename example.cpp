/*

Example.

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

// $Revision: 8758 $ $Date:: 2018-03-14 #$ $Author: serge $

#include <cstdio>
#include <sstream>                          // std::stringstream
#include <iostream>                         // std::cout

#include "product_db.h"                     // ProductDb

#include "utils/dummy_logger.h"             // dummy_log_set_log_level
#include "lang_tools/str_helper.h"          // lang_tools::to_string_iso

int main()
{
    try
    {
        dummy_logger::set_log_level( log_levels_log4j::DEBUG );

        auto log_id             = dummy_logger::register_module( "ProductDb" );

        product_db::ProductDb prod_db;

        prod_db.init( log_id, "product_db.csv" );

        return EXIT_SUCCESS;
    }
    catch( std::exception & e )
    {
        std::cout << "exception: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
}
