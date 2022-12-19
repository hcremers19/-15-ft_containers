/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:17:43 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/19 15:19:54 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template<class Iterator>
	class reverse_iterator
	{
		public:
			typedef				Iterator										iterator_type;
			typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename	iterator_traits<Iterator>::value_type			value_type;
			typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	iterator_traits<Iterator>::pointer				pointer;
			typedef typename	iterator_traits<Iterator>::reference			reference;

		private:
			iterator_type		_base_iterator;

		public:
			/* ----- CONSTRUCTORS ----- */

			/* --------------------------------------------------------------------------------
			- Default constructor -
				Constructs a reverse iterator that points to no object.
				The internal base iterator is value-initialized.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
			-------------------------------------------------------------------------------- */
			reverse_iterator()
			{
				_base_iterator = NULL;

				return;
			}

			/* --------------------------------------------------------------------------------
			- Initalization constructor -
				Constructs a reverse iterator from some original iterator it. The behavior of the constructed object replicates the original, except that it iterates through its pointed elements in the reverse order.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
			-------------------------------------------------------------------------------- */
			explicit reverse_iterator(iterator_type it) : _base_iterator(it)
				{return;}

			/* --------------------------------------------------------------------------------
			- Copy / type-cast constructor -
				Constructs a reverse iterator from some other reverse iterator. The constructed object keeps the same sense of iteration as rev_it.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
			-------------------------------------------------------------------------------- */
			template<class Iterator>
			reverse_iterator(const reverse_iterator<Iterator>& rev_it) : _base_iterator(rev_it.base())
				{return;}


			/* ----- OPERATOR OVERLOADS ----- */

			/* --------------------------------------------------------------------------------
			- Const iterator overload -
			-------------------------------------------------------------------------------- */
			operator			reverse_iterator<const Iterator>() const
				{return (_base_iterator);}

			/* --------------------------------------------------------------------------------
			- Dereference iterator -
				Returns a reference to the element pointed to by the iterator.
				Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
				The iterator shall point to some object in order to be dereferenceable.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator%2a/
			-------------------------------------------------------------------------------- */
			reference			operator*() const
			{
				iterator_type	tmp(_base_iterator);

				return (*(--tmp));
			}

			/* --------------------------------------------------------------------------------
			- Addition operator -
				Returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to.
				Internally, the function applies the binary operator- on the base iterator and returns a reverse iterator constructed with the resulting iterator value.
				Note that this function requires the base iterator to be a random-access iterator.
				This operator is also overloaded as a non-member function, with the left-hand and right-hand types inverted, but this the same behavior (see operator+).

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator+/
			-------------------------------------------------------------------------------- */
			reverse_iterator	operator+(difference_type n) const
				{return (reverse_iterator(_base_iterator - n));}

			/* --------------------------------------------------------------------------------
			- Pre-increment iterator position -
				Advances the reverse_iterator by one position.
				Internally, decrements the base iterator kept by the object (as if applying operator-- to it).
				Returns *this.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator++/
			-------------------------------------------------------------------------------- */
			reverse_iterator&	operator++()
			{
				--_base_iterator;

				return (*this);
			}

			/* --------------------------------------------------------------------------------
			- Post-increment iterator position -
				Advances the reverse_iterator by one position.
				Internally, decrements the base iterator kept by the object (as if applying operator-- to it).
				Returns the value *this had before the call.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator++/
			-------------------------------------------------------------------------------- */
			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);

				--_base_iterator;

				return (tmp);
			}

			/* --------------------------------------------------------------------------------
			- Advance iterator -
				Advances the reverse_iterator by n element positions.
				Internally, the function decreases by n the base iterator kept by the object (as if applying operator-= to it).
				Note that this function requires the base iterator to be a random-access iterator.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator+=/
			-------------------------------------------------------------------------------- */
			reverse_iterator&	operator+=(difference_type n)
			{
				_base_iterator -= n;

				return (*this);
			}

			/* --------------------------------------------------------------------------------
			- Subtraction operator -
				Returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to.
				Internally, the function applies the binary operator+ on the base iterator and returns a reverse iterator constructed with the resulting iterator value.
				Note that this function requires the base iterator to be a random-access iterator.
				This operator is also overloaded as a non-member function to return the difference of subtracting iterators: see operator-).

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator-/
			-------------------------------------------------------------------------------- */
			reverse_iterator	operator-(difference_type n) const
				{return (reverse_iterator(_base_iterator + n));}

			/* --------------------------------------------------------------------------------
			- Pre-decrement iterator position -
				Decreases the reverse_iterator by one position.
				Internally, increments the base iterator kept by the object (as if applying operator++ to it).
				Returns *this.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator--/
			-------------------------------------------------------------------------------- */
			reverse_iterator&	operator--()
			{
				++_base_iterator;

				return (*this);
			}

			/* --------------------------------------------------------------------------------
			- Post-decrement iterator position -
				Decreases the reverse_iterator by one position.
				Internally, increments the base iterator kept by the object (as if applying operator++ to it).
				Returns the value *this had before the call.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator--/
			-------------------------------------------------------------------------------- */
			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);

				++_base_iterator;

				return (tmp);
			}

			/* --------------------------------------------------------------------------------
			- Retrocede iterator -
				Descreases the reverse_iterator by n element positions.
				Internally, the function increases by n the base iterator kept by the object (as if applying operator+= to it).
				Note that this function requires the base iterator to be a random-access iterator.

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator-=/
			-------------------------------------------------------------------------------- */
			reverse_iterator&	operator-=(difference_type n)
			{
				_base_iterator += n;

				return (*this);
			}

			/* --------------------------------------------------------------------------------
			- Dereference iterator -
				Returns a pointer to the element pointed to by the iterator (in order to access one of its members).

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/
			-------------------------------------------------------------------------------- */
			pointer				operator->() const
				{return (&operator*());}

			/* --------------------------------------------------------------------------------
			- Dereference iterator with offset -
				Accesses the element located n positions away from the element currently pointed to by the iterator.
				If such an element does not exist, it causes undefined behavior.
				Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator[]/
			-------------------------------------------------------------------------------- */
			reference			operator[](difference_type n) const
				{return (*(_base_iterator - n - 1));}


			/* ----- MEMBER FUNCTION ----- */

			/* --------------------------------------------------------------------------------
			- Return base iterator -
				Returns a copy of the base iterator.
				The base iterator is an iterator of the same type as the one used to construct the reverse_iterator, but pointing to the element next to the one the reverse_iterator is currently pointing to (a reverse_iterator has always an offset of -1 with respect to its base iterator).

			Source: https://cplusplus.com/reference/iterator/reverse_iterator/base/
			-------------------------------------------------------------------------------- */
			iterator_type		base() const
				{return (_base_iterator);}
	};


	/* ----- NON-MEMBER FUNCTION OVERLOADS ----- */

	/* --------------------------------------------------------------------------------
	- "Equal to" operator -
		Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	bool													operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() == rhs.base());}

	/* --------------------------------------------------------------------------------
	- "Not equal to" operator -
		Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	bool													operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() != rhs.base());}

	/* --------------------------------------------------------------------------------
	- "Less than" operator -
		Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	bool													operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() > rhs.base());}

	/* --------------------------------------------------------------------------------
	- "Less than or equal to" operator -
		Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	bool													operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() >= rhs.base());}

	/* --------------------------------------------------------------------------------
	- "Greater than" operator -
		Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	bool													operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() < rhs.base());}

	/* --------------------------------------------------------------------------------
	- "Greater than or equal to" operator -
		Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	bool													operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() <= rhs.base());}

	/* --------------------------------------------------------------------------------
	- Addition operator -
		Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it.
		The function returns the same as: rev_it+n (see reverse_iterator::operator+).
		This operator is also overloaded as a member function to return a reverse iterator offset by -n element positions (see reverse_iterator::operator-).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator_plus-free/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	reverse_iterator<Iterator>								operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{return (rev_it + n);}

	/* --------------------------------------------------------------------------------
	- Subtraction operator -
		Returns the distance between lhs and rhs.
		The function returns the same as subtracting lhs's base iterator from rhs's base iterator.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator_minus-free/
	-------------------------------------------------------------------------------- */
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (rhs.base() - lhs.base());}
}

#endif