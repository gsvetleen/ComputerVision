
Svetleen Guerrier 
Project 1 ReadME File


This is the basic 2D object recognition program divided into 4 parts. The first part changes the image into a binary image. The second part uses a sequential labeling algorithm. Third part creates a debase of each object in the image and labels the Image. Final part outputs image of objects related to each other. 

The Images in this file pertain to the outputs and what was originally given.
 
*****************************
Original Image Files: two_objects.pgm     many_objects_1.pgm     many_objects_2.pgm
*******************************




P1->Binary Image Converter
->>> Output Files: Binary_1.pgm    Binary_2.pgm      binary_two.pgm

TO RUN————>>>>> ./Program1 Filename outputfilename







P2->Sequential Labeling Algorithm INPUT MUST BE A BINARY FILE!!!
->>>>>>Output files: Labeled_1.pgm    Labeled_2.pgm     labeled_two.pgm

->>To Run ->>>>>> ./Program2 BinaryFileName outputfileName








P3->Image Database INPUT MUST BE A LABELED IMAGE!!!!!
->>>Output files: Draw_1.pgm      Draw_2.pgm      Draw_two.pgm      Database.txt Data1.txt data2.txt

->>To Run ->>>> ./Program3 LabeledImageFile OutPutdatabaseName.txt Outputfilename







P4->Object Recognition 
->>>OutPut files: output.pgm 
->>>>To Run ——>>>>> ./Program4 labeledImagefile Databasefile.txt outputimagefile
