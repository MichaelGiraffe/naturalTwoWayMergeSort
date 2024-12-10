#include <iostream>//cin;cout
#include <fstream>//open_close .txt files
#include <vector>//because never use it before
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
using namespace chrono;

//������������ �������� � �������:
void pushTwice(std::vector<int>& a1) 
{
	int size = a1.size();
	std::vector<int> a2 = a1;
	for (int i = 0; i < size; i++) {
		a1.push_back(a2[i]);
	}
	a2.clear();
}

//������������ ����������� ����������
void naturalTwoWayMergeSort(std::vector<int>& a1, int N) {
	pushTwice(a1);

	int i, j, l, k, d, swap;
	bool s;
	bool f = true;  // ���������� ��� ���� ��������� ������������������

	s = 0;

	// ��������� ��������� ��������
	if (s == 0) {
		i = 0, j = N - 1, k = N, l = 2 * N - 1;
	}
	else {
		i = N, j = 2 * N - 1, k = 0, l = N - 1;
	}
	d = 1;

	while (true) {
		if (a1[i] > a1[j]) {
			a1[k] = a1[j];
			k += d;
			j--;

			if (j < 0 || a1[j + 1] > a1[j]) {  // �������� ��������� ����
				a1[k] = a1[i];
				k += d;
				i++;

				while (i < j && a1[i - 1] <= a1[i]) {  // ���������� ���� ������������� ������������������
					a1[k] = a1[i];
					k += d;
					i++;
				}

				f = false;  // ����� ����� ������������������
				d = -d;
				swap = k;
				k = l;
				l = swap;
			}
		}
		else {
			a1[k] = a1[i];
			k += d;
			i++;

			if (i > j || a1[i - 1] > a1[i]) {  // �������� ��������� ����
				a1[k] = a1[j];
				k += d;
				j--;

				while (j > i && a1[j + 1] <= a1[j]) {  // ���������� ���� ������������� ������������������
					a1[k] = a1[j];
					k += d;
					j--;
				}

				f = false;  // ����� ����� ������������������
				d = -d;
				swap = k;
				k = l;
				l = swap;
			}
		}

		// N13: �������� �� ��������� ����������
		if (i == j) {
			a1[k] = a1[i];
			if (f == false) {
				s = 1 - s;
				if (s == 0) {
					i = 0, j = N - 1, k = N, l = 2 * N - 1;
				}
				else {
					i = N, j = 2 * N - 1, k = 0, l = N - 1;
				}
				d = 1;
				f = true;
			}
			else
			{
				//���������� ��� s=0:
				if (s == 0)
				{
					for (i = 0; i < N; i++)
					{
						a1[i] = a1[N + i];
					}
				}
				break;
			}
		}
	}
}

