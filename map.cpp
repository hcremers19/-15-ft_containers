/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:17:48 by hcremers          #+#    #+#             */
/*   Updated: 2022/12/19 11:42:54 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if 0
# include <map>
  namespace ft = std;
#else
# include "Containers/map.hpp"
#endif

#include <iostream>

#define NBR 20000

int main()
{
	{
		std::cout << "----- INT MAPS -----" << std::endl << std::endl;
		ft::map<int, int>					mp1;
		ft::pair<int, int>					pr[NBR];

		for (int i = 0; i < NBR; i++)
		{
			pr[i].first = i;
			pr[i].second = i;
		}

		for (int i = 0; i < NBR; i++)
			mp1.insert(pr[i]);

		ft::map<int, int>					mp2(mp1);

		mp1.clear();

		std::cout << "--- Capacity functions ---" << std::endl;
		std::cout << "mp1.size\u001b[16G= " << mp1.size() << std::endl;
		std::cout << "mp1.max_size\u001b[16G= " << mp1.max_size() << std::endl;
		std::cout << "mp1.empty\u001b[16G= " << mp1.empty() << std::endl << std::endl;

		std::cout << "mp2.size\u001b[16G= " << mp2.size() << std::endl;
		std::cout << "mp2.max_size\u001b[16G= " << mp2.max_size() << std::endl;
		std::cout << "mp2.empty\u001b[16G= " << mp2.empty() << std::endl << std::endl;

		std::cout << "--- Modifier functions ---" << std::endl;

		mp1.insert(ft::pair<int, int>(1337, 19));
		mp1.insert(ft::pair<int, int>(19, 42));
		mp1.insert(ft::pair<int, int>(42, 1337));

		mp1.insert(ft::make_pair(100, 500));
		mp1.insert(ft::make_pair(0, 1000));
		mp1.insert(ft::make_pair(-999, 0));

		ft::map<int, int>::iterator	it = mp1.begin();
		ft::map<int, int>::iterator	ite = mp1.end();
		while (it != ite)
		{
			std::cout << "mp1[" << it.base()->get_value().first << "]\u001b[12G= " << it.base()->get_value().second << std::endl;
			it++;
		}

		mp1.erase(mp1.find(19));
		mp1.erase(-999);
		mp1.insert(ft::make_pair(100, 19));

		std::cout << std::endl;

		it = mp1.begin();
		ite = mp1.end();
		while (it != ite)
		{
			std::cout << "mp1[" << it.base()->get_value().first << "]\u001b[12G= " << it.base()->get_value().second << std::endl;
			it++;
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "----- STRING MAPS -----" << std::endl << std::endl;
		ft::map<std::string, std::string>					mp1;
		ft::pair<std::string, std::string>					pr[NBR];

		for (int i = 0; i < NBR; i++)
		{
			pr[i].first = "first";
			pr[i].second = "second";
		}

		for (int i = 0; i < NBR; i++)
			mp1.insert(pr[i]);

		ft::map<std::string, std::string>					mp2(mp1);

		mp1.clear();

		std::cout << "--- Capacity functions ---" << std::endl;
		std::cout << "mp1.size\u001b[16G= " << mp1.size() << std::endl;
		std::cout << "mp1.max_size\u001b[16G= " << mp1.max_size() << std::endl;
		std::cout << "mp1.empty\u001b[16G= " << mp1.empty() << std::endl << std::endl;

		std::cout << "mp2.size\u001b[16G= " << mp2.size() << std::endl;
		std::cout << "mp2.max_size\u001b[16G= " << mp2.max_size() << std::endl;
		std::cout << "mp2.empty\u001b[16G= " << mp2.empty() << std::endl << std::endl;

		std::cout << "--- Modifier functions ---" << std::endl;

		mp1.insert(ft::pair<std::string, std::string>("Nineteen", "Forty-two"));
		mp1.insert(ft::pair<std::string, std::string>("One thousand three hundred thirty-seven", "Nineteen"));
		mp1.insert(ft::pair<std::string, std::string>("Forty-two", "One thousand three hundred thirty-seven"));

		mp1.insert(ft::make_pair("One hundred", "Five hundreds"));
		mp1.insert(ft::make_pair("Zero", "One thousand"));
		mp1.insert(ft::make_pair("Minus nine hundreds ninety-nine", "Zero"));

		ft::map<std::string, std::string>::iterator	it = mp1.begin();
		ft::map<std::string, std::string>::iterator	ite = mp1.end();
		while (it != ite)
		{
			std::cout << "mp1[" << it.base()->get_value().first << "]\u001b[48G= " << it.base()->get_value().second << std::endl;
			it++;
		}

		mp1.erase(mp1.find("Nineteen"));
		mp1.erase("Minus nine hundreds ninety-nine");
		mp1.insert(ft::make_pair("One hundred", "Nineteen"));

		std::cout << std::endl;

		it = mp1.begin();
		ite = mp1.end();
		while (it != ite)
		{
			std::cout << "mp1[" << it.base()->get_value().first << "]\u001b[48G= " << it.base()->get_value().second << std::endl;
			it++;
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}

	return (0);
}
