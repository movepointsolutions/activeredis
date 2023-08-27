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
	struct error_type
	{
		int code;
		std::string desc;
	};

	db(std::string_view url);
	redisContext *ctx() { return context; }
	const redisContext *ctx() const { return context; }
	error_type error() const;
	ar::db::check_and_throw() const;
	void select(unsigned int db);
	std::string get(std::string_view key);
};

} // namespace ar

#endif // AR_SYNC_HEADER

// vim: syntax=cpp
