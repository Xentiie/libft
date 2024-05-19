/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:49:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/16 05:21:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_int.h"

/*
Le boug de la vidéo parle d'un truc SUPER IMPORTANT sur l'ordre des bits:
https://youtu.be/SJPvNi4HrWQ?t=1403
Rule#1
Donc en gros quand on push un NOMBRE dans le stream, toujours least significant bit
Quand on a un byte entier, on le reverse et ca pars


Deflate:
https://youtu.be/SJPvNi4HrWQ?t=2891

1 block:
    IS_LAST  BTYPE   BITSTREAM...
    1 bit   2 bits

Plusieurs types de blocks:
Type 0: non-compressé
    IS_LAST  BTYPE   PADDING    SIZE    ~SIZE   BITSTREAM...
    1 bit   2 bits   5 bits   16 bits  16 bits

Type 1: back references

De ce que j'ai compris jusque la:
On se balade dans le stream de donné, tant qu'on trouve une séquence de charactères
qu'on n'a jamais vu, et on envoie tout dans le bitstream (pas rule#1 car pas nombre)

Quand on trouve une séquence qu'on connait, on fout a la place une back-reference:
on rentre la taille de la séquence connue (RULE#1 !!) (jsp sur cb de bytes/bits) puis
la distance (RULE#1 !!) a laquelle on a vu la séquence

La taille est entre 1-258 et la distance 1-32768 en arrière
Prefix codes:
Je crois qu'on assigne a chaque back reference un "prefix code", un code unique qui représente
une back ref. Pour determiner le code on utilise un code tree (??? voir huffman (sauf que dans la vidéo il dit
c'est pas huffman mais nsm))

Ce que fait deflate pour réduire le nombre de codes utilisé c'est que chaque charactères a un code,
et chaque LENGTH d'une back ref en a un aussi, donc si on croise un code pour une back ref, on
sait que derriere on a la distance, et boum pas besoin d'avoir un code unique pour chaque
combinaison length/distance


A partir de la je commence a plus suivre
LL CODES TABLE
https://youtu.be/SJPvNi4HrWQ?t=4077



https://youtu.be/SJPvNi4HrWQ?t=4652
*/

void ft_deflate(U8 *data, U64 size)
{
    
}

void ft_inflate()
{
    
}
