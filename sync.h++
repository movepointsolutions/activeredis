#ifndef AR_SYNC_HEADER
#define AR_SYNC_HEADER

#include <string_view>

namespace ar
{

class db
{
public:
	db(std::string_view url);
	std::string get(std::string_view key);
};

} // namespace ar

#endif // AR_SYNC_HEADER
