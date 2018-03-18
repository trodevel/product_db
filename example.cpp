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

// $Revision: 8767 $ $Date:: 2018-03-15 #$ $Author: serge $

#include <cstdio>
#include <sstream>                          // std::stringstream
#include <iostream>                         // std::cout

#include "product_db.h"                     // ProductDb

#include "utils/dummy_logger.h"             // dummy_log_set_log_level
#include "lang_tools/str_helper.h"          // lang_tools::to_string_iso

void loading_test( uint32_t log_id, const char * name, const char * filename )
{
    std::cout << name << " - started" << std::endl;

    try
    {
        product_db::ProductDb prod_db;

        prod_db.init( log_id, filename );
    }
    catch( std::exception & e )
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

    std::cout << name << " - finished" << std::endl;
}

int main()
{
    try
    {
        dummy_logger::set_log_level( log_levels_log4j::DEBUG );

        auto log_id             = dummy_logger::register_module( "ProductDb" );

        product_db::ProductDb prod_db;

        prod_db.init( log_id, "product_db.csv" );

        loading_test( log_id, "01", "broken_product_db_01.csv" );
        loading_test( log_id, "02", "broken_product_db_02.csv" );

        return EXIT_SUCCESS;
    }
    catch( std::exception & e )
    {
        std::cout << "exception: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
}
