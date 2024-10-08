#################################
#### 	PROJ 3 MAKEFILE    	#####
#################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 



gerp: gerp1.o main.o DirNode.o FSTree.o stringProcessing.o
	$(CXX) $(CXXFLAGS) -O3 -o gerp gerp1.o main.o DirNode.o FSTree.o stringProcessing.o

treeTraversal: FSTreeTraversal.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o treeTraversal FSTreeTraversal.o DirNode.o FSTree.o

stringProcessing.o: stringProcessing.h stringProcessing.cpp 
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp 

unit_test: unit_test_driver.o stringProcessing.o gerp.o DirNode.o FSTree.o stringProcessing.o
	$(CXX) $(CXXFLAGS) $^