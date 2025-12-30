/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:05:39 by shotarokuri       #+#    #+#             */
/*   Updated: 2025/12/30 17:31:18 by skuriyam         ###   ########.fr       */
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
    t_node sent; //番兵（sentinel）ノードは「実体」として中に埋め込む
    size_t size; //要素数（番兵は含めない）
} t_list;

    
#endif