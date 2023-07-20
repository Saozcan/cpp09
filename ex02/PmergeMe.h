#ifndef PMERGEME_H
#define PMERGEME_H

#include <vector>
#include <iostream>
#include <list>

class PmergeMe {
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(char **av);

		std::vector<int> mergeInsertSortVector(std::vector<int>& arr);
		std::vector<int> mergeVector(const std::vector<int>& left, const std::vector<int>& right);
		std::list<int> mergeInsertSortList(std::list<int>& lst);
		std::list<int> mergeList(const std::list<int>& left, const std::list<int>& right);

		void checkIsNum(char c);

	private:
		std::list<int> listNums;
		std::vector<int> vectorNums;
};

#endif