/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:46:53 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/20 15:50:12 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template<typename T, class Container = vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type		c;

		public:
			/* ----- CONSTRUCTOR ----- */

			/* --------------------------------------------------------------------------------
			- Construct stack -
				Constructs a stack container adaptor object.
				A container adaptor keeps internally a container object as data. This container object is a copy of the ctnr argument passed to the constructor, if any, otherwise it is an empty container.

			Source: https://cplusplus.com/reference/stack/stack/stack/
			-------------------------------------------------------------------------------- */
			explicit stack(const container_type& ctnr = container_type()) : c(ctnr)
				{return;}


			/* ----- OPERATOR OVERLOADS ----- */

			/* --------------------------------------------------------------------------------
			- Assign content -
				Assigns new contents to the container, replacing its current contents.
			-------------------------------------------------------------------------------- */
			stack&				operator=(const stack& cpy)
			{
				c = cpy.c;
				return (*this);
			}


			/* ----- MEMBER FUNCTIONS -----*/

			/* --------------------------------------------------------------------------------
			- Test whether container is empty -
				Returns whether the stack is empty: i.e. whether its size is zero.
				This member function effectively calls member empty of the underlying container object.

			Source: https://cplusplus.com/reference/stack/stack/empty/
			-------------------------------------------------------------------------------- */
			bool				empty() const
				{return (c.empty());}

			/* --------------------------------------------------------------------------------
			- Return size -
				Returns the number of elements in the stack.
				This member function effectively calls member size of the underlying container object.

			Source: https://cplusplus.com/reference/stack/stack/size/
			-------------------------------------------------------------------------------- */
			size_type			size() const
				{return (c.size());}

			/* --------------------------------------------------------------------------------
			- Access next element -
				Returns a reference to the top element in the stack.
				Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
				This member function effectively calls member back of the underlying container object.

			Source: https://cplusplus.com/reference/stack/stack/top/
			-------------------------------------------------------------------------------- */
			value_type&			top()
				{return (c.back());}

			/* --------------------------------------------------------------------------------
			- Access next element -
				Returns a constant reference to the top element in the stack.
				Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
				This member function effectively calls member back of the underlying container object.

			Source: https://cplusplus.com/reference/stack/stack/top/
			-------------------------------------------------------------------------------- */
			const value_type&	top() const
				{return (c.back());}

			/* --------------------------------------------------------------------------------
			- Insert element -
				Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
				This member function effectively calls the member function push_back of the underlying container object.

			Source: https://cplusplus.com/reference/stack/stack/push/
			-------------------------------------------------------------------------------- */
			void				push(const value_type& val)
			{
				c.push_back(val);
				return;
			}

			/* --------------------------------------------------------------------------------
			- Remove top element -
				Removes the element on top of the stack, effectively reducing its size by one.
				The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
				This calls the removed element's destructor.
				This member function effectively calls the member function pop_back of the underlying container object.

			Source: https://cplusplus.com/reference/stack/stack/pop/
			-------------------------------------------------------------------------------- */
			void				pop()
			{
				c.pop_back();
				return;
			}

			template <class T1, class Container1>
			friend bool operator==(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);

			template <class T1, class Container1>
 			friend bool operator<(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);
	};
	/* ----- RELATIONAL OPERATORS ----- */

	/* --------------------------------------------------------------------------------
	- "Equal to" operator for vector -
		Performs the appropriate comparison operation between lhs and rhs.
		Calls the same operator on the underlying container objects.

	Source: https://cplusplus.com/reference/stack/stack/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Container>
	bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{return (lhs.c == rhs.c);}

	/* --------------------------------------------------------------------------------
	- "Not equal to" operator for vector -
		Performs the appropriate comparison operation between lhs and rhs.
		Calls the same operator on the underlying container objects.

	Source: https://cplusplus.com/reference/stack/stack/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Container>
	bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{return (!(lhs == rhs));}

	/* --------------------------------------------------------------------------------
	- "Less than" operator for vector -
		Performs the appropriate comparison operation between lhs and rhs.
		Calls the same operator on the underlying container objects.

	Source: https://cplusplus.com/reference/stack/stack/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Container>
	bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{return (lhs.c < rhs.c);}

	/* --------------------------------------------------------------------------------
	- "Less than or equal to" operator for vector -
		Performs the appropriate comparison operation between lhs and rhs.
		Calls the same operator on the underlying container objects.

	Source: https://cplusplus.com/reference/stack/stack/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Container>
	bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{return (!(rhs < lhs));}

	/* --------------------------------------------------------------------------------
	- "Greater than" operator for vector -
		Performs the appropriate comparison operation between lhs and rhs.
		Calls the same operator on the underlying container objects.

	Source: https://cplusplus.com/reference/stack/stack/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Container>
	bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{return (rhs < lhs);}

	/* --------------------------------------------------------------------------------
	- "Greater than or equal to" operator for vector -
		Performs the appropriate comparison operation between lhs and rhs.
		Calls the same operator on the underlying container objects.

	Source: https://cplusplus.com/reference/stack/stack/operators/
	-------------------------------------------------------------------------------- */
	template<class T, class Container>
	bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{return (!(lhs < rhs));}
}

#endif