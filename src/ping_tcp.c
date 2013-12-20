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
	
	get_ipv4(dest,IPPROTO_TCP,&c->addr);
    reverse_dns_v4(ia->dom_dest,HOST_NAME_MAX+1,&c->addr);
    ia->addr_dest = char_to_ip(ia->dom_dest);
    ia->dest = extract_ipv4(&c->addr);
    ia->dest_de_base = dest;
    
    cpt->paquets_transmis = 0;
    cpt->paquets_recus = 0;
    
    tcp4_packet_init(t,ia->dest);
}

void send_paquet_TCP (connexion * c, tcp4_packet * t, compteur * cpt)
{
	int optval;
	create_raw_socket(AF_INET,SOCK_RAW,IPPROTO_RAW,&c->sockfd);
	setsockopt(c->sockfd,IPPROTO_IP,IP_HDRINCL,(char *)&optval,sizeof(optval));
	tcp_set_check(t,tcp_checksum(t->ip_header,t->tcp_header));
	
	
	sendto(c->sockfd, t, sizeof(tcp4_packet), 0, (struct sockaddr *)&c->addr, sizeof(struct sockaddr));
	cpt->paquets_transmis++;
	
	freedom(c->sockfd);
}

void answer_send_TCP (connexion * c, compteur * cpt, struct timeval * tv)
{
	int optval = 1;
	create_raw_socket(AF_INET,SOCK_RAW,IPPROTO_IP,&c->sockfd);
	struct sockaddr_in addr_source;
	get_source_ipv4(IPPROTO_IP,&addr_source);
	
	bind(c->sockfd,(struct sockaddr*) addr_source, sizeof(addr_source));
	setsockopt(c->sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&tampon,sizeof(tampon)); // mode non bloquant de la socket
	
	tcp4_packet packet;
	
	if(recvfrom(c->sockfd, &packet, sizeof *packet, 0, (struct sockaddr *) &c->addr, sizeof(struct sockaddr_in)) != -1)
	{
		cpt->paquets_recus++;
		printf("%lu bytes from ",sizeof(packet));
		print_host_v4(&c->addr);
		printf(": icmp_req=%d ttl=%d ", packet.tcp_header.seq, packet.ip_header.ttl);
    }
}

void pi_ng_tcp(tcp4_packet * t, connexion * c, compteur * cpt, struct timespec * req, struct timeval * tv)
{
	struct timeval debut, fin, diff;
	int avant = cpt->paquets_recus;
	gettimeofday(&debut,NULL);
	send_paquet_TCP(c,t,cpt);
	answer_send_TCP(c,cpt,tv);
	gettimeofday(&fin,NULL);
	diff = diff_timeval(debut,fin);
	if((avant == 0) &&(cpt->paquets_recus == 1))
	{
	    cpt->sum = .0;
		cpt->min = extract_time(diff);
		cpt->max = extract_time(diff);
	}
	rtt(diff,cpt);
	printf("time=%.2Lf ms\n",extract_time(diff));
	tcp_set_seq(t,t->tcp_header.seq+1);
    nanosleep(req,NULL);
}

void pi_ng_tcp_choix_sleep_et_attente_reception(tcp4_packet * t, connexion * c, compteur * cpt, time_t secondes_sleep, long nanosecondes_sleep, int secondes_rec, int microsecondes_rec)
{
	struct timespec req = {secondes_sleep,nanosecondes_sleep};
	struct timeval tv = {secondes_rec,microsecondes_rec};
	pi_ng(t,c,cpt,&req,&tv);
}
