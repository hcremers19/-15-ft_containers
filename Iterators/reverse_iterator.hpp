/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:17:43 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/15 18:52:00 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERS_ITERATOR_HPP
# define REVERS_ITERATOR_HPP

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

			reverse_iterator();
			explicit reverse_iterator(iterator_type it);
			template<class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it);
			~reverse_iterator();

								operator reverse_iterator<const Iterator>() const;	// ???

			reference			operator*() const;
			reverse_iterator	operator+(difference_type n) const;
			reverse_iterator&	operator++();
			reverse_iterator	operator++(int);
			reverse_iterator&	operator+=(difference_type n);
			reverse_iterator	operator-(difference_type n) const;
			reverse_iterator&	operator--();
			reverse_iterator	operator--(int);
			reverse_iterator&	operator-=(difference_type n);
			pointer				operator->() const;
			reference			operator[](difference_type val) const;

			iterator_type		base() const;

		private:
			iterator_type		_base_iterator;
	};


	/* ----- CONSTRUCTORS AND DESTRUCTOR ----- */

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator()
		{return ;}
	/* ------------------------------------------------------------------------
	Default constructor
		Constructs a reverse iterator that points to no object.
		The internal base iterator is value-initialized.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
	------------------------------------------------------------------------ */

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(iterator_type it) : _base_iterator(it)
		{return ;}
	/* ------------------------------------------------------------------------
	Initalization constructor
		Constructs a reverse iterator from some original iterator it. The be-
		havior of the constructed object replicates the original, except that
		it iterates through its pointed elements in the reverse order.

	it
		An iterator, whose sense of iteration is inverted in the constructed
		object.
		Member type iterator_type is the underlying bidirectional iterator type
		(the class template parameter: Iterator).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
	------------------------------------------------------------------------ */

	template <class Iterator>
	template <class Iter>
	reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base_iterator(rev_it.base())
		{return ;}
	/* ------------------------------------------------------------------------
	Copy / type-cast constructor
		Constructs a reverse iterator from some other reverse iterator. The
		constructed object keeps the same sense of iteration as rev_it.

	rev_it
		An iterator of a reverse_iterator type, whose sense of iteration is
		preserved.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
	------------------------------------------------------------------------ */

	template <class Iterator>
	reverse_iterator<Iterator>::~reverse_iterator(void)
		{return ;}
	/* ------------------------------------------------------------------------
	Destructor
	------------------------------------------------------------------------ */


	/* ----- OPERATOR OVERLOADS ----- */

	template<class Iterator>
	reverse_iterator<Iterator>::operator					reverse_iterator<const Iterator>() const
		{return (_base_iterator);}
	/* ------------------------------------------------------------------------
	???
	------------------------------------------------------------------------ */

	template<class Iterator>
	typename reverse_iterator<Iterator>::reference			reverse_iterator<Iterator>::operator*() const
	{
		reverse_iterator<Iterator>::iterator_type tmp(_base_iterator);
		return (*(--tmp));
	}
	/* ------------------------------------------------------------------------
	Dereference iterator
		Returns a reference to the element pointed to by the iterator.
		Internally, the function decreases a copy of its base iterator and re-
		turns the result of dereferencing it.
		The iterator shall point to some object in order to be dereferenceable.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator*
	------------------------------------------------------------------------ */

	template<class Iterator>
	reverse_iterator<Iterator>								reverse_iterator<Iterator>::operator+(reverse_iterator<Iterator>::difference_type n) const
		{return (reverse_iterator<Iterator>(_base_iterator - n));}
	/* ------------------------------------------------------------------------
	Addition operator
		Returns a reverse iterator pointing to the element located n positions
		away from the element the iterator currently points to.
		Internally, the function applies the binary operator- on the base iter-
		ator and returns a reverse iterator constructed with the resulting it-
		erator value.
		Note that this function requires the base iterator to be a random-
		access iterator.
		This operator is also overloaded as a non-member function, with the
		left-hand and right-hand types inverted, but this the same behavior
		(see operator+).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator+/
	------------------------------------------------------------------------ */

	template<class Iterator>
	reverse_iterator<Iterator>&								reverse_iterator<Iterator>::operator++()
	{
		--_base_iterator;
		return (*this);
	}

	template<class Iterator>
	reverse_iterator<Iterator>								reverse_iterator<Iterator>::operator++(int)
	{
		reverse_iterator<Iterator>	tmp(*this);
		--_base_iterator;
		return (tmp);
	}
	/* ------------------------------------------------------------------------
	Increment iterator position
		Advances the reverse_iterator by one position.
		Internally, the pre-increment version decrements the base iterator kept
		by the object (as if applying operator-- to it).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator++/
	------------------------------------------------------------------------ */

	template<class Iterator>
	reverse_iterator<Iterator>&								reverse_iterator<Iterator>::operator+=(reverse_iterator<Iterator>::difference_type n)
	{
		_base_iterator -= n;
		return (*this);
	}
	/* ------------------------------------------------------------------------
	Advance iterator
		Advances the reverse_iterator by n element positions.
		Internally, the function decreases by n the base iterator kept by the
		object (as if applying operator-= to it).
		Note that this function requires the base iterator to be a random-
		access iterator.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator+=/
	------------------------------------------------------------------------ */

	template <class Iterator>
	reverse_iterator<Iterator>								reverse_iterator<Iterator>::operator-(reverse_iterator<Iterator>::difference_type n) const
		{return (reverse_iterator<Iterator>(_base_iterator + n));}
	/* ------------------------------------------------------------------------
	Subtraction operator
		Returns a reverse iterator pointing to the element located n positions
		before the element the iterator currently points to.
		Internally, the function applies the binary operator+ on the base iter-
		ator and returns a reverse iterator constructed with the resulting it-
		erator value.
		Note that this function requires the base iterator to be a random-
		access iterator.
		This operator is also overloaded as a non-member function to return the
		difference of subtracting iterators: see operator-).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator-/
	------------------------------------------------------------------------ */

	template <class Iterator>
	reverse_iterator<Iterator>&								reverse_iterator<Iterator>::operator--()
	{
		++_base_iterator;
		return (*this);
	}

	template <class Iterator>
	reverse_iterator<Iterator>								reverse_iterator<Iterator>::operator--(int)
	{
		reverse_iterator<Iterator>	tmp(*this);
		++_base_iterator;
		return (tmp);
	}
	/* ------------------------------------------------------------------------
	Decrease iterator position
		Decreases the reverse_iterator by one position.
		Internally, the pre-decrement version increments the base iterator kept
		by the object (as if applying operator++ to it).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator--/
	------------------------------------------------------------------------ */

	template <class Iterator>
	reverse_iterator<Iterator>&								reverse_iterator<Iterator>::operator-=(reverse_iterator<Iterator>::difference_type n)
	{
		_base_iterator += n;
		return (*this);
	}
	/* ------------------------------------------------------------------------
	Retrocede iterator
		Descreases the reverse_iterator by n element positions.
		Internally, the function increases by n the base iterator kept by the
		object (as if applying operator+= to it).
		Note that this function requires the base iterator to be a random-
		access iterator.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator-=/
	------------------------------------------------------------------------ */

	template <class Iterator>
	typename reverse_iterator<Iterator>::pointer			reverse_iterator<Iterator>::operator->() const
		{return (&operator*());}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::reference			reverse_iterator<Iterator>::operator[](reverse_iterator<Iterator>::difference_type n) const
	{
		return (*(_base_iterator - n - 1));
	}


	/* ----- MEMBER FUNCTION ----- */

	template<class Iterator>
	typename reverse_iterator<Iterator>::iterator_type		reverse_iterator<Iterator>::base() const
		{return (_base_iterator);}


	/* ----- NON-MEMBER FUNCTION OVERLOADS ----- */

	template <class Iterator>
	bool													operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() == rhs.base());}
	
	template <class Iterator>
	bool													operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() != rhs.base());}
	
	template <class Iterator>
	bool													operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() > rhs.base());}
	
	template <class Iterator>
	bool													operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() >= rhs.base());}
	
	template <class Iterator>
	bool													operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() < rhs.base());}
	
	template <class Iterator>
	bool													operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (lhs.base() <= rhs.base());}
	/* ------------------------------------------------------------------------
	Relational operators for reverse_iterator
		Performs the appropriate comparison operation between the
		reverse_iterator objects lhs and rhs.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operators/
	------------------------------------------------------------------------ */

	template <class Iterator>
	reverse_iterator<Iterator>								operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{return (rev_it + n);}
	/* ------------------------------------------------------------------------
	Addition operator
		Returns a reverse iterator pointing to the element located n positions
		away from the element pointed to by rev_it.
		The function returns the same as: rev_it+n
		(see reverse_iterator::operator+).
		This operator is also overloaded as a member function to return a re-
		verse iterator offset by -n element positions
		(see reverse_iterator::operator-).

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator_plus-free/
	------------------------------------------------------------------------ */

	template <class Iterator> 
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return (rhs.base() - lhs.base());}
	/* ------------------------------------------------------------------------
	Subtraction operator
		Returns the distance between lhs and rhs.
		The function returns the same as subtracting lhs's base iterator from
		rhs's base iterator.

	Source: https://cplusplus.com/reference/iterator/reverse_iterator/operator_minus-free/
	------------------------------------------------------------------------ */
}

#endif