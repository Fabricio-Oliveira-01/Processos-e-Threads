CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = gerador
OBJECTS = geradorMatriz.o criarMatrizes.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean