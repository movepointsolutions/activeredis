#include <iostream>
#include <string>
#include <hiredis.h>
#include "sync.h++"

using namespace ar;

ar::db::db(std::string_view url)
{
}

std::string
ar::db::get(std::string_view key)
{
	redisContext *ctx = redisConnect("127.0.0.1", 6379);
	redisCommand(ctx, "SELECT 7");
	redisReply *reply = static_cast<redisReply *>(
		redisCommand(ctx, "GET hello")
	);
	if (reply->type == REDIS_REPLY_STRING) {
		return std::string(reply->str, reply->str + reply->len);
	} else
		std::cerr << reply->type << std::endl;
	return "ERROR";
}
