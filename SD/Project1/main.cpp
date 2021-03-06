#include <bits/stdc++.h>

#include "STLSort.hpp"
#include "QuickSort.hpp"
#include "CountSort.hpp"
#include "BubbleSort.hpp"
#include "HeapSort.hpp"
#include "RadixSort.hpp"
#include "MergeSort.hpp"
#include "Utils.hpp"

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int tests, n, valmax, negatives;
vector <int> arr;

int main(){
    in >> tests;
    for (int k=1; k<=tests; k++){
        cout << "Incepe testul " << k << '\n';
        in >> n >> valmax >> negatives;
        Utils::generateTest(arr, n, valmax, negatives);
        
        out << "Testul " << k << " :\n";
        out << n << " numere mai mici sau egale in modul decat " << valmax << '\n';
        if (negatives) out << "Sunt si numere negative\n\n";
        else out << "Nu sunt numere negative\n\n";

        if (valmax > 1e8){
            out << "\tNumere prea mari pentru CountSort\n";
        }
        else{
            out << "\n\tCountSort:\n";
            Utils::testTheSort(CountSort::Sort, arr, out);
        }
        

        if (n <= 1e4){
            out << "\n\tBubbleSort:\n";
            Utils::testTheSort(BubbleSort::Sort, arr, out);
        }
        else out << "\tPrea multe numere pentru BubbleSort\n";

        out << "\n\tQuickSort cu pivot ales random:\n";
        Utils::testTheSort(QuickSort::Sort, arr, out);

        out << "\n\tQuickSort cu pivot ales cu mediana din 3:\n";
        Utils::testTheSort(QuickSort::Sort3, arr, out);

        out << "\n\tHeapSort:\n";
        Utils::testTheSort(HeapSort::Sort, arr, out);

        if (negatives){
            out << "\n\tNumerele negative ne impiedica sa folosim RadixSort\n";
        }
        else{
            out << "\n\tRadixSort in baza 16:\n";
            Utils::testTheSort(RadixSort::Sort16, arr, out);

            out << "\n\tRadixSort in baza 256:\n";
            Utils::testTheSort(RadixSort::Sort256, arr, out);
        }        

        out << "\n\tMergeSort:\n";
        Utils::testTheSort(MergeSort::Sort, arr, out);

        out << "\n\tSTLSort:\n";
        Utils::testTheSort(STLSort::Sort, arr, out);

        out << "\n\n";
    }
    return 0;
}