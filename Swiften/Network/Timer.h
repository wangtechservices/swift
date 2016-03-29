/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Base/boost_bsignals.h>

namespace Swift {
	/**
	 * A class for triggering an event after a given period.
	 */
	class SWIFTEN_API Timer {
		public:
			typedef boost::shared_ptr<Timer> ref;

			virtual ~Timer();

			/**
			 * Starts the timer.
			 *
			 * After the given period, onTick() will be called.
			 */
			virtual void start() = 0;

			/**
			 * Cancels the timer.
			 *
			 * If the timer was started, onTick() will no longer be called.
			 */
			virtual void stop() = 0;

			/**
			 * Emitted when the timer expires.
			 */
			boost::signal<void ()> onTick;
	};
}
