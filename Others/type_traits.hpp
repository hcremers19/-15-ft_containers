/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:55:54 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/15 13:26:43 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	/* --------------------------------------------------------------------------------
	- Is integral -
		Trait class that identifies whether T is an integral type.
		It inherits from integral_constant as being either true_type or false_type, depending on whether T is an integral type.
		All fundamental integral types, along with all their aliases (like those in cstdint), are considered integral types by this class, including their const and volatile qualified variants.
		Enums are not considered integral types in C++.

	Source: https://cplusplus.com/reference/type_traits/is_integral/
	-------------------------------------------------------------------------------- */
	template<class T>
	struct is_integral
		{static const bool	value = false;};

	template<>
	struct is_integral <bool>
		{static const bool	value = true;};

	template<>
	struct is_integral <char>
		{static const bool	value = true;};

	template<>
	struct is_integral <char16_t>
		{static const bool	value = true;};

	template<>
	struct is_integral <char32_t>
		{static const bool	value = true;};

	template<>
	struct is_integral <wchar_t>
		{static const bool	value = true;};

	template<>
	struct is_integral <signed char>
		{static const bool	value = true;};

	template<>
	struct is_integral <short int>
		{static const bool	value = true;};

	template<>
	struct is_integral <int>
		{static const bool	value = true;};

	template<>
	struct is_integral <long int>
		{static const bool	value = true;};

	template<>
	struct is_integral <long long int>
		{static const bool	value = true;};

	template<>
	struct is_integral <unsigned char>
		{static const bool	value = true;};

	template<>
	struct is_integral <unsigned short int>
		{static const bool	value = true;};

	template<>
	struct is_integral <unsigned long int>
		{static const bool	value = true;};

	template<>
	struct is_integral <unsigned int>
		{static const bool	value = true;};

	template<>
	struct is_integral <unsigned long long int>
		{static const bool	value = true;};

	/* --------------------------------------------------------------------------------
	- Enable type if condition is met -
	The type T is enabled as member type enable_if::type if Cond is true.
	Otherwise, enable_if::type is not defined.
	This is useful to hide signatures on compile time when a particular condition is not met, since in this case, the member enable_if::type will not be defined and attempting to compile using it should fail.

	Source: https://legacy.cplusplus.com/reference/type_traits/enable_if/
	-------------------------------------------------------------------------------- */
	template<bool, class T = void>
	struct enable_if
	{};

	template<class T>
	struct enable_if<true, T>
		{typedef T type;};
}

#endif