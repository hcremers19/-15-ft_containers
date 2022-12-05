/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_node.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:12:01 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/05 15:28:22 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include <iostream>

namespace ft
{
	struct red_black_node
	{
		int				data;
		red_black_node*	parent;
		red_black_node*	left;
		red_black_node*	right;
		int				color;
	};
}

#endif

// Source: https://www.programiz.com/dsa/red-black-tree/