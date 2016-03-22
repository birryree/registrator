#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/stitching/stitcher.hpp>

#include <boost/range/irange.hpp>
#include <boost/program_options.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <array>

namespace po = boost::program_options;
using boost::format;
using boost::irange;

std::vector<std::string> generateStitchSet(const std::string&, boost::format, bool, int, int);
cv::Mat stitchSet(std::array<cv::Mat, 5>);

int main(int argc, char** argv) {
	bool useGpu = true;
	float matchConfidence = 0.3f;

	std::string directory = "/Users/billylee/source/gladstone/data/cultured-neuron/ch1";
	boost::format filePattern("%1%/PID20151028_JL_T0_0_D1_%2%_488_642_Empty_684_1_0.0_AndorZyla110XELWD.tif");

	// read all images into memory, then do an estimateRigidTransform on all pairs
	// of images, and then do a cv::gpu::warpAffine

/*	
	std::vector<std::vector<cv::Mat>> imageGrid;
	for (auto i : irange(1, 6)) {
		for (auto j : irange(1, 6)) {
			std::string file = filePattern % directory % (i * j);
			imageGrid[i].push_back(cv::imread(file));
		}
	}

	std::vector<cv::MatchesInfo> pairwise_matches;
	cv::BestOf2NearestMatcher matcher(useGpu, matchConfidence);

	cv::Mat matchMask(features.size(), features.size(), cv::CV_8U, )

	cv::Mat stitched;
	cv::Stitcher stitcher = cv::Stitcher::createDefault(true);
	cv::Stitcher::Status status = stitcher.stitch(images, stitched);

	if (status != cv::Stitcher::OK) {
		std::cout << "Can't stitch!"
	}
*/
	for (auto i : irange (0, 5)) {
		bool reverse = (i + 1) % 2 != 0;
		auto files = generateStitchSet(directory, filePattern, reverse, 5*i + 1, 4);

		std::array<cv::Mat, 5> images;
		// load set into memory
		int c = 0;
		for (auto f : files) {
			images[c] = cv::imread(f);
			c += 1;
		}
		stitchSet(images);
	}
}

std::vector<std::string> generateStitchSet(const std::string& directory, boost::format pattern, bool reverse, int start, int rowSize) {
	std::cout << format("Generating stitch set for range %1% to %2%\n") % start % (start + rowSize);
	std::cout << format("Reversing? %1%\n") % reverse;
	std::vector<std::string> files;
	for (auto i : irange(start, rowSize + start + 1)) {
		std::string filename = boost::str(pattern % directory % i);
		files.push_back(filename);
	}
	if (reverse) std::reverse(files.begin(), files.end());
	return files;
}

cv::Mat stitchSet(std::array<cv::Mat, 5> images) {
	// for each pair of images, generate an estimated transform
	// and then do a GPU affine warp
	std::array<cv::Mat, 4> affineWarps;

	// the fused image panoramas
	std::array<cv::Mat, 5> fusedImages;
	fusedImages[0] = cv::Mat(images[0].size() * 4, images[0].type());
	fusedImages[1] = cv::Mat(images[0].size() * 4, images[0].type());
	fusedImages[2] = cv::Mat(images[0].size() * 4, images[0].type());
	fusedImages[3] = cv::Mat(images[0].size() * 4, images[0].type());
	fusedImages[4] = cv::Mat(images[0].size() * 4, images[0].tupe());

	for (int i = 0; i < images.size()-1; ++i) {
		// estimate the rigid transform between each pair of images
		affineWarps[i] = cv::estimateRigidTransform(images[i], images[i+1], false);
	}

	// now warp the image onto the canvases
	for(int i = 0; i < images.size(); ++i) {
		cv::warpAffine(images[i], fusedImages[i], affine
	}
}

