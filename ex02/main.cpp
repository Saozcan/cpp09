#include <iostream>
#include <vector>

// Function to merge two sorted vectors into a single sorted vector
std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
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

    // Copy any remaining elements from the left and right vectors
    result.insert(result.end(), itLeft, left.end());
    result.insert(result.end(), itRight, right.end());

    return result;
}

// Merge-insertion sort function for vector
std::vector<int> mergeInsertSortVector(std::vector<int>& arr) {
    static int threshold = 2; // Threshold to decide when to use insertion sort

    if (arr.size() <= threshold) {
        // Use insertion sort for small segments
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
        // Split the vector into two halves
        std::size_t mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        // Recursively sort the two halves
        left = mergeInsertSortVector(left);
        right = mergeInsertSortVector(right);

        // Merge the sorted halves and return the result
        return merge(left, right);
    }
}

int main() {
    int numbers[10]= {5, 2, 9, 1, 5, 7, 3, 8, 4, 6};
    std::vector<int> arr(numbers, numbers + 10);
    std::vector<int> sortedArr = mergeInsertSortVector(arr);

    // Output the sorted vector
    for (int num : sortedArr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
