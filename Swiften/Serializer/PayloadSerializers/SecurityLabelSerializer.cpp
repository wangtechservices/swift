/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Serializer/PayloadSerializers/SecurityLabelSerializer.h>

#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Base/foreach.h>
#include <Swiften/Serializer/XML/XMLElement.h>
#include <Swiften/Serializer/XML/XMLRawTextNode.h>
#include <Swiften/Serializer/XML/XMLTextNode.h>

namespace Swift {

SecurityLabelSerializer::SecurityLabelSerializer() : GenericPayloadSerializer<SecurityLabel>() {
}

std::string SecurityLabelSerializer::serializePayload(boost::shared_ptr<SecurityLabel> label)  const {
	XMLElement element("securitylabel", "urn:xmpp:sec-label:0");
	if (!label->getDisplayMarking().empty()) {
		boost::shared_ptr<XMLElement> displayMarking(new XMLElement("displaymarking"));
		if (!label->getForegroundColor().empty()) {
			displayMarking->setAttribute("fgcolor", label->getForegroundColor());
		}
		if (!label->getBackgroundColor().empty()) {
			displayMarking->setAttribute("bgcolor", label->getBackgroundColor());
		}
		displayMarking->addNode(boost::make_shared<XMLTextNode>(label->getDisplayMarking()));
		element.addNode(displayMarking);
	}

	boost::shared_ptr<XMLElement> labelElement(new XMLElement("label"));
	labelElement->addNode(boost::make_shared<XMLRawTextNode>(label->getLabel()));
	element.addNode(labelElement);
	
	foreach(const std::string& equivalentLabel, label->getEquivalentLabels()) {
		boost::shared_ptr<XMLElement> equivalentLabelElement(new XMLElement("equivalentlabel"));
		equivalentLabelElement->addNode(boost::make_shared<XMLRawTextNode>(equivalentLabel));
		element.addNode(equivalentLabelElement);
	}
	return element.serialize();
}

}
