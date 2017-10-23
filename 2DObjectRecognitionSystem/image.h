// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.

#ifndef COMPUTER_VISION_IMAGE_H_
#define COMPUTER_VISION_IMAGE_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <list>

namespace ComputerVisionProjects {

// Class for representing a gray-scale image.
// Sample usage:
//   Image one_image;
//   one_image.AllocateSpaceAndSetSize(100, 200);
//   one_image.SetNumberGrayLevels(255);
//   // Creates and image such that each pixel is 150.
//   for (int i = 0; i < 100; ++i)
//     for (int j = 0; j < 200; ++j)
//       one_image.SetPixel(i, j, 150);
//   WriteImage("output_file.pgm", an_image);
//   // See image_demo.cc for read/write image.
class Image {
 public:
  Image(): num_rows_{0}, num_columns_{0},
	   num_gray_levels_{0}, pixels_{nullptr} { }

  Image(const Image &an_image);
  Image& operator=(const Image &an_image) = delete;

  ~Image();

  // Sets the size of the image to the given
  // height (num_rows) and columns (num_columns).
  void AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns);

  size_t num_rows() const { return num_rows_; }
  size_t num_columns() const { return num_columns_; }
  size_t num_gray_levels() const { return num_gray_levels_; }
  void SetNumberGrayLevels(size_t gray_levels) {
    num_gray_levels_ = gray_levels;
  }

  // Sets the pixel in the image at row i and column j
  // to a particular gray_level.
  void SetPixel(size_t i, size_t j, int gray_level) {
    if (i >= num_rows_ || j >= num_columns_) abort();
    pixels_[i][j] = gray_level;
  }

  int GetPixel(size_t i, size_t j) const {
    if (i >= num_rows_ || j >= num_columns_) abort();
    return pixels_[i][j];
  }
  //Sets image to Binary.
  void BinaryConversion(size_t threshold);
  //Sequential Algorithm part 1
  void GrowingAlgorithm();
  //Sequntial Algorithm Part 2
  void SecondPass();
  //Compares values from Image to Database
  void CompareValues(int Area1, int long long MI);
  //Union-find Algorithm for Sequntial Labeling
  void unionSets(int root1, int root2);
  //Union-find algorithm for Sequential Labeling
  int find( int x);
  //Sections each individual Object in Image.
  void Object_labels();
  //Finds center for each image.
  std::vector<int> Center(int ObjectPixel);

  //Return Orientation array
  double * AngleReturn(){
    return Angle;
  }
  //Return Common vector array.
  std::vector<std::vector<int>> ReturnCommonVector(){
    return CommonObjects;
  }
  //Returns arrays with Minimum Inertia.
  int long long * MinimumInertiaReturn(){
    return MinimumInertia;
  }
  //Calculates Minimum Inertia.
  void minimuminertia(double theta, int long long A, int long long B, int long long C, int index);
  //Orientation angle.
  void Orietation(int ObjectPixel, int index);
  std::vector<std::vector<int>>& DatabaseHeadquarters();
  //Labels recognized objects
  void RecognizedObjects();

 private:
  std::vector<std::vector<int>>ObjectData;
  std::vector<std::vector<int>> CommonObjects;
  double Angle [50];
  int long long MinimumInertia [50];
  void DeallocateSpace();
  int s[25000];
  size_t num_rows_;
  size_t num_columns_;
  size_t num_gray_levels_;
  int **pixels_;
};

// Reads a pgm image from file input_filename.
// an_image is the resulting image.
// Returns true if  everyhing is OK, false otherwise.
bool ReadImage(const std::string &input_filename, Image *an_image);

// Writes image an_iamge into the pgm file output_filename.
// Returns true if  everyhing is OK, false otherwise.
bool WriteImage(const std::string &output_filename, const Image &an_image);

//  Draws a line of given gray-level color from (x0,y0) to (x1,y1);
//  an_image is the output_image.
// IMPORTANT: (x0,y0) and (x1,y1) can lie outside the image
//   boundaries, so SetPixel() should check the coordinates passed to it.
void DrawLine(int x0, int y0, int x1, int y1, int color,
	      Image *an_image);

void LabelImage(Image& an_image);
void ModifyImage(Image& an_image);

}  // namespace ComputerVisionProjects

#endif  // COMPUTER_VISION_IMAGE_H_
