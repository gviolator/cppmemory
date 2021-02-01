#pragma once
#include <type_traits>


template<typename T>
inline bool safeBoolean(const T& value)
{
	using ValueType = std::decay_t<T>;

	static_assert(!(
		std::is_same_v<ValueType, const wchar_t*> ||
		std::is_same_v<ValueType, const char*>), "Unsafe condition type");

	return static_cast<bool>(value);
}

void raiseFailure(const char* expression, const char* message);

inline const char* diagMessage()
{
	return "";
}


inline const char* diagMessage(const char* message)
{
	return message;
}




#define CHECK(expression, ...) \
if (!safeBoolean(expression))\
{ \
	raiseFailure(#expression, diagMessage(__VA_ARGS__)); \
}\
