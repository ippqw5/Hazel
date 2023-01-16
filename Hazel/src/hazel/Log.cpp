#include "hzpch.h"
#include "Log.h"

namespace Hazel {
	
	std::shared_ptr<spdlog::logger> Log::m_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::m_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_CoreLogger = spdlog::stdout_color_mt("Core");
		m_CoreLogger->set_level(spdlog::level::trace); // Set global log level to trace
		m_ClientLogger = spdlog::stdout_color_mt("Clinet");
		m_ClientLogger->set_level(spdlog::level::trace); // Set global log level to trace
		
	}


}