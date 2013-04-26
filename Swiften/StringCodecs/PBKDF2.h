/*
 * Copyright (c) 2010-2013 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <Swiften/Base/SafeByteArray.h>
#include <Swiften/Base/Concat.h>
#include <Swiften/Crypto/CryptoProvider.h>

namespace Swift {
	class PBKDF2 {
		public:
			static ByteArray encode(const SafeByteArray& password, const ByteArray& salt, int iterations, CryptoProvider* crypto) {
				ByteArray u = crypto->getHMACSHA1(password, concat(salt, createByteArray("\0\0\0\1", 4)));
				ByteArray result(u);
				int i = 1;
				while (i < iterations) {
					u = crypto->getHMACSHA1(password, u);
					for (unsigned int j = 0; j < u.size(); ++j) {
						result[j] ^= u[j];
					}
					++i;
				}
				return result;
			}
	};
}
