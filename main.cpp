#include <iostream>
#include <random>
int FindPartitionIndex(int* array, const int kLeftIndex,
                       const int kRightIndex) {
  if (kLeftIndex == kRightIndex) {
    return kLeftIndex;
  }
  std::mt19937 rnd(1234);
  int pivot = (rand() % (kRightIndex - kLeftIndex + 1)) + kLeftIndex;
  pivot = array[pivot];
  int k_left_pointer = kLeftIndex;
  int k_right_pointer = kRightIndex;
  while (k_left_pointer <= k_right_pointer) {
    while (array[k_left_pointer] < pivot) {
      ++k_left_pointer;
    }
    while (pivot < array[k_right_pointer]) {
      --k_right_pointer;
    }
    if (k_left_pointer >= k_right_pointer) {
      break;
    }
    std::swap(array[k_left_pointer++], array[k_right_pointer--]);
  }
  return k_right_pointer;
}

void QuickSort(int* array, const int kLeftIndex, const int kRightIndex) {
  if (kLeftIndex >= kRightIndex) {
    return;
  }
  int k_partition_index = FindPartitionIndex(array, kLeftIndex, kRightIndex);
  QuickSort(array, kLeftIndex, k_partition_index);
  QuickSort(array, k_partition_index + 1, kRightIndex);
}

int main() {
  int size;
  std::cin >> size;
  int* array = new int[size];
  for (int i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  QuickSort(array, 0, size - 1);
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  delete[] array;
  return 0;
}