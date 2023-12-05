#include <iostream>

class Logging {
public:
    static void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
};

class Matrix {
private:
    int rows;
    int cols;
    int** data;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix operator+(const Matrix& other) const {
        Logging::log("Thuc hien phep cong");

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Logging::log("Thuc hien phep tru");

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Logging::log("Thuc hien phep nhan");

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const Matrix& other) const {
        Logging::log("Thuc hien phep chia");

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

    void inputMatrix() {
        std::cout << "Nhap gia tri:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << "Matrix[" << i << "][" << j << "]: ";
                std::cin >> data[i][j];
            }
        }
    }

    // in ma trn
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int rows1, cols1, rows2, cols2;
    std::cout << "Nhap hang va cot cua ma tran thu 1: ";
    std::cin >> rows1 >> cols1;

    std::cout << "Nhap hang va cot cua ma tran thu 2: ";
    std::cin >> rows2 >> cols2;

    
    Matrix matrix1(rows1, cols1);
    Matrix matrix2(rows2, cols2);

    matrix1.inputMatrix();
    matrix2.inputMatrix();

    if (rows1 != rows2 || cols1 != cols2) {
    	std::cerr << "Error: Khong thuc hien duoc cong va tru 2 ma tran." << std::endl;
    }else{
    	(matrix1 + matrix2).print();
    	(matrix1 - matrix2).print();
	}
	 if (rows1 != cols2) {
        std::cerr << "Error: Khong thuc hien duoc nhan va chia 2 ma tran." << std::endl;
    }else{
    (matrix1 * matrix2).print();
    (matrix1 / matrix2).print();
	}

    return 0;
}
