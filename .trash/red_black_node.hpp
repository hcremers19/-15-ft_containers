/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_node.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:12:01 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/06 11:55:52 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include <memory>

namespace ft
{
	template<class T, class Compare = std::less<T> >
	class red_black_node
	{
		public:
			typedef T											value_type;
			typedef red_black_node<value_type, Compare>			node_type;
			typedef red_black_node<const value_type, Compare>	node_const_type;
			typedef std::allocator<value_type>					alloc_type;
			typedef Compare										value_compare;
			typedef node_type*									pointer;
			typedef const node_type*							const_pointer;
			typedef size_t										size_type;

		private:
			value_type	data;
			pointer		parent;
			pointer		left;
			pointer		right;
			bool		color;
	};
}

#endif

// Source: https://www.programiz.com/dsa/red-black-tree/