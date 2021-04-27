#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <sstream>
#include <string>

template <class T>
class Matrix {
    private:
        size_t m_rows;
        size_t m_cols;
        size_t m_capacity;
        std::vector<T>* m_vec;

    public:
        // constructors  
        Matrix<T>() : m_rows(0), m_cols(0), m_capacity(0), m_vec(nullptr) {     // Default constructor

        }

        Matrix<T>(size_t d) : m_rows(d), m_cols(d), m_capacity(d*d), m_vec(new std::vector<T>) {       // Square matrix constructor
            for (size_t i = 0; i < d*d; i++) {
                m_vec->push_back(0);
            }
        }

        Matrix<T>(size_t a, size_t b) : m_rows(a), m_cols(b), m_capacity(a * b), m_vec(new std::vector<T>) {      // General matrix constructor
            for (size_t i = 0; i < a*b; i++) {
                m_vec->push_back(0);
            }
        }

        Matrix<T>(const Matrix<T>& m) : m_rows(m.rows()), m_cols(m.cols()), m_capacity(m.rows() * m.cols()) {        // Copy constructor
            m_vec = new std::vector<T>;
            for (size_t i = 0; i < m_rows; i++) {
                for (size_t j = 0; j < m_cols; j++) {
                    m_vec->push_back(m(i, j));
                }
            }
        }

        Matrix<T>(Matrix<T>&& m) : m_rows(std::move(m.m_rows)), m_cols(std::move(m.m_cols)), 
                                            m_capacity(std::move(m.m_capacity)), m_vec(std::move(m.m_vec)) {      // Move constructor
            m.m_rows = 0;
            m.m_cols = 0;
            m.m_capacity = 0;
            m.m_vec = nullptr;
        }

        Matrix<T>(std::initializer_list<T> init) {        // Square matrix initializer with list. WIll throw out_of_range if number of elements is not square
            float d = sqrt(init.size());
            if (init.size() / d != d) {
                throw std::out_of_range("Non-square initializer list!");
            }

            m_rows = m_cols = d;
            m_capacity = init.size();
            m_vec = new std::vector<T>;
            for (T t : init) {
                m_vec->push_back(t);
            }
        }

        ~Matrix<T>() {      // Destructor
            delete m_vec;
            m_vec = nullptr;
        }

        // Self-operators
        void operator *=(Matrix<T>& m) {
            if (m_cols != m.rows()) {
                throw std::out_of_range("Matrix dimensions incompatible for multiplication (lhs width != rhs height)");
            }

            Matrix<T> temp = this * m;      // Call the multiplication operator
            this = temp;        // Call the assignment operator 

            return;
        }

        void operator +=(Matrix<T>& m) {
            if (m_cols != m.cols() || m_rows != m.rows())  {
                throw std::out_of_range("Matrix dimensions incompatible for addition (nonequal dimensions)");
            }

            for (size_t i = 0; i < m_rows; i++) {
                for (size_t j = 0; j < m_cols; j++) {
                    (*m_vec)[i * m_cols + j] += m(i, j);
                }
            }
            return;
        }

        void operator -=(Matrix<T>& m) {
            if (m_cols != m.cols() || m_rows != m.rows())  {
                throw std::out_of_range("Matrix dimensions incompatible for addition (nonequal dimensions)");
            }

            for (size_t i = 0; i < m_rows; i++) {
                for (size_t j = 0; j < m_cols; j++) {
                    (*m_vec)[i * m_cols + j] -= m(i, j);
                }
            }
            return;
        }

        T& operator ()(const int x, const int y) const {
            return edit(x, y);
        }

        Matrix<T>& operator =(Matrix<T>& m) {        // Assignment/copy operator
            m_rows = m.rows();
            m_cols = m.cols();
            m_capacity = m_rows * m_cols;

            delete m_vec;
            m_vec = new std::vector<T>;
            for (size_t i = 0; i < m_rows; i++) {
                for (size_t j = 0; j < m_cols; j++) {
                    m_vec->push_back(m(i, j));
                }
            }
            
            return *this;
        }

        Matrix<T>& operator =(Matrix<T>&& m) {       //  Move assignment
            m_rows = std::move(m.m_rows);
            m_cols = std::move(m.m_cols);
            m_capacity = std::move(m.m_capacity);

            delete m_vec;
            m_vec = std::move(m.m_vec);

            // Null the old object
            m.m_rows = 0;
            m.m_cols = 0;
            m.m_capacity = 0;
            m.m_vec = nullptr;

            return *this;
        }

        // methods
        int rows() const {        // Return nr of rows & cols respectively
            return m_rows;
        }

        int cols() const {
            return m_cols;
        }

        const T& get(const int x, const int y) const {     // Get element M(x,y)
            if (x >= m_rows || y >= m_cols) {
                throw std::out_of_range("Matrix index out of bounds");
            }
            return (*m_vec)[x * m_cols + y];
        }

