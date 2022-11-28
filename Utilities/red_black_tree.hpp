/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:04:11 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/28 11:33:03 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <functional>
# include <memory>
# include "red_black_node.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T>, class Compare = std::less<T> >
	class red_black_tree
	{
		public:
			typedef T													value_type;
			typedef red_black_node<value_type, Compare>					node_type;
			typedef red_black_node<const value_type, Compare>			node_const_type;
			typedef Alloc::template rebind<node_type>::other			allocator_type;
			typedef Compare												value_compare;
			typedef red_black_tree<T, Alloc, Compare>					tree_type;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			typedef value_type*											pointer;
			typedef const value_type*									const_pointer;

		private:
			node_type*		_root;
			node_type*		_end;
			allocator_type	_node_alloc;
			value_compare&	_comp;

		public:
			/* ----- CONSTRUCTORS AND DESTRUCTOR ----- */

			explicit red_black_tree(value_compare& comp = value_compare()) : _root(NULL), _node_alloc(), _comp(comp)
			{
				_end = _node_alloc.allocate(1);
				_node_alloc.construct((_end), node_type(_root, _comp));
				return;
			}

			red_black_tree(const red_black_tree& src) : _root(NULL), _node_alloc(src._node_alloc), _comp(src._comp)
			{
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, node_type(_root, _comp));
				for (node_type* node = node_type::get_smallest(src._root); node != src._end; node = node->iterate())
					insert(node->get_value());
				return;
			}

			~red_black_tree()
			{
				clear();
				_node_alloc.destroy(_end);
				_node_alloc.deallocate(_end, 1);
				return;
			}


			/* ----- OPERATOR OVERLOAD ----- */

			red_black_tree&			operator=(const red_black_tree& right)
			{
				clear();
				for (node_type* node = node_type::get_smallest(right._root); node != right._end && node; node = node->iterate())
					insert(node->get_value());
				return (*this);
			}


			/* ----- ACCESSORS ----- */

			node_type*				get_root()
				{return (_root);}

			node_const_type*		get_root() const
				{return (reinterpret_cast<node_const_type*>_root);}

			node_type*				get_end()
				{return (_end);}

			node_const_type*		get_end() const
				{return (reinterpret_cast<node_const_type*>_end);}

			value_compare const&	get_comp() const
				{return (_comp);}

			allocator_type const&	get_alloc() const
				{return (_node_alloc);}

			void					set_root(node_type* ptr)
			{
				_root = ptr;
				_end->set_end(ptr);
				return;
			}

			void					set_end(node_type* end)
			{
				_end = ptr;
				_end->set_end(_root);
				return;
			}


			/* ----- MEMBER FUNCTIONS ----- */

			node_type*				search(const value_type& val)
				{return (_search(val));}

			node_const_type*		search(const value_type& val) const
				{return (reinterpret_cast<node_const_type*>(_search(val)));}

			node_type*				search_lower_bound(const value_type& val)
				{return (_search_lower_bound(val));}

			node_const_type*		search_lower_bound(const value_type& val) const
				{return (reinterpret_cast<node_const_type*>(_search_lower_bound(val)));}

			node_type*				search_upper_bound(const value_type& val)
				{return (_search_upper_bound(val));}

			node_const_type*		search_upper_bound(const value_type& val) const
				{return (reinterpret_cast<node_const_type*>(_search_upper_bound(val)));}

			pair<node_type*, bool>	insert(node_type& node, node_type* z)
			{
				node_type*	previous = NULL;

				while (z)
				{
					previous = z;
					if (node == *z)
						return (pair<node_type*, bool>(z, false));
					if (node < *z)
						z = z->get_left();
					else
						z = z->get_right();
				}
				node_type*	new_node = _node_alloc.allocate(1);

				_node_alloc.construct(new_node, node_type(node.get_value(), NULL, NULL, previous, _end, _comp));
				if (!previous)
					set_root(new_node);
				else if (node < *previous)
					previous->set_left(new_node);
				else
					previous->set_right(new_node);
				_fix_insertion(new_node);
				return (pair<node_type*, bool>(new_node, true));
			}

			pair<node_type*, bool>	insert(const value_type& val)
			{
				node_type	tmp(val, _end, _comp);

				return (insert(tmp, _root));
			}

			pair<node_type*, bool>	insert(const value_type& val, node_type* hint)
			{
				node_type	tmp(val, _end, _comp);

				if (*hint < tmp && *(hint.iterate()) > tmp)
					return (insert(tmp, hint));
				else
					return (insert(tmp, _root));
			}

			bool					erase(const value_type& val)
			{
				node_type*	z = search(val);
				return (erase(z));
			}

			bool					erase(node_type* k)
			{
				node_type*				left = k->get_left();
				node_type*				right = k->get_right();
				pair<node_type*, bool>	check = pair<node_type*, bool>(k, true);
				bool					color = k->get_color();

				if (k == _end)
					return (false);
				if (!right)
				{
					check = _create_child(k, true);
					_replace_node(k->get_parent, k, check.first);
				}
				else if (!left)
				{
					check = _create_child(k, false);
					_replace_node(k->get_parent(), k, check.first);
				}
				else
				{
					node_type*	smallest = node_type::get_smallest(right);

					color = smallest->get_color();
					check = _create_child(smallest, false);
					if (k == smallest->get_parent())
						check.first->set_parent(smallest);
					else
					{
						_transplant_node(smallest->get_parent(), smallest, smallest->get_right());
						smallest->set_right(right);
						smallest->get_right()->set_parent(smallest);
					}
					_replace_node(k->get_parent(), k, smallest);
					smallest->set_left(left);
					smallest->get_left()->set_parent(smallest);
					smallest->set_color(k->get_color());
				}
				if (color == BLACK)
					_fix_deletion(check.first);
				if (check.second)
				{
					if (check.first->get_parent())
						(check.first == check.first->get_parent()->get_left() ? check.first->get_parent()->set_left(NULL) : check.first->get_parent()->set_right(NULL));
					if (check.first == _root)
						set_root(NULL);
					_node_alloc.destroy(check.first);
					_node_alloc.deallocate(check.first, 1);
				}
				return (true);
			}

			void					clear()
			{
				node_type*	nd = node_type::get_smallest(_root);

				while (nd && nd != _end)
				{
					node_type *tmp = nd->iterate();
					erase(nd);
					nd = tmp;
				}
				_root = NULL;
				return;
			}

			node_type*				create_node(node_type* parent, node_type* left, node_type* right, value_type& content)
			{
				node_type*	new_node = _node_alloc.allocate(1);

				_node_alloc.construct(new_node, node_type(content, left, right, parent, _end, _comp));
				return (new_node);
			}

			void					swap_content(tree_type& tree)
			{
				node_type*	tmp_root = tree.get_root();
				node_type*	tmp_end = tree.get_end();

				tree._root = get_root();
				tree._end = get_end();
				_root = tmp_root;
				_end = tmp_end;
				return;
			}


		private:
			/* ----- MEMBER FUNCTIONS ----- */

			pair<node_type*, bool>	_create_child(node_type* parent, bool is_left)
			{
				node_type*	child = (is_left ? parent->get_left() : parent->get_right());

				if (child)
					return (pair<node_type*, bool>(child, false));

				node_type	*new_node = _node_alloc.allocate(1);

				_node_alloc.construct(new_node, node_type(value_type(), NULL, NULL, parent, _end, _comp));
				new_node->set_color(BLACK);
				(is_left ? parent->set_left(new_node) : parent->set_right(new_node));
				return (pair<node_type*, bool>(new_node, true));
			}

			void					_replace_node(node_type* parent, node_type* k, node_type* replacer)
			{
				if (!parent)
					set_root(replacer);
				else if (k == parent->get_left())
					parent->set_left(replacer);
				else
					parent->set_right(replacer);
				if (replacer)
					replacer->set_parent(parent);
				_node_alloc.destroy(k);
				_node_alloc.deallocate(k, 1);
				return ;
			}

			void					_transplant_node(node_type* parent, node_type* k, node_type* replacer)
			{
				if (!parent)
					set_root(replacer);
				else if (k == parent->get_left())
					parent->set_left(replacer);
				else
					parent->set_right(replacer);
				if (replacer)
					replacer->set_parent(parent);
				return;
			}

			bool					_is_black(node_type* k)
			{
				if (!k || k->is_black())
					return (true);
				return (false);
			}

			bool					_is_red(node_type* k)
			{
				if (!k || k->is_red())
					return (true);
				return (false);
			}

			void					_left_rotate(node_type* k)
			{
				node_type*	right = k->get_right();
				node_type*	child_left = right->get_left();

				k->set_right(child_left);
				if (child_left)
					child_left->set_parent(k);
				right->set_parent(k->get_parent());
				if (!k->get_parent())
					set_root(right);
				else if (k == k->get_parent()->get_left())
					k->get_parent()->set_left(right);
				else
					k->get_parent()->set_right(right);
				right->set_left(k);
				k->set_parent(right);
				return;
			}

			void					_right_rotate(node_type* k)
			{
				node_type*	left = k->get_left();
				node_type*	child_right = left->get_right();

				k->set_left(child_right);
				if (child_right)
					child_right->set_parent(k);
				left->set_parent(k->get_parent());
				if (!k->get_parent())
					set_root(left);
				else if (k == k->get_parent()->get_right())
					k->get_parent()->set_right(left);
				else
					k->get_parent()->set_left(left);
				left->set_right(k);
				k->set_parent(left);
				return;
			}

			void					_fix_insertion(node_type* k)
			{
				while (_is_red(k->get_parent()) && k->get_parent()->get_parent())
				{
					node_type	*parent = k->get_parent();
					node_type	*gparent = parent->get_parent();
					bool		is_left = (gparent->get_left() == parent);
					node_type	*uncle = (is_left ? gparent->get_right() : gparent->get_left());

					if (_is_red(uncle))
					{
						parent->set_color(BLACK);
						uncle->set_color(BLACK);
						gparent->set_color(RED);
						k = gparent;
					}
					else
					{
						if (k == (is_left ? parent->get_right() : parent->get_left()))
						{
							k = parent;
							(is_left ? _left_rotate(k) : _right_rotate(k));
							parent = k->get_parent();
							gparent = parent->get_parent();
						}
						parent->set_color(BLACK);
						gparent->set_color(RED);
						(is_left ? _right_rotate(gparent) : _left_rotate(gparent));
					}
				}
				_root->set_color(BLACK);
				return;
			}

			void					_fix_deletion(node_type* k)
			{
				while (_root != k && _is_black(k))
				{

					node_type*	parent = k->get_parent();
					bool		is_left = (k == k->get_parent()->get_left());
					node_type*	brother = (is_left ? parent->get_right() : parent->get_left());

					if (_is_red(brother))
					{
						brother->set_color(BLACK);
						parent->set_color(RED);
						(is_left ? _left_rotate(parent) : _right_rotate(parent));
						parent = k->get_parent();
						(is_left ? brother = parent->get_right() : parent->get_left());
					}
					if (_is_black(brother) && _is_black(brother->get_left()) && _is_black(brother->get_right()))
					{
						brother->set_color(RED);
						k = parent;
						parent = parent->get_parent();
					}
					else
					{
						if ((is_left && _is_black(brother) && _is_black(brother->get_right()) && _is_red(brother->get_left())) || (!is_left && _is_black(brother) && _is_black(brother->get_left()) && _is_red(brother->get_right())))
						{
							(is_left ? brother->get_left()->set_color(BLACK) : brother->get_right()->set_color(BLACK));
							brother->set_color(RED);
							(is_left ? _right_rotate(brother) : _left_rotate(brother));
							parent = k->get_parent();
							brother = (is_left ? parent->get_right() : parent->get_left());
						}

						brother->set_color(parent->get_color());
						parent->set_color(BLACK);
						(is_left ? brother->get_right()->set_color(BLACK) : brother->get_left()->set_color(BLACK));
						(is_left ? _left_rotate(parent) : _right_rotate(parent));
						k = _root;
					}
				}
				k->set_color(BLACK);
				return;
			}

			node_type*				_search(const value_type& val) const
			{
				node_type*	z = _root;
				node_type	tmp(val, _end, _comp);

				while (z)
				{
					if (*z == tmp)
						return (z);
					else if (tmp > *z)
						z = z->get_right();
					else
						z = z->get_left();
				}
				return (_end);
			}

			node_type*				_search_lower_bound(const value_type& val) const
			{
				node_type*	z = _root;
				node_type	tmp(val, _end, _comp);
				node_type*	previous = NULL;

				while (z)
				{
					previous = z;
					if (*z == tmp)
						return (z);
					else if (tmp > *z)
						z = z->get_right();
					else
						z = z->get_left();
				}
				if (!previous)
					return (_end);
				else if (tmp > *previous)
					return (previous->iterate());
				return (previous);
			}

			node_type*				_search_upper_bound(const value_type& val) const
			{
				node_type*	z = _root;
				node_type	tmp(val, _end, _comp);
				node_type*	previous = NULL;

				while (z)
				{
					previous = z;
					if (*z == tmp)
						return (z->iterate());
					else if (tmp > *z)
						z = z->get_right();
					else
						z = z->get_left();
				}
				if (!previous)
					return (_end);
				else if (tmp > *previous)
					return (previous->iterate());
				return (previous);
			}
	};
}

#endif