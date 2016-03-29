/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Slimber/FileVCardCollection.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Base/ByteArray.h>
#include <Swiften/Elements/VCard.h>
#include <Swiften/Parser/PayloadParsers/UnitTest/PayloadParserTester.h>
#include <Swiften/Parser/PayloadParsers/VCardParser.h>
#include <Swiften/Serializer/PayloadSerializers/VCardSerializer.h>

namespace Swift {

FileVCardCollection::FileVCardCollection(boost::filesystem::path dir) : vcardsPath(dir) {
}

boost::shared_ptr<VCard> FileVCardCollection::getOwnVCard() const {
	if (boost::filesystem::exists(vcardsPath / std::string("vcard.xml"))) {
		ByteArray data;
		readByteArrayFromFile(data, boost::filesystem::path(vcardsPath / std::string("vcard.xml")).string());

		VCardParser parser;
		PayloadParserTester tester(&parser);
		tester.parse(byteArrayToString(data));
		return boost::dynamic_pointer_cast<VCard>(parser.getPayload());
	}
	else {
		return boost::make_shared<VCard>();
	}
}

void FileVCardCollection::setOwnVCard(boost::shared_ptr<VCard> v) {
	boost::filesystem::ofstream file(vcardsPath / std::string("vcard.xml"));
	file << VCardSerializer().serializePayload(v);
	file.close();
}

}
