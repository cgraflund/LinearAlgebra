//
// Created by conno on 8/8/2020.
//

#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    vector<vector<double>> m_initial {
            {1,1,1,2},
            {1,2,1,1},
            {1,1,2,1}
    };
    matrix<double> m(3,4,m_initial);

    m.ref();


    for (unsigned i = 0; i < m.get_rows(); i++) {
        for (unsigned j = 0; j < m.get_cols(); j++) {
            cout << m(i,j) << ", ";
        }
        cout << "\n";
    }
    return 0;
}

