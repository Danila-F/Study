#include "pch.h"
#include <utility>
#include <limits.h>
#include "LoggerLibrary.h"

LOGGERLIBRARY_API Logger* createMyClass()
{
	return new Logger();
}
