/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:31:02 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/06 15:55:05 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "red_black_node.hpp"

namespace ft
{
	template <class key, class T, class Compare = std::less<key>, class Alloc = std::allocator<ft::pair<key, T> > >
	class red_black_tree
	{
		public:
			typedef 			red_black_node<key, T>											node;
			typedef 			key																key_type;
			typedef 			T																mapped_type;
			typedef 			pair<key_type, mapped_type>										value_type;
			typedef 			Compare															key_compare;
			typedef typename	Alloc::template rebind<node>::other								allocator_type;
			typedef typename	allocator_type::reference										reference;
			typedef typename	allocator_type::const_reference									const_reference;
			typedef typename	allocator_type::pointer											pointer;
			typedef typename	allocator_type::const_pointer									const_pointer;
			typedef typename	ft::tree_iterator<red_black_node<key_type, mapped_type> >		iterator;
			typedef typename	ft::const_tree_iterator<red_black_node<key_type, mapped_type> >	const_iterator;
			typedef typename	ft::reverse_iterator<iterator>									reverse_iterator;
			typedef typename	ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef				ptrdiff_t														difference_type;
			typedef				size_t															size_type;

		protected:
			node*			_end;
			allocator_type	_alloc;
			key_compare		_key_cmp;
			size_t			_size;
			node*			_root;

		public:
			/* Default constructor */
			red_black_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _key_cmp(comp), _size(0), _root(NULL)
			{
				_this_is_end();
				return;
			}

			/* Copy constructor */
			red_black_tree(red_black_tree const& cpy) : _alloc(cpy._alloc), _key_cmp(cpy._key_cmp), _size(0), _root(NULL)
			{
				iterator	it(cpy.min_val());

				_this_is_end();
				while (!it._node->is_leaf())
				{
					insert(it._node->value);
					it++;
				}
			}

			/* Destructor */
			~red_black_tree()
			{
				node*	tmp = _root;

				while (_size != 0)
				{
					if (tmp->right && tmp->right != _end)
						tmp = tmp->right;
					else if (tmp->left && tmp->left != _end)
						tmp = tmp->left;
					else
					{
						node	*bis = tmp;

						if (tmp->parent)
						{
							tmp = tmp->parent;
							if (bis == tmp->left)
								tmp->left = NULL;
							else
								tmp->right = NULL;
						}
						_alloc.destroy(bis);
						_alloc.deallocate(bis, 1);
						_size--;
					}
				}
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
			}

			ft::pair<iterator, bool>	insert(value_type val)
			{
				ft::pair<iterator, bool>	ret;
				node*						tmp;
				node*						tmp_tmp;
				node*						u;

				if (_size == 0)
				{
					_its_empty(val);
					ret.first = _root;
					ret.second = true;
					return (ret);
				}
				ret = _where_is_the_value(val);
				if (!ret.second)
					return (ret);
				tmp = ret.first._node;
				while (tmp && tmp->parent && tmp->parent->color == RED)
				{
					if (tmp->parent->parent->right == tmp->parent)
					{
						u = tmp->parent->parent->left;
						if (u->color == RED)
						{
							u->color = BLACK;
							tmp->parent->color = BLACK;
							tmp->parent->parent->color = RED;
							tmp = tmp->parent->parent;
						}
						else
						{
							if (tmp == tmp->parent->left)
							{
								tmp_tmp = tmp->parent;
								_rotation_right(tmp, tmp->parent, tmp->parent->parent);
								tmp = tmp_tmp;
							}
							tmp->parent->color = BLACK;
							tmp->parent->parent->color = RED;
							_rotation_left(tmp->parent->parent, tmp->parent->parent->right, tmp->parent->parent->parent);
						}
					}
					else
					{
						u = tmp->parent->parent->right;
						if (u->color == RED)
						{
							u->color = BLACK;
							tmp->parent->color = BLACK;
							tmp->parent->parent->color = RED;
							tmp = tmp->parent->parent;
						}
						else
						{
							if (tmp == tmp->parent->right)
							{
								tmp_tmp = tmp->parent;
								_rotation_left(tmp->parent, tmp, tmp->parent->parent);
								tmp = tmp_tmp;
							}
							tmp->parent->color = BLACK;
							tmp->parent->parent->color = RED;
							_rotation_right(tmp->parent, tmp->parent->parent, tmp->parent->parent->parent);
						}
					}
					_root->color = BLACK;
				}
				return (ret);
			}

