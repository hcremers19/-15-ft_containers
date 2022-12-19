/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:56:33 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/19 15:17:44 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>	// ptrdiff_t

# include "iterator.hpp"

namespace ft
{
	struct	input_iterator_tag			{};
	struct	output_iterator_tag			{};
	struct	forward_iterator_tag		{};
	struct	bidirectional_iterator_tag	{};
	struct	random_access_iterator_tag	{};

	template<class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template<class T>
	class iterator_traits<T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef random_access_iterator_tag				iterator_category;
	};

	template<class T>
	class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef random_access_iterator_tag				iterator_category;
	};

	/* --------------------------------------------------------------------------------
	- Return distance between iterators -
		Calculates the number of elements between first and last.
		The function uses operator- to calculate this.

	Source: https://cplusplus.com/reference/iterator/distance/
	-------------------------------------------------------------------------------- */
	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type 		distance(InputIterator first, InputIterator last)
		{return (last - first);}
}

#endif

/* --------------------------------------------------------------------------------
Source: https://cplusplus.com/reference/iterator/iterator_traits/
-------------------------------------------------------------------------------- */