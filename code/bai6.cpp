#include <iostream>
using namespace std;
/*Ham tinh mang LPS phuc vu thuat toan KMP*/
int* computeLPSArray(int* pattern, int m) {
    int* lps = new int[m]();
    int len = 0;
    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
/*Ham tim cac vi tri xuat hien cua mang A trong mang B*/
int* findOccurrences(int* a, int na, int* b, int nb, int& count) {
    int* result = new int[nb]; /*Mang luu cac vi tri xuat hien*/
    count = 0;
    if (na > nb) return result;

    int* lps = computeLPSArray(a, na); /*Tinh mang LPS de toi uu tim kiem*/
    int i = 0, j = 0;

    while (i < nb) 
    {
        if (a[j] == b[i]) 
        {
            i++;
            j++;
        }
        if (j == na) 
        {
            result[count++] = i - j;
            j = lps[j - 1];
        } 
        else if (i < nb && a[j] != b[i]) 
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    delete[] lps;
    return result;
}

int main()
{
    /*Nhap mang A va B*/
    int na, nb;
    cout << "\nNhap so phan tu cua mang A: ";
    cin >> na;
    int *a = new int[na];
    cout << "\nNhap cac phan tu cua mang A: ";
    for(int i = 0; i < na; i++) {cin >> a[i];}
    cout << "\nNhap so phan tu cua mang B: ";
    cin >> nb;
    int *b = new int[nb];
    cout << "\nNhap cac phan tu cua mang B: ";
    for(int i = 0; i < nb; i++) {cin >> b[i];}

    int count;
    int* occurrences = findOccurrences(a, na, b, nb, count); /*Tim vi tri xuat hien*/
    
    /*Xuat ket qua*/
    cout << "\nSo lan xuat hien: " << count;
    cout << "\nCac lan xuat hien: ";
    for (int i = 0; i < count; i++) {
        cout << occurrences[i] << " ";
    }
    cout << endl;
    
    /*Giai phong bo nho dong*/
    delete[] a;
    delete[] b;
    delete[] occurrences;

    return 0;
}