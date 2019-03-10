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

// $Revision: 10609 $ $Date:: 2019-03-10 #$ $Author: serge $

#include "product_db.h"             // self

#include <algorithm>                // std::transform

#include "utils/dummy_logger.h"     // dummy_log_debug
#include "utils/read_config_file.h" // utils::read_config_file
#include "utils/tokenizer.h"        // tokenize_to_vector
#include "utils/tokenizer_ext.h"    // tokenize_and_convert
#include "utils/utils_assert.h"           // ASSERT
#include "utils/mutex_helper.h"     // MUTEX_SCOPE_LOCK
#include "lang_tools/parser.h"      // lang_tools::to_lang()


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

    std::vector<std::string> lines;

    utils::read_config_file( product_db, lines );

    parse_lines( lines );

    dummy_log_info( log_id_, "loaded %u products from %s", lines.size(), product_db.c_str() );

    return true;
}

const Product * ProductDb::get_product( product_id_t product_id ) const
{
    auto it = map_id_to_product_.find( product_id );

    if( it == map_id_to_product_.end() )
        return nullptr;

    return & it->second;
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

    process_line( e );
}

void ProductDb::process_line( const FlatProduct & e )
{
    auto b = map_id_to_product_.insert( std::make_pair( e.product_id, e.product ) ).second;

    if( b == false )
    {
        throw std::runtime_error( "duplicate product id " + std::to_string( e.product_id ) );
    }
}

ProductDb::FlatProduct ProductDb::to_flat_product( const std::string & l )
{
    // format: 1;some product name;templ_id_1 ... templ_id_n;lang_code_1 ... lang_code_m.
    FlatProduct res;

    std::vector< std::string > elems;
    tokenize_to_vector( elems, l, ";" );

    if( elems.size() < 4 )
        throw std::runtime_error( "not enough arguments (<4) in entry: " + l  );

    try
    {
        res.product_id      = std::stoi( elems[0] );
        res.product         = to_product( elems );
    }
    catch( std::exception & e )
    {
        throw std::runtime_error( std::string( e.what() ) + ": " + l );
    }

    return res;
}

Product ProductDb::to_product( const std::vector<std::string> & elems )
{
    // format: 1;some product name;templ_id_1 ... templ_id_n;lang_code_1 ... lang_code_m.
    Product res;

    res.name    = elems[1];

    std::vector<template_id_t> templ_ids;
    utils::tokenize_and_convert( templ_ids, elems[2], " " );

    res.template_ids    = std::set<template_id_t>( templ_ids.begin(), templ_ids.end() );

    std::vector<std::string> lang_codes;
    tokenize_to_vector( lang_codes, elems[3], " " );

    std::transform(
            lang_codes.begin(), lang_codes.end(),
            std::inserter( res.langs, res.langs.begin() ),
            [] ( const std::string & s ) { auto lang = lang_tools::to_lang( s );
            if( lang == lang_tools::lang_e::UNDEF ) throw std::runtime_error( "unknown language " + s ); return lang; } );

    return res;
}
} // namespace product_db
