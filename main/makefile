CC = g++
CFLAGS = -std=c++17
LIBS = `pkg-config --cflags --libs opencv4`
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

$(BUILD_DIR)/fullBuild: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(BUILD_DIR)/fullBuild