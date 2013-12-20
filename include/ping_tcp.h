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
 * \brief Initialisation des différentes structures et création d'un paquet tcp4_packet.
 * \param[in,out] t Paquet TCP + IPv4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] ia Informations sur la destination.
 * \param[in,out] dest Destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 */
void init_tcp4_ping (tcp4_packet * t, connexion * c, info_addr * ia, char * dest, compteur * cpt);

/**
 * \brief Envoie d'un paquet RAW en TCP.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] t Paquet TCP + IPv4.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 */
void send_paquet_TCP (connexion * c, tcp4_packet * t, compteur * cpt);

/**
 * \brief Réponse du paquet par une réception d'un paquet IP.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param[in,out] tv Temps d'attente de réception.
 */
void answer_send_TCP (connexion * c, compteur * cpt, struct timeval * tv);

/**
 * \brief Fonction réalisant l'affichage et l'application de Ping en TCP.
 * \param[in,out] t Paquet TCP + IPv4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param[in,out] req Temps d'attente du sleep.
 * \param[in,out] tv Temps d'attente de la réception.
 */
void pi_ng_tcp(tcp4_packet * t, connexion * c, compteur * cpt, struct timespec * req, struct timeval * tv);

/**
 * \brief Fonction réalisant l'affichage et l'application de Ping avec le choix précis des attentes en TCP.
 * \param[in,out] t Paquet TCP + IPv4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param secondes_sleep secondes d'attente du sleep.
 * \param nanosecondes_sleep nanosecondes d'attente du sleep.
 * \param secondes_rec secondes d'attente de réception.
 * \param nanosecondes_sleep microsecondes d'attente de réception.
 */
void pi_ng_tcp_choix_sleep_et_attente_reception(tcp4_packet * t, connexion * c, compteur * cpt, time_t secondes_sleep, long nanosecondes_sleep, int secondes_rec, int microsecondes_rec);

#endif /* __PING_TCP_H */
