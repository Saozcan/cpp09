#include "PmergeMe.h"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(char **av){
	int i = -1, j;
	while (av[++i]){
		j = -1;
		while (av[i][++j]) {
			checkIsNum(av[i][j]);
		}
	}
}

std::vector<int> PmergeMe::mergeInsertSortVector(std::vector<int>& arr) {
    static int threshold = 4; 

    if (arr.size() <= threshold) {
        for (std::size_t i = 1; i < arr.size(); ++i) {
            int temp = arr[i];
            std::size_t j = i;
            while (j > 0 && arr[j - 1] > temp) {
                arr[j] = arr[j - 1];
                --j;
            }
            arr[j] = temp;
        }
        return arr;
    } else {
        std::size_t mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        left = mergeInsertSortVector(left);
        right = mergeInsertSortVector(right);

        return mergeVector(left, right);
    }
}

std::vector<int> PmergeMe::mergeVector(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    std::vector<int>::const_iterator itLeft = left.begin();
    std::vector<int>::const_iterator itRight = right.begin();

    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft < *itRight) {
            result.push_back(*itLeft);
            ++itLeft;
        } else {
            result.push_back(*itRight);
            ++itRight;
        }
    }

    result.insert(result.end(), itLeft, left.end());
    result.insert(result.end(), itRight, right.end());

    return result;
}

std::list<int> PmergeMe::mergeInsertSortList(std::list<int>& lst) {
        static int threshold = 4; 

        if (lst.size() <= threshold) {
            for (std::list<int>::iterator it = std::next(lst.begin()); it != lst.end(); ++it) {
                int temp = *it;
                std::list<int>::iterator j = it;
                while (j != lst.begin() && *(std::prev(j)) > temp) {
                    *j = *(std::prev(j));
                    --j;
                }
                *j = temp;
            }
            return lst;
        } else {
            std::size_t mid = lst.size() / 2;
            std::list<int> left(lst.begin(), std::next(lst.begin(), mid));
            std::list<int> right(std::next(lst.begin(), mid), lst.end());

            left = mergeInsertSortList(left);
            right = mergeInsertSortList(right);

            return mergeList(left, right);
        }
    }

std::list<int> PmergeMe::mergeList(const std::list<int>& left, const std::list<int>& right) {
        std::list<int> result;
        std::list<int>::const_iterator itLeft = left.begin();
        std::list<int>::const_iterator itRight = right.begin();

        while (itLeft != left.end() && itRight != right.end()) {
            if (*itLeft < *itRight) {
                result.push_back(*itLeft);
                ++itLeft;
            } else {
                result.push_back(*itRight);
                ++itRight;
            }
        }

        result.insert(result.end(), itLeft, left.end());
        result.insert(result.end(), itRight, right.end());

        return result;
    }

void PmergeMe::checkIsNum(char c) {
	const std::string checkArr = "0123456789";
        if (checkArr.find(c) == std::string::npos)
            throw std::invalid_argument("Error");
}