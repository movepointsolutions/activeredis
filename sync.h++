#ifndef AR_SYNC_HEADER
#define AR_SYNC_HEADER

#include <string_view>

struct redisContext;

namespace ar
{

class db
{
	redisContext *context;

public:
	db(std::string_view url);
	redisContext *ctx() { return context; }
	void select(unsigned int db);
	std::string get(std::string_view key);
};

} // namespace ar

#endif // AR_SYNC_HEADER
