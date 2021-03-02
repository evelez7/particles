HOME = ./
MATPLOTLIB = $(HOME)matplotlib-cpp

# WINDOWS WSL PYTHON DIR
# PYTHON_DIR = /usr/include/python2.7
# MACOS PYTHON DIR
PYTHON_DIR = /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

CXX=g++
CXXFLAGS = -std=c++11 -I$(PYTHON_DIR) -I$(MATPLOTLIB)  -lpython2.7
odir = ./o

$(odir)/%.o:%.cpp GNUmakefile
	mkdir -p $(odir);$(CXX) -c $(CXXFLAGS) $< -o $@
	mkdir -p $(ddir);$(CXX) -MM $(CXXFLAGS) $< | sed '1s/^/o\//' > $*.d;mv $*.d $(ddir)

particles1D: GNUmakefile main.cpp util.cpp w.cpp
	$(CXX) main.cpp util.cpp w.cpp $(CXXFLAGS) -o particles1D.exe