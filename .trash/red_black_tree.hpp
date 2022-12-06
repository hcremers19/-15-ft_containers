/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:14:12 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/06 13:15:09 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "red_black_node.hpp"

# define RED	true
# define BLACK	false

namespace ft
{
	template<class T, class Alloc = std::allocator<T>, class Compare = std::less<T> >
	class red_black_tree
	{
		public:
			typedef 			T											value_type;
			typedef 			red_black_node<value_type, Compare>			node_type;
			typedef 			red_black_node<const value_type, Compare>	node_const_type;
			typedef typename	Alloc::template rebind<node_type>::other	allocator_type;
			typedef 			Compare										value_compare;
			typedef 			red_black_tree<T, Alloc, Compare>			tree_type;
			typedef 			value_type&									reference;
			typedef 			const value_type&							const_reference;
			typedef 			value_type*									pointer;
			typedef 			const value_type*							const_pointer;

		private:
			node_type*	_root;
			node_type*	_null;

		public:
			red_black_tree()
			{
				_null = new red_black_node;
				_null->color = BLACK;
				_null->left = NULL;
				_null->right = NULL;
				_root = _null;
			}

			void		preorder()
			{
				_pre_order(_root);
				return;
			}

			void		inorder()
			{
				_in_order(_root);
				return;
			}

			void		postorder()
			{
				_post_order(_root);
				return;
			}

			node_type*	search_tree(int k)
				{return (_search_tree(_root, k));}

			node_type*	minimum(node_type* node)
			{
				while (node->left != _null)
					node = node->left;

				return (node);
			}

			node_type*	maximum(node_type* node)
			{
				while (node->right != _null)
					node = node->right;
				return (node);
			}

			node_type*	successor(node_type* x)
			{
				if (x->right != _null)
					return (minimum(x->right));

				node_type* y = x->parent;
				while (y != _null && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return (y);
			}

			node_type*	predecessor(node_type* x)
			{
				if (x->left != _null)
					return (maximum(x->left));

				node_type* y = x->parent;
				while (y != _null && x == y->left)
				{
					x = y;
					y = y->parent;
				}

				return (y);
			}

			void		left_rotate(node_type* x)
			{
				node_type*	y = x->right;

				x->right = y->left;
				if (y->left != _null)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void		right_rotate(node_type* x)
			{
				node_type*	y = x->left;

				x->left = y->right;
				if (y->right != _null)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			// Inserting a node
			void		insert(int key)
			{
				node_type*	node = new red_black_node;

				node->parent = NULL;
				node->data = key;
				node->left = _null;
				node->right = _null;
				node->color = RED;

				node_type*	y = NULL;
				node_type*	x = _root;

				while (x != _null)
				{
					y = x;
					if (node->data < x->data)
						x = x->left;
					else
						x = x->right;
				}

				node->parent = y;
				if (y == NULL)
					_root = node;
				else if (node->data < y->data)
					y->left = node;
				else
					y->right = node;

				if (node->parent == NULL)
				{
					node->color = BLACK;
					return;
				}

				if (node->parent->parent == NULL)
					return;

				_insert_fix(node);
			}

			node_type*	get_root()
				{return (_root);}

			void		delete_node(int data)
			{
				_delete_node(_root, data);
				return;
			}

			// void		print_tree()
			// {
			// 	if (_root)
			// 		_print_tree(_root, "", true);
			// }

		private:
			void		_init_null_node(node_type* node, node_type* parent)
			{
				node->data = 0;
				node->parent = parent;
				node->left = NULL;
				node->right = NULL;
				node->color = BLACK;
			}

			// Preorder
			void		_pre_order(node_type* node)
			{
				if (node != _null)
				{
					std::cout << node->data << " ";
					_pre_order(node->left);
					_pre_order(node->right);
				}
			}

			// Inorder
			void		_in_order(node_type* node)
			{
				if (node != _null)
				{
					_in_order(node->left);
					std::cout << node->data << " ";
					_in_order(node->right);
				}
			}

			// Post order
			void		_post_order(node_type* node)
			{
				if (node != _null)
				{
					_post_order(node->left);
					_post_order(node->right);
					std::cout << node->data << " ";
				}
			}

			node_type*	_search_tree(node_type* node, int key)
			{
				if (node == _null || key == node->data)
					return (node);

				if (key < node->data)
					return (_search_tree(node->left, key));

				return (_search_tree(node->right, key));
			}

			// For balancing the tree after deletion
			void		_delete_fix(node_type* x)
			{
				node_type*	s;

				while (x != _root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == RED)
						{
							s->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == BLACK && s->right->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							if (s->right->color == BLACK)
							{
								s->left->color = BLACK;
								s->color = RED;
								right_rotate(s);
								s = x->parent->right;
							}

							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == RED)
						{
							s->color = BLACK;
							x->parent->color = RED;
							right_rotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == BLACK && s->right->color == BLACK)
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
								left_rotate(s);
								s = x->parent->left;
							}

							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							right_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
			}

			void		_rbtransplant(node_type* u, node_type* v)
			{
				if (u->parent == NULL)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void		_delete_node(node_type* node, int key)
			{
				node_type*	z = _null;
				node_type*	x;
				node_type*	y;

				while (node != _null)
				{
					if (node->data == key)
						z = node;

					if (node->data <= key)
						node = node->right;
					else
						node = node->left;
				}

				if (z == _null)
				{
					std::cout << "Key not found in the tree" << std::endl;
					return;
				}

				y = z;
				bool	y_original_color = y->color;

				if (z->left == _null)
				{
					x = z->right;
					_rbtransplant(z, z->right);
				}
				else if (z->right == _null)
				{
					x = z->left;
					_rbtransplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
					{
						x->parent = y;
					}
					else
					{
						_rbtransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					_rbtransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				delete z;
				if (y_original_color == BLACK)
					_delete_fix(x);
			}

			// For balancing the tree after insertion
			void		_insert_fix(node_type* k)
			{
				node_type*	u;

				while (k->parent->color == RED)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left;
						if (u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								k = k->parent;
								right_rotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							left_rotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;

						if (u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								left_rotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							right_rotate(k->parent->parent);
						}
					}
					if (k == _root)
						break;
				}
				_root->color = BLACK;
			}

			// void		_print_tree(node_type* root, std::string indent, bool last)
			// {
			// 	if (root != _null)
			// 	{
			// 		std::cout << indent;
			// 		if (last)
			// 		{
			// 			std::cout << "R----";
			// 			indent += "   ";
			// 		}
			// 		else
			// 		{
			// 			std::cout << "L----";
			// 			indent += "|  ";
			// 		}

			// 		std::string sColor = root->color ? "RED" : "BLACK";
			// 		std::cout << root->data << "(" << sColor << ")" << std::endl;
			// 		_print_tree(root->left, indent, false);
			// 		_print_tree(root->right, indent, true);
			// 	}
			// }

	};
}
#endif

// int main()
// {
// 	red_black_tree bst;
// 	bst.insert(55);
// 	bst.insert(65);
// 	bst.insert(40);
// 	bst.insert(60);
// 	bst.insert(75);
// 	bst.insert(57);

// 	bst.print_tree();
// 	std::cout << std::endl << "After deleting" << std::endl;
// 	bst.delete_node(40);
// 	bst.print_tree();
// }

// Source: https://www.programiz.com/dsa/red-black-tree/