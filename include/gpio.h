// gpio.h

#if !defined(__GPIO_H)
#define __GPIO_H

#define GPIO_USER1_LED              GPIO8
#define GPIO_BANK_USER1_LED         GPIOA
#define GPIO_USER2_LED              GPIO9
#define GPIO_BANK_USER2_LED         GPIOA
#define GPIO_ERROR_LED              GPIO10
#define GPIO_BANK_ERROR_LED         GPIOA

#define GPIO_RMII_MDC               GPIO1
#define GPIO_BANK_RMII_MDC          GPIOC
#define GPIO_RMII_MDIO              GPIO2
#define GPIO_BANK_RMII_MDIO         GPIOA

#define GPIO_RMII_REFCLK            GPIO1
#define GPIO_BANK_RMII_REFCLK       GPIOA
#define GPIO_RMII_TXEN              GPIO11
#define GPIO_RMII_TXD0              GPIO12
#define GPIO_RMII_TXD1              GPIO13
#define GPIO_BANK_RMII_TX           GPIOB
#define GPIO_RMII_RXD0              GPIO4
#define GPIO_RMII_RXD1              GPIO5
#define GPIO_BANK_RMII_RX           GPIOC
#define GPIO_RMII_CRS_DV            GPIO7
#define GPIO_BANK_RMII_CRS_DV       GPIOA


void sys_gpio_init(void);

#endif // __GPIO_H