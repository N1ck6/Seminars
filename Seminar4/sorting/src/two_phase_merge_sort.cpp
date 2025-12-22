#include "two_phase_merge_sort.h"

template <typename T>
void two_phase_merge_sort(vector<T>& arr) {
    if (arr.size() <= 1) return;

    const string files[] = { "temp_input.bin", "temp_B.bin", "temp_C.bin" };
    const auto cleanup = [&]() {
        for (const auto& f : files) remove(f.c_str());
    };

    ofstream out(files[0], ios::binary);
    if (!out) throw runtime_error("File write error");
    for (const T& item : arr) out.write(reinterpret_cast<const char*>(&item), sizeof(T));
    out.close();

    int runSize = 1;
    while (runSize < arr.size()) {
        {
            ifstream in(files[0], ios::binary);
            ofstream outB(files[1], ios::binary);
            ofstream outC(files[2], ios::binary);
            if (!in || !outB || !outC) throw runtime_error("Distribution error");

            bool toB = true;
            for (int i = 0; in; i++) {
                T item;
                if (!in.read(reinterpret_cast<char*>(&item), sizeof(T))) break;
                (toB ? outB : outC).write(reinterpret_cast<const char*>(&item), sizeof(T));
                if ((i + 1) % runSize == 0) toB = !toB;
            }
        }

        {
            ifstream inB(files[1], ios::binary);
            ifstream inC(files[2], ios::binary);
            ofstream out(files[0], ios::binary);
            if (!inB || !inC || !out) throw runtime_error("Merge error");

            auto read = [](ifstream& f, T& item) { return f.read(reinterpret_cast<char*>(&item), sizeof(T)); };

            T itemB, itemC;
            bool validB = static_cast<bool>(read(inB, itemB);
            bool validC = static_cast<bool>(read(inC, itemC));

            while (validB || validC) {
                int countB = 0, countC = 0;

                while ((countB < runSize && validB) || (countC < runSize && validC)) {
                    if (validB && (!validC || (countB < runSize && itemB <= itemC))) {
                        out.write(reinterpret_cast<const char*>(&itemB), sizeof(T));
                        validB = static_cast<bool>(read(inB, itemB));
                        countB++;
                    } else {
                        out.write(reinterpret_cast<const char*>(&itemC), sizeof(T));
                        validC = static_cast<bool>(read(inC, itemC));
                        countC++;
                    }
                }
            }
        }
        runSize *= 2;
    }

    ifstream in(files[0], ios::binary);
    if (!in) throw runtime_error("Result error");
    arr.clear();
    T item;
    while (in.read(reinterpret_cast<char*>(&item), sizeof(T))) arr.push_back(item);

    cleanup();
}

template void two_phase_merge_sort<int>(vector<int>& arr);
template void two_phase_merge_sort<double>(vector<double>& arr);