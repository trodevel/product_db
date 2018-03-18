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

// $Revision: 8769 $ $Date:: 2018-03-15 #$ $Author: serge $

#ifndef LIB_PRODUCT_DB__PRODUCT_DB_H
#define LIB_PRODUCT_DB__PRODUCT_DB_H

#include <map>              // std::map
#include <vector>           // std::vector
#include <mutex>            // std::mutex

#include "product.h"        // Product


namespace product_db
{

class ProductDb
{
public:
    ProductDb();

    bool init(
            uint32_t            log_id,
            const std::string   & product_db );

    const Product * get_product( product_id_t product_id ) const;

private:

    struct FlatProduct
    {
        product_id_t    product_id;
        Product         product;
    };

    typedef std::map<product_id_t,Product>  MapIdToProduct;

private:

    void parse_lines( const std::vector<std::string> & lines );

    void process_line( const std::string & line );
    void process_line( const FlatProduct & p );

    FlatProduct to_flat_product( const std::string & l );

    Product to_product( const std::vector<std::string> & elems );

private:
    mutable std::mutex          mutex_;

    uint32_t                log_id_;

    MapIdToProduct          map_id_to_product_;     // map: contact id --> Product*
};

} // namespace product_db

#endif // LIB_PRODUCT_DB__PRODUCT_DB_H
