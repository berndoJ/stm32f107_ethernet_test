## MAKEFILE

FW_NAME        = liblwiparm32

Q              = @


INC          = -I ./include
INC         += -I ../../include

LIBDIRS      = -L $(LIBDIR_OPENCM3)

SOURCEDIR    = .

COREFILES=$(SOURCEDIR)/core/init.o \
	$(SOURCEDIR)/core/def.o \
	$(SOURCEDIR)/core/dns.o \
	$(SOURCEDIR)/core/inet_chksum.o \
	$(SOURCEDIR)/core/ip.o \
	$(SOURCEDIR)/core/mem.o \
	$(SOURCEDIR)/core/memp.o \
	$(SOURCEDIR)/core/netif.o \
	$(SOURCEDIR)/core/pbuf.o \
	$(SOURCEDIR)/core/raw.o \
	$(SOURCEDIR)/core/stats.o \
	$(SOURCEDIR)/core/sys.o \
	$(SOURCEDIR)/core/altcp.o \
	$(SOURCEDIR)/core/altcp_alloc.o \
	$(SOURCEDIR)/core/altcp_tcp.o \
	$(SOURCEDIR)/core/tcp.o \
	$(SOURCEDIR)/core/tcp_in.o \
	$(SOURCEDIR)/core/tcp_out.o \
	$(SOURCEDIR)/core/timeouts.o \
	$(SOURCEDIR)/core/udp.o

CORE4FILES=$(SOURCEDIR)/core/ipv4/acd.o \
	$(SOURCEDIR)/core/ipv4/autoip.o \
	$(SOURCEDIR)/core/ipv4/dhcp.o \
	$(SOURCEDIR)/core/ipv4/etharp.o \
	$(SOURCEDIR)/core/ipv4/icmp.o \
	$(SOURCEDIR)/core/ipv4/igmp.o \
	$(SOURCEDIR)/core/ipv4/ip4_frag.o \
	$(SOURCEDIR)/core/ipv4/ip4.o \
	$(SOURCEDIR)/core/ipv4/ip4_addr.o

CORE6FILES=$(SOURCEDIR)/core/ipv6/dhcp6.o \
	$(SOURCEDIR)/core/ipv6/ethip6.o \
	$(SOURCEDIR)/core/ipv6/icmp6.o \
	$(SOURCEDIR)/core/ipv6/inet6.o \
	$(SOURCEDIR)/core/ipv6/ip6.o \
	$(SOURCEDIR)/core/ipv6/ip6_addr.o \
	$(SOURCEDIR)/core/ipv6/ip6_frag.o \
	$(SOURCEDIR)/core/ipv6/mld6.o \
	$(SOURCEDIR)/core/ipv6/nd6.o

# APIFILES: The files which implement the sequential and socket APIs.
APIFILES=$(SOURCEDIR)/api/api_lib.o \
	$(SOURCEDIR)/api/api_msg.o \
	$(SOURCEDIR)/api/err.o \
	$(SOURCEDIR)/api/if_api.o \
	$(SOURCEDIR)/api/netbuf.o \
	$(SOURCEDIR)/api/netdb.o \
	$(SOURCEDIR)/api/netifapi.o \
	$(SOURCEDIR)/api/sockets.o \
	$(SOURCEDIR)/api/tcpip.o

# NETIFFILES: Files implementing various generic network interface functions
NETIFFILES=$(SOURCEDIR)/netif/ethernet.o \
	$(SOURCEDIR)/netif/bridgeif.o \
	$(SOURCEDIR)/netif/bridgeif_fdb.o \
	$(SOURCEDIR)/netif/slipif.o

# SIXLOWPAN: 6LoWPAN
SIXLOWPAN=$(SOURCEDIR)/netif/lowpan6_common.o \
        $(SOURCEDIR)/netif/lowpan6.o \
	$(SOURCEDIR)/netif/lowpan6_ble.o \
	$(SOURCEDIR)/netif/zepif.o

