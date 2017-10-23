/*
Svetleen Guerrier
Ioannis Stamos
Fall 2017

// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.
*/
#include "image.h"
#include <cstdio>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

namespace ComputerVisionProjects {

Image::Image(const Image &an_image)
{
  AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
  SetNumberGrayLevels(an_image.num_gray_levels());

  for (size_t i = 0; i < num_rows(); ++i)
    for (size_t j = 0; j < num_columns(); ++j){
      SetPixel(i,j, an_image.GetPixel(i,j));
    }
}

Image::~Image(){
  DeallocateSpace();
}

void
Image::AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns) {
  if (pixels_ != nullptr) DeallocateSpace();
  pixels_ = new int*[num_rows];
  for (size_t i = 0; i < num_rows; ++i)
    pixels_[i] = new int[num_columns];

  num_rows_ = num_rows;
  num_columns_ = num_columns;
}
//Counts the different labels in the object and puts them in a vector.
void Image::Object_labels()
{
  int count = 0;
  vector<int> Objects;
  bool done = false;

  for(size_t i= 0; i < num_rows();++i)
  {
    for(size_t j = 0; j<num_columns();++j)
    {
      const int pixel = GetPixel(i,j);
      if(!(pixel==0))
      {
        for(int a = 0; a < Objects.size(); a++ )
        {
          if(pixel==Objects[a])
          {
            done = true;
          }
        }

        if(done==false)
        {
          count++;
          Objects.push_back(pixel);
        }
      }

      done = false;
    }
  }

  ObjectData.resize(count);

  for(int i = 0; i < Objects.size();i++)
  {
    ObjectData[i].push_back(Objects[i]);
  }

}
//Finds the center of each Object and returns a temp vector.
vector<int> Image::Center(int ObjectPixel)
{

  int count = 0;
  int tempx = 0;
  int tempy = 0;
  int x = 0;
  int y = 0;

  for(size_t i= 0; i < num_rows();++i)
  {
    for(size_t j = 0; j< num_columns();++j)
    {
      const int pixel = GetPixel(i,j);
      if(pixel==ObjectPixel)
      {
        ++count;
        tempx += i;
        tempy += j;
      }

    }

  }

  x = (tempx/(double)count);
  y = (tempy/(double)count);

  vector<int>CenterValues;
  CenterValues.push_back(x);
  CenterValues.push_back(y);
  CenterValues.push_back(count);
  return CenterValues;

}
//Finds the Minimum inertia and puts it in a minimum inertia array.
void Image::minimuminertia(double theta, int long long A, int long long B, int long long C, int index)
{
  const double PI = atan(1.0)*4;
  int long long E = (A*pow(sin(theta),2))-(B*sin(theta)*cos(theta))+(C*pow(cos(theta),2));
  MinimumInertia[index] = E;
}

