/**
 * \file tcp_util.h
 * \brief Utilitaires ICMP (implémentation)
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

#include "tcp_util.h"

int tcp_set_port_source(tcphdr * t, u_int16_t src)
{
	t->source = src;
	return 0;
}

int tcp_set_port_destination(tcphdr * t, u_int16_t dest)
{
	t->dest = dest;
	return 0;
}

int tcp_set_seq (tcphdr * t, u_int32_t sequence)
{
	t->seq = sequence;
	return 0;
}

int tcp_set_ack_seq (tcphdr * t, u_int32_t acquittement_sequence)
{
	t->ack_seq = acquittement_sequence;
	return 0;
}

int tcp_set_reserved1 (tcphdr * t, u_int16_t reserved1)
{
	t->res1 = reserved1;
	return 0;
}

int tcp_set_reserved2 (tcphdr * t, u_int16_t reserved2)
{
	t->res2 = reserved2;
	return 0;
}

int tcp_set_offset (tcphdr * t, u_int16_t taille)
{
	t->doff = taille;
	return 0;
}

int tcp_set_fin (tcphdr * t, u_int16_t fin)
{
	t->fin = fin;
	return 0;
}

int tcp_set_syn (tcphdr * t, u_int16_t synchronisation)
{
	t->syn = synchronisation;
	return 0;
}

int tcp_set_rst (tcphdr * t, u_int16_t reinitialisation)
{
	t->rst = reinitialisation;
	return 0;
}

int tcp_set_psh (tcphdr * t, u_int16_t attente_remplissage_buffer)
{
	t->psh = attente_remplissage_buffer;
	return 0;
}

int tcp_set_ack (tcphdr * t, u_int16_t validite_acquittement)
{
	t->ack = validite_acquittement;
	return 0;
}

int tcp_set_urg (tcphdr * t, u_int16_t urgence)
{
	t->urg = urgence;
	return 0;
}

int tcp_set_window (tcphdr * t, u_int16_t fenetre)
{
	t->window = fenetre;
	return 0;
}

int tcp_set_check (tcphdr * t, u_int16_t _checksum)
{
	t->check = _checksum;
	return 0;
}

int tcp_set_urg_ptr (tcphdr * t, u_int16_t adresse_pointeur_urgent)
{
	t->urg_ptr = adresse_pointeur_urgent;
	return 0;
}

void tcp_print (tcphdr * t)
{
	printf("====Affichage paquet TCP==== \n\n");
	
		printf("\t-Source: %d\n",t->source);
		printf("\t-Destination: %d\n",t->dest);
		printf("\t-Sequence: %d\n",t->seq);
		printf("\t-Acquitement de la Sequence: %d\n",t->ack_seq);
		printf("\t-Espace réservé 1: %d\n",t->res1);
		printf("\t-Espace réservé 2: %d\n",t->res2);
		printf("\t-Début des données: %d\n",t->doff);
		printf("\t-Fin d'envoie: %d\n",t->fin);
		printf("\t-Synchronisation d'envoie: %d\n",t->syn);
		printf("\t-Réinitialisation d'envoie: %d\n",t->rst);
		printf("\t-Non attente du remplissage du tampon: %d\n",t->psh);
		printf("\t-Validité de l'acquittement: %d\n",t->ack);
		printf("\t-Urgence d'envoie: %d\n",t->urg);
		printf("\t-Taille de la fenêtre: %d\n",t->window);
		printf("\t-Validité paquet: %d\n",t->check);
		printf("\t-Adresse du paquet urgent: %d\n",t->urg_ptr);
}


int tcp_checksum (iphdr * ip_header, tcphdr * tcp_header)
{
	int success = -1;
    tcphdr t = *tcp_header;
    t.check = 0;
    fake_iphdr f = (fake_iphdr) { 0, 0, 0, IPPROTO_TCP, ip_header->tot_len };
    fake_tcp_packet fake = (fake_tcp_packet) { f, t };

    fake.tcp_header.check = checksum(&fake, sizeof fake / 2);
    int check = checksum(&fake, sizeof fake / 2);
    if (check == 0)
    {
        tcp_header->check = fake.tcp_header.check;
        success = 0;
    }

    return success;
}