# PPPFILES: PPP
PPPFILES=$(SOURCEDIR)/netif/ppp/auth.o \
	$(SOURCEDIR)/netif/ppp/ccp.o \
	$(SOURCEDIR)/netif/ppp/chap-md5.o \
	$(SOURCEDIR)/netif/ppp/chap_ms.o \
	$(SOURCEDIR)/netif/ppp/chap-new.o \
	$(SOURCEDIR)/netif/ppp/demand.o \
	$(SOURCEDIR)/netif/ppp/eap.o \
	$(SOURCEDIR)/netif/ppp/ecp.o \
	$(SOURCEDIR)/netif/ppp/eui64.o \
	$(SOURCEDIR)/netif/ppp/fsm.o \
	$(SOURCEDIR)/netif/ppp/ipcp.o \
	$(SOURCEDIR)/netif/ppp/ipv6cp.o \
	$(SOURCEDIR)/netif/ppp/lcp.o \
	$(SOURCEDIR)/netif/ppp/magic.o \
	$(SOURCEDIR)/netif/ppp/mppe.o \
	$(SOURCEDIR)/netif/ppp/multilink.o \
	$(SOURCEDIR)/netif/ppp/ppp.o \
	$(SOURCEDIR)/netif/ppp/pppapi.o \
	$(SOURCEDIR)/netif/ppp/pppcrypt.o \
	$(SOURCEDIR)/netif/ppp/pppoe.o \
	$(SOURCEDIR)/netif/ppp/pppol2tp.o \
	$(SOURCEDIR)/netif/ppp/pppos.o \
	$(SOURCEDIR)/netif/ppp/upap.o \
	$(SOURCEDIR)/netif/ppp/utils.o \
	$(SOURCEDIR)/netif/ppp/vj.o \
	$(SOURCEDIR)/netif/ppp/polarssl/arc4.o \
	$(SOURCEDIR)/netif/ppp/polarssl/des.o \
	$(SOURCEDIR)/netif/ppp/polarssl/md4.o \
	$(SOURCEDIR)/netif/ppp/polarssl/md5.o \
	$(SOURCEDIR)/netif/ppp/polarssl/sha1.o

# LWIPNOAPPSFILES: All LWIP files without apps
LWIPNOAPPSFILES=$(COREFILES) \
	$(CORE4FILES) \
	$(CORE6FILES) \
	$(APIFILES) \
	$(NETIFFILES) \
	$(PPPFILES) \
	$(SIXLOWPAN)

# SNMPFILES: SNMPv2c agent
SNMPFILES=$(SOURCEDIR)/apps/snmp/snmp_asn1.o \
	$(SOURCEDIR)/apps/snmp/snmp_core.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_icmp.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_interfaces.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_ip.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_snmp.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_system.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_tcp.o \
	$(SOURCEDIR)/apps/snmp/snmp_mib2_udp.o \
	$(SOURCEDIR)/apps/snmp/snmp_snmpv2_framework.o \
	$(SOURCEDIR)/apps/snmp/snmp_snmpv2_usm.o \
	$(SOURCEDIR)/apps/snmp/snmp_msg.o \
	$(SOURCEDIR)/apps/snmp/snmpv3.o \
	$(SOURCEDIR)/apps/snmp/snmp_netconn.o \
	$(SOURCEDIR)/apps/snmp/snmp_pbuf_stream.o \
	$(SOURCEDIR)/apps/snmp/snmp_raw.o \
	$(SOURCEDIR)/apps/snmp/snmp_scalar.o \
	$(SOURCEDIR)/apps/snmp/snmp_table.o \
	$(SOURCEDIR)/apps/snmp/snmp_threadsync.o \
	$(SOURCEDIR)/apps/snmp/snmp_traps.o

# HTTPFILES: HTTP server + client
HTTPFILES=$(SOURCEDIR)/apps/http/altcp_proxyconnect.o \
	$(SOURCEDIR)/apps/http/fs.o \
	$(SOURCEDIR)/apps/http/http_client.o \
	$(SOURCEDIR)/apps/http/httpd.o

