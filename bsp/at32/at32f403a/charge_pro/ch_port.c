/*******************************************************************************
 * @file ch_port.c
 * @note
 * @brief 充电接口函数
 *
 * @author
 * @date     2021-05-02
 * @version  V1.0.0
 *
 * @Description
 *
 * @note History:
 * @note     <author>   <time>    <version >   <desc>
 * @note
 * @warning
 *******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>
#include "chtask.h"
#include "ch_port.h"
#include "common.h"

#define  IS_LEAP_YEAR(usYear)      ((((usYear) % 4) == 0) && (((usYear) % 100) != 0) || (((usYear) % 400) == 0))
#define  YEAR_TOTAL_DATA(usYear)   ((IS_LEAP_YEAR(usYear)) ? 366 : 365)

/* 1970年1月1日是周四 */
static const uint8_t  cucaWeekTab[7] = {4,5,6,7,1,2,3};
/* 1年12个月对应的天数 */
static const uint8_t  cucaDay[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
/* 充电启动完成码 */
uint16_t g_usChStartCpltCode = 0;

extern rt_mq_t pstChMq;

/**
 * @brief 本地时间转换为cp56
 * @param[in] tTime: 本地时间 pstCp56: 输出的cp56时间
 * @param[out]
 * @return
 * @note
 */
void localtime_to_cp56time(time_t tTime, CP56TIME2A_T *pstCp56)
{
    uint32_t    uiDay = 0;
    uint32_t    uiWeekIndex = 0;
    uint32_t    uiTmp = 0;
    uint8_t     ucMonDay[12] = {0};
    uint8_t     ucSec = 0;
    uint8_t     ucMon = 0;
    uint16_t    usYear = 0;

    uiDay       = tTime/86400;                   //一天86400 秒，计算有多少天
    uiTmp       = tTime - uiDay * 86400;           //剩余的是当天的时间
    uiWeekIndex = uiDay % 7;

    pstCp56->ucHour = uiTmp / 3600;
    uiTmp -= (uint32_t)pstCp56->ucHour * 3600;

    pstCp56->ucMin = uiTmp / 60;
    ucSec = uiTmp % 60;
    pstCp56->usMsec = (uint16_t)ucSec * 1000;

    pstCp56->ucWeek = cucaWeekTab[uiWeekIndex];

    for(usYear = 1970; uiDay >= YEAR_TOTAL_DATA(usYear); usYear++)
    {
        uiDay -= YEAR_TOTAL_DATA(usYear);
    }

    pstCp56->ucYear = usYear >= 2000 ? usYear - 2000 : usYear - 1970;

    memcpy(ucMonDay,cucaDay,12);

    if(IS_LEAP_YEAR(usYear))
    {
        ucMonDay[1] = 29;
    }

    for(ucMon = 1; uiDay >= ucMonDay[ucMon - 1]; ucMon++)
    {
        uiDay -= ucMonDay[ucMon - 1];
    }

    pstCp56->ucMon = ucMon;
    pstCp56->ucDay = uiDay + 1;
}

/**
 * @brief
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
static uint32_t time_cal_day(uint8_t ucMon)
{
    uint8_t  i;
    uint32_t uiSum = 0;

    if (ucMon > 12 || ucMon <= 1)
    {
        return 0;
    }

    for (i = 0; i < (ucMon - 1); i++)
    {
        uiSum += cucaDay[i];
    }
    return uiSum;
}

/**
 * @brief cp56转换为本地时间
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
time_t cp56time_to_localtime(CP56TIME2A_T *pstCp56)
{
    uint8_t  ucTmp0 = 0;
    uint8_t  ucTmp1 = 0;
    uint8_t  ucYear = 0;
    uint32_t uiDt = 0;

    /* pstCp56->ucYear 从 2000 年开始 */
    ucYear = 30 + pstCp56->ucYear;

    ucTmp0 = ucYear / 4;
    ucTmp1 = ucYear % 4;

    uiDt  = ucTmp0 * 1461 + ucTmp1 * 365;
    uiDt += ucTmp1 > 2 ? 1 : 0;


    uiDt += time_cal_day(pstCp56->ucMon);
    /* 润年 多一天 */
    uiDt += ((ucTmp1 == 2) && (pstCp56->ucMon > 2)) ? 1 : 0;

    uiDt += (pstCp56->ucDay - 1);

    uiDt *= 24;
    uiDt += pstCp56->ucHour;

    uiDt *= 60;
    uiDt += pstCp56->ucMin;

    uiDt    *= 60;
    ucTmp0   = pstCp56->usMsec / 1000;
    uiDt    += ucTmp0;
    uiDt    += (pstCp56->usMsec % 1000) > 500 ? 1 : 0;

    return uiDt;
}

