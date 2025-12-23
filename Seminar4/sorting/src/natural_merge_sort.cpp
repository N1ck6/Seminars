#include "natural_merge_sort.h"

template <typename T>
void natural_merge_sort(vector<T>& arr) {
    if (arr.size() <= 1) return;

    const string files[] = { "temp_input.bin", "temp_B.bin", "temp_C.bin" };

    ofstream out(files[0], ios::binary);
    if (!out) throw runtime_error("File write error");
    for (const T& item : arr) out.write(reinterpret_cast<const char*>(&item), sizeof(T));
    out.close();

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        {
            ifstream in(files[0], ios::binary);
            ofstream outB(files[1], ios::binary);
            ofstream outC(files[2], ios::binary);
            if (!in || !outB || !outC) throw runtime_error("Distribution error");

            bool toB = true;
            T prev, current;

            if (in.read(reinterpret_cast<char*>(&prev), sizeof(T))) {
                (toB ? outB : outC).write(reinterpret_cast<const char*>(&prev), sizeof(T));
                while (in.read(reinterpret_cast<char*>(&current), sizeof(T))) {
                    if (current < prev) {
                        toB = !toB;
                        sorted = false;
                    }
                    (toB ? outB : outC).write(reinterpret_cast<const char*>(&current), sizeof(T));
                    prev = current;
                }
            }
        }

        {
            ifstream inB(files[1], ios::binary);
            ifstream inC(files[2], ios::binary);
            ofstream out(files[0], ios::binary);
            if (!inB || !inC || !out) throw runtime_error("Merge error");

            T itemB, itemC;
            inB.read(reinterpret_cast<char*>(&itemB), sizeof(T));
            bool validB = static_cast<bool>(inB);

            inC.read(reinterpret_cast<char*>(&itemC), sizeof(T));
            bool validC = static_cast<bool>(inC);

            while (validB || validC) {
                if (validB && (!validC || itemB <= itemC)) {
                    out.write(reinterpret_cast<const char*>(&itemB), sizeof(T));
                    inB.read(reinterpret_cast<char*>(&itemB), sizeof(T));
                    validB = static_cast<bool>(inB);
                }
                else {
                    out.write(reinterpret_cast<const char*>(&itemC), sizeof(T));
                    inC.read(reinterpret_cast<char*>(&itemC), sizeof(T));
                    validC = static_cast<bool>(inC);
                }
            }
        }
    }

    ifstream in(files[0], ios::binary);
    if (!in) throw runtime_error("File error");
    arr.clear();
    T item;
    while (in.read(reinterpret_cast<char*>(&item), sizeof(T))) arr.push_back(item);

    for (const auto& f : files) {
        remove(f.c_str());
    }
}

template void natural_merge_sort<int>(vector<int>& arr);
template void natural_merge_sort<double>(vector<double>& arr);