# MAKEFSDATA: MAKEFSDATA HTTP server host utility
MAKEFSDATAFILES=$(SOURCEDIR)/apps/http/makefsdata/makefsdata.o

# LWIPERFFILES: IPERF server
LWIPERFFILES=$(SOURCEDIR)/apps/lwiperf/lwiperf.o

# SMTPFILES: SMTP client
SMTPFILES=$(SOURCEDIR)/apps/smtp/smtp.o

# SNTPFILES: SNTP client
SNTPFILES=$(SOURCEDIR)/apps/sntp/sntp.o

# MDNSFILES: MDNS responder
MDNSFILES=$(SOURCEDIR)/apps/mdns/mdns.o \
	$(SOURCEDIR)/apps/mdns/mdns_out.o \
	$(SOURCEDIR)/apps/mdns/mdns_domain.o

# NETBIOSNSFILES: NetBIOS name server
NETBIOSNSFILES=$(SOURCEDIR)/apps/netbiosns/netbiosns.o

# TFTPFILES: TFTP client/server files
TFTPFILES=$(SOURCEDIR)/apps/tftp/tftp.o

# MQTTFILES: MQTT client files
MQTTFILES=$(SOURCEDIR)/apps/mqtt/mqtt.o

# MBEDTLS_FILES: MBEDTLS related files of lwIP rep
MBEDTLS_FILES=$(SOURCEDIR)/apps/altcp_tls/altcp_tls_mbedtls.o \
	$(SOURCEDIR)/apps/altcp_tls/altcp_tls_mbedtls_mem.o \
	$(SOURCEDIR)/apps/snmp/snmpv3_mbedtls.o

# LWIPAPPFILES: All LWIP APPs
LWIPAPPFILES=$(SNMPFILES) \
	$(HTTPFILES) \
	$(LWIPERFFILES) \
	$(SMTPFILES) \
	$(SNTPFILES) \
	$(MDNSFILES) \
	$(NETBIOSNSFILES) \
	$(TFTPFILES) \
	$(MQTTFILES) \
	$(MBEDTLS_FILES)



OBJS         = $(LWIPNOAPPSFILES)

CFLAGS       = -Os -ggdb3
CPPFLAGS     = -MD $(DEFS) $(INC)
FP_FLAGS	?= -msoft-float
ARCH_FLAGS	 = -mthumb -mcpu=cortex-m3 $(FP_FLAGS) -mfix-cortex-m3-ldrd

PREFIX		 ?= arm-none-eabi

CC		     := $(PREFIX)-gcc
CXX		     := $(PREFIX)-g++
LD		     := $(PREFIX)-gcc
AR		     := $(PREFIX)-ar
AS		     := $(PREFIX)-as
OBJCOPY		 := $(PREFIX)-objcopy
OBJDUMP		 := $(PREFIX)-objdump
GDB		     := $(PREFIX)-gdb
SIZE		 := $(PREFIX)-size


.PHONY: all clean rebuild rebuild-flash flash size __endsplash
.PRECIOUS: %.o

all: $(FW_NAME).a

clean:
	$(Q)find $(SOURCEDIR) -name "*.o" -type f -delete
	$(Q)find $(SOURCEDIR) -name "*.d" -type f -delete
	$(Q)find . -name "*.a" -type f -delete

rebuild: clean all

%.o: %.c
	@printf "  CC      $<\n"
	$(Q)$(CC) $(CFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $@ -c $<

%.o: %.cxx
	@printf "  CXX     $<\n"
	$(Q)$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $@ -c $<

%.o: %.cpp
	@printf "  CXX     $(*).cpp\n"
	$(Q)$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $@ -c $<

%.a: $(OBJS)
	@printf "  AR      $@\n"
	$(Q)$(AR) cr $@ $(OBJS)

