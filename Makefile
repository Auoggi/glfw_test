CFLAGS := -I include
CXXFLAGS := -g $$(pkg-config --cflags glfw3) $(CFLAGS) 
GLFW_LIBS := $$(pkg-config --static --libs glfw3) -lGL 
LIB_FILES := $(wildcard lib/*.cpp)

texture_gl: texture_gl.o include/glad/glad.o $(LIB_FILES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GLFW_LIBS)

# texture_gl.o: texture_gl.cpp
# 	$(CXX) -c $(CXXFLAGS) $^ -o $@ -I include $(GLFW_LIBS)

clean:
	rm -f $(shell fdfind -e o)