#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <boost/program_options.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <vector>
#include <string>

namespace po = boost::program_options;

// In the Stitching_Grid.java plugin,
// Snake-by-rows is grid type 2

enum class GridType { GridRowByRow, GridRowByColumn, GridSnakeByRow, GridSnakeByColumn};

std::vector<cv::Mat> getGridLayout(GridType, int, int, double, double, std::string&, std::string&, int, int, int);

struct StitchingParameters {
	StitchingParameters() = default;

	double tileOverlapX;
	double tileOverlapY;
	double regressionThreshold;
	double maxDisplacementThreshold;
	double absoluteDisplacmentThreshold;

	int gridSizeX;
	int gridSizeY;
	int sequenceRange;
	int dimensionality;

	bool computeOverlap;

	GridType gridType;
};

std::vector<cv::Mat> stitchCollection(cv::InputArray, const StitchingParameters);

int main(int argc, char** argv) {

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "Show this help message")
		("imagedir", po::value<std::string>(), "Directory to use")
		("filepattern", po::value<std::string>(), "Filename pattern to use")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	// The most important options have been preserved

	int gridSizeX = 3, gridSizeY = 3;
	const double TILE_OVERLAP_X = 0.10;
	const double TILE_OVERLAP_Y = 0.10;
	const double REGRESSION_THRESHOLD = 0.30;
	const double MAX_DISPLACEMENT_THRESHOLD = 2.50;
	const double ABSOLUTE_DISPLACEMENT_THRESHOLD = 3.50;

	// maps to defaultComputeOverlap
	const bool COMPUTER_OVERLAP = true;

	// set this to define how many adjacent images each image will be compared to
	int defaultSequenceRange = 1;

	// This is just going to be hardcoded for now because
	// we're only dealing with 2 dimensional imagery for now
	int dimensionality = 2;

	auto imageDir = vm["imagedir"].as<std::string>();
	auto filepattern = vm["filepattern"].as<std::string>();

	// load all images into the data set
	std::vector<cv::Mat> baseMats = getGridLayout(GridType::GridSnakeByRow,
												  gridSizeX, gridSizeY,
												  TILE_OVERLAP_X, TILE_OVERLAP_Y,
												  imageDir, filepattern,
												  1, 1, 1);

	std::cout << baseMats.size();

	if (baseMats.size() < 2)
	{
		std::cout << boost::format("Found %1% images, but at least 2 are required to stitch. Exiting.\n") % baseMats.size();
		return 2;
	}

	// TODO insert the code to load all the mats into the data

	// this thing will be passed a collection of images and then it will be passed
	// various configurations like the orientation and grid size.

	// The orientation and grid size (2x2, 3x3, 4x4, etc.) determine how to
	// correctly align the imagery

	// Now do the full stitching



}

std::vector<cv::Mat> getGridLayout(GridType type, int gridSizeX, int gridSizeY, double overlapX, double overlapY,
									std::string& directory, std::string& filenames, int startI, int startX, int startY)
{
	// TODO also have to downsample these images with pyramid down
	// if the option is set
	return std::vector<cv::Mat>();
}