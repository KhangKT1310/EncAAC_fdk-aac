/**
 ******************************************************************************
 * @author: PND
 * @date:   04/09/2018
 * @brief: debug mt function
 ******************************************************************************
**/
#ifndef __MT_DBG_H__
#define __MT_DBG_H__

#include <stdio.h>

#define MT_MSG_DBG_EN				0
#define MT_TIMER_DBG_EN				0

//extern void APP_PRINT(const char *fmt, ...);


#define DEBUG
#ifdef DEBUG
#define APP_PRINT(x...) \
	do { \
	printf("\033[1;32m"); \
	printf(x); \
	printf("\033[0m\n"); \
	} while (0)
#define APP_DBG(x...) \
	do { \
	printf("\033[2;33m%s->%d: ", __FUNCTION__, __LINE__); \
	printf(x); \
	printf("\033[0m\n"); \
	} while (0)
#define APP_INFO(x...) \
	do { \
	printf("\033[1;35m%s->%d: ", __FUNCTION__, __LINE__); \
	printf(x); \
	printf("\033[0m\n"); \
	} while (0)

#define APP_ERR(x...) \
	do { \
	printf("\033[1;31m%s->%d: ", __FUNCTION__, __LINE__); \
	printf(x); \
	printf("\033[0m\n"); \
	} while (0)

	#define APP_PRF(x...) printf(x);

#else
#define APP_PRINT(args...) do { } while (0)
#define APP_DBG(args...) do { } while (0)
#define APP_INFO(args...) do { } while (0)
#define APP_PRF(args...) do { } while (0)
#endif



#if (MT_MSG_DBG_EN == 1)
#define MT_MSG_DBG(fmt, ...)       APP_PRINT(fmt, ##__VA_ARGS__)
#else
#define MT_MSG_DBG(fmt, ...)
#endif

#if (MT_TIMER_DBG_EN == 1)
#define MT_TIMER_DBG(fmt, ...)      APP_PRINT(fmt, ##__VA_ARGS__)
#else
#define MT_TIMER_DBG(fmt, ...)
#endif

#endif //__MT_DBG_H__
