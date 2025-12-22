#include "one_phase_merge_sort.h"

template <typename T>
void one_phase_merge_sort(vector<T>& arr) {
    if (arr.size() <= 1) return;

    const string files[] = { "temp_input.bin", "temp_B.bin" };
    const auto cleanup = [&]() {for (const auto& f : files) remove(f.c_str()); };

    ofstream out(files[0], ios::binary);
    if (!out) throw runtime_error("File write error");
    for (const T& item : arr) out.write(reinterpret_cast<const char*>(&item), sizeof(T));
    out.close();

    int runSize = 1;
    bool useTemp = false;
    while (runSize < arr.size()) {
        ifstream in(files[useTemp], ios::binary);
        ofstream out(files[!useTemp], ios::binary);
        if (!in || !out) throw runtime_error("File error");

        const auto read = [](ifstream& f, T& item) {return f.read(reinterpret_cast<char*>(&item), sizeof(T)); };

        T itemA, itemB;
        bool validA = read(in, itemA), validB = false;
        int countA = 1, countB = 0;

        while (validA || validB) {
            while ((countA < runSize && validA) || (countB < runSize && validB)) {
                if (validB && (!validA || (countB < runSize && itemB < itemA))) {
                    out.write(reinterpret_cast<const char*>(&itemB), sizeof(T));
                    validB = read(in, itemB);
                    countB++;
                } else {
                    out.write(reinterpret_cast<const char*>(&itemA), sizeof(T));
                    if (!read(in, itemA)) validA = false;
                    countA++;
                }
            }

            countA = countB = 0;
            validB = read(in, itemB);
        }
        runSize *= 2;
        useTemp = !useTemp;
    }
    ifstream in(useTemp ? files[1] : files[0], ios::binary);
    if (!in) throw runtime_error("File error");
    arr.clear();
    T item;
    while (in.read(reinterpret_cast<char*>(&item), sizeof(T))) arr.push_back(item);

    cleanup();
}

template void one_phase_merge_sort<int>(vector<int>& arr);
template void one_phase_merge_sort<double>(vector<double>& arr);