#if !defined(__ETH_MAC_H)
#define __ETH_MAC_H

#include <lwip/def.h>
#include <lwip/netif.h>
#include <lwip/err.h>

#define ETHMAC_TXBUFNB 2
#define ETHMAC_RXBUFNB 2
#define ETHMAC_TX_BUF_SIZE (1520 + 16)
#define ETHMAC_RX_BUF_SIZE (1520 + 16)

void sys_ethmac_init(void);

err_t sys_ethmac_netif_init(struct netif *netif);
void sys_ethmac_poll(int phy, struct netif *netif);

#endif // __ETH_MAC_H