/*******************************************************************************
 * @file
 * @note
 * @brief
 *
 * @author
 * @date     2021-05-02
 * @version  V1.0.0
 *
 * @Description cp采样
 *
 * @note History:
 * @note     <author>   <time>    <version >   <desc>
 * @note
 * @warning
 *******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>
#include <stdlib.h>
#include <board.h>
#include "common.h"
#include "drv_hwtimer.h"

/* 引脚支持adc1通道10 */
#define   CP_ADC_NAME          "adc1"
#define   CP_ADC_CHANNEL       ADC_CHANNEL_1


#define   CP2_ADC_NAME          "adc1"
#define   CP2_ADC_CHANNEL       ADC_CHANNEL_13

/* 1ms */
#define   CP_PERIOD             1000000    //ns为单位
/* 533333 */
#define   CP_CH_PULSE           467000    //467   占空比53.3%    
#define   CP_CH_PULSE_half      734000    //734===占空比26.6%       
#define   CP_CH_NULL            0
/* 3300mv */
#define   CP_ADC_REFER_VOLT     3300
/* 转换位数为12位 */
#define   CP_ADC_CONVERT_BITS   (1ul << 12)
#define   CP_ADC_MIN_CONVERT_V  1300
#define   CP_ADC_DIFF            700
/* defined the PWM pin: PA0 */
#define PWM_RUN_PIN             0

#define PWM_DEV_NAME        "pwm2"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL     1       /* PWM通道 */


#define PWM2_DEV_NAME        "pwm9"  /* PWM设备名称 */
#define PWM2_DEV_CHANNEL     1       /* PWM通道 */

struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */
struct rt_device_pwm *pwm_dev2;      /* PWM9设备句柄 */

/**
 * @brief 通用定时器1初始化PWM函数
 * @param[in] psr:时钟预分频系数,预分频值=psr+1
 *            arr:自动重装载值,计数次数=arr+1
 * @param[out]
 * @return
 * @note
 */
void timer1_pwm_init()
{
    rt_uint32_t period, pulse, dir;

    period = 1000000;    /* 周期为0.5ms，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */

    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}


/**cp2  pwm**/
void timer9_pwm_init()
{
//	/****引脚初始化后，拉高低**/
//	//gpio_bits_set(GPIOA, GPIO_PINS_0);
//	gpio_bits_reset(GPIOA, GPIO_PINS_0);
//		/****引脚初始化后，拉高低**/
//	gpio_bits_set(GPIOE, GPIO_PINS_5);
//	gpio_bits_reset(GPIOE, GPIO_PINS_5);

    rt_uint32_t period, pulse, dir;

    period = 1000000;    /* 周期为1ms，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */

    /* 查找设备 */
    pwm_dev2 = (struct rt_device_pwm *)rt_device_find(PWM2_DEV_NAME);
    if (pwm_dev2 == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM2_DEV_NAME);
        return;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev2, PWM2_DEV_CHANNEL, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev2, PWM2_DEV_CHANNEL);
}





/**
 * @brief pwm 占空比100%输出
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
void cp_pwm_full(void)
{
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, CP_PERIOD, CP_CH_NULL);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}

/**
 * @brief pwm 占空比100%输出
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
void cp_pwm9_full(void)
{
    rt_pwm_set(pwm_dev2, PWM2_DEV_CHANNEL, CP_PERIOD, CP_CH_NULL);
    rt_pwm_enable(pwm_dev2, PWM2_DEV_CHANNEL);
}

/**
 * @brief pwm 制定的 CP_CH_PULSE 输出   设置PWM周期和脉冲宽度
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
void cp1_pwm_ch_puls(void)
{
    /***cp1  pwm53%***/
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, CP_PERIOD, CP_CH_PULSE);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}

void cp2_pwm_ch_puls(void)
{
    /***cp2  pwm53%***/
    rt_pwm_set(pwm_dev2, PWM2_DEV_CHANNEL, CP_PERIOD, CP_CH_PULSE);
    rt_pwm_enable(pwm_dev2, PWM2_DEV_CHANNEL);
}

//7kw一半
void cp1_pwm_ch_half(void)
{
    /***cp1  pwm26.6%***/
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, CP_PERIOD, CP_CH_PULSE_half);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}
void cp2_pwm_ch_half(void)
{
    /***cp2  pwm26.6%***/
    rt_pwm_set(pwm_dev2, PWM2_DEV_CHANNEL, CP_PERIOD, CP_CH_PULSE_half);
    rt_pwm_enable(pwm_dev2, PWM2_DEV_CHANNEL);
}



/**
 * @brief pwm 输出初始化
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
int32_t cp_pwm_init(void)
{
    timer1_pwm_init();
    timer9_pwm_init();
    cp_pwm_full();
    cp_pwm9_full(); // 初始一个通道即可
    return RT_EOK;
}


/**
 * @brief cp adc采样初始化
 * @param[in]
 * @param[out]
 * @return
 * @note
 */
