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

//дублирование значений в векторе:
void pushTwice(std::vector<int>& a1) 
{
	int size = a1.size();
	std::vector<int> a2 = a1;
	for (int i = 0; i < size; i++) {
		a1.push_back(a2[i]);
	}
	a2.clear();
}

//Естественная двухпутевая сортировка
void naturalTwoWayMergeSort(std::vector<int>& a1, int N) {
	pushTwice(a1);

	int i, j, l, k, d, swap;
	bool s;
	bool f = true;  // Используем как флаг окончания последовательности

	s = 0;

	// Установка начальных значений
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

			if (j < 0 || a1[j + 1] > a1[j]) {  // Проверка ступеньки вниз
				a1[k] = a1[i];
				k += d;
				i++;

				while (i < j && a1[i - 1] <= a1[i]) {  // Продолжаем пока упорядоченная последовательность
					a1[k] = a1[i];
					k += d;
					i++;
				}

				f = false;  // Конец одной последовательности
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

			if (i > j || a1[i - 1] > a1[i]) {  // Проверка ступеньки вниз
				a1[k] = a1[j];
				k += d;
				j--;

				while (j > i && a1[j + 1] <= a1[j]) {  // Продолжаем пока упорядоченная последовательность
					a1[k] = a1[j];
					k += d;
					j--;
				}

				f = false;  // Конец одной последовательности
				d = -d;
				swap = k;
				k = l;
				l = swap;
			}
		}

		// N13: Проверка на окончание сортировки
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
				//исправлено при s=0:
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

void insertionSort(vector<int>& arr)//сортировка вставками
{
	for (int i = 1; i < arr.size(); i++)
	{
		int key = arr[i];
		int j = i - 1;
		// Перемещение элементов, которые больше key, на одну позицию вперед
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

// Функция для вывода времени в нужном формате
void printDuration(microseconds duration) {
	milliseconds millisec = duration_cast<milliseconds>(duration); // Получаем время в миллисекундах
	int microsec = duration.count() % 1000; // Остаток времени в микросекундах

	cout << millisec.count()
		<< setfill('0') << setw(3) << microsec
		<< " micorsec" << endl;
}

// Функция сравнения для qsort
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

//функция рандомного числа
int getRandomNumber(int min, int max)
{
	return rand() % (max - min) + min;
}

//функция, проверяющая сортировку:
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

//функция, проверяющая сортировку Естественным двухпутевым слиянием:
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
	setlocale(LC_ALL, "ru");//установка локали
	//объявление текстовых файлов в статический массив
	string files[5] = { "d16.txt", "d100.txt", "d500.txt", "d1000.txt", "d5000.txt" };
	string outfiles[5] = { "ar16.txt", "ar100.txt", "ar500.txt", "ar1000.txt", "ar5000.txt" };
	vector<int> a1, aCopy, aCopy1;//razmer a.size(), ochistka a.clear()		//!
	int num, i;//переменная для цикла
	int N;//переменная размер массива

	for (int f=0; f<5;f++)
	{
		ifstream input(files[f]);//чтение файла
		ofstream output(outfiles[f]);//запись файла
		//проверка наличия входных и выходных файлов:
		if (!input)
		{
			cerr << "ошибка открытия считываемого файла" << endl;
			return 16;
		}
		if (!output)
		{
			cerr << "ошибка открытия вписываемого файла" << endl;
			return -16;
		}
		while (input >> num)//добавление чисел файла в вектор
		{
			a1.push_back(num);
		}

		//!
		aCopy = a1;
		aCopy1 = a1;
		N = a1.size();

		// Замер времени сортировки Естественным двухпутевым слиянием
		high_resolution_clock::time_point start_NaturalTwoWayMergeSort = high_resolution_clock::now();
		naturalTwoWayMergeSort(a1, N);//сортировка Естественным двухпутевым слиянием
		high_resolution_clock::time_point stop_NaturalTwoWayMergeSort = high_resolution_clock::now();
		cout<<checknaturalTwoWayMergeSort(a1,N)<<endl;
		// Подсчет времени выполнения сортировки Естественным двухпутевым слиянием
		microseconds durationNaturalTwoWayMergeSort = duration_cast<microseconds>(stop_NaturalTwoWayMergeSort - start_NaturalTwoWayMergeSort);
		cout << "NaturalTwoWayMergeSort sort time for " << a1.size()/2 << " elements: ";
		printDuration(durationNaturalTwoWayMergeSort);
		for (i = 0; i < N; i++)//цикл для записи сортированных чисел
		{
			output << a1[i] << endl;
		}

		// Замер времени стандартной функции qsort
		high_resolution_clock::time_point startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		high_resolution_clock::time_point stopQSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy) << endl;
		// Подсчет времени выполнения qsort
		microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);

		// Замер времени сортировки под номером 3(сортировки вставками): 
		high_resolution_clock::time_point startInsertionSort = high_resolution_clock::now();
		insertionSort(aCopy1);
		high_resolution_clock::time_point stopInsertionSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy1) << endl;
		// Подсчет времени выполнения qsort
		microseconds durationInsertionSort = duration_cast<microseconds>(stopInsertionSort - startInsertionSort);
		cout << "Insertion sort time for " << aCopy.size() << " elements: ";
		printDuration(durationInsertionSort);
		//!
		

		for (i = 0; i < N; i++)//цикл для записи сортированных чисел
		{
			output << a1[i] << endl;
		}
		//закрытие файлов+очистка вектора
		input.close();
		output.close();
		a1.clear();
		N = 0;//на всякий
	}

	//окончание программы:
	cout << "программа выполнена" << endl;
	cout << "хотите еще поиграться? 1-сортировка с произвольными рандомными числами" << endl;
	cin >> num;
	while (num == 1)
	{
		int k, min, max;//количество чисел,минимальное и максимальное число
		cout << "введите количество, минимальное и максимальное число" << endl;
		cin >> k >> min >> max;
		for (int i = 0; i < k; i++)
		{
			a1.push_back(getRandomNumber(min, max));// диапазон [min, max]
		}
		ofstream output("any.txt");
		//проверка наличия файлов:
		if (!output)
		{
			cerr << "ошибка открытия вписываемого файла" << endl;
			return -16;
		}
		//!
		aCopy = a1;
		N = a1.size();
		// Замер времени сортировки Натуральной Двухпутевой
		high_resolution_clock::time_point start_NaturalTwoWayMergeSort = high_resolution_clock::now();
		naturalTwoWayMergeSort(a1, N);//сортировка Натуральной двухпутевой
		high_resolution_clock::time_point stop_NaturalTwoWayMergeSort = high_resolution_clock::now();
		cout << checknaturalTwoWayMergeSort(a1,N) << endl;
		// Подсчет времени выполнения сортировки Натуральной двухпутевой
		microseconds durationNaturalTwoWayMergeSort = duration_cast<microseconds>(stop_NaturalTwoWayMergeSort - start_NaturalTwoWayMergeSort);
		cout << "NaturalTwoWayMergeSort time for " << a1.size() << " elements: ";
		printDuration(durationNaturalTwoWayMergeSort);

		// Замер времени стандартной функции qsort
		high_resolution_clock::time_point startQSort = high_resolution_clock::now();
		qsort(aCopy.data(), aCopy.size(), sizeof(int), compare);
		high_resolution_clock::time_point stopQSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy) << endl;
		// Подсчет времени выполнения qsort
		microseconds durationQSort = duration_cast<microseconds>(stopQSort - startQSort);
		cout << "qsort time for " << aCopy.size() << " elements: ";
		printDuration(durationQSort);


		// Замер времени сортировки под номером 3(сортировки вставками): 
		high_resolution_clock::time_point startInsertionSort = high_resolution_clock::now();
		insertionSort(aCopy1);
		high_resolution_clock::time_point stopInsertionSort = high_resolution_clock::now();
		cout << checkSortedArray(aCopy1) << endl;
		// Подсчет времени выполнения qsort
		microseconds durationInsertionSort = duration_cast<microseconds>(stopInsertionSort - startInsertionSort);
		cout << "Insertion sort time for " << aCopy.size() << " elements: ";
		printDuration(durationInsertionSort);
		//!


		for (const int& num : a1)//цикл для записи сортированных чисел
		{
			output << num << endl;
		}
		//закрытие файлов+очистка вектора
		output.close();
		a1.clear();
		N = 0;//на всякий
		cout << "повторить 1?" << endl; cin >> num;
	}
	return 0;
};