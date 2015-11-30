#ifndef COMMON_TEST_PIN_H
#define COMMON_TEST_PIN_H
class TestInputPin {
public:
  TestInputPin(unsigned constantVal) : constantVal(constantVal) {}
  unsigned readInput() const { /*printf("read");*/
    return constantVal;
  }

private:
  unsigned constantVal;
};

class TestOutputPin {
public:
  TestOutputPin(unsigned constantVal) : constantVal(constantVal) {}
  void outputHigh() const { /*printf("output");*/
  }
  void outputLow() const { /*printf("output");*/
  }

private:
  unsigned constantVal;
};
#endif
