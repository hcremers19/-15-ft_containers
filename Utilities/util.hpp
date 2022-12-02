/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:51:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/29 18:24:52 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_HPP
# define UTIL_HPP

# include "../Iterators/iterator_traits.hpp"

namespace ft
{
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type 		__distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first++ != last)
			++n;
		return (n);
	}

	template<class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		return (last - first);
	}

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type 		distance(InputIterator first, InputIterator last)
	{
		return (__distance(first, last, typename iterator_traits<InputIterator>::iterator_category()));
	}

	/* ------------------------------------------------------------------------
	Test whether the elements in two ranges are equal
		Compares the elements in the range [first1, last1] with those in the range beginning at first2, and returns true if all of the elements in both ranges match.
		The elements are compared using operator==.
	------------------------------------------------------------------------ */
	template<class InputIterator1, class InputIterator2>
	bool															equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* ------------------------------------------------------------------------
	Lexicographical less-than comparison
		Returns true if the range [first1, last1] compares lexicographically less than the range [first2, last2].
		A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries; It involves comparing sequentially the elements that have the same position in both ranges against each other until one element is not equivalent to the other. The result of comparing these first non-matching elements is the result of the lexicographical comparison.
		If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
		The elements are compared using operator<. Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)).
	------------------------------------------------------------------------ */
	template<class InputIterator1, class InputIterator2>
	bool															lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif