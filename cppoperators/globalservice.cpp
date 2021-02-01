#include "pch.h"
#include "globalservice.h"

#include <cppmem/singletonmemop.h>


namespace {


class GlobalServiceImpl final : public GlobalService
{
public:

	SINGLETON_MEMOP(GlobalServiceImpl)

	GlobalServiceImpl()
	{
		s_instance = this;
	}

	~GlobalServiceImpl()
	{
		s_instance = nullptr;
	}


private:

	void doServiceJob() override
	{
		std::cout << "Service job !\n";
	}

	static GlobalServiceImpl* s_instance;

	friend class GlobalService;
};


GlobalServiceImpl* GlobalServiceImpl::s_instance = nullptr;
}



std::unique_ptr<GlobalService> GlobalService::create()
{
	return std::make_unique<GlobalServiceImpl>();
}

GlobalService& GlobalService::instance()
{
	if (!GlobalServiceImpl::s_instance)
	{
		throw std::exception("Not initializes");
	}

	return *GlobalServiceImpl::s_instance;
}
