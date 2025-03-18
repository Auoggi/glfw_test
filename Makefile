BUILD_DIR := .build

CFLAGS := -I include
CXXFLAGS := -g $$(pkg-config --cflags glfw3) $(CFLAGS) 
GLFW_LIBS := $$(pkg-config --static --libs glfw3) -lGL 
DEPS := include/glad/glad.o $(patsubst %.cpp, %.o, $(wildcard lib/*.cpp))

$(BUILD_DIR)/texture_gl: $(BUILD_DIR) texture_gl.o $(DEPS)
	$(CXX) $(CXXFLAGS) texture_gl.o $(DEPS) -o $@ $(GLFW_LIBS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# texture_gl.o: texture_gl.cpp
# 	$(CXX) -c $(CXXFLAGS) $^ -o $@ -I include $(GLFW_LIBS)

.PHONY: run
run: texture_gl
	./$<

# .PHONY: build
# build: texture_gl texture_gl.exe

.PHONY: clean
clean:
	rm -f $(shell fdfind -e o)
	rm -rf $(BUILD_DIR)