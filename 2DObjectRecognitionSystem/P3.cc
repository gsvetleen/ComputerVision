/*
Svetleen Guerrier
Ioannis Stamos
Fall 2017

Program 3-> Object Database.
*/
#include "image.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
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

  int count = 1;
  vector<vector<int>> Imagedata = an_image.DatabaseHeadquarters();
  double* AngleData = an_image.AngleReturn();
  int long long* MinInertaData = an_image.MinimumInertiaReturn();

  ofstream myfile;
  myfile.open(argv[2]);
  myfile<<"Imagevalue|CenterX|CenterY|Area|Orientation|MinimumInertia"<<endl;
  for(int i = 0; i<Imagedata.size();i++)
  {
    if(Imagedata[i].at(3)<200)
      continue;
    myfile<<"Object"<<count<<endl;

    double theta = AngleData[i];
    int CenterX = Imagedata[i].at(1);
    int CenterY = Imagedata[i].at(2);
    int ToX = (CenterX + (25*sin(theta))+0.5);
    int ToY = (CenterY + (25*cos(theta))+0.5);
    DrawLine(CenterX,CenterY,ToX,ToY, 255,&an_image);
    for(int j = 0; j<Imagedata[i].size();j++)
    {
      myfile<<" "<<Imagedata[i].at(j);

    }
    myfile<<" "<<AngleData[i];
    myfile<<" "<<MinInertaData[i];
    myfile<<endl;
    count++;
  }

  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }


  return 0;
}
