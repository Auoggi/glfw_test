# Learning rescources: 
# https://makefiletutorial.com
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

BUILD_DIR := .build

CFLAGS := -g -I include
CXXFLAGS := $(CFLAGS) 
GLFW_LIBS := $$(pkg-config --static --libs glfw3 gl)
WIN_LIBS := $(CFLAGS) ./include/GLFW/lib-mingw-w64/libglfw3.a -lopengl32 -lgdi32
DEPS := include/glad/glad.o $(patsubst %.cpp, %.o, $(wildcard lib/*.cpp))

$(BUILD_DIR)/texture_gl: $(BUILD_DIR) texture_gl.o $(DEPS)
	$(CXX) $(CXXFLAGS) texture_gl.o $(DEPS) -o $@ $(GLFW_LIBS)

$(BUILD_DIR)/texture_gl.exe: $(BUILD_DIR) texture_gl.exe.o $(DEPS:.o=.exe.o)
	x86_64-w64-mingw32-g++ texture_gl.exe.o $(DEPS:.o=.exe.o) -o $@ $(WIN_LIBS)

./include/glad/glad.exe.o: ./include/glad/glad.c
	x86_64-w64-mingw32-gcc -c $^ -o $@ $(CFLAGS)

%.exe.o: %.cpp
	x86_64-w64-mingw32-g++ -c $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: run
run: $(BUILD_DIR)/texture_gl
	$<

.PHONY: build
build: $(BUILD_DIR)/texture_gl $(BUILD_DIR)/texture_gl.exe

.PHONY: clean
clean:
	rm -f $(shell fdfind -I -e o)
	rm -rf $(BUILD_DIR)