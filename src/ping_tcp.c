/**
 * \file ping_tcp.c
 * \brief Implémentation de la fonction Ping avec TCP. (source)
 * \author MEYER Jérémy
 * \author RAZANAJATO Harenome
 * \date 2013
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
 
#include "ping_tcp.h"
 
void init_tcp4_ping (tcp4_packet * t, connexion * c, info_addr * ia, char * dest, compteur * cpt)
{
	tcp_set_port_source(t,(unsigned short)(rand()%64511+1+1024));   // Port entre 1025 et 65535
	tcp_set_seq(t,(unsigned long)((rand()%65536)*(rand()%65536)));  // Sequence aléatoire entre 0 et 4294967295
	get_ipv4(dest,IPPROTO_ICMP,&c->addr);
    reverse_dns_v4(ia->dom_dest,HOST_NAME_MAX+1,&c->addr);
    ia->addr_dest = char_to_ip(ia->dom_dest);
    ia->dest = extract_ipv4(&c->addr);
    ia->dest_de_base = dest;
    
    cpt->paquets_transmis = 0;
    cpt->paquets_recus = 0;
    
    icmp4_packet_init(p,ia->dest);
    create_raw_socket(AF_INET,SOCK_RAW,IPPROTO_ICMP,&c->sockfd);
}
