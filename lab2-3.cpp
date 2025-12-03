#include <iostream>
#include <iomanip>
#include <clocale>

using namespace std;

// Ввод n значений в динамический массив
void inputData(float* p, int n)
{
    cout << "Введите значения: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> *(p + i);  
    }
}

// Среднее значение
float average(const float* p, int n)
{
    float sum = 0.0f;
    for (int i = 0; i < n; ++i)
    {
        sum += *(p + i);
    }
    return (n > 0) ? sum / n : 0.0f;
}

// Минимум
float minValue(const float* p, int n)
{
    if (n <= 0) return 0.0f;
    float minVal = *p; // первый элемент
    for (int i = 1; i < n; ++i)
    {
        float val = *(p + i);
        if (val < minVal)
            minVal = val;
    }
    return minVal;
}

// Максимум
float maxValue(const float* p, int n)
{
    if (n <= 0) return 0.0f;
    float maxVal = *p;
    for (int i = 1; i < n; ++i)
    {
        float val = *(p + i);
        if (val > maxVal)
            maxVal = val;
    }
    return maxVal;
}

// Создаёт новый массив со значениями, превышающими среднее
float* filterAboveAverage(float* p, int n, int& newCount)
{
    newCount = 0;
    float avg = average(p, n);

    // Сначала считаем, сколько элементов > среднего
    for (int i = 0; i < n; ++i)
    {
        if (*(p + i) > avg)
            ++newCount;
    }

    // Если таких нет — возвращаем nullptr
    if (newCount == 0)
        return nullptr;

    // Выделяем новый динамический массив
    float* result = new float[newCount];

    // Заполняем его подходящими значениями
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        float val = *(p + i);
        if (val > avg)
        {
            *(result + j) = val;
            ++j;
        }
    }

    return result;
}

int main()
{
    setlocale(LC_ALL, ".UTF-8"); // для отображения русского

    cout << "=== Анализ сенсора ===\n";

    int n;
    cout << "Введите количество измерений: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Некорректное количество измерений.\n";
        return 0;
    }

    // Динамическое выделение массива
    float* data = new float[n];

    // Ввод значений
    inputData(data, n);

    // Анализ
    float avg = average(data, n);
    float minVal = minValue(data, n);
    float maxVal = maxValue(data, n);

    cout << fixed << setprecision(1);
    cout << "\nСреднее значение: " << avg << endl;
    cout << "Минимум: " << minVal << endl;
    cout << "Максимум: " << maxVal << endl;

    // Фильтр значений выше среднего
    int newCount = 0;
    float* above = filterAboveAverage(data, n, newCount);

    cout << "\nЗначения выше среднего:\n";
    if (above != nullptr)
    {
        for (int i = 0; i < newCount; ++i)
        {
            cout << *(above + i) << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "таких значений нет.\n";
    }

    // Освобождение памяти
    delete[] data;
    delete[] above;

    return 0;
}