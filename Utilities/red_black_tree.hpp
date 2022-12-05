/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:14:12 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/05 15:36:31 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include "red_black_node.hpp"

namespace ft
{
	class red_black_tree
	{
		public:
			typedef red_black_node*	node_ptr;

		private:
			node_ptr	_root;
			node_ptr	_null;

		public:
			red_black_tree()
			{
				_null = new red_black_node;
				_null->color = 0;
				_null->left = nullptr;
				_null->right = nullptr;
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

			node_ptr	search_tree(int k)
				{return (_search_tree(_root, k));}

			node_ptr	minimum(node_ptr node)
			{
				while (node->left != _null)
					node = node->left;

				return (node);
			}

			node_ptr	maximum(node_ptr node)
			{
				while (node->right != _null)
					node = node->right;
				return (node);
			}

			node_ptr	successor(node_ptr x)
			{
				if (x->right != _null)
					return (minimum(x->right));

				node_ptr y = x->parent;
				while (y != _null && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return (y);
			}

			node_ptr	predecessor(node_ptr x)
			{
				if (x->left != _null)
					return (maximum(x->left));

				node_ptr y = x->parent;
				while (y != _null && x == y->left)
				{
					x = y;
					y = y->parent;
				}

				return (y);
			}

			void		left_rotate(node_ptr x)
			{
				node_ptr y = x->right;
				x->right = y->left;
				if (y->left != _null)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void		right_rotate(node_ptr x)
			{
				node_ptr y = x->left;
				x->left = y->right;
				if (y->right != _null)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
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
				node_ptr	node = new red_black_node;

				node->parent = nullptr;
				node->data = key;
				node->left = _null;
				node->right = _null;
				node->color = 1;

				node_ptr	y = nullptr;
				node_ptr	x = _root;

				while (x != _null)
				{
					y = x;
					if (node->data < x->data)
						x = x->left;
					else
						x = x->right;
				}

				node->parent = y;
				if (y == nullptr)
					_root = node;
				else if (node->data < y->data)
					y->left = node;
				else
					y->right = node;

				if (node->parent == nullptr)
				{
					node->color = 0;
					return;
				}

				if (node->parent->parent == nullptr)
					return;

				_insert_fix(node);
			}

			node_ptr	get_root()
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
			void		_init_null_node(node_ptr node, node_ptr parent)
			{
				node->data = 0;
				node->parent = parent;
				node->left = nullptr;
				node->right = nullptr;
				node->color = 0;
			}

			// Preorder
			void		_pre_order(node_ptr node)
			{
				if (node != _null)
				{
					std::cout << node->data << " ";
					_pre_order(node->left);
					_pre_order(node->right);
				}
			}

			// Inorder
			void		_in_order(node_ptr node)
			{
				if (node != _null)
				{
					_in_order(node->left);
					std::cout << node->data << " ";
					_in_order(node->right);
				}
			}

			// Post order
			void		_post_order(node_ptr node)
			{
				if (node != _null)
				{
					_post_order(node->left);
					_post_order(node->right);
					std::cout << node->data << " ";
				}
			}

			node_ptr	_search_tree(node_ptr node, int key)
			{
				if (node == _null || key == node->data)
					return (node);

				if (key < node->data)
					return (_search_tree(node->left, key));

				return (_search_tree(node->right, key));
			}

			// For balancing the tree after deletion
			void		_delete_fix(node_ptr x)
			{
				node_ptr	s;

				while (x != _root && x->color == 0)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == 1)
						{
							s->color = 0;
							x->parent->color = 1;
							left_rotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == 0 && s->right->color == 0)
						{
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->right->color == 0)
							{
								s->left->color = 0;
								s->color = 1;
								right_rotate(s);
								s = x->parent->right;
							}

							s->color = x->parent->color;
							x->parent->color = 0;
							s->right->color = 0;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == 1)
						{
							s->color = 0;
							x->parent->color = 1;
							right_rotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == 0 && s->right->color == 0)
						{
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->left->color == 0)
							{
								s->right->color = 0;
								s->color = 1;
								left_rotate(s);
								s = x->parent->left;
							}

							s->color = x->parent->color;
							x->parent->color = 0;
							s->left->color = 0;
							right_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = 0;
			}

			void		_rbtransplant(node_ptr u, node_ptr v)
			{
				if (u->parent == nullptr)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void		_delete_node(node_ptr node, int key)
			{
				node_ptr	z = _null;
				node_ptr	x;
				node_ptr	y;

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
				int	y_original_color = y->color;

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
				if (y_original_color == 0)
					_delete_fix(x);
			}

			// For balancing the tree after insertion
			void		_insert_fix(node_ptr k)
			{
				node_ptr	u;

				while (k->parent->color == 1)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left;
						if (u->color == 1)
						{
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								k = k->parent;
								right_rotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							left_rotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;

						if (u->color == 1)
						{
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								left_rotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							right_rotate(k->parent->parent);
						}
					}
					if (k == _root)
						break;
				}
				_root->color = 0;
			}

			// void		_print_tree(node_ptr root, std::string indent, bool last)
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