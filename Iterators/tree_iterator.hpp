/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:37:55 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/15 12:45:05 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "../Others/red_black_node.hpp"

namespace ft
{
	template<class T, class Compare = std::less<T>, class Node = red_black_node<T, Compare> >
	class tree_iterator
	{
		public:
			typedef T								value_type;
			typedef T&								reference;
			typedef T*								pointer;
			typedef ptrdiff_t						difference_type;
			typedef Node&							node_reference;
			typedef Node*							node_pointer;
			typedef tree_iterator<T, Compare, Node>	iterator;
			typedef bidirectional_iterator_tag		iterator_category;

		private:
			node_pointer	_content;

		public:
			/* ----- CONSTRUCTORS AND DESTRUCTORS ----- */

			tree_iterator()
				{return;}

			tree_iterator(const tree_iterator& src) : _content(src._content)
				{return;}

			tree_iterator(node_pointer ptr) : _content(ptr)
				{return;}

			~tree_iterator()
				{return;}


			/* ----- OPERATOR OVERLOADS ----- */

			operator			tree_iterator<const T, Compare, red_black_node<const T, Compare> >() const
			{
				const iterator&	it = *this;
				return (reinterpret_cast<const tree_iterator<const T, Compare, red_black_node<const T, Compare> >&>(it));
			}

			operator			node_pointer() const
				{return (_content);}

			iterator&			operator=(const tree_iterator& rhs)
			{
				_content = rhs._content;
				return (*this);
			}

			reference			operator*() const
				{return (_content->get_value());}

			pointer				operator->() const
				{return (&_content->get_value());}

			iterator&			operator++()
			{
				_content = _content->iterate();
				return (*this);
			}

			iterator			operator++(int)
			{
				tree_iterator	tmp(*this);

				_content = _content->iterate();
				return (*this);
			}

			iterator&			operator--()
			{
				_content = _content->reverse_iterate();
				return (*this);
			}

			iterator			operator--(int)
			{
				tree_iterator	tmp(*this);

				_content = _content->reverse_iterate();
				return (*this);
			}


			/* ----- MEMBER FUNCTION ----- */

			const node_pointer&	base() const
				{return (_content);}
	};


	/* ----- NON-MEMBER OPERATOR OVERLOADS ----- */

	template<class T1, class T2, class Compare, class Node1, class Node2>
	bool	operator==(const tree_iterator<T1, Compare, Node1>& left, const tree_iterator<T2, Compare, Node2>& right)
		{return (left.base() == reinterpret_cast<typename tree_iterator<T1, Compare, Node1>::node_pointer>(right.base()));}

	template<class T1, class T2, class Compare, class Node1, class Node2>
	bool	operator!=(const tree_iterator<T1, Compare, Node1>& left, const tree_iterator<T2, Compare, Node2>& right)
		{return (!(left == right));}
}

#endif