//Finds the Objects Orientation and returns the degree in radians.
void Image::Orietation(int ObjectPixel, int index)
{
  int long long a = 0;
  int long long b = 0;
  int long long c = 0;
  int centerx = 0;
  int centery = 0;
  int long long xprime = 0;
  int long long yprime = 0;

  for(int i=0; i<ObjectData.size();i++)
  {
    if(ObjectData[i].at(0)==ObjectPixel)
    {
      centerx = ObjectData[i].at(1);
      centery = ObjectData[i].at(2);
      break;
    }
  }
  for (size_t i = 0; i < num_rows(); ++i)
  {
    for (size_t j = 0; j < num_columns(); ++j)
    {
      const int pixel = GetPixel(i,j);
      if((pixel==ObjectPixel))
      {
        xprime = i-centerx;
        yprime = j-centery;

        a += pow(xprime,2);
        b += 2*(xprime*yprime);
        c += pow(yprime,2);
      }
    }
  }
  double theta = (atan2(b,a-c)/2);
  Angle[index] = theta;
  minimuminertia(theta,a,b,c,index);

}
//Compares the values in the database and the Image and finds whether they match. If so put in Common
//Objects vector.
void Image::CompareValues(int Area1, int long long MI)
{

  for(int i =0; i<ObjectData.size();i++)
  {
    int CompareArea = ObjectData[i].at(3);
    int long long CompareMI = MinimumInertia[i];
    if((Area1 <= CompareArea+700) and (Area1 >= CompareArea-700))
    {
      if((MI <= CompareMI+300000) and (MI>=CompareMI-300000))
      {
        CommonObjects.push_back(ObjectData[i]);
        break;
      }
    }
  }
}
//Labels the recognized objects.
void Image::RecognizedObjects()
{
  bool set = false;

  for(size_t i = 0; i<num_rows();i++)
  {
    for(size_t j = 0; j<num_columns();j++)
    {
      int Pixel = GetPixel(i,j);
      if(!(Pixel==0))
      {
        for(int a = 0; a < CommonObjects.size();a++)
        {
          if(Pixel ==CommonObjects[a].at(0))
          {
            set =true;
            break;
          }
        }
        if(set == false)
          SetPixel(i,j,0);
      }
      set = false;
    }
  }
}
//Finds all the required information for each labeled object.
vector<vector<int>>& Image::DatabaseHeadquarters()
{
  //Puts labels on each object in the graph.
  Object_labels();

  //Finds center values for each object.
  //Then Orientation.
  //Then MinimumInertia.
  for(int i = 0; i < ObjectData.size();i++)
  {
    int pixelfind = ObjectData[i].at(0);
    vector<int>center = Center(pixelfind);
    for(int a = 0; a < center.size();a++)
    {
      ObjectData[i].push_back(center[a]);
    }
    if(ObjectData[i].at(3) < 200)
    {
      continue;
    }
    SetPixel(center[0],center[1],255);
    SetPixel(center[0],center[1]+1,255);
    SetPixel(center[0],center[1]-1,255);
    SetPixel(center[0]-1,center[1],255);
    SetPixel(center[0]+1,center[1],255);
    Orietation(pixelfind, i);
  }

  return ObjectData;
}
//Converts Image to a binary Image
void Image::BinaryConversion(size_t threshold)
{
  for (size_t i = 0; i < num_rows(); ++i)
  {
    for (size_t j = 0; j < num_columns(); ++j)
    {
      const int pixel = GetPixel(i,j);
      if(pixel < threshold)
      {
        SetPixel(i,j,0);
      }
      else
      {
        SetPixel(i,j,255);
      }

    }
  }
}
//Sequential Algoritm Part 1.
void Image::GrowingAlgorithm()
{
  int label = 15;

  for(int i = 0; i < 25000; i++)
  {
      s[i] = -1;
  }
  for(size_t i= 1; i < num_rows();++i)
  {
    for(size_t j = 1; j<num_columns();++j)
    {
      const int pixel = GetPixel(i,j);
      if(pixel==255)
      {
        int West = GetPixel(i-1,j);
        int North = GetPixel(i,j-1);
        if(!(West==0) and !(North==0))
        {
          if(!(West==North))
          {
            int lesser = min(North,West);
            int larger = max(North,West);
            SetPixel(i,j,lesser);
            unionSets(lesser,larger);
          }
          else
            SetPixel(i,j,West);

        }
        else if (!(West==0))
          SetPixel(i,j,West);

        else if(!(North==0))
          SetPixel(i,j,North);

        else
        {
          SetPixel(i,j,label);
          label+=13;
        }

      }
    }
  }
}
//Sequential Algorithm Part 2.
void Image::SecondPass()
{

  for(size_t i= 1; i < num_rows();++i)
  {
    for(size_t j = 1; j<num_columns();++j)
    {

      const int pixel = GetPixel(i,j);
      if(!(pixel==0))
      {
        int root = find(pixel);
        SetPixel(i,j,root);
      }

    }
  }

}
//Used for second Pass for children of common Pixels.
int Image::find(int x)
{
  if(s[x] < 0)
    return x;
  else
    return find(s[x]);
}
//Used for Second Pass for children of Common Pixels.
void Image::unionSets(int root1, int root2)
{
  s[root2] = root1;
}

//Used for Binary Imaging
void ModifyImage(Image& an_image)
{
  an_image.BinaryConversion(110);

}
//Labels Image.
void LabelImage(Image& an_image)
{
  an_image.GrowingAlgorithm();
  an_image.SecondPass();
}

void Image::DeallocateSpace() {
  for (size_t i = 0; i < num_rows_; i++)
    delete pixels_[i];
  delete pixels_;
  pixels_ = nullptr;
  num_rows_ = 0;
  num_columns_ = 0;
}

