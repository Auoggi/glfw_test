# Learning rescources: 
# https://makefiletutorial.com
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

.PRECIOUS: %.o
.PRECIOUS: %.exe.o

BUILD_DIR := .build

CFLAGS := -g -I include
CXXFLAGS := $(CFLAGS) 
FLAGS := $(CFLAGS) $$(pkg-config --static --libs glfw3 gl)
DEPS := include/glad/glad.o $(patsubst %.cpp, %.o, $(wildcard lib/*.cpp))

$(BUILD_DIR)/%: %.o $(DEPS) $(BUILD_DIR)
	$(CXX) $< $(DEPS) -o $@ $(FLAGS)

WCC := x86_64-w64-mingw32-gcc
WCXX := x86_64-w64-mingw32-g++
WFLAGS := $(CFLAGS) ./include/GLFW/lib-mingw-w64/libglfw3.a -lopengl32 -lgdi32
WDEPS := $(DEPS:.o=.exe.o)

$(BUILD_DIR)/%.exe: %.exe.o $(WDEPS) $(BUILD_DIR) 
	$(WCXX) $< $(WDEPS) -o $@ $(WFLAGS)

%.exe.o: %.c
	$(WCC) -c $(CFLAGS) $^ -o $@

%.exe.o: %.cpp
	$(WCXX) -c $(CXXFLAGS) $^ -o $@
	
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

MAIN_FILE := texture_gl

.PHONY: run
run: $(BUILD_DIR)/$(MAIN_FILE)
	$<

.PHONY: build
build: $(BUILD_DIR)/$(MAIN_FILE) $(BUILD_DIR)/$(MAIN_FILE).exe

.PHONY: clean
clean:
	rm -f $(shell fdfind -I -e o)
	rm -rf $(BUILD_DIR)