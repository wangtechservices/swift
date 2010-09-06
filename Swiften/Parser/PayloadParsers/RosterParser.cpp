/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include "Swiften/Parser/PayloadParsers/RosterParser.h"
#include "Swiften/Parser/SerializingParser.h"

namespace Swift {

RosterParser::RosterParser() : level_(TopLevel), unknownContentParser_(0) {
}

void RosterParser::handleStartElement(const String& element, const String& ns, const AttributeMap& attributes) {
	if (level_ == PayloadLevel) {
		if (element == "item") {
			inItem_ = true;
			currentItem_ = RosterItemPayload();

			currentItem_.setJID(JID(attributes.getAttribute("jid")));
			currentItem_.setName(attributes.getAttribute("name"));

			String subscription = attributes.getAttribute("subscription");
			if (subscription == "both") {
				currentItem_.setSubscription(RosterItemPayload::Both);
			}
			else if (subscription == "to") {
				currentItem_.setSubscription(RosterItemPayload::To);
			}
			else if (subscription == "from") {
				currentItem_.setSubscription(RosterItemPayload::From);
			}
			else if (subscription == "remove") {
				currentItem_.setSubscription(RosterItemPayload::Remove);
			}
			else {
				currentItem_.setSubscription(RosterItemPayload::None);
			}

			if (attributes.getAttribute("ask") == "subscribe") {
				currentItem_.setSubscriptionRequested();
			}
		}
	}
	else if (level_ == ItemLevel) {
		if (element == "group") {
			currentText_ = "";
		}
		else {
			assert(!unknownContentParser_);
			unknownContentParser_ = new SerializingParser();
			unknownContentParser_->handleStartElement(element, ns, attributes);
		}
	}
	else if (unknownContentParser_) {
		unknownContentParser_->handleStartElement(element, ns, attributes);
	}
	++level_;
}

void RosterParser::handleEndElement(const String& element, const String& ns) {
	--level_;
	if (level_ == PayloadLevel) {
		if (inItem_) {
			getPayloadInternal()->addItem(currentItem_);
			inItem_ = false;
		}
	}
	else if (level_ == ItemLevel) {
		if (unknownContentParser_) {
			unknownContentParser_->handleEndElement(element, ns);
			currentItem_.addUnknownContent(unknownContentParser_->getResult());
			delete unknownContentParser_;
			unknownContentParser_ = NULL;
		}
		else if (element == "group") {
			currentItem_.addGroup(currentText_);
		}
	}
	else if (unknownContentParser_) {
		unknownContentParser_->handleEndElement(element, ns);
	}
}

void RosterParser::handleCharacterData(const String& data) {
	if (unknownContentParser_) {
		unknownContentParser_->handleCharacterData(data);
	}
	else {
		currentText_ += data;
	}
}

}