			node*						find_the_value(key_type val) const
			{
				if (_size == 0)
					return (_end);
				node*	tmp = _root;

				while (tmp != _end && tmp->value.first != val)
				{
					if (_key_cmp(val, tmp->value.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return (tmp);
			}

			size_type					to_delete(key_type val)
			{
				node*	tmp;
				node*	bis;

				tmp = find_the_value(val);
				if (tmp == _end)
					return (0);
				bis = _binary_search_tree_delete(tmp);
				if (bis)
					bis = _rebalanced_delete(bis);
				return (1);
			}

			node*						min_val() const
			{
				node*	tmp = _root;

				while (tmp->left != _end)
					tmp = tmp->left;
				return (tmp);
			}

			node*						max_val() const
			{
				node*	tmp = _root;

				while (tmp->right != _end)
					tmp = tmp->right;
				return (tmp);
			}

			node*						lower_bound(key_type k) const
			{
				node*	tmp = _root;
				node*	previous;

				while (tmp != _end)
				{
					previous = tmp;
					if (tmp->value.first == k)
						return (tmp);
					else if (tmp->value.first > k)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (previous->value.first > k)
					return (previous);
				else
				{
					if (previous == max_val())
						return (_end);
					while (previous->parent->right == previous)
						previous = previous->parent;
				}
				return (previous->parent);
			}

			node*						upper_bound(key_type k) const
			{
				node*	tmp = _root;
				node*	previous;

				while (tmp != _end)
				{
					previous = tmp;
					if (tmp->value.first == k)
						break;
					else if (tmp->value.first > k)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (tmp != _end)
				{
					if (tmp->right != _end)
						return (_find_min_val(tmp->right));
					if (tmp == max_val())
						return _end;
					while (tmp->parent && tmp == tmp->parent->right)
						tmp = tmp->parent;
					return (tmp->parent);
				}
				else
				{
					if (previous == max_val())
						return (_end);
					if (previous == min_val())
						return (min_val());
					while (tmp->parent && tmp == tmp->parent->right)
						tmp = tmp->parent;
					return (tmp->parent);
				}
			}

			// Display function just to vizualisation
			//  void print(void) const { printRBTRec("", _root, RED); };

			size_type					get_size() const
				{return (_size);}

			node*						get_the_end() const
				{return (_end);}

			allocator_type				get_alloc() const
				{return (_alloc);}

			void						swap(red_black_tree* rhs)
			{
				node*	tmp_end = _end;
				node*	tmp_root = _root;
				size_t	tmp_size = _size;

				_end = rhs->_end;
				_root = rhs->_root;
				_size = rhs->_size;

				rhs->_end = tmp_end;
				rhs->_root = tmp_root;
				rhs->_size = tmp_size;
			}

		private:
			void						_this_is_end()
			{
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node());
				_end->color = BLACK;
				_end->left = NULL;
				_end->right = NULL;
				_end->parent = NULL;
				_end->end = _end;
			}

			void						_its_empty(value_type val)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, node(val));
				_size++;
				_root->right = _end;
				_root->left = _end;
				_root->color = BLACK;
				_root->end = _end;
				_end->parent = _root;
			}

			pair<iterator, bool>		_where_is_the_value(value_type val)
			{
				node*					tmp = _root;
				pair<iterator, bool>	ret;

				while (1)
				{
					if (_key_cmp(val.first, tmp->value.first))
					{
						if (tmp->left && tmp->left != _end)
							tmp = tmp->left;
						else
						{
							node*	nw = _alloc.allocate(1);

							_alloc.construct(nw, node(val));
							tmp->left = nw;
							nw->right = _end;
							nw->left = _end;
							nw->parent = tmp;
							nw->end = _end;
							tmp = tmp->left;
							_size++;
							break;
						}
					}
					else
					{
						if (!_key_cmp(tmp->value.first, val.first))
						{
							ret.first = tmp;
							ret.second = false;
							return (ret);
						}
						if (tmp->right && tmp->right != _end)
							tmp = tmp->right;
						else
						{
							node*	nw = _alloc.allocate(1);

							_alloc.construct(nw, node(val));
							tmp->right = nw;
							nw->right = _end;
							nw->left = _end;
							nw->parent = tmp;
							nw->end = _end;
							tmp = tmp->right;
							_size++;
							break;
						}
					}
				}
				ret.first = tmp;
				ret.second = true;
				return (ret);
			}

			void						_rotation_left(node* x, node* y, node* p)
			{
				if (!p)
					_root = y;
				else if (x == p->left)
					p->left = y;
				else
					p->right = y;
				y->parent = p;
				x->right = y->left;
				if (!x->right->is_leaf())
					x->right->parent = x;
				y->left = x;
				x->parent = y;
			}

			void						_rotation_right(node* x, node* y, node* p)
			{
				if (!p)
					_root = x;
				else if (y == p->left)
					p->left = x;
				else
					p->right = x;
				x->parent = p;
				y->left = x->right;
				if (!y->left->is_leaf())
					y->left->parent = y;
				x->right = y;
				y->parent = x;
			}

			void						_re_color(node* x)
			{
				if (x->color == BLACK)
					x->color = RED;
				else
					x->color = BLACK;
			}


		private:
			void						_replace_node(node* to_replace, node* replacer)
			{
				if (!to_replace->parent)
					_root = replacer;
				else if (to_replace->parent->right == to_replace)
					to_replace->parent->right = replacer;
				else if (to_replace->parent->left == to_replace)
					to_replace->parent->left = replacer;
				replacer->parent = to_replace->parent;
			}

			node*						_find_min_val(node* tmp) const
			{

				while (tmp != _end && tmp->left != _end)
					tmp = tmp->left;
				return tmp;
			}

			node*						_binary_search_tree_delete(node* tmp)
			{
				bool					todelete_color = tmp->color;
				node*					x;
				node*					y;
				node*					todelete = tmp;

				if (todelete->left == _end)
				{
					x = todelete->right;
					_replace_node(todelete, todelete->right);
				}
				else if (todelete->right == _end)
				{
					x = todelete->left;
					_replace_node(todelete, todelete->left);
				}
				else
				{
					y = _find_min_val(todelete->right);
					todelete_color = y->color;
					x = y->right;
					if (y->parent && y->parent == todelete)
						x->parent = y;
					else
					{
						_replace_node(y, y->right);
						y->right = todelete->right;
						y->right->parent = y;
					}
					_replace_node(todelete, y);
					y->left = todelete->left;
					y->left->parent = y;
					y->color = todelete->color;
				}
				_alloc.destroy(todelete);
				_alloc.deallocate(todelete, 1);
				_size--;
				if (todelete_color == BLACK)
					return (x);
				return (NULL);
			}

			node*						_rebalanced_delete(node* tmp)
			{
				node*	x = tmp;
				node*	s;

				while (x != _root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == RED)
						{
							_re_color(s);
							x->parent->color = RED;
							_rotation_left(x->parent, x->parent->right, x->parent->parent);
							s = x->parent->right;
						}
						if (s != _end && s->left->color == BLACK && s->right->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							if (s != _end && s->right->color == BLACK)
							{
								s->left->color = BLACK;
								s->color = RED;
								_rotation_right(s->left, s, s->parent);
								s = x->parent->right;
							}
							if (s != _end)
								s->color = x->parent->color;
							x->parent->color = BLACK;
							if (s != _end)
								s->right->color = BLACK;
							_rotation_left(x->parent, x->parent->right, x->parent->parent);
							x = _root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == RED)
						{
							_re_color(s);
							x->parent->color = RED;
							_rotation_right(x->parent->left, x->parent, x->parent->parent);
							s = x->parent->left;
						}
						if (s != _end && s->right->color == BLACK && s->left->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							if (s->left->color == BLACK)
							{
								s->right->color = BLACK;
								s->color = RED;
								_rotation_left(s, s->right, s->parent);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							_rotation_right(x->parent->left, x->parent, x->parent->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
				return (x);
			}
	};
}

#endif