#include <cxxtest/TestSuite.h>
#include "main.h"
#include <algorithm>
#include <fstream>

class MatrixTest : public CxxTest::TestSuite {
    public:
        void testConstructors(void) {
            TS_TRACE("Beginning constructor tests");
            Matrix<int> m1 = Matrix<int>();     //Default constructor
            Matrix<int> m2 = Matrix<int>(5);    //Square matrix constructor
            std::cout << m2 << std::endl;

            Matrix<int> m3 = Matrix<int>(6, 8);
            TS_ASSERT_EQUALS(m3(3,4), 0);

            Matrix<int> m4(m3);     //Copy constructor
            std::cout << m4 << std::endl;

            Matrix<int> id = m4.identity(5);

            for (int i = 0; i < 5; i++) {
                TS_ASSERT_EQUALS(id.get(i, i), 1);
            }

            TS_TRACE("Constructor tests complete");
        }

        void testInserts(void) {
            TS_TRACE("Beginning insert and append tests");
            Matrix<int> m1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::cout << m1 << std::endl;

            m1.insert_row(2);
            TS_ASSERT_EQUALS(m1(1, 0), 0);

            m1.insert_column(2);
            TS_ASSERT_EQUALS(m1(0, 1), 0);

            Matrix<int> m2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::cout << m2 << std::endl;

            m2.append_row(2);
            TS_ASSERT_EQUALS(m2(2, 0), 0);

            m2.append_column(2);
            TS_ASSERT_EQUALS(m2(0, 2), 0);
            TS_TRACE("Insert and append tests complete");
        }

        void testMultiplication(void) {
            TS_TRACE("Beginning multiplication tests");
            Matrix<int> m1 = {7, 4, 2, 9, 3, 6, 11, 2, 1};
            Matrix<int> m2 = {11, 4, 8, 6, 9, 14, 1, 3, 10};

            std::cout << m1 << std::endl;
            std::cout << m2 << std::endl;
            m2.append_column(3);
            std::cout << m2 << std::endl;
            m2(0, 3) = 5;
            m2(1, 3) = 2;
            m2(2, 3) = 1;
            TS_ASSERT_EQUALS(m2(2, 3), 1);

            Matrix<int> res = m1 * m2;
            TS_ASSERT_EQUALS(res(0, 0), 103);
            TS_ASSERT_EQUALS(res(1, 1), 81);
            TS_ASSERT_EQUALS(res(2, 2), 126);
            TS_ASSERT_EQUALS(res(0, 3), 45);

            TS_TRACE("Multiplication tests complete");
        }

        void testAdditionSubtraction(void) {
            TS_TRACE("Beginning addition and subtraction tests");
            Matrix<int> m1 = {1, 2, 3, 4};
            Matrix<int> m2 = {4, 3, 2, 1};

            m1 += m2;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    TS_ASSERT_EQUALS(m1(i, j), 5);
                }
            }

            m1 -= m2;
            std::cout << m1 << std::endl;

            TS_TRACE("Running non-member addition & subtraction");

            Matrix<int> matSum = m1 + m2;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    TS_ASSERT_EQUALS(matSum(i, j), 5);
                }
            }
            
            Matrix<int> matDiff = m1 - m2;
            TS_ASSERT_EQUALS(matDiff(0, 0), -3)
            std::cout << m2 << std::endl;
            TS_TRACE("Addition and subtraction tests complete");
        }

        void testRemoveRowCol(void) {
            TS_TRACE("Beginning row and column removal tests");
            Matrix<int> m1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::cout << m1 << std::endl;

            TS_ASSERT_THROWS_ANYTHING(m1.remove_row(5));

            m1.remove_row(0);
            TS_ASSERT_EQUALS(m1(0, 0), 4);

            Matrix<int> m2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::cout << m2 << std::endl;

            m2.remove_column(0);
            TS_ASSERT_EQUALS(m2(0, 0), 2);

            TS_TRACE("Row and column removal tests complete");
        }

        void testMoveFuncs(void) {
            TS_TRACE("Beginning move function tests");
            Matrix<int> m1 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
            Matrix<int> m2 = {4, 4, 4, 4, 4, 4, 4, 4, 4};

            Matrix<int> m3 = std::move(m1);
            TS_ASSERT_EQUALS(m3(2, 1), 1);
            TS_ASSERT_EQUALS(m3(0, 0), 1);
            TS_ASSERT_THROWS_ANYTHING(m1(0, 0));

            m3 = m3 + m2;
            TS_ASSERT_EQUALS(m3(2, 2), 5);
            TS_ASSERT_EQUALS(m3(0, 0), 5);

            TS_TRACE("Testing deletes and such");
            Matrix<int> m4;
            if (1) {
                Matrix<int> m5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                m4 = std::move(m5);
            }
            TS_ASSERT_EQUALS(m4(0, 0), 1);
            TS_ASSERT_EQUALS(m4(2, 2), 9);

            TS_TRACE("Move function tests complete");
        }

        void testInputStream(void) {
            TS_TRACE("Beginning input stream tests");

            Matrix<int> m1;
            std::cin >> m1;

            std::cout << "Input matrix:\n" << m1 << std::endl;

            std::ifstream inFile;
            inFile.open("inFile.txt");
            if (!inFile) {
                std::cerr << "File's fucked, yo!";
                exit(1);
            } 
            Matrix<float> m2;
            inFile >> m2;

            std::cout << m2 << std::endl;

            Matrix<int> m3;
            inFile >> m3;

            std::cout << m3 << std::endl;

            Matrix <int> m4;
            inFile >> m4;

            std::cout << m4 << std::endl;

            TS_TRACE("Finished input stream tests");
        }

        void testInverseMatrix(void) {
            TS_TRACE("Beginning inverse tests");
            Matrix<float> m1 = {1, 4, 1, 3, 9, 7, 11, 5, 6};

            std::cout << m1 << std::endl;

            Matrix<float> m2 = m1.inverse(m1);
            TS_ASSERT_DELTA(m2(0, 0), 0.111111, 10e-6);
            TS_ASSERT_DELTA(m2(1, 1), -0.0292398, 10e-6);
            TS_ASSERT_DELTA(m2(1, 2), -0.0233918, 10e-6);
            TS_ASSERT_DELTA(m2(2, 1), 0.22807, 10e-6);

            Matrix<int> m3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            TS_ASSERT_THROWS_ANYTHING(m3.inverse(m3));

            Matrix<int> m4(4, 6);
            TS_ASSERT_THROWS_ANYTHING(m4.inverse(m4));

            TS_TRACE("Inverse tests complete");
        }

        void testDeterminant(void) {
            TS_TRACE("Beginning determinant tests");

            Matrix<int> zerodet = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            Matrix<int> det = {1, 4, 1, 3, 9, 7, 11, 5, 6};
            Matrix<int> det2 = {1, 9, 8, 12, 15, 3, 2, 7, 8, 32, 19, 6, 72, 84, 4, 17};

            TS_ASSERT_EQUALS(zerodet.determinant(), 0);
            TS_ASSERT_EQUALS(det.determinant(), 171);
            TS_ASSERT_EQUALS(det2.determinant(), 204840);

            TS_TRACE("Determinant tests complete");
        }

        void testIterators(void) {
            TS_TRACE("Beginning iterator tests");
            Matrix<int> m1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
            
            std::sort(m1.begin(), m1.end());

            TS_ASSERT_EQUALS(m1(0, 0), 1);

            TS_TRACE("Iterator tests complete");
        }
};