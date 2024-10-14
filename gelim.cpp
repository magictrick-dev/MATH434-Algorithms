#include <iostream>
#include <vector>
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

        bool gauss(vector<int>& p_order);

    protected:
        vector<vector<double>> rows;

};

bool Matrix::
gauss(vector<int>& p_order)
{

    bool singular = false;
    for (int i = 0; i < this->size(); ++i) p_order.push_back(i);

    for (i = 0; i < p_order.size(); ++i)
    {

        for (j = 0; j < p_order[0].size(); ++j)
        {



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

    vector<int> p_order;
    bool is_singular = A.gauss(p_order);
    std::cout << "Matrix is singular?: " << ((is_singular) ? "True" : "False") << std::endl;
    std::cout << "LU Matrix:\n" << A << "Permute Order:\n";
    for (auto i : p_order) std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
