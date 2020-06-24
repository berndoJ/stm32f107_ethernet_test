#include "ethmac.h"

#include "tick.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/ethernet/mac.h>
#include <libopencm3/ethernet/phy.h>
#include <libopencm3/ethernet/phy_lan87xx.h>

#include <lwip/def.h>
#include <lwip/mem.h>
#include <lwip/pbuf.h>
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include <netif/etharp.h>

uint8_t eth_descs[(ETHMAC_TXBUFNB * ETHMAC_TX_BUF_SIZE) + (ETHMAC_RXBUFNB * ETHMAC_RX_BUF_SIZE)];
static uint8_t _eth_framebuffer[2000];
static bool last_link;

static err_t _sys_ethmac_ll_tx(struct netif *netif, struct pbuf *p);
static struct pbuf *_sys_ethmac_ll_rx(struct netif *netif);

void sys_ethmac_init(void)
{
    // Reset the MAC.
    rcc_periph_reset_pulse(RST_ETHMAC);

    // Init ethernet.
    eth_init(PHY0, ETH_CLK_060_100MHZ);
    eth_desc_init(eth_descs, ETHMAC_TXBUFNB, ETHMAC_RXBUFNB, ETHMAC_TX_BUF_SIZE, ETHMAC_RX_BUF_SIZE, false);
    eth_start();
}

err_t sys_ethmac_netif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

    #if LWIP_NETIF_HOSTNAME
    netif->hostname = "lwip";
    #endif

    //NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);

    netif->name[0] = 'e';
    netif->name[1] = 'n';
    netif->output = etharp_output;
    netif->linkoutput = _sys_ethmac_ll_tx;

    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    netif->hwaddr[0] = 0x00;
    netif->hwaddr[1] = 0x80;
    netif->hwaddr[2] = 0xFF;
    netif->hwaddr[3] = 0xFF;
    netif->hwaddr[4] = 0xFF;
    netif->hwaddr[5] = 0x01;
    eth_set_mac(netif->hwaddr);

    netif->mtu = 1500;

    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

    return ERR_OK;
}

void sys_ethmac_poll(int phy, struct netif *netif)
{
    bool link_active;
    struct eth_hdr *ethhdr;
    struct pbuf *p;

    link_active = phy_link_isup(phy);

    if (link_active != last_link)
    {
        last_link = link_active;

        if (last_link)
        {
            netif_set_link_up(netif);
            printf("[%09.3lf] en%d link changed to UP.\n", sys_get_tick() / (double)1000, phy);
        }
        else
        {
            netif_set_link_down(netif);
            printf("[%09.3lf] en%d link changed to DOWN.\n", sys_get_tick() / (double)1000, phy);
        }        
    }

    p = _sys_ethmac_ll_rx(netif);

    if (p == NULL)
        return;
    
    ethhdr = p->payload;

    switch (htons(ethhdr->type))
    {
        case ETHTYPE_IP:
        case ETHTYPE_ARP:
        #if PPPOE_SUPPORT
        case ETHTYPE_PPPOEDISC:
        case ETHTYPE_PPPOE:
        #endif
            if (netif->input(p, netif) != ERR_OK)
            {
                LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
                pbuf_free(p);
                p = NULL;
            }
            break;
        default:
            pbuf_free(p);
            p = NULL;
            break;
    }
}

static err_t _sys_ethmac_ll_tx(struct netif *netif, struct pbuf *p)
{
    uint32_t idx = 0;
    struct pbuf *cur;

    #if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE);
    #endif

    // Copy the complete frame into the framebuffer.
    for (cur = p; cur != NULL; cur = p->next)
    {
        memcpy(&_eth_framebuffer[idx], cur->payload, cur->len);
        idx += cur->len;
    }

    // Transmit the frame.
    eth_tx(_eth_framebuffer, idx);

    #if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE);
    #endif

    return ERR_OK;
}

static struct pbuf *_sys_ethmac_ll_rx(struct netif *netif)
{
    struct pbuf *p, *cur;
    uint32_t idx = 0, packet_size = 0;

    // Copy a recieved packet into the framebuffer and retrieve it's size.
    if (!eth_rx(_eth_framebuffer, &packet_size, sizeof(_eth_framebuffer)))
        return NULL;
    
    #if ETH_PAD_SIZE
    packet_size += ETH_PAD_SIZE;
    #endif

    p = pbuf_alloc(PBUF_RAW, packet_size, PBUF_POOL);

    if (p != NULL)
    {
        #if ETH_PAD_SIZE
        pbuf_header(p, -ETH_PAD_SIZE);
        #endif

        for (cur = p; cur != NULL; cur = cur->next)
        {
            memcpy(cur->payload, &_eth_framebuffer[idx], cur->len);
            idx += cur->len;
        }

        #if ETH_PAD_SIZE
        pbuf_header(p, ETH_PAD_SIZE);
        #endif
    }

    return p;
}

uint32_t sys_now()
{
    return sys_get_tick();
}