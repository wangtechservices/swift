/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Parser/PayloadParserFactory.h>
#include <Swiften/Parser/PayloadParserFactoryCollection.h>

namespace Swift {
	class SWIFTEN_API FullPayloadParserFactoryCollection : public PayloadParserFactoryCollection {
		public:
			FullPayloadParserFactoryCollection();
			~FullPayloadParserFactoryCollection();

		private:
			std::vector< boost::shared_ptr<PayloadParserFactory> > factories_;
			PayloadParserFactory* defaultFactory_;
	};
}
