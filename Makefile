# Learning rescources: 
# https://makefiletutorial.com
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

# .PRECIOUS: %.o
# .PRECIOUS: %.exe.o

LIB_DIR := lib
BUILD_DIR := .build
MAIN_FILE := texture_gl

CXXFLAGS := -g -I include
WFLAGS := $(CXXFLAGS) ./include/GLFW/lib-mingw-w64/libglfw3.a -lopengl32 -lgdi32
FLAGS := $(CXXFLAGS) $$(pkg-config --static --libs glfw3 gl)
DEPS := include/glad/glad.o $(patsubst %.cpp, %.o, $(shell fdfind -e cpp . $(LIB_DIR)))
CXX := g++

%.exe %.exe.o: CXX := x86_64-w64-mingw32-g++

$(BUILD_DIR)/%: $(BUILD_DIR) %.o $(DEPS)
	$(CXX) $(filter-out $(BUILD_DIR), $^) -o $@ $(FLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.exe: $(BUILD_DIR) %.exe.o $(DEPS:.o=.exe.o) 
	$(CXX) $(filter-out $(BUILD_DIR), $^) -o $@ $(WFLAGS)

%.exe.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@
	
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: run
run: $(BUILD_DIR)/$(MAIN_FILE)
	$<

.PHONY: build
build: 
	$(MAKE) $(BUILD_DIR)/$(MAIN_FILE)
	$(MAKE) $(BUILD_DIR)/$(MAIN_FILE).exe

.PHONY: clean
clean:
	rm -f $(shell fdfind -I -e o)
	rm -rf $(BUILD_DIR)