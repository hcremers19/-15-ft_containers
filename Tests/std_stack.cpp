/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_stack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:17:48 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/19 17:17:20 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
namespace ft = std;

#include <iostream>
#include <sys/time.h>

#define NBR 100000

void	std_stack()
{
	struct timeval	begin, end;
	gettimeofday(&begin, 0);

	{
		std::cout << "----- INT STACKS -----" << std::endl << std::endl;
		ft::stack<int>					stk1;

		for (int i = 0; i < NBR; i++)
			stk1.push(i);

		ft::stack<int>					stk2;

		stk2.push(42);
		stk2.push(19);
		stk2.push(1337);

		std::cout << "--- Capacity functions ---" << std::endl;
		std::cout << "stk1.size() 	\u001b[16G= " << stk1.size()	<< std::endl;
		std::cout << "stk1.empty()	\u001b[16G= " << stk1.empty()	<< std::endl << std::endl;

		std::cout << "stk2.size() 	\u001b[16G= " << stk2.size()	<< std::endl;
		std::cout << "stk2.empty()	\u001b[16G= " << stk2.empty()	<< std::endl << std::endl;

		while (stk2.size())
		{
			std::cout << "stk2.top()	\u001b[16G= " << stk2.top()	<< std::endl;
			stk2.pop();
		}

		std::cout << std::endl;
	}

	{
		std::cout << "----- STRING STACKS -----" << std::endl << std::endl;
		ft::stack<std::string>					stk1;

		for (int i = 0; i < NBR; i++)
			stk1.push("i");

		ft::stack<std::string>					stk2;

		stk2.push("Forty-two");
		stk2.push("Nineteen");
		stk2.push("One thousand three hundreds thirty-seven");

		std::cout << "--- Capacity functions ---" << std::endl;
		std::cout << "stk1.size()	\u001b[16G= " << stk1.size()	<< std::endl;
		std::cout << "stk1.empty()	\u001b[16G= " << stk1.empty()	<< std::endl << std::endl;

		std::cout << "stk2.size()	\u001b[16G= " << stk2.size()	<< std::endl;
		std::cout << "stk2.empty()	\u001b[16G= " << stk2.empty()	<< std::endl << std::endl;

		while (stk2.size())
		{
			std::cout << "stk2.top()	\u001b[16G= " << stk2.top()	<< std::endl;
			stk2.pop();
		}

		std::cout << std::endl;
	}

	gettimeofday(&end, 0);
	long	seconds		= end.tv_sec - begin.tv_sec;
	long	useconds	= end.tv_usec - begin.tv_usec;
	double	time		= seconds * 1e6 + useconds;

	std::cout << "Execution time: " << time << " microseconds." << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return;
}
