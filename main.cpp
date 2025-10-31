#include <vector>
#include <iostream>

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

// 1.(Insertion Sort)
Stats insertionSort(std::vector<int>& array) {
    Stats stats;

    // Начинаем со второго элемента (индекс 1)
    for (size_t i = 1; i < array.size(); ++i) {
        int current = array[i];  // Текущий элемент для вставки
        stats.copy_count++;

        size_t j = i;

        
        while (j > 0) {
            stats.comparison_count++;
            
            if (array[j - 1] <= current) {
                break;
            }

            
            array[j] = array[j - 1];
            stats.copy_count++;
            j--;
        }

        
        array[j] = current;
        stats.copy_count++;
    }

    return stats;
}

// 2. (Comb Sort)
Stats combSort(std::vector<int>& array) {
    Stats stats;
    size_t gap = array.size();  
    bool swapped = true;        

    
    while (gap > 1 || swapped) {
        
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;

        swapped = false;

        
        for (size_t i = 0; i + gap < array.size(); ++i) {
            stats.comparison_count++;

           
            if (array[i] > array[i + gap]) {
                std::swap(array[i], array[i + gap]);
                stats.copy_count += 3;
                swapped = true;
            }
        }
    }

    return stats;
}

// 3. (Natural Two-Way Merge Sort)
Stats naturalMergeSort(std::vector<int>& array) {
    Stats stats;

    if (array.size() <= 1) {
        return stats;
    }

    std::vector<int> temp(array.size());

    
    while (true) {
        
        std::vector<std::pair<size_t, size_t>> runs;  

        size_t i = 0;
        while (i < array.size()) {
            size_t start = i;

            
            while (i + 1 < array.size()) {
                stats.comparison_count++;
                if (array[i] > array[i + 1]) break;
                i++;
            }
            size_t end_asc = i;
            i++;

            
            size_t start_desc = i;
            while (i + 1 < array.size()) {
                stats.comparison_count++;
                if (array[i] < array[i + 1]) break;
                i++;
            }
            size_t end_desc = i;
            i++;

            
            runs.emplace_back(start, end_asc);
            if (start_desc < array.size()) {
                runs.emplace_back(start_desc, end_desc);
            }
        }

        
        if (runs.size() <= 1) {
            break;
        }

        
        for (size_t j = 0; j + 1 < runs.size(); j += 2) {
            size_t left_start = runs[j].first;
            size_t left_end = runs[j].second;
            size_t right_start = runs[j + 1].first;
            size_t right_end = runs[j + 1].second;

            size_t left_idx = left_start;
            size_t right_idx = right_start;
            size_t temp_idx = left_start;

            
            while (left_idx <= left_end && right_idx <= right_end) {
                stats.comparison_count++;
                if (array[left_idx] <= array[right_idx]) {
                    temp[temp_idx] = array[left_idx];
                    stats.copy_count++;
                    left_idx++;
                }
                else {
                    temp[temp_idx] = array[right_idx];
                    stats.copy_count++;
                    right_idx++;
                }
                temp_idx++;
            }

            
            while (left_idx <= left_end) {
                temp[temp_idx] = array[left_idx];
                stats.copy_count++;
                left_idx++;
                temp_idx++;
            }
            while (right_idx <= right_end) {
                temp[temp_idx] = array[right_idx];
                stats.copy_count++;
                right_idx++;
                temp_idx++;
            }
        }

        
        for (size_t k = 0; k < array.size(); ++k) {
            array[k] = temp[k];
            stats.copy_count++;
        }
    }

    return stats;
}

int main() {
    std::vector<int> v = { 1,2,4,3,9,8,7,6,5,100 };
    Stats s1 = insertionSort(v);

    
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Comparisons: " << s1.comparison_count << std::endl;
    std::cout << "Copies: " << s1.copy_count << std::endl;

    return 0;
}