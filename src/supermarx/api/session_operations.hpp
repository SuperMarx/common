#include <supermarx/api/session.hpp>

#include <libscrypt.h>

namespace supermarx
{
namespace api
{

static_assert(SCRYPT_N == 1 << 14, "SCRYPT_N changed");
static_assert(SCRYPT_r == 8, "SCRYPT_r changed");
static_assert(SCRYPT_p == 16, "SCRYPT_p changed");

static inline token random_token()
{
	token result;

	if(::libscrypt_salt_gen(result.data(), result.size()) == -1)
		throw std::runtime_error("Incapable of generating proper random token");

	return result;
}

static inline token hash(const std::string &pw, token const& salt)
{
	token result;
	if(::libscrypt_scrypt(
		(const uint8_t*)pw.data(), pw.size(),
		salt.data(), salt.size(),
		SCRYPT_N, SCRYPT_r, SCRYPT_p,
		result.data(), result.size()
	) == -1)
		throw std::runtime_error("Incapable of hashing plaintext");

	return result;
}

static inline token hash(token const& pw, token const& salt)
{
	token result;
	if(::libscrypt_scrypt(
		pw.data(), pw.size(),
		salt.data(), salt.size(),
		SCRYPT_N, SCRYPT_r, SCRYPT_p,
		result.data(), result.size()
	) == -1)
		throw std::runtime_error("Incapable of hashing token");

	return result;
}

}
}
