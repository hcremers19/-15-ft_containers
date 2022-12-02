/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:14:38 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/02 12:15:01 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	class pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;


			/* ----- CONSTRUCTORS ----- */

			/* --------------------------------------------------------------------------------
			- Default constructor -
				Constructs a pair object with its elements value-initialized

			Source: https://legacy.cplusplus.com/reference/utility/pair/pair/
			-------------------------------------------------------------------------------- */
			pair() : first(), second()
				{return;}

			/* --------------------------------------------------------------------------------
			- Copy / move constructor (and implicit conversion) -
				The object is initialized with the contents of the pr pair object.
				The corresponding member of pr is passed to the constructor of each of its members.

			Source: https://legacy.cplusplus.com/reference/utility/pair/pair/
			-------------------------------------------------------------------------------- */
			template<class U, class V>
			pair(const pair<U, V>& pr) : first(pr.first), second(pr.second)
				{return;}

			/* --------------------------------------------------------------------------------
			- Initialization constructor -
				Member first is constructed with a and member second with b.

			Source: https://legacy.cplusplus.com/reference/utility/pair/pair/
			-------------------------------------------------------------------------------- */
			pair(const first_type& a, const second_type& b) : first(a), second(b)
				{return;}


			/* ----- OPERATOR OVERLOAD ----- */

			/* --------------------------------------------------------------------------------
			- Assign contents -
				Assigns pr as the new content for the pair object.
				Member first is assigned pr.first, and member second is assigned pr.second.
				Performs copy assignments, with the elements of its argument preserving their values after the call.

			Source: https://legacy.cplusplus.com/reference/utility/pair/operator=/
			-------------------------------------------------------------------------------- */
			pair&	operator=(const pair& pr)
			{
				first = pr.first;
				second = pr.second;
				return (*this);
			}
	};
	/* ----- NON-MEMBER OPERATOR OVERLOADS ----- */

	/* --------------------------------------------------------------------------------
	- "Equal to" operator for pair -
		Performs the appropriate comparison operation between the pair objects lhs and rhs.
		Two pair objects compare equal to each other if both their first members compare equal to each other and both their second members compare also equal to each other (in both cases using operator== for the comparison).

	Source: https://legacy.cplusplus.com/reference/utility/pair/operators/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{return (lhs.first == rhs.first && lhs.second == rhs.second);}

	/* --------------------------------------------------------------------------------
	- "Not equal to" operator for pair -
		Performs the appropriate comparison operation between the pair objects lhs and rhs.
		Uses the operator == internally to compare the elements

	Source: https://legacy.cplusplus.com/reference/utility/pair/operators/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{return (!(lhs == rhs));}

	/* --------------------------------------------------------------------------------
	- "Less than" operator for pair -
		Performs the appropriate comparison operation between the pair objects lhs and rhs.
		Performs a lexicographical comparison on the sequence formed by members first and second.

	Source: https://legacy.cplusplus.com/reference/utility/pair/operators/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));}

	/* --------------------------------------------------------------------------------
	- "Less than or equal to" operator for pair -
		Performs the appropriate comparison operation between the pair objects lhs and rhs.
		Uses the operator < internally to compare the elements

	Source: https://legacy.cplusplus.com/reference/utility/pair/operators/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{return (!(rhs < lhs));}

	/* --------------------------------------------------------------------------------
	- "Greater than" operator for pair -
		Performs the appropriate comparison operation between the pair objects lhs and rhs.
		Uses the operator < internally to compare the elements

	Source: https://legacy.cplusplus.com/reference/utility/pair/operators/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{return (rhs < lhs);}

	/* --------------------------------------------------------------------------------
	- "Greater than or equal to" operator for pair -
		Performs the appropriate comparison operation between the pair objects lhs and rhs.
		Uses the operator < internally to compare the elements

	Source: https://legacy.cplusplus.com/reference/utility/pair/operators/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{return (!(lhs < rhs));}

	
	/* ----- NON-MEMBER FUNCTION ----- */

	/* --------------------------------------------------------------------------------
	- Construct pair object -
		Constructs a pair object with its first element set to x and its second element set to y.
		The template types can be implicitly deduced from the arguments passed to make_pair.
		pair objects can be constructed from other pair objects containing different types, if the respective types are implicitly convertible.

	Source: https://legacy.cplusplus.com/reference/utility/make_pair/
	-------------------------------------------------------------------------------- */
	template<class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y)
		{return (pair<T1, T2>(x, y));}
}

#endif