/* 引脚支持adc1通道10 */

rt_adc_device_t adc_dev;
int32_t cp_adc_init(void)
{
    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(CP_ADC_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", CP_ADC_NAME);
        return RT_ERROR;
    }

    /* 使能设备 */
    rt_adc_enable(adc_dev, CP_ADC_CHANNEL);
    return RT_EOK;
}



rt_adc_device_t adc_dev2;
#define HWTIMER_DEV_NAME   "timer3"     /* 定时器名称 */

uint32_t ADCConvertedValue[2][100]= {0};
uint32_t	count = 0;

/* 定时器超时回调函数 */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    ADCConvertedValue[0][count] = rt_adc_read(adc_dev, CP_ADC_CHANNEL);   //A枪
    ADCConvertedValue[1][count]=  rt_adc_read(adc_dev2, CP2_ADC_CHANNEL); //B枪
    count++;
    if(count >= 100)
    {
        count = 0;
    }

    return 0;
}

static int hwtimer_sample()
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;      /* 定时器超时值 */
    rt_device_t hw_dev = RT_NULL;   /* 定时器设备句柄 */
    rt_hwtimer_mode_t mode;         /* 定时器模式 */
    rt_uint32_t freq = 1000000;               /* 计数频率 */

    /* 查找定时器设备 */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* 设置计数频率(若未设置该项，默认为1Mhz 或 支持的最小计数频率) */
    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    /* 设置模式为周期性定时器（若未设置，默认是HWTIMER_MODE_ONESHOT）*/
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* 设置定时器超时值为5s并启动定时器 */
    timeout_s.sec = 0;      /* 秒 */
    timeout_s.usec = 10;     /* 微秒 */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    /* 延时3500ms */
//    rt_thread_mdelay(3500);

    /* 读取定时器当前值 */
    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
//    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}



int32_t cp2_adc_init(void)
{
    /* 查找设备 */
    adc_dev2 = (rt_adc_device_t)rt_device_find(CP2_ADC_NAME);
    if (adc_dev2 == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", CP2_ADC_NAME);
        return RT_ERROR;
    }
    /* 使能设备 */
    //rt_adc_enable(adc_dev, CP_ADC_CHANNEL);
    /*****csh220921 ***/
    rt_adc_enable(adc_dev2, CP2_ADC_CHANNEL);

    hwtimer_sample();
    return RT_EOK;
}








void Swap(uint32_t *a,uint32_t *b)
{
    int t;
    t=*a;
    *a=*b;
    *b=t;
}
void BubbleSort(uint32_t * a,uint8_t n)
{
    int i,j;
    for(i=0; i<(n-1); i++)    //0728修改 外层循环 最后一个只有一个元素
    {
        int flag=0;
		for(j=0; j<(n-1)-i; j++)   //内层循环
        {
            if(a[j]>a[j+1])
            {
                Swap(&a[j],&a[j+1]);
                flag=1;
            }
        }
        if(flag==0) break;
    }
}



uint32_t adcbuf[GUN_MAX][100];
uint8_t  cpcount[GUN_MAX] = {0};
uint32_t ch_get_cp_volt(_GUN_NUM gun,uint32_t *puiCpVolt)
{
    uint8_t i;
    uint32_t alladc[GUN_MAX] = {0};
    uint8_t  adccount[GUN_MAX] = {0};
    cpcount[gun] = 0;
    for(i = 0; i < 100; i++)
    {
        /* 读取采样值 */
        if(ADCConvertedValue[gun][i] < CP_ADC_DIFF)
        {
            continue;
        }
        adcbuf[gun][cpcount[gun]] = ADCConvertedValue[gun][i];

        cpcount[gun]++;
    }
    if(cpcount[gun] < 5)
    {
        *puiCpVolt = 0;
        return 1;
    }
	
    BubbleSort(&adcbuf[gun][0],cpcount[gun]);  //排序大小
	
    if(cpcount[gun] > 40)
    {
        for(i = 10; i<cpcount[gun]-10; i++)
        {
            alladc[gun] += adcbuf[gun][i];
            adccount[gun]++;
        }
        alladc[gun] /= adccount[gun];
    }
    else if(cpcount[gun] > 20)
    {
        for(i = 5; i<cpcount[gun]-5; i++)
        {
            alladc[gun] += adcbuf[gun][i];
            adccount[gun]++;
        }
        alladc[gun] /= adccount[gun];
    }
    else
    {
        for(i = 0; i<cpcount[gun]; i++)
        {
            alladc[gun] += adcbuf[gun][i];
            adccount[gun]++;
        }
        alladc[gun] /= adccount[gun];
    }
    *puiCpVolt = alladc[gun] * 3.117 + 700;
    return cpcount[gun];
}


