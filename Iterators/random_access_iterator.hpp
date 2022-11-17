/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:38:52 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/17 12:38:18 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename	ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::value_type			value_type;

			random_access_iterator();
			random_access_iterator(const random_access_iterator& src);
			random_access_iterator(pointer ptr);										// ?
			~random_access_iterator();

									operator random_access_iterator<const T>() const;	// ?

			random_access_iterator&	operator=(const random_access_iterator& rhs);
			reference				operator*() const;
			pointer					operator->() const;
			random_access_iterator&	operator++();
			random_access_iterator	operator++(int);
			random_access_iterator&	operator--();
			random_access_iterator	operator--(int);
			random_access_iterator	operator+(difference_type rhs) const;
			random_access_iterator	operator-(difference_type rhs) const;
			random_access_iterator	operator+=(difference_type rhs);
			random_access_iterator	operator-=(difference_type rhs);
			reference				operator[](difference_type val) const;

			const pointer&			base() const;

		private:
			pointer				_content;
	};


	/* ----- CONSTRUCTORS AND DESTRUCTOR ----- */

	template<typename T>
	random_access_iterator<T>::random_access_iterator()
		{return ;}

	template<typename T>
	random_access_iterator<T>::random_access_iterator(const random_access_iterator& src) : _content(src._content)
		{return ;}

	template<typename T>
	random_access_iterator<T>::random_access_iterator(pointer ptr) : _content(ptr)
		{return ;}

	template<typename T>
	random_access_iterator<T>::~random_access_iterator()
		{return ;}


	/* ----- OPERATOR OVERLOADS ----- */

	template<typename T>
	random_access_iterator<T>::operator								random_access_iterator<const T>() const
		{return (_content);}

	template<typename T>
	random_access_iterator<T>&										random_access_iterator<T>::operator=(const random_access_iterator& rhs)
	{
		_content = rhs._content;
		return (*this);
	}

	template<typename T>
	typename random_access_iterator<T>::reference					random_access_iterator<T>::operator*() const
		{return (*(_content));}

	template<typename T>
	typename random_access_iterator<T>::pointer						random_access_iterator<T>::operator->() const
		{return (_content);}

	template<typename T>
	random_access_iterator<T>&										random_access_iterator<T>::operator++()
	{
		++_content;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>										random_access_iterator<T>::operator++(int)
	{
		random_access_iterator<T>	tmp(*this);
		++_content;
		return (tmp);
	}

	template<typename T>
	random_access_iterator<T>&										random_access_iterator<T>::operator--()
	{
		--_content;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>										random_access_iterator<T>::operator--(int)
	{
		random_access_iterator<T>	tmp(*this);
		--_content;
		return (tmp);
	}

	template<typename T>
	random_access_iterator<T>										random_access_iterator<T>::operator+(difference_type rhs) const
		{return (random_access_iterator<T>(_content + rhs));}

	template<typename T>
	random_access_iterator<T>										random_access_iterator<T>::operator-(difference_type rhs) const
		{return (random_access_iterator<T>(_content - rhs));}

	template<typename T>
	random_access_iterator<T>										random_access_iterator<T>::operator+=(difference_type rhs)
	{
		_content += rhs;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>										random_access_iterator<T>::operator-=(difference_type rhs)
	{
		_content -= rhs;
		return (*this);
	}

	template<typename T>
	typename random_access_iterator<T>::reference					random_access_iterator<T>::operator[](difference_type val) const
		{return (*(_content + val))};


	/* ----- MEMBER FUNCTION ----- */

	template<typename T>
	typename random_access_iterator<T>::pointer const&				random_access_iterator<T>::base() const
		{return (_content);}


	/* ----- NON-MEMBER OPERATOR OVERLOADS ----- */

	template<class iterator1, class iterator2>
	bool															operator==(const random_access_iterator<iterator1>& lhs, const random_access_iterator<iterator2>& rhs)
		{return (lhs.base() == rhs.base());}

	template<class iterator1, class iterator2>
	bool															operator!=(const random_access_iterator<iterator1>& lhs, const random_access_iterator<iterator2>& rhs)
		{return (lhs.base() != rhs.base());}

	template<class Iterator>
	random_access_iterator<Iterator>								operator+(typename random_access_iterator<Iterator>::difference_type left, random_access_iterator<Iterator> const& right)
		{return (right + left);}

	template<class Iterator1, class Iterator2>
	typename	random_access_iterator<Iterator1>::difference_type	operator-(random_access_iterator<Iterator2> const& left, random_access_iterator<Iterator1> const& right)
		{return (left.base() - right.base());}

	template<class iterator1, class iterator2>
	bool															operator<(const random_access_iterator<iterator1>& lhs, const random_access_iterator<iterator2>& rhs)
		{return (lhs.base() < rhs.base());}

	template<class iterator1, class iterator2>
	bool															operator>(const random_access_iterator<iterator1>& lhs, const random_access_iterator<iterator2>& rhs)
		{return (lhs.base() > rhs.base());}

	template<class iterator1, class iterator2>
	bool															operator<=(const random_access_iterator<iterator1>& lhs, const random_access_iterator<iterator2>& rhs)
		{return (lhs.base() <= rhs.base());}

	template<class iterator1, class iterator2>
	bool															operator>=(const random_access_iterator<iterator1>& lhs, const random_access_iterator<iterator2>& rhs)
		{return (lhs.base() >= rhs.base());}
}

#endif

/* ----------------------------------------------------------------------------
Source: https://cplusplus.com/reference/iterator/RandomAccessIterator/
---------------------------------------------------------------------------- */