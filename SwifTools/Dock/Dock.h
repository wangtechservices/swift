/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

namespace Swift {
	class String;

	class Dock {
		public:
			virtual ~Dock();

			virtual void setNumberOfPendingMessages(int i) = 0;
	};
}
