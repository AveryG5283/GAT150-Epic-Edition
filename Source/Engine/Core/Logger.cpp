#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace minimum
{
	Logger g_logger(LogLevel::Info, &std::cout, "log.txt");


	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case minimum::LogLevel::Info:
			*this << "Here's some facts! ";

			break;
		case minimum::LogLevel::Warning:
			*this << "Something's not quite right, let me warn ya! ";

			break;
		case minimum::LogLevel::Error:
			*this << "DAMN! Something broke. Must be an error: ";

			break;
		case minimum::LogLevel::Assert:
			*this << "ASSERT: ";

			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}

}