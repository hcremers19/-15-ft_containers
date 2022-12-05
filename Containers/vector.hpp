/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:46:38 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/05 14:55:21 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>		// size_t
# include <stdexcept>	// out_of_range
# include <memory>		// allocator
# include <iterator>	// distance
# include "../Iterators/random_access_iterator.hpp"
# include "../Iterators/reverse_iterator.hpp"
# include "../Utilities/util.hpp"

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:																	// Need to declare some public types here to use them privately just after
			typedef				T												value_type;
			typedef				Alloc											allocator_type;
			typedef				value_type&										reference;
			typedef				const value_type&								const_reference;
			typedef				value_type*										pointer;
			typedef				const value_type*								const_pointer;
			typedef typename	ft::random_access_iterator<value_type>			iterator;
			typedef typename	ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename	iterator_traits<iterator>::difference_type		difference_type;
			typedef				size_t											size_type;

		private:
			pointer 			_container;
			size_type			_size;
			size_type			_capacity;
			allocator_type		_alloc;

		public:
			/* ----- CONSTRUCTORS AND DESTRUCTOR ----- */

			/* --------------------------------------------------------------------------------
			- Empty container constructor (default constructor) -
			Constructs an empty container, with no elements.

			-alloc
				Allocator object.
				The container keeps and uses an internal copy of this allocator.
				Member type allocator_type is the internal allocator type used by the container, defined in vector as an alias of its second template parameter (Alloc).
				If allocator_type is an instantiation of the default allocator (which has no state), this is not relevant.

			Source: https://cplusplus.com/reference/vector/vector/vector/
			-------------------------------------------------------------------------------- */
			explicit vector(const allocator_type& alloc = allocator_type()) : _container(NULL), _size(0), _capacity(0), _alloc(alloc)
				{return;}

			/* --------------------------------------------------------------------------------
			- Fill constructor -
				Constructs a container with n elements. Each element is a copy of val.

			-n
				Initial container size (i.e., the number of elements in the container at construction).
				Member type size_type is an unsigned integral type.
			-val
				Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
				Member type value_type is the type of the elements in the container, defined in vector as an alias of its first template parameter (T).
			-alloc
				Allocator object.
				The container keeps and uses an internal copy of this allocator.
				Member type allocator_type is the internal allocator type used by the container, defined in vector as an alias of its second template parameter (Alloc).
				If allocator_type is an instantiation of the default allocator (which has no state), this is not relevant.

			Source: https://cplusplus.com/reference/vector/vector/vector/
			-------------------------------------------------------------------------------- */
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
			{
				if (n < 0)
					throw (std::out_of_range("ft::vector"));
				_container = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_container + i, val);
				return;
			}

			/* --------------------------------------------------------------------------------
			- Range constructor -
				Constructs a container with as many elements as the range [first, last], with each element constructed from its corresponding element in that range, in the same order.

			-first, last
				Input iterators to the initial and final positions in a range. The range used is [first, last], which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
				The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
			-alloc
				Allocator object.
				The container keeps and uses an internal copy of this allocator.
				Member type allocator_type is the internal allocator type used by the container, defined in vector as an alias of its second template parameter (Alloc).
				If allocator_type is an instantiation of the default allocator (which has no state), this is not relevant.

			Source: https://cplusplus.com/reference/vector/vector/vector/
			-------------------------------------------------------------------------------- */
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				_size = std::distance(first, last);
				_capacity = _size;
				_container = _alloc.allocate(_size);
				for (size_type i = 0; first != last; i++)
					_alloc.construct(_container + i, *first);
				return;
			}

			/* --------------------------------------------------------------------------------
			- Copy constructor -
				Constructs a container with a copy of each of the elements in x, in the same order.

			-x
				Another vector object of the same type (with the same class template arguments T and Alloc), whose contents are either copied or acquired.

			Source: https://cplusplus.com/reference/vector/vector/vector/
			-------------------------------------------------------------------------------- */
			vector(const vector& x)
			{
				_alloc = x._alloc;
				const_iterator	first = x.begin();
				const_iterator	last = x.end();

				_size = x._size;
				_capacity = _size;
				_container = _alloc.allocate(_size);
				for (size_type i = 0; first != last; first++, i++)
					_alloc.construct(_container + i, *first);
				return;
			}

			/* --------------------------------------------------------------------------------
			- Vector destructor -
				Destroys the container object.
				This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.

			Source: https://legacy.cplusplus.com/reference/vector/vector/~vector/
			-------------------------------------------------------------------------------- */
			~vector()
			{
				size_type	n = 0;

				for (iterator it = begin(); it != end(); it++, n++)
					_alloc.destroy(_container + n);
				_alloc.deallocate(_container, _capacity);
				return;
			}


			/* ----- OPERATOR OVERLOADS ----- */

			/* --------------------------------------------------------------------------------
			- Assign content -
				Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.

			Source: https://cplusplus.com/reference/vector/vector/operator=/
			-------------------------------------------------------------------------------- */
			vector&					operator=(const vector& x)
			{
				if (*this == x)
					return *this;
				assign(x.begin(), x.end());
				return (*this);
			}

			/* --------------------------------------------------------------------------------
			- Access element -
				Returns a reference to the element at position n in the vector container.
				A similar member function, vector::at, has the same behavior as this operator function, except that vector::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
				Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.

			Source: https://cplusplus.com/reference/vector/vector/operator[]/
			-------------------------------------------------------------------------------- */
			reference				operator[](size_type n)
				{return (_container[n]);}

			/* --------------------------------------------------------------------------------
			- Access element -
				Returns a reference to the element at position n in the vector container.
				A similar member function, vector::at, has the same behavior as this operator function, except that vector::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
				Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.

			Source: https://cplusplus.com/reference/vector/vector/operator[]/
			-------------------------------------------------------------------------------- */
			const_reference			operator[](size_type n) const
				{return (_container[n]);}


			/* ----- MEMBER FUNCTIONS ----- */

			/* ITERATORS */

			/* --------------------------------------------------------------------------------
			- Return iterator to beginning -
				Returns an iterator pointing to the first element in the vector.
				Notice that, unlike member vector::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
				If the container is empty, the returned iterator value shall not be dereferenced.

			Source: https://cplusplus.com/reference/vector/vector/begin/
			-------------------------------------------------------------------------------- */
			iterator				begin()
				{return (iterator(_container));}

			/* --------------------------------------------------------------------------------
			- Return iterator to beginning -
				Returns an iterator pointing to the first element in the vector.
				Notice that, unlike member vector::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
				If the container is empty, the returned iterator value shall not be dereferenced.

			Source: https://cplusplus.com/reference/vector/vector/begin/
			-------------------------------------------------------------------------------- */
			const_iterator			begin() const
				{return (const_iterator(_container));}

			/* --------------------------------------------------------------------------------
			- Return iterator to end -
				Returns an iterator referring to the past-the-end element in the vector container.
				The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
				Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with vector::begin to specify a range including all the elements in the container.
				If the container is empty, this function returns the same as vector::begin.

			Source: https://cplusplus.com/reference/vector/vector/end/
			-------------------------------------------------------------------------------- */
			iterator				end()
				{return (iterator(_container + _size));}

			/* --------------------------------------------------------------------------------
			- Return iterator to end -
				Returns an iterator referring to the past-the-end element in the vector container.
				The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
				Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with vector::begin to specify a range including all the elements in the container.
				If the container is empty, this function returns the same as vector::begin.

			Source: https://cplusplus.com/reference/vector/vector/end/
			-------------------------------------------------------------------------------- */
			const_iterator			end() const
				{return (const_iterator(_container + _size));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse beginning -
				Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
				Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
				rbegin points to the element right before the one that would be pointed to by member end.
				Notice that unlike member vector::back, which returns a reference to this same element, this function returns a reverse random access iterator.

			Source: https://cplusplus.com/reference/vector/vector/rbegin/
			-------------------------------------------------------------------------------- */
			reverse_iterator		rbegin()
				{return (reverse_iterator(end()));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse beginning -
				Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
				Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
				rbegin points to the element right before the one that would be pointed to by member end.
				Notice that unlike member vector::back, which returns a reference to this same element, this function returns a reverse random access iterator.

			Source: https://cplusplus.com/reference/vector/vector/rbegin/
			-------------------------------------------------------------------------------- */
			const_reverse_iterator	rbegin() const
				{return (const_reverse_iterator(end()));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse end -
				Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
				The range between vector::rbegin and vector::rend contains all the elements of the vector (in reverse order).

			Source: https://cplusplus.com/reference/vector/vector/rend/
			-------------------------------------------------------------------------------- */
			reverse_iterator		rend()
				{return (reverse_iterator(begin()));}

			/* --------------------------------------------------------------------------------
			- Return reverse iterator to reverse end -
				Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
				The range between vector::rbegin and vector::rend contains all the elements of the vector (in reverse order).

			Source: https://cplusplus.com/reference/vector/vector/rend/
			-------------------------------------------------------------------------------- */
			const_reverse_iterator	rend() const
				{return (const_reverse_iterator(begin()));}

			/* CAPACITY */

			/* --------------------------------------------------------------------------------
			- Return size -
				Returns the number of elements in the vector.
				This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.

			Source: https://cplusplus.com/reference/vector/vector/size/
			-------------------------------------------------------------------------------- */
			size_type				size() const
				{return (_size);}

			/* --------------------------------------------------------------------------------
			- Return size -
				Returns the number of elements in the vector.
				This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.

			Source: https://cplusplus.com/reference/vector/vector/max_size/
			-------------------------------------------------------------------------------- */
			size_type				max_size() const
				{return (_alloc.max_size());}

			/* --------------------------------------------------------------------------------
			- Change size -
				Resizes the container so that it contains n elements.
				If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
				If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
				If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
				Notice that this function changes the actual content of the container by inserting or erasing elements from it.

			Source: https://cplusplus.com/reference/vector/vector/resize/
			-------------------------------------------------------------------------------- */
			void					resize(size_type n, value_type val = value_type())
			{
				if (n > max_size())
					throw (std::out_of_range("vector::resize"));
				reserve(n);
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_container + i, val);
				if (_size > 0)
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_container + i);
				_size = n;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Return size of allocated storage capacity -
				Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
				This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
				Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
				The capacity of a vector can be explicitly altered by calling member vector::reserve.

			Source: https://cplusplus.com/reference/vector/vector/capacity/
			-------------------------------------------------------------------------------- */
			size_type				capacity() const
				{return (_capacity);}

			/* --------------------------------------------------------------------------------
			- Test whether vector is empty -
				Returns whether the vector is empty (i.e. whether its size is 0).
				This function does not modify the container in any way. To clear the content of a vector, see vector::clear.

			Source: https://cplusplus.com/reference/vector/vector/empty/
			-------------------------------------------------------------------------------- */
			bool					empty() const
				{return (_size == 0);}

			/* --------------------------------------------------------------------------------
			- Request a change in capacity -
				Requests that the vector capacity be at least enough to contain n elements.
				If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
				In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
				This function has no effect on the vector size and cannot alter its elements.

			Source: https://cplusplus.com/reference/vector/vector/reserve/
			-------------------------------------------------------------------------------- */
			void					reserve(size_type n)
			{
				if (n > max_size())
					throw (std::out_of_range("vector::reserve"));
				else if (_capacity >= n)
					return;
				pointer	tmp = _alloc.allocate(n);

				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(tmp + i, _container[i]);
					_alloc.destroy(_container + i);
				}
				_alloc.deallocate(_container, _capacity);
				_container = tmp;
				_capacity = n;
				return;
			}

			/* ELEMENT ACCESS */

			/* --------------------------------------------------------------------------------
			- Access element -
				Returns a reference to the element at position n in the vector.
				The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.

			Source: https://cplusplus.com/reference/vector/vector/at/
			-------------------------------------------------------------------------------- */
			reference				at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (_container[n]);
			}

			/* --------------------------------------------------------------------------------
			- Access element -
				Returns a reference to the element at position n in the vector.
				The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.

			Source: https://cplusplus.com/reference/vector/vector/at/
			-------------------------------------------------------------------------------- */
			const_reference			at(size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (_container[n]);
			}

			/* --------------------------------------------------------------------------------
			- Access first element -
				Returns a reference to the first element in the vector.
				Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
				Calling this function on an empty container causes undefined behavior.

			Source: https://cplusplus.com/reference/vector/vector/front/
			-------------------------------------------------------------------------------- */
			reference				front()
				{return (*_container);}

			/* --------------------------------------------------------------------------------
			- Access first element -
				Returns a reference to the first element in the vector.
				Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
				Calling this function on an empty container causes undefined behavior.

			Source: https://cplusplus.com/reference/vector/vector/front/
			-------------------------------------------------------------------------------- */
			const_reference			front() const
				{return (*_container);}

			/* --------------------------------------------------------------------------------
			- Access last element -
				Returns a reference to the last element in the vector.
				Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
				Calling this function on an empty container causes undefined behavior.

			Source: https://cplusplus.com/reference/vector/vector/back/
			-------------------------------------------------------------------------------- */
			reference				back()
				{return (_container[_size - 1]);}

			/* --------------------------------------------------------------------------------
			- Access last element -
				Returns a reference to the last element in the vector.
				Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
				Calling this function on an empty container causes undefined behavior.

			Source: https://cplusplus.com/reference/vector/vector/back/
			-------------------------------------------------------------------------------- */
			const_reference			back() const
				{return (_container[_size - 1]);}

			/* MODIFIERS */

			/* --------------------------------------------------------------------------------
			- Assign vector content -
				Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
				The new contents are elements constructed from each of the elements in the range between first and last, in the same order.
				If a reallocation happens,the storage needed is allocated using the internal allocator.
				Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no assignments of elements take place).
				This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.

			-first, last
				Input iterators to the initial and final positions in a sequence. The range used is [first, last], which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
				The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.

			Source: https://cplusplus.com/reference/vector/vector/assign/
			-------------------------------------------------------------------------------- */
			template<class InputIterator>
			void					assign(InputIterator first, InputIterator last)
			{
				size_type	size = std::distance(first, last);

				clear();
				if (size > _capacity)
				{
					_alloc.deallocate(_container, _capacity);
					_container = _alloc.allocate(size);
					_capacity = size;
				}
				for (size_type i = 0; i < size; i++, first++)
					_alloc.construct(_container + i, *first);
				_size = size;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Assign vector content -
				Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
				The new contents are n elements, each initialized to a copy of val.
				If a reallocation happens,the storage needed is allocated using the internal allocator.
				Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no assignments of elements take place).
				This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.

			-n
				New size for the container.
				Member type size_type is an unsigned integral type.
			-val
				Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
				Member type value_type is the type of the elements in the container, defined in vector as an alias of its first template parameter (T).

			Source: https://cplusplus.com/reference/vector/vector/assign/
			-------------------------------------------------------------------------------- */
			void					assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
				{
					_alloc.deallocate(_container, _capacity);
					_container = _alloc.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_container + i, val);
				_size = n;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Add element at the end -
				Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
				This effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.

			Source: https://cplusplus.com/reference/vector/vector/push_back/
			-------------------------------------------------------------------------------- */
			void					push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
					reserve(_capacity ? _capacity * 2 : 1);
				_alloc.construct(_container + _size, val);
				_size++;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Delete last element -
				Removes the last element in the vector, effectively reducing the container size by one.
				This destroys the removed element.

			Source: https://cplusplus.com/reference/vector/vector/pop_back/
			-------------------------------------------------------------------------------- */
			void					pop_back()
			{
				if (!_size)
					return;
				_alloc.destroy(_container + _size - 1);
				_size--;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Insert elements -
				The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
				This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
				The parameters determine how many elements are inserted and to which values they are initialized:

			-position
				Position in the vector where the new elements are inserted.
				iterator is a member type, defined as a random access iterator type that points to elements.
			-val
				Value to be copied (or moved) to the inserted elements.
				Member type value_type is the type of the elements in the container, defined in deque as an alias of its first template parameter (T).

			Source: https://cplusplus.com/reference/vector/vector/insert/
			-------------------------------------------------------------------------------- */
			iterator				insert(iterator position, const value_type& val)
			{
				size_type	dist = 0;

				if (_size)
					dist = std::distance(begin(), position);
				insert(position, 1, val);
				return (begin() + dist);
			}

			/* --------------------------------------------------------------------------------
			- Insert elements -
				The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
				This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
				The parameters determine how many elements are inserted and to which values they are initialized:

			-position
				Position in the vector where the new elements are inserted.
				iterator is a member type, defined as a random access iterator type that points to elements.
			-n
				Number of elements to insert. Each element is initialized to a copy of val.
				Member type size_type is an unsigned integral type.
			-val
				Value to be copied (or moved) to the inserted elements.
				Member type value_type is the type of the elements in the container, defined in deque as an alias of its first template parameter (T).

			Source: https://cplusplus.com/reference/vector/vector/insert/
			-------------------------------------------------------------------------------- */
			void					insert(iterator position, size_type n, const value_type& val)
			{

				size_type	pos = std::distance(begin(), position);

				if (_size + n > _capacity)
				{
					if (!_capacity)
						_capacity = 1;
					size_type	size = 2;

					while (_capacity * size < _size + n)
						size *= 2;
					if (_capacity * size > max_size())
						throw std::out_of_range("vector::insert");
					pointer	tmp = _alloc.allocate(_capacity * size);

					for (size_type i = 0; i < pos; i++)
					{
						_alloc.construct(tmp + i, _container[i]);
						_alloc.destroy(_container + i);
					}
					for (size_type i = 0; i < n; i++)
						_alloc.construct(tmp + pos + i, val);
					for (size_type i = pos; i < _size; i++)
					{
						_alloc.construct(tmp + i + n, _container[i]);
						_alloc.destroy(_container + i);
					}
					_alloc.deallocate(_container, _capacity);
					_container = tmp;
					_capacity = _capacity * size;
				}
				else
				{
					for (size_t i = _size - 1; i >= static_cast<size_t>(pos); i--)
						_container[i + n] = _container[i];
					for (size_t i = pos; i < pos + n; i++)
						_alloc.construct(_container + i, val);
				}
				_size += n;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Insert elements -
				The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
				This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
				Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
				The parameters determine how many elements are inserted and to which values they are initialized:

			-position
				Position in the vector where the new elements are inserted.
				iterator is a member type, defined as a random access iterator type that points to elements.
			-first, last
				Iterators specifying a range of elements. Copies of the elements in the range [first, last] are inserted at position (in the same order).
				Notice that the range includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
				The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.

			Source: https://cplusplus.com/reference/vector/vector/insert/
			-------------------------------------------------------------------------------- */
			template<class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type	pos = std::distance(begin(), position);
				size_type	dist = std::distance(first, last);

				if (_size + dist > _capacity)
				{
					if (!_capacity)
						_capacity = 1;
					size_type	size = 2;

					while (_capacity * size < _size + dist)
						size *= 2;
					if (_capacity * size > max_size())
						throw std::out_of_range("vector::insert");
					pointer	tmp = _alloc.allocate(_capacity * size);

					for (size_type i = 0; i < pos; i++)
					{
						_alloc.construct(tmp + i, _container[i]);
						_alloc.destroy(_container + i);
					}
					for (size_type i = 0; i < dist; i++, first++)
						_alloc.construct(tmp + pos + i, *first);
					for (size_type i = pos; i < _size; i++)
					{
						_alloc.construct(tmp + i + dist, _container[i]);
						_alloc.destroy(_container + i);
					}
					_alloc.deallocate(_container, _capacity);
					_container = tmp;
					_capacity = _capacity * size;
				}
				else
				{
					for (size_t i = _size - 1; i >= static_cast<size_t>(pos); i--)
						_container[i + dist] = _container[i];
					for (size_t i = pos; i < pos + dist; i++)
						_alloc.construct(_container + i, *first++);
				}
				_size += dist;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Erase elements -
				Removes from the vector a single element (position).
				This effectively reduces the container size by the number of elements removed, which are destroyed.
				Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end causes the container to relocate all the elements after the segment erased to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).

			Source: https://cplusplus.com/reference/vector/vector/erase/
			-------------------------------------------------------------------------------- */
			iterator				erase(iterator position)
			{
				iterator	it = position;
				iterator	ite = end();

				_alloc.destroy(position.base());
				for (iterator tmp = it + 1; tmp != ite; ++it, ++tmp)
					*it = *tmp;
				--_size;
				return (position);
			}

			/* --------------------------------------------------------------------------------
			- Erase elements -
				Removes from the vector a range of elements ([first, last]).
				This effectively reduces the container size by the number of elements removed, which are destroyed.
				Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end causes the container to relocate all the elements after the segment erased to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).

			Source: https://cplusplus.com/reference/vector/vector/erase/
			-------------------------------------------------------------------------------- */
			iterator				erase(iterator first, iterator last)
			{
				for (iterator it = first; it != last; ++it)
					_alloc.destroy(it.base());
				iterator	it = first;
				iterator	itp = last;

				for (; itp != end(); it++, itp++)
					*it = *itp;
				_size -= std::distance(first, last);
				return (iterator(_container + std::distance(begin(), first)));
			}

			/* --------------------------------------------------------------------------------
			- Swap content -
				Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
				After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
				Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function.
				The bool specialization of vector provides an additional overload for this function (see vector<bool>::swap).

			Source: https://cplusplus.com/reference/vector/vector/swap/
			-------------------------------------------------------------------------------- */
			void					swap(vector& x)
			{
				pointer		tmp_container = _container;
				size_type	tmp_size = _size;
				size_type	tmp_capacity = _capacity;

				_container = x._container;
				_size = x._size;
				_capacity = x._capacity;
				x._container = tmp_container;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
				return;
			}

			/* --------------------------------------------------------------------------------
			- Clear content -
				Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
				A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change due to calling this function.

			Source: https://cplusplus.com/reference/vector/vector/clear/
			-------------------------------------------------------------------------------- */
			void					clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_container + i);
				_size = 0;
				return;
			}

			/* ALLOCATOR */

			/* --------------------------------------------------------------------------------
			- Get allocator -
				Returns a copy of the allocator object associated with the vector.

			Source: https://cplusplus.com/reference/vector/vector/get_allocator/
			-------------------------------------------------------------------------------- */
			allocator_type			get_allocator() const
				{return (_alloc);}
	};


	/* ----- NON-MEMBER FUNCTIONS ----- */

	/* --------------------------------------------------------------------------------
	- "Equal to" operator for vector -
		Performs the appropriate comparison operation between the vector containers lhs and rhs.
		Performed by first comparing sizes, and if they match, the elements are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).

	Source: https://cplusplus.com/reference/vector/vector/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	bool							operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));}

	/* --------------------------------------------------------------------------------
	- "Not equal to" operator for vector -
		Performs the appropriate comparison operation between the vector containers lhs and rhs.
		Uses the operator == internally to compare the elements

	Source: https://cplusplus.com/reference/vector/vector/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	bool							operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (!(lhs == rhs));}

	/* --------------------------------------------------------------------------------
	- "Less than" operator for vector -
		Performs the appropriate comparison operation between the vector containers lhs and rhs.
		Uses algorithm lexicographical_compare, which compares the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and stopping at the first occurrence.

	Source: https://cplusplus.com/reference/vector/vector/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	bool							operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	/* --------------------------------------------------------------------------------
	- "Less than or equal to" operator for vector -
		Performs the appropriate comparison operation between the vector containers lhs and rhs.
		Uses the operator < internally to compare the elements

	Source: https://cplusplus.com/reference/vector/vector/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	bool							operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (!(rhs < lhs));}

	/* --------------------------------------------------------------------------------
	- "Greater than" operator for vector -
		Performs the appropriate comparison operation between the vector containers lhs and rhs.
		Uses the operator < internally to compare the elements

	Source: https://cplusplus.com/reference/vector/vector/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	bool							operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (rhs < lhs);}

	/* --------------------------------------------------------------------------------
	- "Greater than or equal to" operator for vector -
		Performs the appropriate comparison operation between the vector containers lhs and rhs.
		Uses the operator < internally to compare the elements

	Source: https://cplusplus.com/reference/vector/vector/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	bool							operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (!(lhs < rhs));}

	/* --------------------------------------------------------------------------------
	- Exchange contents of vectors -
		The contents of container x are exchanged with those of y. Both container objects must be of the same type (same template parameters), although sizes may differ.
		After the call to this member function, the elements in x are those which were in y before the call, and the elements of y are those which were in x. All iterators, references and pointers remain valid for the swapped objects.
		This is an overload of the generic algorithm swap that improves its performance by mutually transferring ownership over their assets to the other container (i.e., the containers exchange references to their data, without actually performing any element copy or movement): It behaves as if x.swap(y) was called.

	Source: https://cplusplus.com/reference/vector/vector/swap-free/
	-------------------------------------------------------------------------------- */
	template<class T, class Alloc>
	void 							swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
		return;
	}
}

#endif