bool ReadImage(const string &filename, Image *an_image) {
  if (an_image == nullptr) abort();
  FILE *input = fopen(filename.c_str(),"rb");
  if (input == 0) {
    cout << "ReadImage: Cannot open file" << endl;
    return false;
  }

  // Check for the right "magic number".
  char line[1024];
  if (fread(line, 1, 3, input) != 3 || strncmp(line,"P5\n",3)) {
    fclose(input);
    cout << "ReadImage: Expected .pgm file" << endl;
    return false;
  }

  // Skip comments.
  do
    fgets(line, sizeof line, input);
  while(*line == '#');

  // Read the width and height.
  int num_columns,num_rows;
  sscanf(line,"%d %d\n", &num_columns, &num_rows);
  an_image->AllocateSpaceAndSetSize(num_rows, num_columns);


  // Read # of gray levels.
  fgets(line, sizeof line, input);
  int levels;
  sscanf(line,"%d\n", &levels);
  an_image->SetNumberGrayLevels(levels);

  // read pixel row by row.
  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0;j < num_columns; ++j)
    {
      const int byte=fgetc(input);
      if (byte == EOF)
      {
        fclose(input);
        cout << "ReadImage: short file" << endl;
        return false;
      }
      an_image->SetPixel(i, j, byte);
    }
  }

  fclose(input);
  return true;
}

bool WriteImage(const string &filename, const Image &an_image) {
  FILE *output = fopen(filename.c_str(), "w");
  if (output == 0) {
    cout << "WriteImage: cannot open file" << endl;
    return false;
  }
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();

  // Write the header.
  fprintf(output, "P5\n"); // Magic number.
  fprintf(output, "#\n");  // Empty comment.
  fprintf(output, "%d %d\n%03d\n", num_columns, num_rows, colors);

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_columns; ++j) {
      const int byte = an_image.GetPixel(i , j);
      if (fputc(byte,output) == EOF) {
	    fclose(output);
            cout << "WriteImage: could not write" << endl;
	    return false;
      }
    }
  }

  fclose(output);
  return true;
}

// Implements the Bresenham's incremental midpoint algorithm;
// (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
// "Computer Graphics. Principles and practice",
// 2nd ed., 1990, section 3.2.2);
void
DrawLine(int x0, int y0, int x1, int y1, int color,
	 Image *an_image)
{
  if (an_image == nullptr) abort();

#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a,b) {a^=b; b^=a; a^=b;}

  const int DIR_X = 0;
  const int DIR_Y = 1;

  // Increments: East, North-East, South, South-East, North.
  int incrE,
    incrNE,
    incrS,
    incrSE,
    incrN;
  int d;         /* the D */
  int x,y;       /* running coordinates */
  int mpCase;    /* midpoint algorithm's case */
  int done;      /* set to 1 when done */

  int xmin = x0;
  int xmax = x1;
  int ymin = y0;
  int ymax = y1;

  int dx = xmax - xmin;
  int dy = ymax - ymin;
  int dir;

  if (dx * dx > dy * dy) {  // Horizontal scan.
    dir=DIR_X;
    if (xmax < xmin) {
      SWAP(xmin, xmax);
      SWAP(ymin , ymax);
    }
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dy >= 0) {
      mpCase = 1;
      d = 2 * dy - dx;
    } else {
      mpCase = 2;
      d = 2 * dy + dx;
    }

    incrNE = 2 * (dy - dx);
    incrE = 2 * dy;
    incrSE = 2 * (dy + dx);
  } else {// vertical scan.
    dir = DIR_Y;
    if (ymax < ymin) {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax-ymin;

    if (dx >=0 ) {
      mpCase = 1;
      d = 2 * dx - dy;
    } else {
      mpCase = 2;
      d = 2 * dx + dy;
    }

    incrNE = 2 * (dx - dy);
    incrE = 2 * dx;
    incrSE = 2 * (dx + dy);
  }

  /// Start the scan.
  x = xmin;
  y = ymin;
  done = 0;

  while (!done) {
    an_image->SetPixel(x,y,color);

    // Move to the next point.
    switch(dir) {
    case DIR_X:
      if (x < xmax) {
	      switch(mpCase) {
	      case 1:
		if (d <= 0) {
		  d += incrE;
		  x++;
		} else {
		  d += incrNE;
		  x++;
		  y++;
		}
		break;

            case 2:
              if (d <= 0) {
                d += incrSE;
		x++;
		y--;
              } else {
                d += incrE;
		x++;
              }
	      break;
	      }
      } else {
	done=1;
      }
      break;

    case DIR_Y:
        if (y < ymax) {
          switch(mpCase) {
	  case 1:
	    if (d <= 0) {
	      d += incrE;
	      y++;
	    } else {
	      d += incrNE;
	      y++;
	      x++;
	    }
            break;

	  case 2:
	    if (d <= 0) {
                d += incrSE;
		y++;
		x--;
              } else {
                d += incrE;
		y++;
	    }
            break;
	  } // mpCase
        } // y < ymin
        else {
	  done=1;
	}
	break;
    }
  }
}

}  // namespace ComputerVisionProjects
