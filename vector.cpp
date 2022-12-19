/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:17:48 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/19 10:33:08 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if 0
# include <vector>
  namespace ft = std;
#else
# include "Containers/vector.hpp"
#endif

#include <iostream>

#define NBR 20000

int main()
{
	{
		std::cout << "----- INT VECTORS -----" << std::endl << std::endl;
		ft::vector<int>					vct1;

		for (int i = 0; i < NBR; i++)
			vct1.push_back(i);

		ft::vector<int>					vct2(vct1);

		vct1.clear();
		vct1.resize(0);

		std::cout << "--- Capacity functions ---" << std::endl;
		std::cout << "vct1.size		\u001b[16G= " << vct1.size() << std::endl;
		std::cout << "vct1.max_size	\u001b[16G= " << vct1.max_size() << std::endl;
		std::cout << "vct1.capacity	\u001b[16G= " << vct1.capacity() << std::endl;
		std::cout << "vct1.empty	\u001b[16G= " << vct1.empty() << std::endl << std::endl;

		std::cout << "vct2.size		\u001b[16G= " << vct2.size() << std::endl;
		std::cout << "vct2.max_size	\u001b[16G= " << vct2.max_size() << std::endl;
		std::cout << "vct2.capacity	\u001b[16G= " << vct2.capacity() << std::endl;
		std::cout << "vct2.empty	\u001b[16G= " << vct2.empty() << std::endl << std::endl;

		std::cout << "--- Modifier functions ---" << std::endl;

		vct1.push_back(42);
		vct1.push_back(19);
		vct1.push_back(1337);

		std::cout << "vct1.at(0)	\u001b[16G= " << vct1.at(0) << std::endl;
		std::cout << "vct1.at(1)	\u001b[16G= " << vct1.at(1) << std::endl << std::endl;

		ft::vector<int>::iterator	it = vct1.begin();
		ft::vector<int>::iterator	ite = vct1.end();

		vct1.erase(it);

		std::cout << "vct1.at(0)	\u001b[16G= " << vct1.at(0) << std::endl;
		std::cout << "vct1.at(1)	\u001b[16G= " << vct1.at(1) << std::endl << std::endl;

		vct1.assign(5, 100);

		vct1.resize(10);

		for (size_t i = 0; i < vct1.size(); i++)
			std::cout << "vct1.at(" << i << ")	\u001b[16G= " << vct1.at(i) << std::endl;

		it = vct1.begin() + 1;
		ft::vector<int>::iterator	it2 = it + 7;
		ite = vct1.end();

		vct1.insert(it, 3, 555);

		std::cout << std::endl;

		for (size_t i = 0; i < vct1.size(); i++)
			std::cout << "vct1.at(" << i << ")	\u001b[16G= " << vct1.at(i) << std::endl;

		std::cout << std::endl;
	}

	{
		std::cout << "----- STRING VECTORS -----" << std::endl << std::endl;
		ft::vector<std::string>					vct1;

		for (int i = 0; i < NBR; i++)
			vct1.push_back("index");

		ft::vector<std::string>					vct2(vct1);

		vct1.clear();
		vct1.resize(0);

		std::cout << "--- Capacity functions ---" << std::endl;
		std::cout << "vct1.size		\u001b[16G= " << vct1.size() << std::endl;
		std::cout << "vct1.max_size	\u001b[16G= " << vct1.max_size() << std::endl;
		std::cout << "vct1.capacity	\u001b[16G= " << vct1.capacity() << std::endl;
		std::cout << "vct1.empty	\u001b[16G= " << vct1.empty() << std::endl << std::endl;

		std::cout << "vct2.size		\u001b[16G= " << vct2.size() << std::endl;
		std::cout << "vct2.max_size	\u001b[16G= " << vct2.max_size() << std::endl;
		std::cout << "vct2.capacity	\u001b[16G= " << vct2.capacity() << std::endl;
		std::cout << "vct2.empty	\u001b[16G= " << vct2.empty() << std::endl << std::endl;

		std::cout << "--- Modifier functions ---" << std::endl;

		vct1.push_back("Forty-two");
		vct1.push_back("Nineteen");
		vct1.push_back("One thousand three hundred thirty-seven");

		std::cout << "vct1.at(0)	\u001b[16G= " << vct1.at(0) << std::endl;
		std::cout << "vct1.at(1)	\u001b[16G= " << vct1.at(1) << std::endl << std::endl;

		ft::vector<std::string>::iterator	it = vct1.begin();
		ft::vector<std::string>::iterator	ite = vct1.end();

		vct1.erase(it);

		std::cout << "vct1.at(0)	\u001b[16G= " << vct1.at(0) << std::endl;
		std::cout << "vct1.at(1)	\u001b[16G= " << vct1.at(1) << std::endl << std::endl;

		vct1.assign(5, "One hundred");

		vct1.resize(10);

		for (size_t i = 0; i < vct1.size(); i++)
			std::cout << "vct1.at(" << i << ")	\u001b[16G= " << vct1.at(i) << std::endl;

		it = vct1.begin() + 1;
		ft::vector<std::string>::iterator	it2 = it + 7;
		ite = vct1.end();

		vct1.insert(it, 3, "Five hundreds fifty-five");

		std::cout << std::endl;

		for (size_t i = 0; i < vct1.size(); i++)
			std::cout << "vct1.at(" << i << ")	\u001b[16G= " << vct1.at(i) << std::endl;

		std::cout << std::endl;
	}

	return (0);
}