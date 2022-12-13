/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:46:56 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/13 17:14:32 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>

// # include "../.trash/red_black_tree_old.hpp"
# include "../.trash/rbt.hpp"
# include "../Iterators/tree_iterator.hpp"
# include "../Iterators/reverse_iterator.hpp"
# include "../Others/pair.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef 			Key																										key_type;
			typedef 			T																										mapped_type;
			typedef 			pair<const key_type, mapped_type>																		value_type;
			typedef 			Compare																									key_compare;
			class																														value_compare
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c)
						{return;}

				public:
					bool operator()(const value_type& x, const value_type& y) const
						{return (comp(x.first, y.first));}
			};
			typedef 			Alloc																									allocator_type;
			typedef typename	allocator_type::reference																				reference;
			typedef typename	allocator_type::const_reference																			const_reference;
			typedef typename	allocator_type::pointer																					pointer;
			typedef typename	allocator_type::const_pointer																			const_pointer;
			typedef typename	ft::tree_iterator<value_type, value_compare, red_black_node<value_type, value_compare> >				iterator;
			typedef typename	ft::tree_iterator<const value_type, value_compare, red_black_node<const value_type, value_compare> >	const_iterator;
			typedef typename	ft::reverse_iterator<iterator>																			reverse_iterator;
			typedef typename	ft::reverse_iterator<const_iterator>																	const_reverse_iterator;
			typedef typename	iterator_traits<iterator>::difference_type																difference_type;
			typedef 			size_t																									size_type;

		private:
			red_black_tree<value_type, Alloc, value_compare>	_tree;
			size_type											_size;
			key_compare											_key_comp;
			value_compare										_val_comp;

		public:
			/* ----- CONSTRUCTORS AND DESTRUCTOR ----- */

			/* --------------------------------------------------------------------------------
			- Empty container constructor (default constructor) -
				Constructs an empty container, with no elements.

			Source: https://legacy.cplusplus.com/reference/map/map/map/
			-------------------------------------------------------------------------------- */
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(_val_comp), _size(0), _key_comp(comp), _val_comp(_key_comp)
			{
				(void)alloc;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Range constructor -
				Constructs a container with as many elements as the range [first, last], with each element constructed from its corresponding element in that range.
				The container keeps an internal copy of alloc and comp, which are used to allocate storage and to sort the elements throughout its lifetime.

			Source: https://legacy.cplusplus.com/reference/map/map/map/
			-------------------------------------------------------------------------------- */
			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(_val_comp), _size(0), _key_comp(comp), _val_comp(_key_comp)
			{
				(void)alloc;
				insert(first, last);
				return;
			}

			/* --------------------------------------------------------------------------------
			- Copy constructor -
				Constructs a container with a copy of each of the elements in x.
				Creates a container that keeps and uses copies of x's allocator and comparison object.

			Source: https://legacy.cplusplus.com/reference/map/map/map/
			-------------------------------------------------------------------------------- */
			map(const map& x) : _tree(x._tree), _size(x.size()), _key_comp(x._key_comp), _val_comp(_key_comp)
				{return;}

			/* --------------------------------------------------------------------------------
			- Map destructor -
				Destroys the container object.
				This destroys all container elements, and deallocates all the storage capacity allocated by the map container using its allocator.

			Source: https://legacy.cplusplus.com/reference/map/map/~map/
			-------------------------------------------------------------------------------- */
			~map()
				{return;}


			/* ----- MEMBER FUNCTIONS ----- */

			/* --- Operator overloads --- */

			/* --------------------------------------------------------------------------------
			- Copy container content -
				Assigns new contents to the container, replacing its current content.
				Copies all the elements from x into the container, changing its size accordingly.
				The container preserves its current allocator, which is used to allocate additional storage if needed.
				The elements stored in the container before the call are either assigned to or destroyed.

			Source: https://cplusplus.com/reference/map/map/operator=/
			-------------------------------------------------------------------------------- */
			map&									operator=(const map& x)
			{
				_tree = x._tree;
				_size = x._size;
				return (*this);
			}

			/* --------------------------------------------------------------------------------
			- Access element -
				If k matches the key of an element in the container, the function returns a reference to its mapped value.
				If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value. Notice that this always increases the container size by one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).

			Source: https://cplusplus.com/reference/map/map/operator[]/
			-------------------------------------------------------------------------------- */
			mapped_type&							operator[](const key_type& k)
			{
				value_type	v = value_type(k, mapped_type());
				iterator	it = iterator(_tree.search(v));
				iterator	ite = end();

				if (it != ite)
					return (it->second);
				_size++;
				return (_tree.insert(v).first->get_value().second);
			}


			/* --- Iterators --- */

			/* --------------------------------------------------------------------------------
			- Return iterator to beginning -
				Returns an iterator referring to the first element in the map container.
				Because map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
				If the container is empty, the returned iterator value shall not be dereferenced.

			Source: https://cplusplus.com/reference/map/map/begin/
			-------------------------------------------------------------------------------- */
			iterator								begin()
			{
				if (!_size)
					return (end());
				return (iterator(red_black_node<value_type, value_compare>::get_smallest(_tree.get_root())));
			}

			/* --------------------------------------------------------------------------------
			- Return iterator to beginning -
				Returns an iterator referring to the first element in the map container.
				Because map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
				If the container is empty, the returned iterator value shall not be dereferenced.

			Source: https://cplusplus.com/reference/map/map/begin/
			-------------------------------------------------------------------------------- */
			const_iterator							begin() const
			{
				if (!_size)
					return (end());
				return (static_cast<const_iterator>(red_black_node<const value_type, value_compare>::get_smallest(_tree.get_root())));
			}

			/* --------------------------------------------------------------------------------
			- Return iterator to end -
				Returns an iterator referring to the past-the-end element in the map container.
				The past-the-end element is the theoretical element that would follow the last element in the map container. It does not point to any element, and thus shall not be dereferenced.
				Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with map::begin to specify a range including all the elements in the container.
				If the container is empty, this function returns the same as map::begin.

			Source: https://cplusplus.com/reference/map/map/end/
			-------------------------------------------------------------------------------- */
			iterator								end()
				{return (iterator(_tree.get_end()));}

			/* --------------------------------------------------------------------------------
			- Return iterator to end -
				Returns an iterator referring to the past-the-end element in the map container.
				The past-the-end element is the theoretical element that would follow the last element in the map container. It does not point to any element, and thus shall not be dereferenced.
				Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with map::begin to specify a range including all the elements in the container.
				If the container is empty, this function returns the same as map::begin.

			Source: https://cplusplus.com/reference/map/map/end/
			-------------------------------------------------------------------------------- */
			const_iterator							end() const
				{return (static_cast<const_iterator>(_tree.get_end()));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse beginning -
				Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
				Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
				rbegin points to the element preceding the one that would be pointed to by member end.

			Source: https://cplusplus.com/reference/map/map/rbegin/
			-------------------------------------------------------------------------------- */
			reverse_iterator						rbegin()
				{return (reverse_iterator(_tree.get_end()));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse beginning -
				Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
				Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
				rbegin points to the element preceding the one that would be pointed to by member end.

			Source: https://cplusplus.com/reference/map/map/rbegin/
			-------------------------------------------------------------------------------- */
			const_reverse_iterator					rbegin() const
				{return (const_reverse_iterator(_tree.get_end()));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse end -
				Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
				The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).

			Source: https://cplusplus.com/reference/map/map/rend/
			-------------------------------------------------------------------------------- */
			reverse_iterator						rend()
				{return (reverse_iterator(red_black_node<value_type, value_compare>::get_smallest(_tree.get_root())));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse end -
				Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
				The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).

			Source: https://cplusplus.com/reference/map/map/rend/
			-------------------------------------------------------------------------------- */
			const_reverse_iterator					rend() const
				{return (const_reverse_iterator(red_black_node<value_type, value_compare>::get_smallest(_tree.get_root())));}


			/* --- Capacity --- */

			/* --------------------------------------------------------------------------------
			- Test whether container is empty -
				Returns whether the map container is empty (i.e. whether its size is 0).
				This function does not modify the container in any way. To clear the content of a map container, see map::clear.

			Source: https://cplusplus.com/reference/map/map/empty/
			-------------------------------------------------------------------------------- */
			bool									empty() const
				{return (!_size);}

			/* --------------------------------------------------------------------------------
			- Return container size -
				Returns the number of elements in the map container.

			Source: https://cplusplus.com/reference/map/map/size/
			-------------------------------------------------------------------------------- */
			size_type								size() const
				{return (_size);}

			/* --------------------------------------------------------------------------------
			- Return maximum size -
				Returns the maximum number of elements that the map container can hold.
				This is the maximum potential size the container can reach due to known system or library implementation limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.

			Source: https://cplusplus.com/reference/map/map/max_size/
			-------------------------------------------------------------------------------- */
			size_type								max_size() const
				{return (_tree.get_alloc().max_size());}


			/* --- Modifiers --- */

			/* --------------------------------------------------------------------------------
			- Insert elements -
				Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
				Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
				An alternative way to insert elements in a map is by using member function map::operator[].
				Internally, map containers keep all their elements sorted by their key following the criterion specified by its comparison object. The elements are always inserted in its respective position following this ordering.
				The parameters determine how many elements are inserted and to which values they are initialized.

			-val
				Value to be copied to (or moved as) the inserted element.
				Member type value_type is the type of the elements in the container, defined in map as pair<const key_type,mapped_type> (see map member types).
				The template parameter P shall be a type convertible to value_type.
				If P is instantiated as a reference type, the argument is copied.

			Returns a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map. The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.

			Source: https://cplusplus.com/reference/map/map/insert/
			-------------------------------------------------------------------------------- */
			pair<iterator, bool>					insert(const value_type& val)
			{
				pair<red_black_node<value_type, value_compare>*, bool>	tmp = _tree.insert(val);
				pair<iterator, bool>									itp(iterator(tmp.first), tmp.second);

				if (itp.second)
					_size++;
				return (itp);
			}

			/* --------------------------------------------------------------------------------
			- Insert elements -
				Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
				Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
				An alternative way to insert elements in a map is by using member function map::operator[].
				Internally, map containers keep all their elements sorted by their key following the criterion specified by its comparison object. The elements are always inserted in its respective position following this ordering.
				The parameters determine how many elements are inserted and to which values they are initialized.

			-val
				Value to be copied to (or moved as) the inserted element.
				Member type value_type is the type of the elements in the container, defined in map as pair<const key_type,mapped_type> (see map member types).
				The template parameter P shall be a type convertible to value_type.
				If P is instantiated as a reference type, the argument is copied.
			-position
				Hint for the position where the element can be inserted.
				The function optimizes its insertion time if position points to the element that will precede the inserted element.
				Notice that this is just a hint and does not force the new element to be inserted at that position within the map container (the elements in a map always follow a specific order depending on their key).
				Member types iterator and const_iterator are defined in map as bidirectional iterator types that point to elements.

			Returns an iterator pointing to either the newly inserted element or to the element that already had an equivalent key in the map.

			Source: https://cplusplus.com/reference/map/map/insert/
			-------------------------------------------------------------------------------- */
			iterator								insert(iterator position, const value_type& val)
			{
				pair<red_black_node<value_type, value_compare>*, bool>	tmp;

				if (position != begin() && position != end() && _val_comp(*(--position), val) && _val_comp(val, *(++position)))
					tmp = _tree.insert(val, position);
				else
					tmp = _tree.insert(val);

				if (tmp.second)
					_size++;
				return (iterator(tmp.first));
			}

			/* --------------------------------------------------------------------------------
			- Insert elements -
				Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
				Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
				An alternative way to insert elements in a map is by using member function map::operator[].
				Internally, map containers keep all their elements sorted by their key following the criterion specified by its comparison object. The elements are always inserted in its respective position following this ordering.
				The parameters determine how many elements are inserted and to which values they are initialized.

			-first, last
				Iterators specifying a range of elements. Copies of the elements in the range [first, last] are inserted in the container.
				Notice that the range includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
				The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.

			Source: https://cplusplus.com/reference/map/map/insert/
			-------------------------------------------------------------------------------- */
			template<class InputIterator>
			void									insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					pair<red_black_node<value_type, value_compare>*, bool>	tmp = _tree.insert(*first++);

					if (tmp.second)
						_size++;
				}
				return;
			}

			/* --------------------------------------------------------------------------------
			- Erase elements -
				Removes from the map container a single element.
				This effectively reduces the container size by the number of elements removed, which are destroyed.

			Source: https://cplusplus.com/reference/map/map/erase/
			-------------------------------------------------------------------------------- */
			void									erase(iterator position)
			{
				if (_tree.erase(*position))
					_size--;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Erase elements -
				Removes from the map container a single element.
				This effectively reduces the container size by the number of elements removed, which are destroyed.

			Returns the number of elements erased.

			Source: https://cplusplus.com/reference/map/map/erase/
			-------------------------------------------------------------------------------- */
			size_type								erase(const key_type& k)
			{
				value_type	val(value_type(k, mapped_type()));

				if (_tree.erase(val))
				{
					_size--;
					return (1);
				}
				return (0);
			}

			/* --------------------------------------------------------------------------------
			- Erase elements -
				Removes from the map container a range of elements ([first, last]).
				This effectively reduces the container size by the number of elements removed, which are destroyed.

			Source: https://cplusplus.com/reference/map/map/erase/
			-------------------------------------------------------------------------------- */
			void									erase(iterator first, iterator last)
			{
				while (first != last)
				{
					iterator	tmp = first;

					++first;
					if (_tree.erase(*tmp))
						_size--;
				}
				return;
			}

			/* --------------------------------------------------------------------------------
			- Swap content -
				Exchanges the content of the container by the content of x, which is another map of the same type. Sizes may differ.
				After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
				Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function.

			Source: https://cplusplus.com/reference/map/map/swap/
			-------------------------------------------------------------------------------- */
			void									swap(map& x)
			{
				_tree.swap_content(x._tree);
				size_type	tmp = x._size;

				x._size = _size;
				_size = tmp;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Clear content -
				Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.

			Source: https://cplusplus.com/reference/map/map/clear/
			-------------------------------------------------------------------------------- */
			void									clear()
			{
				_tree.clear();
				_size = 0;
				return;
			}


			/* --- Observers --- */

			/* --------------------------------------------------------------------------------
			- Return key comparison object -
				Returns a copy of the comparison object used by the container to compare keys.
				The comparison object of a map object is set on construction. Its type (member key_compare) is the third template parameter of the map template. By default, this is a less object, which returns the same as operator<.
				This object determines the order of the elements in the container: it is a function pointer or a function object that takes two arguments of the same type as the element keys, and returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
				Two keys are considered equivalent if key_comp returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).

			Source: https://cplusplus.com/reference/map/map/key_comp/
			-------------------------------------------------------------------------------- */
			key_compare								key_comp() const
				{return (_key_comp);}

			/* --------------------------------------------------------------------------------
			Return value comparison object
				Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
				The arguments taken by this function object are of member type value_type (defined in map as an alias of pair<const key_type,mapped_type>), but the mapped_type part of the value is not taken into consideration in this comparison.
				The comparison object returned is an object of the member type map::value_compare, which is a nested class that uses the internal comparison object to generate the appropriate comparison functional class.
				The public member of this comparison class returns true if the key of the first argument is considered to go before that of the second (according to the strict weak ordering specified by the container's comparison object, key_comp), and false otherwise.
				Notice that value_compare has no public constructor, therefore no objects can be directly created from this nested class outside map members.

			Source: https://cplusplus.com/reference/map/map/
			-------------------------------------------------------------------------------- */
			value_compare							value_comp() const
				{return (_val_comp);}

			/* --- Operations --- */

			/* --------------------------------------------------------------------------------
			- Get iterator to element -
				Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
				Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
				Another member function, map::count, can be used to just check whether a particular key exists.

			Source: https://cplusplus.com/reference/map/map/find/
			-------------------------------------------------------------------------------- */
			iterator								find(const key_type& k)
			{
				value_type	val(k, mapped_type());

				return (iterator(_tree.search()));
			}

			/* --------------------------------------------------------------------------------
			- Get iterator to element -
				Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
				Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
				Another member function, map::count, can be used to just check whether a particular key exists.

			Source: https://cplusplus.com/reference/map/map/find/
			-------------------------------------------------------------------------------- */
			const_iterator							find(const key_type& k) const
			{
				value_type	val(k, mapped_type());

				return (static_cast<const_iterator>(_tree.search()));
			}

			/* --------------------------------------------------------------------------------
			- Count elements with a specific key -
				Searches the container for elements with a key equivalent to k and returns the number of matches.
				Because all elements in a map container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
				Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).

			Source: https://cplusplus.com/reference/map/map/count/
			-------------------------------------------------------------------------------- */
			size_type								count(const key_type& k) const
			{
				value_type	val(k, mapped_type());

				if (_tree.search(val) == _tree.get_end())
					return (0);
				return (1);
			}

			/* --------------------------------------------------------------------------------
			- Return iterator to lower bound -
				Returns an iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).
				The function uses its internal comparison object (_key_comp) to determine this, returning an iterator to the first element for which key_comp(elementkey,k) would return false.
				If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is not less than k.
				A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.

			Source: https://cplusplus.com/reference/map/map/lower_bound/
			-------------------------------------------------------------------------------- */
			iterator								lower_bound(const key_type& k)
			{
				value_type	val(k, mapped_type());

				return (iterator(_tree.search_lower_bound(val)));
			}

			/* --------------------------------------------------------------------------------
			- Return iterator to lower bound -
				Returns an iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).
				The function uses its internal comparison object (_key_comp) to determine this, returning an iterator to the first element for which key_comp(elementkey, k) would return false.
				If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is not less than k.
				A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.

			Source: https://cplusplus.com/reference/map/map/lower_bound/
			-------------------------------------------------------------------------------- */
			const_iterator							lower_bound(const key_type& k) const
			{
				value_type	val(k, mapped_type());

				return (static_cast<const_iterator>(_tree.search_lower_bound(val)));
			}

			/* --------------------------------------------------------------------------------
			- Return iterator to upper bound -
				Returns an iterator pointing to the first element in the container whose key is considered to go after k.
				The function uses its internal comparison object (_key_comp) to determine this, returning an iterator to the first element for which key_comp(k, elementkey) would return true.
				If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is greater than k.
				A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the map contains an element with a key equivalent to k: In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.

			Source: https://cplusplus.com/reference/map/map/upper_bound/
			-------------------------------------------------------------------------------- */
			iterator								upper_bound(const key_type& k)
			{
				value_type	val(k, mapped_type());

				return (iterator(_tree.search_upper_bound(val)));
			}

			/* --------------------------------------------------------------------------------
			- Return iterator to upper bound -
				Returns an iterator pointing to the first element in the container whose key is considered to go after k.
				The function uses its internal comparison object (_key_comp) to determine this, returning an iterator to the first element for which key_comp(k,elementkey) would return true.
				If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is greater than k.
				A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the map contains an element with a key equivalent to k: In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.

			Source: https://cplusplus.com/reference/map/map/upper_bound/
			-------------------------------------------------------------------------------- */
			const_iterator							upper_bound(const key_type& k) const
			{
				value_type	val(k, mapped_type());

				return (static_cast<const_iterator>(_tree.search_upper_bound(val)));
			}

			/* --------------------------------------------------------------------------------
			- Get range of equal elements -
				Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
				Because the elements in a map container have unique keys, the range returned will contain a single element at most.
				If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element that has a key considered to go after k according to the container's internal comparison object (_key_comp).
				Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).

			Source: https://cplusplus.com/reference/map/map/equal_range/
			-------------------------------------------------------------------------------- */
			pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
			{
				value_type	val(k, mapped_type());

				return (pair<const_iterator, const_iterator>(_tree.search_lower_bound(val), _tree.search_upper_bound(val)));
			}

			/* --------------------------------------------------------------------------------
			- Get range of equal elements -
				Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
				Because the elements in a map container have unique keys, the range returned will contain a single element at most.
				If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element that has a key considered to go after k according to the container's internal comparison object (_key_comp).
				Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).

			Source: https://cplusplus.com/reference/map/map/equal_range/
			-------------------------------------------------------------------------------- */
			pair<iterator, iterator>				equal_range(const key_type& k)
			{
				value_type	val(k, mapped_type());

				return (pair<iterator, iterator>(_tree.search_lower_bound(val), _tree.search_upper_bound(val)));
			}


			/* --- Allocator --- */

			/* --------------------------------------------------------------------------------
			- Get allocator -
				Returns a copy of the allocator object associated with the map.

			Source: https://cplusplus.com/reference/map/map/get_allocator/
			-------------------------------------------------------------------------------- */
			allocator_type							get_allocator() const
				{return (allocator_type());}

	};
	/* ----- NON-MEMBER OPERATOR OVERLOADS (C++20) ----- */

	// template <typename Key, typename T, typename Compare, typename Alloc>
	// bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	// 	{return (equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size());}

	// template <typename Key, typename T, typename Compare, typename Alloc>
	// bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	// 	{return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	// template <typename Key, typename T, typename Compare, typename Alloc>
	// bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	// 	{return (!(lhs == rhs));}

	// template <typename Key, typename T, typename Compare, typename Alloc>
	// bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	// 	{return (rhs < lhs);}

	// template <typename Key, typename T, typename Compare, typename Alloc>
	// bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	// 	{return (!(rhs < lhs));}

	// template <typename Key, typename T, typename Compare, typename Alloc>
	// bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	// 	{return (!(lhs < rhs));}
}

#endif