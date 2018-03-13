/*

Product DB.

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

// $Revision: 8746 $ $Date:: 2018-03-12 #$ $Author: serge $

#include "product_db.h"             // self

#include "utils/dummy_logger.h"     // dummy_log_debug
#include "utils/read_config_file.h" // utils::read_config_file
#include "utils/tokenizer.h"        // tokenize_to_vector
#include "utils/assert.h"           // ASSERT
#include "utils/mutex_helper.h"     // MUTEX_SCOPE_LOCK

namespace product_db
{

ProductDb::ProductDb():
        log_id_( 0 )
{
}

bool ProductDb::init(
        uint32_t            log_id,
        const std::string   & product_db )
{
    log_id_ = log_id;

    if( product_db.empty() )
        return false;

    try
    {
        std::vector<std::string> lines;

        utils::read_config_file( product_db, lines );

        parse_lines( lines );

        dummy_log_info( log_id_, "loaded %u products from %s", lines.size(), product_db.c_str() );
    }
    catch( std::exception & e )
    {
        throw e;
    }

    return true;
}

void ProductDb::parse_lines( const std::vector<std::string> & lines )
{
    for( auto & l : lines )
    {
        process_line( l );
    }
}

void ProductDb::process_line( const std::string & line )
{
    auto e = to_flat_product( line );

    auto b = map_id_to_product_.insert( std::make_pair( e.product_id, e.product ) ).second;

    if( b == false )
    {
        throw std::runtime_error( "duplicate template id " + std::to_string( e.product_id ) );
    }
}

ProductDb::FlatProduct ProductDb::to_flat_product( const std::string & l )
{
    // format: 1;some product name;templ_id_1,...,templ_id_n;lang_code_1,...,lang_code_m.
    FlatProduct res;

    std::vector< std::string > elems;
    tokenize_to_vector( elems, l, ";" );

    if( elems.size() < 4 )
        throw std::runtime_error( "not enough arguments (<5) in entry: " + l  );

    try
    {
        res.id          = std::stoi( elems[1] );
        res.locale      = lang_tools::to_lang_iso( elems[2] );
        res.name        = elems[3];
        res.templ       = elems[4];
    }
    catch( std::exception & e )
    {
        throw std::runtime_error( "invalid entry: " + l );
    }

    return res;
}

} // namespace product_db
