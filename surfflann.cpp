#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace cv::xfeatures2d;

bool cmpfun(DMatch a, DMatch b) { return a.distance < b.distance; }

int main(int argc, char** argv) {
    std::vector<std::string> args(argv, argv + argc);

    for(auto a : args) {
        std::cout << a << "\n";
    }

    Mat base = imread(args[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat dest = imread(args[2], CV_LOAD_IMAGE_GRAYSCALE);

    // Surf detection
    int minHessian = 5000;

    Ptr<SURF> surf = SURF::create(minHessian);

    std::vector<KeyPoint> baseKeypoints, destKeypoints;

    surf->detect(base, baseKeypoints);
    surf->detect(dest, destKeypoints);

    Mat baseDescriptors, destDescriptors;

    surf->compute(base, baseKeypoints, baseDescriptors);
    surf->compute(dest, destKeypoints, destDescriptors);

    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;

    matcher.match( baseDescriptors, destDescriptors, matches);

    double max_dist = 0, min_dist = 100;

    // calculate max and min distances between keypoints
    for (int i = 0; i < baseDescriptors.rows; ++i)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    std::cout << "-- max distance: " << max_dist << "\n";
    std::cout << "-- min distance: " << min_dist << "\n";

    std::vector<DMatch> good_matches;

    std::cout << baseDescriptors.rows;

    for (int i = 0; i < baseDescriptors.rows; ++i) {
        if (matches[i].distance <= (3*min_dist))
        {
            good_matches.push_back(matches[i]);
        }   
    }

    std::sort(matches.begin(), matches.end(), cmpfun);

    Mat matchedImage;

    drawMatches(base, baseKeypoints, dest, destKeypoints,
                matches, matchedImage, Scalar::all(-1), Scalar::all(-1),
                std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    std::vector<Point2f> obj, scene;

    std::cout << "Found " << good_matches.size() << " matches\n";

    for (int i = 0; i < good_matches.size(); ++i)
    {
        obj.push_back(baseKeypoints[good_matches[i].queryIdx].pt);
        scene.push_back(destKeypoints[good_matches[i].trainIdx].pt);
    }

//Mat hTransform = findHomography(obj, scene, CV_RANSAC);

    /*std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0,0);
    obj_corners[1] = cvPoint(base.cols, 0);
    obj_corners[2] = cvPoint(base.cols, base.rows);
    obj_corners[3] = cvPoint(0, base.rows);

    std::vector<Point2f> scene_corners(4);

 //   perspectiveTransform(obj_corners, scene_corners, hTransform);

    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    line( matchedImage, scene_corners[0] + Point2f( base.cols, 0), scene_corners[1] + Point2f( base.cols, 0), Scalar(0, 255, 0), 4 );
    line( matchedImage, scene_corners[1] + Point2f( base.cols, 0), scene_corners[2] + Point2f( base.cols, 0), Scalar( 0, 255, 0), 4 );
    line( matchedImage, scene_corners[2] + Point2f( base.cols, 0), scene_corners[3] + Point2f( base.cols, 0), Scalar( 0, 255, 0), 4 );
    line( matchedImage, scene_corners[3] + Point2f( base.cols, 0), scene_corners[0] + Point2f( base.cols, 0), Scalar( 0, 255, 0), 4 );*/

    //imshow("Good Matches", matchedImage);
    //
    imwrite("cells.tif", matchedImage);

    waitKey(0); 
}
