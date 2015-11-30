#ifndef BOARD_MPAD6_CONFIG_H
#define BOARD_MPAD6_CONFIG_H
#include "common/MatrixConfig.h"
#include "../../src/target/kinetis/mkl27z/in_pin.h"
#include "../../src/target/kinetis/mkl27z/out_pin.h"
using LayoutT = MatrixConfig<2, 3, MKL27ZInputPin, MKL27ZOutputPin>;
using ResultT = Matrix<unsigned, 2, 3>;

extern const MKL27ZInputPin mkl27zRowPins[2];
extern const MKL27ZOutputPin mkl27zColumnPins[3];
#endif
