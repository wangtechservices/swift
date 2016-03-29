/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <string>

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/Elements/IQ.h>
#include <Swiften/Elements/RosterPayload.h>
#include <Swiften/JID/JID.h>
#include <Swiften/Roster/RosterPushResponder.h>

namespace Swift {
	class IQRouter;
	class XMPPRosterImpl;
	class RosterStorage;

	class SWIFTEN_API XMPPRosterController {
		public:
			XMPPRosterController(IQRouter *iqRouter, XMPPRosterImpl* xmppRoster, RosterStorage* storage);
			~XMPPRosterController();

			void requestRoster();

			void setUseVersioning(bool b) {
				useVersioning = b;
			}

		private:
			void handleRosterReceived(boost::shared_ptr<RosterPayload> rosterPayload, bool initial, boost::shared_ptr<RosterPayload> previousRoster);
			void saveRoster(const std::string& version);

		private:
			IQRouter* iqRouter_;
			RosterPushResponder rosterPushResponder_;
			XMPPRosterImpl* xmppRoster_;
			RosterStorage* rosterStorage_;
			bool useVersioning;
	};
}

