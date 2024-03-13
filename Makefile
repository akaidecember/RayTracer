CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp

# Derive object file names from source files
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = ray_tracer

# Optional output file
PPM_FILE = output.ppm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) | tee $(PPM_FILE)

clean:
	rm -f $(OBJS) $(TARGET) $(PPM_FILE)
