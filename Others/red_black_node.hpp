/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_node.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:56:12 by ldelmas           #+#    #+#             */
/*   Updated: 2022/12/15 12:34:12 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include <memory>

# define RBT_RED	true
# define RBT_BLACK	false

namespace ft
{
	template <class T, class Compare>
	class red_black_node
	{
		public:
			typedef T												value_type;
			typedef ft::red_black_node<value_type, Compare>			node_type;
			typedef ft::red_black_node<const value_type, Compare>	node_const_type;
			typedef std::allocator<value_type>						alloc_type;
			typedef Compare											value_compare;
			typedef node_type*										pointer;
			typedef const node_type*								const_pointer;
			typedef size_t											size_type;

		private:
			value_type				_content;
			bool					_color;
			pointer					_left;
			pointer					_right;
			pointer					_parent;
			pointer					_end;
			const value_compare&	_comp;


		public:
			/* ----- CONSTRUCTORS AND DESTRUCTOR ----- */

			explicit red_black_node(const pointer ptr = NULL, const value_compare& comp = value_compare()) : _content(), _color(RBT_RED), _left(NULL), _right(NULL), _parent(NULL), _end(ptr), _comp(comp)
				{return;}

			red_black_node(const value_type& val, const pointer ptr = NULL, const value_compare& comp = value_compare()) : _content(val), _color(RBT_RED), _left(NULL), _right(NULL), _parent(NULL), _end(ptr), _comp(comp)
				{return;}

			red_black_node(const pointer parent, const pointer ptr = NULL, const value_compare& comp = value_compare()) : _content(), _color(RBT_BLACK), _left(NULL), _right(NULL), _parent(parent), _end(ptr), _comp(comp)
				{return;}

			red_black_node(const value_type& val, const pointer left, const pointer right, const pointer parent = NULL, const pointer end = NULL, const value_compare &comp = value_compare()) : _content(val), _color(RBT_RED), _left(left), _right(right), _parent(parent), _end(end), _comp(comp)
				{return;}

			red_black_node(const node_type &src) : _content(src._content), _color(src._color), _left(src._left), _right(src._right), _parent(src._parent), _end(src._end), _comp(src._comp)
				{return;}

			~red_black_node()
				{return;}


			/* ----- ACCESSORS ----- */

			value_type&		get_value()
				{return (_content);}

			pointer			get_left() const
				{return (_left);}

			pointer			get_right() const
				{return (_right);}

			pointer			get_parent() const
				{return (_parent);}

			pointer			get_grand_parent() const
				{return (_parent->_parent);}

			pointer			get_end() const
				{return (_end);}

			bool			get_color() const
				{return (_color);}

			pointer			get_uncle() const
			{
				pointer	parent = _parent;
				pointer	grand_parent = parent->_parent;

				if (!grand_parent)
					return (NULL);
				else if (grand_parent->_left == parent)
					return (grand_parent->_right);
				else
					return (grand_parent->_left);
			}

			bool			is_red() const
				{return (_color == RBT_RED);}

			bool			is_black() const
				{return (_color == RBT_BLACK);}

			void			set_value(const value_type& val)
			{
				_content = val;
				return;
			}

			void			set_right(pointer node)
			{
				_right = node;
				return;
			}

			void			set_left(pointer node)
			{
				_left = node;
				return;
			}

			void			set_parent(pointer node)
			{
				_parent = node;
				return;
			}

			void			set_end(const pointer ptr)
			{
				_end = ptr;
				return;
			}

			void			set_color(bool color)
			{
				_color = color;
				return;
			}


			/* ----- UTILS ----- */

			pointer			iterate() const
			{
				const node_type*	k = this;
				node_type*			right = k->get_right();
				node_type*			parent = k->get_parent();

				if (right)
					return (get_smallest(right));

				while (parent && parent->get_right() == k)
				{
					k = parent;
					parent = k->get_parent();
				}

				if (parent && parent->get_left() == k)
					return (parent);

				return (_end);
			}

			pointer			reverse_iterate() const
			{
				if (!_parent && !_left && !_right)
					return (get_biggest(_end));

				const node_type*	k = this;
				node_type*			left = k->get_left();
				node_type*			parent = k->get_parent();

				if (left)
					return (get_biggest(left));

				while (parent && parent->get_left() == k)
				{
					k = parent;
					parent = k->get_parent();
				}

				if (parent)
					return (parent);

				return (_end);
			}


			/* ----- STATIC UTILS ----- */

			static pointer	get_smallest(pointer ptr)
			{
				while (ptr && ptr->_left)
					ptr = ptr->_left;
				return (ptr);
			}

			static pointer	get_biggest(pointer ptr)
			{
				while (ptr && ptr->_right)
					ptr = ptr->_right;
				return (ptr);
			}


			/* ----- OPERATORS ----- */

			operator		red_black_node<const T, Compare>() const
			{
				return (red_black_node<const T, Compare>(*this));
			}


			/* ----- RELATIONAL OPERATORS ----- */

			bool			operator==(const node_type& right) const
				{return (!_comp(_content, right._content) && !_comp(right._content, _content));}

			bool			operator!=(const node_type& right) const
				{return (!(*this == right));}

			bool			operator<(const node_type& right) const
				{return (_comp(_content, right._content));}

			bool			operator<=(const node_type& right) const
				{return (!(right < *this));}

			bool			operator>(const node_type& right) const
				{return (right < *this);}

			bool			operator>=(const node_type& right) const
				{return (!(*this < right));}
	};
}

#endif