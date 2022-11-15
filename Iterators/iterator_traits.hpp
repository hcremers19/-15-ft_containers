/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:56:33 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/15 18:50:19 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include "iterator.hpp"

namespace ft
{
	template<class Category, class T, class Distance, class Pointer, class Reference>
	class iterator;

	struct	input_iterator_tag			{};
	struct	output_iterator_tag			{};
	struct	forward_iterator_tag		{};
	struct	bidirectional_iterator_tag	{};
	struct	random_access_iterator_tag	{}; // Only tag that will be needed here

	template<class Iterator>
	class iterator_traits
	{
		public:
			typedef typename	Iterator::difference_type	difference_type;
			typedef typename	Iterator::value_type		value_type;
			typedef typename	Iterator::pointer			pointer;
			typedef typename	Iterator::reference			reference;
			typedef typename	Iterator::iterator_category	iterator_category;
	};

	template<class T>
	class iterator_traits<T*>
	{
		public:
			typedef random_access_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*							pointer;
			typedef T&							reference;
	};

	template<class T>
	class iterator_traits<const T*>
	{
		public:
			typedef random_access_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*							pointer;
			typedef T&							reference;
	};
}

#endif

/* ----------------------------------------------------------------------------
Source: https://cplusplus.com/reference/iterator/iterator_traits/
---------------------------------------------------------------------------- */