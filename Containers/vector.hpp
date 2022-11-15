/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:46:38 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/15 15:30:11 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "../Iterators/random_access_iterator.hpp"

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class vector
	{
	public:																								// Need to declare some public types here to use them privately just after
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
		typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef				size_t											size_type;

	private:
		pointer 		_container;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
		vector(/* args */);
		~vector();
	};
	
	vector::vector(/* args */)
	{
	}
	
	vector::~vector()
	{
	}
	
}

#endif