void insertionSort(vector<int>& arr)//���������� ���������
{
	for (int i = 1; i < arr.size(); i++)
	{
		int key = arr[i];
		int j = i - 1;
		// ����������� ���������, ������� ������ key, �� ���� ������� ������
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

// ������� ��� ������ ������� � ������ �������
void printDuration(microseconds duration) {
	milliseconds millisec = duration_cast<milliseconds>(duration); // �������� ����� � �������������
	int microsec = duration.count() % 1000; // ������� ������� � �������������

	cout << millisec.count()
		<< setfill('0') << setw(3) << microsec
		<< " micorsec" << endl;
}

// ������� ��������� ��� qsort
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

//������� ���������� �����
int getRandomNumber(int min, int max)
{
	return rand() % (max - min) + min;
}

//�������, ����������� ����������:
bool checkSortedArray(vector<int> vec)
{
	cout << "Sort checked: ";
	for (int i = 0; i < vec.size() - 1; i++)
	{
		if (vec[i] > vec[i + 1])
		{
			return false;
		}
	}
	return true;
}

//�������, ����������� ���������� ������������ ����������� ��������:
bool checknaturalTwoWayMergeSort(vector<int> vec,int N)
{
	cout << "Sort checked: ";
	for (int i = 0; i < N-1; i++)
	{
		if (vec[i] > vec[i + 1])
		{
			return false;
		}
	}

	return true;
}

//! 
int main()
{
	setlocale(LC_ALL, "ru");//��������� ������
	//���������� ��������� ������ � ����������� ������
	string files[5] = { "d16.txt", "d100.txt", "d500.txt", "d1000.txt", "d5000.txt" };
	string outfiles[5] = { "ar16.txt", "ar100.txt", "ar500.txt", "ar1000.txt", "ar5000.txt" };
	vector<int> a1, aCopy, aCopy1;//razmer a.size(), ochistka a.clear()		//!
	int num, i;//���������� ��� �����
	int N;//���������� ������ �������

	for (int f=0; f<5;f++)
	{
		ifstream input(files[f]);//������ �����
		ofstream output(outfiles[f]);//������ �����
		//�������� ������� ������� � �������� ������:
		if (!input)
		{
			cerr << "������ �������� ������������ �����" << endl;
			return 16;
		}
		if (!output)
		{
			cerr << "������ �������� ������������ �����" << endl;
			return -16;
		}
		while (input >> num)//���������� ����� ����� � ������
		{
			a1.push_back(num);
		}

		//!
		aCopy = a1;
		aCopy1 = a1;
		N = a1.size();

		// ����� ������� ���������� ������������ ����������� ��������
		high_resolution_clock::time_point start_NaturalTwoWayMergeSort = high_resolution_clock::now();
		naturalTwoWayMergeSort(a1, N);//���������� ������������ ����������� ��������
		high_resolution_clock::time_point stop_NaturalTwoWayMergeSort = high_resolution_clock::now();
		cout<<checknaturalTwoWayMergeSort(a1,N)<<endl;
		// ������� ������� ���������� ���������� ������������ ����������� ��������
		microseconds durationNaturalTwoWayMergeSort = duration_cast<microseconds>(stop_NaturalTwoWayMergeSort - start_NaturalTwoWayMergeSort);
		cout << "NaturalTwoWayMergeSort sort time for " << a1.size()/2 << " elements: ";
		printDuration(durationNaturalTwoWayMergeSort);
		for (i = 0; i < N; i++)//���� ��� ������ ������������� �����
		{
			output << a1[i] << endl;
		}

		// ����� ������� ����������� ������� qsort
		high_resolution_clock::time_point startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		high_resolution_clock::time_point stopQSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy) << endl;
		// ������� ������� ���������� qsort
		microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);

		// ����� ������� ���������� ��� ������� 3(���������� ���������): 
		high_resolution_clock::time_point startInsertionSort = high_resolution_clock::now();
		insertionSort(aCopy1);
		high_resolution_clock::time_point stopInsertionSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy1) << endl;
		// ������� ������� ���������� qsort
		microseconds durationInsertionSort = duration_cast<microseconds>(stopInsertionSort - startInsertionSort);
		cout << "Insertion sort time for " << aCopy.size() << " elements: ";
		printDuration(durationInsertionSort);
		//!
		

		for (i = 0; i < N; i++)//���� ��� ������ ������������� �����
		{
			output << a1[i] << endl;
		}
		//�������� ������+������� �������
		input.close();
		output.close();
		a1.clear();
		N = 0;//�� ������
	}

	//��������� ���������:
	cout << "��������� ���������" << endl;
	cout << "������ ��� ����������? 1-���������� � ������������� ���������� �������" << endl;
	cin >> num;
	while (num == 1)
	{
		int k, min, max;//���������� �����,����������� � ������������ �����
		cout << "������� ����������, ����������� � ������������ �����" << endl;
		cin >> k >> min >> max;
		for (int i = 0; i < k; i++)
		{
			a1.push_back(getRandomNumber(min, max));// �������� [min, max]
		}
		ofstream output("any.txt");
		//�������� ������� ������:
		if (!output)
		{
			cerr << "������ �������� ������������ �����" << endl;
			return -16;
		}
		//!
		aCopy = a1;
		N = a1.size();
		// ����� ������� ���������� ����������� �����������
		high_resolution_clock::time_point start_NaturalTwoWayMergeSort = high_resolution_clock::now();
		naturalTwoWayMergeSort(a1, N);//���������� ����������� �����������
		high_resolution_clock::time_point stop_NaturalTwoWayMergeSort = high_resolution_clock::now();
		cout << checknaturalTwoWayMergeSort(a1,N) << endl;
		// ������� ������� ���������� ���������� ����������� �����������
		microseconds durationNaturalTwoWayMergeSort = duration_cast<microseconds>(stop_NaturalTwoWayMergeSort - start_NaturalTwoWayMergeSort);
		cout << "NaturalTwoWayMergeSort time for " << a1.size() << " elements: ";
		printDuration(durationNaturalTwoWayMergeSort);

		// ����� ������� ����������� ������� qsort
		high_resolution_clock::time_point startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		high_resolution_clock::time_point stopQSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy) << endl;
		// ������� ������� ���������� qsort
		microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);


		// ����� ������� ���������� ��� ������� 3(���������� ���������): 
		high_resolution_clock::time_point startInsertionSort = high_resolution_clock::now();
		insertionSort(aCopy1);
		high_resolution_clock::time_point stopInsertionSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy1) << endl;
		// ������� ������� ���������� qsort
		microseconds durationInsertionSort = duration_cast<microseconds>(stopInsertionSort - startInsertionSort);
		cout << "Insertion sort time for " << aCopy.size() << " elements: ";
		printDuration(durationInsertionSort);
		//!


		for (const int& num : a1)//���� ��� ������ ������������� �����
		{
			output << num << endl;
		}
		//�������� ������+������� �������
		output.close();
		a1.clear();
		N = 0;//�� ������
		cout << "��������� 1?" << endl; cin >> num;
	}
	return 0;
};