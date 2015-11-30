#ifndef COMMON_TEST_MATRIX_CONFIG_H
#define COMMON_TEST_MATRIX_CONFIG_H
#include <vector>
#include "common/TestPin.h"

class TestMatrix {
public:
  TestMatrix(unsigned N) : data() { data.resize(N); }
  void put(unsigned C, unsigned R, unsigned NC, unsigned val) {
    data[C + (R * NC)] = val;
  }
  void dump() {
    printf("\n");
    for (unsigned &U : data) {
      printf("%d ", (int)U);
    }
    printf("\n");
  }

private:
  std::vector<unsigned> data;
};

class TestMatrixConfig {
public:
  TestMatrix createResultMatrix() { return TestMatrix(Rows * Columns); }
  void reconfigure(unsigned R, unsigned C) {
    Rows = R;
    rowPins.clear();
    rowPins.reserve(Rows);
    for (unsigned i = 0; i < Rows; ++i) {
      rowPins.push_back(TestInputPin{(i % 2) == 0 ? 0u : 1u});
    }
    Columns = C;
    columnPins.clear();
    columnPins.reserve(Columns);
    for (unsigned i = 0; i < Columns; ++i) {
      columnPins.push_back(TestOutputPin{0});
    }
  }

  TestInputPin getRowPin(unsigned R) { return rowPins[R]; }

  TestOutputPin getColumnPin(unsigned C) { return columnPins[C]; }

  unsigned getNumRows() { return Rows; }
  unsigned getNumColumns() { return Columns; }

private:
  unsigned Rows;
  unsigned Columns;
  std::vector<TestInputPin> rowPins;
  std::vector<TestOutputPin> columnPins;
};
#endif
