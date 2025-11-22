




#include <stdlib.h>
#include <sys/_stdint.h>
#include <sys/errno.h>
#include <zephyr/kernel.h>


#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(led_loop);

static int32_t isInit = 0;
static struct k_sem led_sem;


int32_t led_send() {
    if (isInit == 0) {
        LOG_INF("LED loop not initialized");
        return ENOENT;
    }
    k_sem_give(&led_sem);

    return 0;
}


static void led_loop(void *p1, void *p2, void *p3)
{

    k_sem_init(&led_sem, 0, 1);
    if (isInit == 0) {
        isInit = 1;
        LOG_INF("LED loop initialized");
    }

    while (1) {
        k_timeout_t timeout = K_MSEC(rand() % 100);

        k_sem_take(&led_sem, timeout);
        LOG_INF("LED loop running");
        /* Add your LED control code here */
    }
}



K_THREAD_DEFINE(led_thread, 2*1024, led_loop, NULL, NULL, NULL, 7, 0, 0);


