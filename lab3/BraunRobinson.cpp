#include <bits/stdc++.h>
#include <iomanip> // для форматирования

using namespace std;

// Установка ширины столбцов
const int columnWidth = 10;

void BraunRobinson(vector<vector<int>> &strategyMatrix, double epsilon){
    int n = strategyMatrix.size(), m = strategyMatrix[0].size();
    
    // Заголовки таблицы
    cout << left << setw(columnWidth) << "k" 
         << left << setw(columnWidth) << "Aa";

    for (int col = 1; col <= m; col++)
        cout << left << setw(columnWidth) << "B" + to_string(col);
    
    cout << left << setw(columnWidth) << "Bb";
    
    for (int col = 1; col <= n; col++)
        cout << left << setw(columnWidth) << "A" + to_string(col);

    cout << left << setw(columnWidth) << "v1(k)"
         << left << setw(columnWidth) << "v2(k)"
         << left << setw(columnWidth) << "v*"
         << left << setw(columnWidth) << "maxV1"
         << left << setw(columnWidth) << "minV2" << endl;
    // Разделительная линия
    cout << setfill('-') << setw(columnWidth * (2 + m + 1 + n + 3 + 2)) << "-" << setfill(' ') << endl;
    
    // Определим первый шаг
    int alpha = -1e9;
    int indexA, indexB;
    for (int i = 0; i < n; i++){
       int minimum = *min_element(strategyMatrix[i].begin(), strategyMatrix[i].end());
       if (minimum > alpha){
           alpha = minimum;
           indexA = i;
       }
    }
    vector<int> A(n, 0), B(m, 0);
    vector<int> countA(n, 0), countB(m, 0);
    vector<double> v1, v2;
    pair<int, int> maxV1 = {-1e9, 1}, minV2 = {1e9, 1};
    int k = 1;
    while (minV2.first * maxV1.second - maxV1.first * minV2.second > epsilon * minV2.second * maxV1.second){
        
        cout << left << setw(columnWidth) << k 
             << left << setw(columnWidth) << "A" + to_string(indexA + 1);
        
        // Выше находится часть вывода
        countA[indexA]++;
        
        for (int i = 0; i < m; i++){
           B[i] += strategyMatrix[indexA][i];
        }
        double minElement = *min_element(B.begin(), B.end());
        if (minElement * maxV1.second > maxV1.first * k){
            maxV1.first = minElement;
            maxV1.second = k;
        }
        v1.push_back(minElement / k);
        for (int i = 0; i < m; i++){
            if (B[i] == minElement){
                indexB = i;
                break;
            }
        }
        
        countB[indexB]++;
        
        for (int i = 0; i < n; i++){
            A[i] += strategyMatrix[i][indexB];
        }
        double maxElement = *max_element(A.begin(), A.end());
        if (maxElement * minV2.second < minV2.first * k){
            minV2.first = maxElement;
            minV2.second = k;
        }
        v2.push_back(maxElement / k);
        for (int i = 0; i < n; i++){
            if (A[i] == maxElement){
                indexA = i;
                break;
            }
        }
        
        // Часть вывода
    
        for (int col = 0; col < m; col++)
            cout << left << setw(columnWidth) << B[col];
        
        cout << left << setw(columnWidth) << "B" + to_string(indexB + 1);
        
        for (int col = 0; col < n; col++)
            cout << left << setw(columnWidth) << A[col];
    
        cout << left << setw(columnWidth) << v1.back()
             << left << setw(columnWidth) << v2.back()
             << left << setw(columnWidth) << (1.0 * maxV1.first / maxV1.second + 1.0 * minV2.first / minV2.second) / 2
             << left << setw(columnWidth) << 1.0 * maxV1.first / maxV1.second
             << left << setw(columnWidth) << 1.0 * minV2.first / minV2.second << endl;
        // Разделительная линия
        cout << setfill('-') << setw(columnWidth * (2 + m + 1 + n + 3 + 2)) << "-" << setfill(' ') << endl;
        
        k++;
    }
    cout << "\nСмешанные стратегии:\n";
    // Вывод смешанных стратегий для A
    cout << "\nSA:\n";
    cout << setfill('-') << setw(columnWidth * (n)) << "-" << setfill(' ') << endl;
    for (int col = 1; col <= n; col++)
        cout << left << setw(columnWidth) << "A" + to_string(col);
    cout << "\n" << setfill('-') << setw(columnWidth * (n)) << "-" << setfill(' ') << endl;
    for (int col = 0; col < n; col++)
        cout << left << setw(columnWidth) << to_string(countA[col]) + "/" + to_string(k);
    cout << "\n" << setfill('-') << setw(columnWidth * (n)) << "-" << setfill(' ') << endl;
    
    // Вывод смешанных стратегий для B
    cout << "\nSB:\n";
    cout << setfill('-') << setw(columnWidth * (m)) << "-" << setfill(' ') << endl;
    for (int col = 1; col <= m; col++)
        cout << left << setw(columnWidth) << "B" + to_string(col);
    cout << "\n" << setfill('-') << setw(columnWidth * (m)) << "-" << setfill(' ') << endl;
    for (int col = 0; col < m; col++)
        cout << left << setw(columnWidth) << to_string(countB[col]) + "/" + to_string(k);
    cout << "\n" << setfill('-') << setw(columnWidth * (m)) << "-" << setfill(' ') << endl;
    
    cout << "\nv*:\n";
    cout << maxV1.first * minV2.second + minV2.first * maxV1.second << "/" << 2 * maxV1.second * minV2.second << "\n";
    
    return;
}

int main()
{
    vector<vector<int>> strategyMatrix = {
        {2, 6, 7, 6},
        {2, 8, 1, 2},
        {9, 9, 1, 3},
        {5, 3, 9, 1}
    };
    BraunRobinson(strategyMatrix, 0.01);
    return 0;
}
