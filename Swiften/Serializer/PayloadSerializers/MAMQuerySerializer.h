/*
 * Copyright (c) 2014-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/Override.h>
#include <Swiften/Elements/MAMQuery.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>

namespace Swift {
	class PayloadSerializerCollection;

	class SWIFTEN_API MAMQuerySerializer : public GenericPayloadSerializer<MAMQuery> {
		public:
			MAMQuerySerializer();
			virtual ~MAMQuerySerializer();

			virtual std::string serializePayload(boost::shared_ptr<MAMQuery>) const SWIFTEN_OVERRIDE;
	};
}
