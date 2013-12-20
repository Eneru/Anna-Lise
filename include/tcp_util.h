/**
 * \file tcp_util.h
 * \brief Utilitaires TCP (header)
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

#ifndef __TCP_UTIL_H
#define __TCP_UTIL_H

#include <netinet/tcp.h>
#include <sys/types.h>
#include <errno.h>

#include "base.h"
#include "checksum.h"
#include "address.h"

/**
 * \brief TCP header.
 */
typedef struct tcphdr tcphdr;

/**
 * \brief Modifie le port source.
 * \param[in,out] t Header TCP.
 * \param src Port source.
 */
int tcp_set_port_source (tcphdr * t, u_int16_t src);

/**
 * \brief Modifie le port de destination.
 * \param[in,out] t Header TCP.
 * \param dest Port de destination.
 */
int tcp_set_port_destination (tcphdr * t, u_int16_t dest);

/**
 * \brief Modifie le numéro de séquence.
 * \param[in,out] t Header TCP.
 * \param sequence Numéro de séquence.
 */
int tcp_set_seq (tcphdr * t, u_int32_t sequence);

/**
 * \brief Modifie le numéro de l'accusé de réception.
 * \param[in,out] t Header TCP.
 * \param acquittement_sequence Numéro de l'accusé de récpetion.
 */
int tcp_set_ack_seq (tcphdr * t, u_int32_t acquittement_sequence);

/**
 * \brief Modifie du champ réservé 1.
 * \param[in,out] t Header TCP.
 * \param reserved1 Champ réservé 1.
 */
int tcp_set_reserved1 (tcphdr * t, u_int16_t reserved1);

/**
 * \brief Modifie du champ réservé 2.
 * \param[in,out] t Header TCP.
 * \param reserved1 Champ réservé 2.
 */
int tcp_set_reserved2 (tcphdr * t, u_int16_t reserved2);

/**
 * \brief Modifie l'offset des données.
 * \param[in,out] t Header TCP.
 * \param taille Début des données.
 */
int tcp_set_offset (tcphdr * t, u_int16_t taille);

/**
 * \brief Modifie le champ de fin.
 * \param[in,out] t Header TCP.
 * \param fin Champ de fin.
 */
int tcp_set_fin (tcphdr * t, u_int16_t fin);

/**
 * \brief Modifie le champ de synchronisation.
 * \param[in,out] t Header TCP.
 * \param synchronisation Champ de synchronisation.
 */
int tcp_set_syn (tcphdr * t, u_int16_t synchronisation);

/**
 * \brief Modifie le champ de réinitilasation.
 * \param[in,out] t Header TCP.
 * \param reinitilasation Champ de réinitilasation.
 */
int tcp_set_rst (tcphdr * t, u_int16_t reinitialisation);

/**
 * \brief Modifie le champ d'attente de remplissage de tampon.
 * \param[in,out] t Header TCP.
 * \param attente_remplissage_buffer Champ de remplissage.
 */
int tcp_set_psh (tcphdr * t, u_int16_t attente_remplissage_buffer);

/**
 * \brief Modifie le champ de validité d'un acquittement.
 * \param[in,out] t Header TCP.
 * \param validite_acquittement Champ de validité d'un acquittement.
 */
int tcp_set_ack (tcphdr * t, u_int16_t validite_acquittement);

/**
 * \brief Modifie le champ d'urgence d'envoie d'un paquet.
 * \param[in,out] t Header TCP.
 * \param urgence Champ d'urgence d'envoie d'un paquet.
 */
int tcp_set_urg (tcphdr * t, u_int16_t urgence);

/**
 * \brief Modifie la taille de la fenêtre.
 * \param[in,out] t Header TCP.
 * \param fenetre Taille de la fenêtre.
 */
int tcp_set_window (tcphdr * t, u_int16_t fenetre);

/**
 * \brief Modifie le champ de validité d'un paquet TCP.
 * \param[in,out] t Header TCP.
 * \param _checksum Valeur du checksum du paquet.
 */
int tcp_set_check (tcphdr * t, u_int16_t _checksum);

/**
 * \brief Modifie l'adresse du pointeur sur le paquet urgent.
 * \param[in,out] t Header TCP.
 * \param adresse_pointeur_urgent Adresse du pointeur sur le paquet urgent.
 */
int tcp_set_urg_ptr (tcphdr * t, u_int16_t adresse_pointeur_urgent);

/**
 * \brief Affichage paquet TCP.
 * \param[in,out] t Header TCP.
 */
void tcp_print (tcphdr * t);

#endif /* __ICMP_UTIL_H */
