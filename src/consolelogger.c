// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/consolelogger.h"

#define BUFFER_SIZE 384

#if defined(__GNUC__)
__attribute__ ((format (printf, 6, 7)))
#endif
void consolelogger_log(LOG_CATEGORY log_category, const char* file, const char* func, int line, unsigned int options, const char* format, ...)
{
    time_t t;
    va_list args;
    char buffer[BUFFER_SIZE];
    va_start(args, format);

    t = time(NULL); 
    
    switch (log_category)
    {
    case AZ_LOG_INFO:
        (void)printf("Info: ");
        break;
    case AZ_LOG_ERROR:
        (void)printf("Error: Time:%.24s File:%s Func:%s Line:%d ", ctime(&t), file, func, line);
        break;
    default:
        break;
    }

	(void)vsnprintf(buffer, BUFFER_SIZE, format, args);
	(void)printf(buffer);
    (void)vprintf(format, args);
    va_end(args);

    (void)log_category;
    if (options & LOG_LINE)
    {
        (void)printf("\r\n");
    }
}

