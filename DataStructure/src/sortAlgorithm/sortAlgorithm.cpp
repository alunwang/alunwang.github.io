#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<ranges>


template <typename T>
void insertSort(T arr[], int n)
{
    for (int i {1}; i<n; i++) {
        T next { arr[i] };
        int j { i-1 };
        while ((j>=0) && (next<arr[j])) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = next;
    }
}

template <typename T>
void quickSort(T arr[], int start, int end)
{
    if (start >= end) {
        return;
    }

    // 1. 挑选基准值：从数列中挑出一个元素，称为“基准”（pivot）
    T pivot = arr[end];
    // 2. 分割：所有比基准小的元素摆放在基准前面，所有比基准大的元素摆在基准后面（与基准值相等的数可以到任何一边）
    int left {start}, right {end-1};
    while (left < right) {
        while ((arr[left] < pivot) && (left < right)) {
            left++;
        }
        while ((arr[right] >= pivot) && (left < right)) {
            right--;
        }
        std::swap(arr[left], arr[right]);
    }
    if (arr[left] >= arr[end]) {
        std::swap(arr[left], arr[end]);
    } else {
        left++;
    }
    // 3. 递归排序子序列：递归地将小于基准的子序列和大于基准的子序列排序。
    quickSort(arr, start, left-1);
    quickSort(arr, left+1, end);
}


void print(auto comment, auto const& seq, char term=' ')
{
    for (std::cout << comment << '\n'; auto const& elem : seq) {
        std::cout << elem << term;
    }
    std::cout << '\n';
}

int main(int argc, char* argv[])
{
    int arr[] {3, 2, 6, 7, 9, 10, 1, 4, 5, 11, 8};
    print("Before sorting", arr);

    insertSort(arr, 11);
    print("Sorting using insertSort", arr);

    quickSort(arr, 0, 10);
    print("Sorint using quickSort", arr);

    std::array s {3, 2, 6, 7, 9, 10, 1, 4, 5, 11, 8};
    namespace ranges = std::ranges;
    ranges::sort(s);
    print("Sorting using the default oeprator", s);

    ranges::sort(s, ranges::greater());
    print("Sorting using a Stardard Library compare function object", s);

    struct {
        bool operator()(int a, int b) const { return a < b; }
    } customLessThan;
    ranges::sort(begin(s), end(s), customLessThan);
    print("Sorting using a custom function object", s);

    ranges::sort(s, [](int a, int b) { return a>b; });
    print("Sorting using a lambda expression", s);

    return 0;
}