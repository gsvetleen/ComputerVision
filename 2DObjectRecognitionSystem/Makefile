########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)

Cpp_OBJ1=image.o P1.o

PROGRAM_NAME1=Program1

$(PROGRAM_NAME1): $(Cpp_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ1) $(INCLUDES) $(LIBS_ALL)

#Second Program
Cpp_OBJ2=image.o P2.o

PROGRAM_NAME2=Program2

$(PROGRAM_NAME2): $(Cpp_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Third Program
Cpp_OBJ3=image.o P3.o

PROGRAM_NAME3=Program3

$(PROGRAM_NAME3): $(Cpp_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ3) $(INCLUDES) $(LIBS_ALL)


#Fourth Program
Cpp_OBJ4=image.o P4.o

PROGRAM_NAME4=Program4

$(PROGRAM_NAME4): $(Cpp_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ4) $(INCLUDES) $(LIBS_ALL)

all: 
	make $(PROGRAM_NAME1) 
	make $(PROGRAM_NAME2)
	make $(PROGRAM_NAME3)
	make $(PROGRAM_NAME4)

clean:
	(rm -f *.o;)

(:
