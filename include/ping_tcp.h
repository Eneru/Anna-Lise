/**
 * \file ping_tcp.h
 * \brief Implémentation de la fonction Ping avec TCP. (header)
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

#ifndef __PING_TCP_H
#define __PING_TCP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "base.h"
#include "icmp_util.h"
#include "ip_util.h"
#include "address.h"
#include "packet.h"
#include "time_util.h"
#include "ping_icmp.h"

/**
 * \brief Structure de connexion à une adresse.
 */
typedef struct connexion_tcp
{
	int sockfd;/**<- Socket de connexion.*/
	struct sockaddr_in addr;/**<- Adresse de connexion.*/
	u_int16_t port_destination;
} connexion_tcp;

/**
 * \brief Initialisation des différentes structures et création d'un paquet tcp4_packet.
 * \param[in,out] t Paquet TCP + IPv4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] ia Informations sur la destination.
 * \param[in,out] dest Destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 */
void init_tcp4_ping (tcp4_packet * t, connexion * c, info_addr * ia, char * dest, compteur * cpt);



#endif /* __PING_TCP_H */
