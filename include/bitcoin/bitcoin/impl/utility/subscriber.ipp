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
#ifndef LIBBITCOIN_SUBSCRIBER_IPP
#define LIBBITCOIN_SUBSCRIBER_IPP

#include <bitcoin/bitcoin/utility/sequencer.hpp>
#include <bitcoin/bitcoin/utility/threadpool.hpp>
   
namespace libbitcoin {

template <typename... Args>
subscriber<Args...>::subscriber(threadpool& pool)
  : strand_(pool)
{
}

template <typename... Args>
void subscriber<Args...>::subscribe(subscription_handler notifier)
{
    strand_.queue(&subscriber<Args...>::do_subscribe,
        this->shared_from_this(), notifier);
}

template <typename... Args>
void subscriber<Args...>::relay(Args... args)
{
    strand_.queue(&subscriber<Args...>::do_relay,
        this->shared_from_this(), args...);
}

template <typename... Args>
void subscriber<Args...>::do_subscribe(subscription_handler notifier)
{
    subscriptions_.push_back(notifier);
}

template <typename... Args>
void subscriber<Args...>::do_relay(Args... args)
{
    if (subscriptions_.empty())
        return;

    const auto subscriptions_copy = subscriptions_;
    subscriptions_.clear();
    for (const auto notifier: subscriptions_copy)
        notifier(args...);
}

} // namespace libbitcoin

#include <bitcoin/bitcoin/impl/utility/subscriber.ipp>

#endif
