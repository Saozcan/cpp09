#include "PmergeMe.h"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(char **av){
	int i = 0, j;
	while (av[++i]){
		j = -1;
		while (av[i][++j]) {
			checkIsNum(av[i][j]);
		}
	}
	i = 0;
	while (av[++i]) {
		listNums.push_back(atoi(av[i]));
		vectorNums.push_back(atoi(av[i]));
	}
	isSort();
	start();
}

void PmergeMe::start() {
	srand(time(NULL));
	std::cout << "Before: ";
    display(vectorNums);
    clock_t start1 = clock();
	endVector = mergeInsertSortVector(vectorNums);
	clock_t end1 = clock();
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;

	clock_t start2 = clock();
    endList = mergeInsertSortList(listNums);
    clock_t end2 = clock();
    double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;

	std::cout << "After: ";
	display(endVector);
	std::cout << "Time to process a range of " << vectorNums.size() << " elements with std::vector container: " << time1 << " us" << std::endl;
	std::cout << "Time to process a range of " << listNums.size() << " elements with std::list container: " << time2 << " us" << std::endl;
}

template <typename T>
void PmergeMe::display(const T& container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
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

void PmergeMe::isSort() {
	std::list<int>::iterator it = listNums.begin();
	for (; it != std::prev(listNums.end()); it++) {
		if (*it > *(std::next(it)))
			return ;
	}
	throw std::runtime_error("Already sorted...");
}