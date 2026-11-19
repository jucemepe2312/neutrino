/*
 * neutrino.c - Sniffer de red en C puro para Linux
 * Copyright (C) 2026 Julio <jucemepe2312@gmail.com>
 *
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo
 * bajo los términos de la GNU General Public License publicada por la
 * Free Software Foundation, ya sea la versión 3 de la Licencia, o
 * (a tu elección) cualquier versión posterior.
 *
 * Este programa se distribuye con la esperanza de que sea útil,
 * pero SIN NINGUNA GARANTÍA; ni siquiera la garantía implícita de
 * COMERCIABILIDAD o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. Véase la
 * GNU General Public License para más detalles.
 *
 * Deberías haber recibido una copia de la GNU General Public License
 * junto con este programa. Si no, consulta <https://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

void procesar_paquete(unsigned char *buffer, int tam)
{

    struct ethhdr *eth = (struct ethhdr *) buffer;
    if (ntohs(eth->h_proto) == ETH_P_IP)
    {
        struct iphdr *ip = (struct iphdr *) (buffer + sizeof(struct ethhdr));

        char ip_origen[16];
        uint32_t ip_lista = ntohl(ip->saddr);
        inet_ntop(AF_INET, &(ip_lista), ip_origen, sizeof(ip_origen));

        char ip_destino[16];
        uint32_t ip_ddestino = ntohl(ip->daddr);
        inet_ntop(AF_INET, &(ip_ddestino), ip_destino, sizeof(ip_destino));

        if (ip->protocol == 6)
        {
            struct tcphdr *tcp = (struct tcphdr *) ((unsigned char *) ip + (ip->ihl * 4));
            printf("[TCP] %s:%d -> %s:%d\n",
                   ip_origen,
                   ntohs(tcp->source),
                   ip_destino,
                   ntohs(tcp->dest));
        }

        if (ip->protocol == 17)
        {
            struct udphdr *udp = (struct udphdr *) ((unsigned char *) ip + (ip->ihl * 4));
            printf("[UDP] %s:%d -> %s:%d\n",
                   ip_origen,
                   ntohs(udp->source),
                   ip_destino,
                   ntohs(udp->dest));
        }
    }
}

int main()
{
    int fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd < 0)
    {
        printf("correme como sudo por favor\n");
        return 1;
    }

    unsigned char buffer[65536];
    while (1)
    {
        ssize_t n = recvfrom(fd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (n > 0)
        {
            procesar_paquete(buffer, (int) n);

        }
    }
    return 0;
}
