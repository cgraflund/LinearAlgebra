//
// Created by conno on 8/8/2020.
//

#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    vector<vector<double>> m_initial {
            {1,2,2},
            {1,4,1},
            {2,0,0}
    };
    matrix<double> m(3,3,m_initial);

    cout << "Determinant: " << m.determinant() << "\n";

    m = m.ref();

    for (unsigned i = 0; i < m.get_rows(); i++) {
        for (unsigned j = 0; j < m.get_cols(); j++) {
            cout << m(i,j) << ", ";
        }
        cout << "\n";
    }



    vector<double> eigens = m.eigenvalues();
    cout << "Eigenvalues: ";
    for(double lambda: eigens) {
        cout << lambda << ", ";
    }

    return 0;
}

