/* Diagnostic Client library
 * Copyright (C) 2022  Avijit Dey
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef ONESHOTSYNCTIMER_H
#define ONESHOTSYNCTIMER_H

#include <boost/asio.hpp>

#include "common_Header.h"

namespace libBoost {
namespace libTimer {
namespace oneShot {
// Clock Type
using SteadyClock = boost::asio::steady_timer;
using HighResolutionClock = boost::asio::high_resolution_timer;
using BoostTimer = SteadyClock;
using msTime = boost::asio::chrono::milliseconds;

class oneShotSyncTimer {
public:
  // timer state
  enum class timer_state : std::uint8_t { kIdle = 0, kCancelRequested, kTimeout };

  //ctor
  oneShotSyncTimer();

  //dtor
  virtual ~oneShotSyncTimer();

  // Start timer
  auto Start(int timeout) noexcept -> timer_state;

  // Stop Timer
  auto Stop() noexcept -> void;

private:
  // io context
  boost::asio::io_context io_e;
  // timer - next timeout
  std::unique_ptr<BoostTimer> timer_ptr_;
  // timer - current state
  timer_state timer_state_;
  // error
  boost::system::error_code error_;
};
}  // namespace oneShot
}  // namespace libTimer
}  // namespace libBoost
#endif  // ONESHOTSYNCTIMER_H
