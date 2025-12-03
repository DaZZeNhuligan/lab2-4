#include <iostream>
#include <iomanip>
#include <clocale>

using namespace std;

// Средняя температура за один день (одна строка)
float dayAverage(float* row, int h)
{
    float sum = 0.0f;
    for (int j = 0; j < h; ++j)
    {
        sum += *(row + j);          
    }
    return (h > 0) ? sum / h : 0.0f;
}

// Общая средняя температура по всем дням
float overallAverage(float** p, int d, int h)
{
    if (d <= 0 || h <= 0) return 0.0f;

    float sum = 0.0f;
    int count = d * h;

    for (int i = 0; i < d; ++i)
    {
        float* row = *(p + i);       
        for (int j = 0; j < h; ++j)
        {
            sum += *(row + j);
        }
    }
    return sum / count;
}

// Вывод «тёплых» дней — тех, где средняя > общей средней
void showHotDays(float** p, int d, int h)
{
    float overall = overallAverage(p, d, h);

    cout << fixed << setprecision(1);
    cout << "Общая средняя температура: " << overall << '\n';
    cout << "Теплые дни:\n";

    bool any = false;
    for (int i = 0; i < d; ++i)
    {
        float* row = *(p + i);
        float avg = dayAverage(row, h);

        if (avg > overall)
        {
            any = true;
            cout << "День " << (i + 1)
                 << " (среднее = " << avg << ")\n";
        }
    }

    if (!any)
        cout << "нет дней с температурой выше общей средней\n";
}

int main()
{
    setlocale(LC_ALL, ".UTF-8"); // для отображения русского

    int d, h;
    cout << "Введите количество дней: ";
    cin >> d;
    cout << "Введите количество измерений в дне: ";
    cin >> h;

    if (d <= 0 || d > 30 || h <= 0 || h > 24)
    {
        cout << "Некорректные размеры.\n";
        return 0;
    }

    // 2. Создаём двумерный динамический массив float** data
    float** data = new float*[d];        // массив указателей на строки
    for (int i = 0; i < d; ++i)
    {
        *(data + i) = new float[h];      // каждая строка — массив из h float
    }

    // 3. Считываем значения
    for (int i = 0; i < d; ++i)
    {
        cout << "День " << (i + 1) << ": ";
        float* row = *(data + i);
        for (int j = 0; j < h; ++j)
        {
            cin >> *(row + j);           
        }
    }

    cout << '\n';
    showHotDays(data, d, h);

    // 5. Освобождаем память (два уровня delete[])
    for (int i = 0; i < d; ++i)
    {
        delete[] *(data + i);            // delete[] data[i];
    }
    delete[] data;

    return 0;

}
