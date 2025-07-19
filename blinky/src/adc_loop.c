




#include "zephyr/sys/clock.h"
#include <stdlib.h>
#include <sys/_stdint.h>
#include <sys/errno.h>
#include <zephyr/kernel.h>


#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(adc_loop);

static int32_t isInit = 0;
static struct k_sem adc_sem;


int32_t adc_send() {
    if (isInit == 0) {
        LOG_INF("ADC loop not initialized");
        return ENOENT;
    }
    k_sem_give(&adc_sem);

    return 0;
}


static void adc_loop(void *p1, void *p2, void *p3)
{

    k_sem_init(&adc_sem, 0, 1);
    if (isInit == 0) {
        isInit = 1;
        LOG_INF("ADC loop initialized");
    }

    while (1) {
        k_timeout_t timeout = K_MSEC(rand() % 100);

        k_sem_take(&adc_sem, timeout);
        LOG_INF("ADC loop running");
        /* Add your LED control code here */
    }
}



K_THREAD_DEFINE(adc_thread, 2*1024, adc_loop, NULL, NULL, NULL, 7, 0, 0);


