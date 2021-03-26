HOME = ./

# WINDOWS WSL PYTHON DIR
# MACOS PYTHON DIR
# PYTHON_DIR =/usr/local/Frameworks/Python.framework/Versions/3.9/include/python3.9

CXX=clang++
CXXFLAGS = -std=c++17
odir = ./o

$(odir)/%.o:%.cpp GNUmakefile
	mkdir -p $(odir);$(CXX) -c $(CXXFLAGS) $< -o $@
	mkdir -p $(ddir);$(CXX) -MM $(CXXFLAGS) $< | sed '1s/^/o\//' > $*.d;mv $*.d $(ddir)

particles1D: GNUmakefile main.cpp util.cpp w.cpp
	$(CXX) main.cpp util.cpp w.cpp $(CXXFLAGS) -o particles1D.exe

clean:
	rm *.exe *.curve 
