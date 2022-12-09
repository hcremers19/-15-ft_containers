/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_node.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:30:27 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/06 15:54:53 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include "pair.hpp"
# include "../Iterators/tree_iterator.hpp"
# include "../Iterators/reverse_iterator.hpp"
# include <functional>

# define RED	false
# define BLACK	true

namespace ft
{
	template <class key, class T>
	class red_black_node
	{
		public:
			typedef	ft::pair<key, T>		value_type;
			typedef	const ft::pair<key, T>	const_value_type;
			typedef	value_type&				value_type_ref;
			typedef	const value_type&		const_value_type_ref;
			typedef	value_type*				value_type_ptr;
			typedef	const value_type*		const_value_type_ptr;

			red_black_node*	end;
			red_black_node*	parent;
			red_black_node*	left;
			red_black_node*	right;
			value_type		value;
			bool			color;

			/*Default constructor, Construct an empty node*/
			red_black_node() : end(NULL), parent(NULL), left(NULL), right(NULL), color(RED)
				{return;}

			/*Construct a node which has a parent and a value, but no child.*/
			red_black_node(red_black_node* parent, value_type val) : parent(parent), left(NULL), right(NULL), value(val), color(RED)
				{return;}

			/*Construct a top of the tree node.*/
			red_black_node(value_type val) : parent(NULL), left(NULL), right(NULL), value(val), color(RED)
				{return;}

			red_black_node(key first, T second) : parent(NULL), left(NULL), right(NULL), color(RED)
			{
				value._first = first;
				value._second = second;
				return;
			}

			~red_black_node()
				{return;}

			red_black_node&	operator=(const red_black_node& rhs)
			{
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				value = rhs.value;
				color = rhs->color;
				end = rhs->end;
			}

			bool is_leaf()
			{
				if (right == NULL && left == NULL)
					return (1);
				return (0);
			}
	};

	// Display Function just for vizualisation
	//  template <class key, class T>
	//  void printRBTRec(const std::string& prefix, const red_black_node<key, T>* node, bool isLeft)
	//  {
	//  	if (node != nullptr)
	//  	{
	//  		std::cout << prefix;
	//  		std::cout << (isLeft ? "├──" : "└──");
	//  		if (node->color)
	//  			std::cout << node->value.first << std::endl;
	//  		else
	//  		{
	//  			std::cout << "\033[31m" << node->value.first << "\033[0m" << std::endl;
	//  		}
	//  		printRBTRec(prefix + (isLeft ? "│   " : "    "), node->right, BLACK);
	//  		printRBTRec(prefix + (isLeft ? "│   " : "    "), node->left, RED);
	//  	}
	//  	else
	//  	{
	//  		std::cout << prefix;
	//  		std::cout << (isLeft ? "├──" : "└──");
	//  		std::cout << std::endl;
	//  	}
	//  }

	// template <class T>
	// struct less : public std::binary_function<T, T, bool>
	// {
	// 	bool operator()(const T& x, const T& y) const { return x < y; }
	// };
}

#endif