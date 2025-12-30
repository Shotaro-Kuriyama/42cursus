/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shotarokuriyama <shotarokuriyama@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:05:39 by shotarokuri       #+#    #+#             */
/*   Updated: 2025/12/29 10:40:05 by shotarokuri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCLIST_H
# define DCLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

//双方向リスト
typedef struct s_node {
    int v;
    struct s_node *prev;
    struct s__node *next;
} t_node;

typedef struct s_list {
    t_node sent; //番兵（sentinel）
    size_t size;
} t_list;

    
#endif