        T& edit(const int x, const int y) const {      // Get editable M(x,y)
            if (x >= m_rows || y >= m_cols) {
                throw std::out_of_range("Matrix index out of bounds");
            }
            return (*m_vec)[x * m_cols + y];
        }

        void setAll(const int rows, const int cols, std::vector<T>* vec) {
            if ( rows == 0 || cols == 0 || vec->empty()) {
                throw std::invalid_argument("Incorrect setAll input. To zero a matrix use reset().");
            }
            m_rows = rows;
            m_cols = cols;
            m_capacity = rows * cols;
            delete m_vec;
            m_vec = vec;

            return;
        }

        double determinant(void) { 
            if (m_rows != m_cols) {
                throw std::out_of_range("Invalid matrix dimensions for determinant calculation.");
            } 

            double det = 0;
            Matrix<T> submatrix(m_rows - 1);
            if (m_rows == 2)
                return ((get(0, 0) * get(1, 1)) - (get(1, 0) * get(0, 1)));     // ad - bc
            else {
                for (int x = 0; x < m_rows; x++) {
                    int subi = 0; 
                    for (int i = 1; i < m_rows; i++) {
                    int subj = 0;
                    for (int j = 0; j < m_rows; j++) {
                        if (j == x) {
                            continue;
                        }
                        submatrix(subi, subj) = get(i, j);
                        subj++;
                    }
                    subi++;
                    }
                    det += (pow(-1, x) * get(0, x) * submatrix.determinant());
                }
            }
            return det;
        }

        void reset(Matrix<T> m) {       // Set all elements of M to the respective default T();
            for (int i = 0; i < m_vec.size(); i++) {
                (*m_vec)[i] = T();
            }
            return;
        }

        Matrix<T> identity(unsigned int d) {        // Returns a square d*d identity matrix
            Matrix<T> id(d);
            size_t j = 0;
            for (size_t i = 0; i < d; i++) {
                id(i, j) = 1;
                j++;
            }

            return id;
        }

        void insert_row(int r) {        // Inserts a row of zeroes BEFORE row r
            for (size_t i = 0; i < m_cols; i++) {
                auto itr = m_vec->begin();
                itr += (r - 1) * m_cols + i;
                m_vec->insert(itr, T());
            }
            m_rows++;
            m_capacity += m_cols;
            return;
        }

        void append_row(int r) {        // Inserts a row of zeroes AFTER row r
            for (size_t i = 0; i < m_cols; i++) {
                auto itr = m_vec->begin();
                itr += r * m_cols + i;
                m_vec->insert(itr, T());
            }
            m_rows++;
            m_capacity += m_cols;
            return;
        }

        void remove_row(int r) {        // Removes row r from the matrix
            if (r >= m_rows || r < 0) {
                throw std::out_of_range("Could not delete row: row number out of bounds");
            }

            for (size_t i = (r + 1) * m_cols; i < m_capacity; i++) {
                (*m_vec)[i - m_cols] = (*m_vec)[i];
            }
            m_vec->resize(m_capacity - m_cols);
            m_vec->shrink_to_fit();

            m_rows--;
            m_capacity -= m_cols;
            return;
        }

        void insert_column(int c) {     // Inserts a column of zeroes BEFORE column c
            for (size_t i = 0; i < m_rows; i++) {
                auto itr = m_vec->begin();
                itr += i * m_cols + (c - 1) + i;
                m_vec->insert(itr, T());
            }
            m_cols++;
            m_capacity += m_rows;
            return;
        }

        void append_column(int c) {     // Inserts a column of zeroes AFTER column c
            for (size_t i = 0; i < m_rows; i++) {
                auto itr = m_vec->begin();
                itr += i * m_cols + c + i;
                m_vec->insert(itr, T());
            }
            m_cols++;
            m_capacity += m_rows;
            return;
        }

        void remove_column(int c) {     // Removes column c from the matrix
            if (c >= m_cols || c < 0) {
                throw std::out_of_range("Could not delete column: column number out of bounds");
            }

            std::vector<T>* newVec = new std::vector<T>;
            for (size_t i = 0; i < m_capacity; i++) {
                if (i % m_rows == c) {
                    continue;
                }
                newVec->push_back((*m_vec)[i]);
            }
            delete m_vec;
            m_vec = newVec;

            m_cols--;
            m_capacity -= m_rows;
            return;
        }

