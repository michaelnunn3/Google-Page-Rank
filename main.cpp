#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

int main ()
{
    std::cout << std::setprecision(2) << std::fixed;

    int m;
    int n;
    //m n
    std::cin >>m;
    std::cin >>n;
    //get Data

    int nextIndex = 0;


    std::map<std::string, int> dictionary;
    int matrix[m][m];
    int outCounts[m];

    for(int i = 0; i < m; i++){
        outCounts[i] = 0;
    }

    for ( int row = 0; row < m; row++) {
        for ( int col = 0; col < m; col++ ) {
            matrix[row][col] = 0;
        }
    }

    for(int i = 0; i < m; i++){
        //std::cout << "insert data by pairs: ";
        std::string d1;
        std::string d2;
        std::cin >> d1;
        std::cin >> d2;

        if (dictionary.count(d1) == 0) {
            std::pair<std::string, int> val(d1,nextIndex++);
            dictionary.insert(val);
        }
        int d1index = dictionary[d1];

        if (dictionary.count(d2) == 0) {
            std::pair<std::string, int> val(d2,nextIndex++);
            dictionary.insert(val);
        }
        int d2index = dictionary[d2];

        // google gmail
        // ...
        // google gmail
        // if you get the same line repeated, then how to count it?
        if ( matrix[d2index][d1index] == 0 ) {
            matrix[d2index][d1index] = 1;
            outCounts[d1index]++;
        }
    }

    m = dictionary.size();

    double weightedMatrix[m][m];
    for ( int row = 0; row < m; row++) {
        for ( int col = 0; col < m; col++ ) {
            if (outCounts[col] == 0)
                weightedMatrix[row][col] = 0;
            else
                weightedMatrix[row][col] = matrix[row][col] / (double) outCounts[col];
        }
    }

    double sum[m];
    for ( int row = 0; row < m; row++) {
        sum[row] = 0;
        for ( int col = 0; col < m; col++ ) {
            sum[row] += weightedMatrix[row][col];
        }
    }


    // compute initial scores
    double rank[m];
    for ( int row = 0; row < m; row++) {
        rank[row] = 1.0 / m;
    }

    for (int p = 2; p <= n; p++){
        for ( int row = 0; row < m; row++) {
            for ( int col = 0; col < m; col++ ) {
                if(outCounts[col] == 0)
                    weightedMatrix[row][col] = 0;
                else
                    weightedMatrix[row][col] = (matrix[row][col] / (double) outCounts[col]) * rank[col];
            }
        }
        for ( int row = 0; row < m; row++) {
            rank[row] = 0;
            for (int col = 0; col < m; col++) {
                rank[row] += weightedMatrix[row][col];
            }
        }
    }

    // sort by alpha
    std::vector<std::string> alphaList;
    std::map<std::string, int> :: iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); it++) {
        alphaList.push_back(it->first);
    }
    std::sort(alphaList.begin(), alphaList.end());

    std::vector<std::string> :: iterator it2;
    for (it2 = alphaList.begin(); it2 != alphaList.end(); it2++) {
        std::cout << *it2;
        std::cout << " ";
        int index = dictionary[*it2];
        // print rank
        //printf("%.02f", rank[index])
        std::cout << rank[index] << std::endl;
        //std::cout << std::endl;
    }



    return 0;
}