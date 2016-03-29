/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Elements/SecurityLabel.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>

namespace Swift {
	class SWIFTEN_API SecurityLabelSerializer : public GenericPayloadSerializer<SecurityLabel> {
		public:
			SecurityLabelSerializer();

			virtual std::string serializePayload(boost::shared_ptr<SecurityLabel> version)  const;
	};
}
