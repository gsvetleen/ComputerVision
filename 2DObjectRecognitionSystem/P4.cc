/*
Svetleen Guerrier
Computer Vision
Ioannis Stamos
Fall 2017

Program 4->Object Recognition

*/

#include "image.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv)
{
  const double PI = atan(1.0)*4;

  if (argc!=4)
  {
    printf("Usage: %s file1 file2 file3\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_file, &an_image))
  {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  //Gets the required data from image.
  vector<vector<int>> Common;
  Common = an_image.DatabaseHeadquarters();

  //Opens database file.
  ifstream Datafile;
  Datafile.open(argv[2]);
  if(Datafile.is_open())
    cout<<"Database file opened."<<endl;
  else
  {
    cout<<"Error opening file."<<endl;
    exit(1);
  }
  //Gets the data within the database file.
  string line;
  int ImageValue;
  int ObjectNum;
  int CenterX;
  int CenterY;
  int Area;
  double  Orientation;
  int long long MinimumInertia;

  getline(Datafile,line);
  while(!(Datafile.eof()))
  {
    Datafile>>line;
    Datafile>>ImageValue;
    Datafile>>CenterX;
    Datafile>>CenterY;
    Datafile>>Area;
    Datafile>>Orientation;
    Datafile>>MinimumInertia;
    //Compares values in the database and in the image.
    an_image.CompareValues(Area, MinimumInertia);
  }
  //Formulates the recognized values.
  an_image.RecognizedObjects();

  //Returns the Objects that are recognized.
  Common = an_image.ReturnCommonVector();

  double* AngleData = an_image.AngleReturn();
  int long long* MinInertaData = an_image.MinimumInertiaReturn();

  //Draws the Orientation line starting from the position.
  for(int i = 0; i<Common.size();i++)
  {
    double theta = AngleData[i];
    int CenterX = Common[i].at(1);
    int CenterY = Common[i].at(2);
    int ToX = (CenterX + (25*sin(theta))+0.5);
    int ToY = (CenterY + (25*cos(theta))+0.5);
    DrawLine(CenterX,CenterY,ToX,ToY, 255,&an_image);
  }
  //Writes back Image.
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }


  return 0;
}