        Matrix<T> inverse(Matrix<T> m) {      // Inverts the input matrix
            if (m.rows() != m.cols() || m.determinant() == 0) {
                throw std::out_of_range("Matrix not invertible.");
            }
            //static_assert(std::is_something_useful<T>::m, "The elements of m must support inversion");

            T temp = T();
            int n = m.rows();       // Save the dimensions of the matrix for future use
            Matrix<T> res = m.identity(n);     // Create the matrix which will eventually hold the result

            for (int i = n - 1; i > 0; i--) {     // Place the row with the largest starting element at the top by sorting from the bottom up
                
                if (m(i - 1, 0) < m(i, 0)) {        // If the row above the current is smaller, then swap them
                    for (int j = 0; j < n; j++) {
                        // Swap the original matrix
                        temp = m(i, j);
                        m(i, j) = m(i-1, j);
                        m(i-1, j) = temp;

                        // Swap the res matrx
                        temp = res(i, j);
                        res(i, j) = res(i - 1, j);
                        res(i - 1, j) = temp;
                    }
                }
            }

            // Perform Gauss-Jordan through row operations
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    
                    if ( j != i ) {
                        float newTemp;
                        if (m(i, i) != 0) {
                            newTemp = m(j, i) / m(i, i);       // Find the correct multiple of the top element and zero every element in the column below
                        } else { 
                            newTemp = m(j, i); 
                        }

                        for (int k = 0; k < n; k++) {
                            m(j, k) -= m(i, k) * newTemp;       // Original matrix
                            res(j, k) -= res(i, k) * newTemp;   // Identity->result matrix
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++) {   // Finally we divide out the elements to get the identity on the lhs
                if (m(i, i) != 0) {         // Cannot divide by 0
                    temp = m(i, i);
                    for (int j = 0; j < n; j++) {
                        m(i, j) = m(i, j) / temp;
                        res(i, j) = res(i, j) / temp;
                    }
                }
            }

            return res;
        }

        //ITERATORS
        typename std::vector<T>::iterator begin() {
            return m_vec->begin();
        }

        typename std::vector<T>::iterator end() {
            return m_vec->end();
        }
};

// Non-member operators
template <class T>
Matrix<T> operator *(const Matrix<T>& a, const Matrix<T>& b) {
    if (a.cols() != b.rows()) {
        throw std::out_of_range("Matrix dimensions incompatible for multiplication (lhs width != rhs height)");
    }

    Matrix<T> result = Matrix<T>(a.rows(), b.cols());
    T sum;
    for (int a_row = 0; a_row < a.rows(); a_row++) {
        for (int i = 0; i < b.cols(); i++) {
            sum = T();
            for (int j = 0; j < a.cols(); j++) {
                //std::cout << "sum a(" << a_row << ", " << j << ") : b(" << j << ", " << i << ")" << std::endl;
                sum += a(a_row, j) * b(j, i);
            }
            result(a_row, i) = sum;
        }
    }

    return result;
}

template <class T>
Matrix<T> operator +(const Matrix<T>& a, const Matrix<T>& b) {
    if (a.cols() != b.cols() || a.rows() != b.rows())  {
        throw std::out_of_range("Matrix dimensions incompatible for addition (nonequal dimensions)");
    }

    Matrix<T> res = Matrix<T>(a.rows(), a.cols());

    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            res(i, j) = a(i, j) + b(i, j);
        }
    }
    return res;
}

template <class T>
Matrix<T> operator -(const Matrix<T>& a, const Matrix<T>& b) {
    if (a.cols() != b.cols() || a.rows() != b.rows())  {
        throw std::out_of_range("Matrix dimensions incompatible for addition (nonequal dimensions)");
    }

    Matrix<T> res(a.rows(), a.cols());

    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            res(i, j) = a(i, j) - b(i, j);
        }
    }
    return res;
}

// IO operators
template <class T>
std::ostream& operator <<(std::ostream& out, Matrix<T>& m) {
    out << std::endl;
    for (int i = 0; i < m.rows(); i++) {
        out << "[ ";
        for (int j = 0; j < m.cols(); j++) {
            out << m(i, j) << " ";
        }
        out << "]" << std::endl;
    }
    return out;
}

template <class T>
std::istream& operator >>(std::istream& in, Matrix<T>& m) {
    std::string input;
    T data;
    int rows = 0;
    int cols = 0;
    std::vector<T>* vec = new std::vector<T>;

    //std::cout << "Please input the Matrix row by row [x y z] : " << std::endl;

    bool endLine = false;
    while (std::getline(in, input)) {
        std::stringstream split(input);
        if (split.get() != '[') {
            if (vec->empty() || rows == 0 || cols == 0) {
                throw std::invalid_argument("Invalid input format.");
            } else {
                m.setAll(rows, cols, vec);      //Put the input data into the matrix and return
                break;
            }
        }

        endLine = false;
        while (!endLine) {      // Loop for each input row
            int count = 0;
            while(std::getline(split, input, ' ')) {        // Loop for each element in the row
                if (input == "]") {
                    rows++;
                    endLine = true;
                    break;
                } else if (input == "") {           // Handle inital space if present
                    continue;
                }
                count++;
                if (input.back() == ']') {
                    rows++;
                    input.pop_back();
                    endLine = true; 
                }

                std::stringstream convert(input);
                convert >> data;                // Covert to type T
                vec->push_back(data);           // Save the data
            }
            if (count > cols) { 
                if (cols == 0) { cols = count; } 
                else { throw std::invalid_argument("Invalid input format."); }
            }
        }
        split.clear();
    }
    return in;
}

#endif  // MAIN_HEADER