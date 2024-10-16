#include <iostream>
#include <vector>
#include <cmath>
using std::vector;

// --- Matrix ------------------------------------------------------------------
//
// We assume the matrix is n-by-n, but we are not checking for this. We also
// assume that if we call Matrix.gauss() that we provided an n-by-n matrix.
//

class Matrix
{
    
    public:
        inline  Matrix() {};
        inline ~Matrix() {};

        inline void add_row(vector<double> row) { this->rows.push_back(row); }
        inline vector<double>& operator[](int row) { return this->rows[row]; }
        inline size_t size() const { return this->rows.size(); }
        inline double& at(int i, int j) { return this->rows[i][j]; }

        bool gauss(vector<int>& p_order);

    protected:
        vector<vector<double>> rows;

};

bool Matrix::
gauss(vector<int>& p_order)
{

    bool singular = false;
    for (int i = 0; i < this->size(); ++i) p_order.push_back(i);

    for (int k = 0; k < this->rows.size() - 1; ++k)
    {

        // amax <- max {|ak,k|, |ak+1,k|...}
        int a_max = 0;
        int a_row = 0;
        for (int a = k; a < this->rows.size(); ++a)
        {
            int v = abs(this->at(a, k));
            if (v > a_max) 
            {
                a_max = v;
                a_row = a;
            }
        }

        // if(amax == 0), Singular
        if (a_max == 0)
        {
            singular = true;
            return singular;
        }

        // Interchange p.
        int temp = p_order[k];
        p_order[k] = a_row;
        p_order[a_row] = temp;

        // Interchange rows & multipliers.
        if (a_row != k && k != 0)
        {
            auto temp = this->rows[k];
            this->rows[k] = this->rows[a_row];
            this->rows[a_row] = temp;
        }

        for (int i = k + 1; i < this->rows.size(); ++i)
        {
            this->at(i, k) = this->at(i, k) / this->at(k, k);
            for (int j = k + 1; j < this->rows.size(); ++j)
            {
                this->at(i, j) -= (this->at(i, k) * this->at(k, j));
            }
        }

    }

    return singular;

}

// --- Helpers -----------------------------------------------------------------

std::ostream&
operator<<(std::ostream& lhs, vector<double>& rhs)
{

    for (int i = 0; i < rhs.size(); ++i)
    {
        lhs << rhs[i];
        if (i < rhs.size() - 1) lhs << " ";
    }

    return lhs;
}

std::ostream& 
operator<<(std::ostream& lhs, Matrix& rhs)
{

    for (int i = 0; i < rhs.size(); ++i)
    {
        lhs << rhs[i] << std::endl;
    }

    return lhs;
}

// --- Main --------------------------------------------------------------------

int
main(int argc, char ** argv)
{

    Matrix A;
    A.add_row({ 2, 2, -4 });
    A.add_row({ 1, 1,  5 });
    A.add_row({ 1, 3,  6 });
    std::cout << A << std::endl;

    vector<int> p_order;
    bool is_singular = A.gauss(p_order);
    std::cout << "Matrix is singular?: " << ((is_singular) ? "True" : "False") << std::endl;
    std::cout << "LU Matrix:\n" << A << "Permute Order:\n";
    for (auto i : p_order) std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
