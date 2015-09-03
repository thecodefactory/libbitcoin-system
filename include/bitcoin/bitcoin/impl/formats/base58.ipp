/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_BASE58_IPP
#define LIBBITCOIN_BASE58_IPP

#include <bitcoin/bitcoin/utility/assert.hpp>
#include <bitcoin/bitcoin/utility/data.hpp>

namespace libbitcoin {

template <size_t Size>
bool decode_base58(byte_array<Size>& out, const std::string &in)
{
    byte_array<Size> result;
    if (!decode_base58_private(result.data(), result.size(), in.data()))
        return false;

    out = result;
    return true;
}

// For support of template implementation only, do not call directly.
BC_API bool decode_base58_private(uint8_t* out, size_t out_size, const char* in);

} // libbitcoin

#endif
