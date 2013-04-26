/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#include <Swiften/Crypto/CommonCryptoCryptoProvider.h>

#include <CommonCrypto/CommonDigest.h>
#include <CommonCrypto/CommonHMAC.h>
#include <cassert>

#include <Swiften/Crypto/Hash.h>
#include <Swiften/Base/ByteArray.h>
#include <boost/numeric/conversion/cast.hpp>

using namespace Swift;

namespace {
	class SHA1Hash : public Hash {
		public:
			SHA1Hash() : finalized(false) {
				if (!CC_SHA1_Init(&context)) {
					assert(false);
				}
			}

			~SHA1Hash() {
			}

			virtual Hash& update(const ByteArray& data) SWIFTEN_OVERRIDE {
				return updateInternal(data);
			}

			virtual Hash& update(const SafeByteArray& data) SWIFTEN_OVERRIDE {
				return updateInternal(data);
			}

			virtual std::vector<unsigned char> getHash() {
				assert(!finalized);
				std::vector<unsigned char> result(CC_SHA1_DIGEST_LENGTH);
				CC_SHA1_Final(vecptr(result), &context);
				return result;
			}

		private:
			template<typename ContainerType>
			Hash& updateInternal(const ContainerType& data) {
				assert(!finalized);
				if (!CC_SHA1_Update(&context, vecptr(data), boost::numeric_cast<CC_LONG>(data.size()))) {
					assert(false);
				}
				return *this;
			}

		private:
			CC_SHA1_CTX context;
			bool finalized;
	};

	class MD5Hash : public Hash {
		public:
			MD5Hash() : finalized(false) {
				if (!CC_MD5_Init(&context)) {
					assert(false);
				}
			}

			~MD5Hash() {
			}

			virtual Hash& update(const ByteArray& data) SWIFTEN_OVERRIDE {
				return updateInternal(data);
			}

			virtual Hash& update(const SafeByteArray& data) SWIFTEN_OVERRIDE {
				return updateInternal(data);
			}

			virtual std::vector<unsigned char> getHash() {
				assert(!finalized);
				std::vector<unsigned char> result(CC_MD5_DIGEST_LENGTH);
				CC_MD5_Final(vecptr(result), &context);
				return result;
			}

		private:
			template<typename ContainerType>
			Hash& updateInternal(const ContainerType& data) {
				assert(!finalized);
				if (!CC_MD5_Update(&context, vecptr(data), boost::numeric_cast<CC_LONG>(data.size()))) {
					assert(false);
				}
				return *this;
			}

		private:
			CC_MD5_CTX context;
			bool finalized;
	};

	template<typename T>
	class HMACHash : public Hash {
		public:
			HMACHash(const T& key) : finalized(false) {
				CCHmacInit(&context, kCCHmacAlgSHA1, vecptr(key), key.size());
			}

			~HMACHash() {
			}

			virtual Hash& update(const ByteArray& data) SWIFTEN_OVERRIDE {
				return updateInternal(data);
			}

			virtual Hash& update(const SafeByteArray& data) SWIFTEN_OVERRIDE {
				return updateInternal(data);
			}

			virtual std::vector<unsigned char> getHash() {
				assert(!finalized);
				std::vector<unsigned char> result(CC_SHA1_DIGEST_LENGTH);
				CCHmacFinal(&context, vecptr(result));
				return result;
			}

		private:
			template<typename ContainerType>
			Hash& updateInternal(const ContainerType& data) {
				assert(!finalized);
				CCHmacUpdate(&context, vecptr(data), boost::numeric_cast<CC_LONG>(data.size()));
				return *this;
			}

		private:
			CCHmacContext context;
			bool finalized;
	};
}

CommonCryptoCryptoProvider::CommonCryptoCryptoProvider() {
}

CommonCryptoCryptoProvider::~CommonCryptoCryptoProvider() {
}

Hash* CommonCryptoCryptoProvider::createSHA1() {
	return new SHA1Hash();
}

Hash* CommonCryptoCryptoProvider::createMD5() {
	return new MD5Hash();
}

Hash* CommonCryptoCryptoProvider::createHMACSHA1(const SafeByteArray& key) {
	return new HMACHash<SafeByteArray>(key);
}

Hash* CommonCryptoCryptoProvider::createHMACSHA1(const ByteArray& key) {
	return new HMACHash<ByteArray>(key);
}


bool CommonCryptoCryptoProvider::isMD5AllowedForCrypto() const {
	return true;
}

