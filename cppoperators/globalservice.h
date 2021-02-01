#pragma once
#include <memory>

struct GlobalService
{
	static std::unique_ptr<GlobalService> create();

	static GlobalService& instance();

	virtual ~GlobalService() = default;

	virtual void doServiceJob() = 0;
};
