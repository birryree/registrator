#include <opencv2/opencv2.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/core/cuda.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// maximal number of registration iterations per level
// when speed is requested at the expense of accuracy.
// This number must be corrected so that there are more iterations
// at the coarse levels of the pyramid than at fine levels
const int FEW_ITERATIONS = 5;

// Initial value of the Marquardt-Levenberg fudge factor
const double FIRST_LAMBDA = 1.0;

// Update parameter of the Marquardt-Levenberg fudge factor
const double LAMBDA_MAGSTEP = 4.0;

// Maximal number of registration iterations per level, when
// accuracy is requested at the expense of speed. This number
// must be correct so that there are more iterations at the
// coarse levels of the pyramid than at fine levels.
const int MANY_ITERATIONS = 10;

// Minimal update distance of landmarks, in pixel units,
// when accuracy is requested at the expense of speed. This
// distance does not depend on the pyramid level.
const double PIXEL_HIGH_PRECISION = 0.001;

// Minimal update distance of landmarks, in pixel units,
// when speed is requested at the expense of accuracy.
// This distance does not depend on the pyramid level.
const double PIXEL_LOW_PRECISION = 0.1;

// multiplicative factor that determines how many more
// iterations are allowed for a pyramid level one unit coarser.
const int ITERATION_PROGRESSION = 2;

cv::OutputArray doFinalTransform(int width, int height) {

}

int main(int argc, char** argv) {
    std::vector<std::string> args(arg, argv + argc);
}
