#include "main.h"

#include "gpio.h"
#include "uart.h"
#include "tick.h"
#include "syscalls.h"
#include "ethmac.h"

#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/ethernet/mac.h>
#include <libopencm3/ethernet/phy.h>

#include <netif/etharp.h>
#include <lwip/init.h>
#include <lwip/dhcp.h>
#include <lwip/ip_addr.h>

static void cpu_clock_setup(void);

struct netif networkif;

static ip_addr_t ipaddr, netmask, gateway;

int main(void)
{
    cpu_clock_setup();

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    sys_tick_init();
    sys_gpio_init();
    sys_uart_init();

    // Clear the console and print welcome message.
    printf("\033[2J\nSTM32F107 Ethernet Test v1.0 Debug Console\n\n");

    sys_ethmac_init();

    // Test LEDs.
    gpio_set(GPIO_BANK_USER1_LED, GPIO_USER1_LED);
    gpio_set(GPIO_BANK_USER2_LED, GPIO_USER2_LED);
    gpio_set(GPIO_BANK_ERROR_LED, GPIO_ERROR_LED);
    sys_tick_delay(500);
    gpio_clear(GPIO_BANK_USER1_LED, GPIO_USER1_LED);
    gpio_clear(GPIO_BANK_USER2_LED, GPIO_USER2_LED);
    gpio_clear(GPIO_BANK_ERROR_LED, GPIO_ERROR_LED);

    printf("[%09.3lf] System hardware initialised.\n\n", sys_get_tick() / (double)1000);

    // Initialise LwIP stack and ethernet.
    printf("[%09.3lf] Initialising network interface...\n", sys_get_tick() / (double)1000);
    lwip_init();
    printf("[%09.3lf] LwIP init done\n", sys_get_tick() / (double)1000);
    ip4addr_aton("10.42.0.8", &ipaddr);
    ip4addr_aton("255.255.255.0", &netmask);
    ip4addr_aton("10.42.0.1", &gateway);
    netif_add(&networkif, &ipaddr, &netmask, &gateway, NULL, &sys_ethmac_netif_init, &ethernet_input);
    netif_set_default(&networkif);
    netif_set_up(&networkif);
    printf("[%09.3lf] LwIP netif setup done\n", sys_get_tick() / (double)1000);
    //dhcp_start(&networkif);
    //printf("[%09.3lf] Started DHCP.\n", sys_get_tick() / (double)1000);
    printf("[%09.3lf] Network interface initialised.\n", sys_get_tick() / (double)1000);

    

    while (1)
    {
        sys_ethmac_poll(PHY0, &networkif);
    }

    return 0;
}

static void cpu_clock_setup(void)
{
    // Configure the internal clock to 72MHz using an external 16MHz crystal.
    rcc_clock_setup_in_hse_16mhz_out_72mhz();

    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_AFIO);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_ETHMAC);
    rcc_periph_clock_enable(RCC_ETHMACRX);
    rcc_periph_clock_enable(RCC_ETHMACTX);

    rcc_set_pll3_multiplication_factor(RCC_CFGR2_PLL3MUL_PLL3_CLK_MUL10);
    rcc_osc_on(RCC_PLL3);
    rcc_wait_for_osc_ready(RCC_PLL3);
    rcc_set_mco(RCC_CFGR_MCO_PLL3);
}