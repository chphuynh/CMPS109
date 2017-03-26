G++ = g++

PROBLEM1 = problem1/problem1.cpp problem1/CardReader.cpp
P1TARGET = problem1.out
PROBLEM2 = problem2/problem2.cpp problem2/ScanningDevice.cpp
P2TARGET = problem2.out
PROBLEM3 = problem3/problem3.cpp problem3/Heap.cpp
P3TARGET = problem3.out


all: $(P1TARGET) $(P2TARGET) $(P3TARGET)

problem1: $(P1TARGET)

problem2: $(P2TARGET)

problem3: $(P3TARGET)

$(P1TARGET): $(PROBLEM1)
	$(G++) -o $(P1TARGET) $(PROBLEM1)

$(P2TARGET): $(PROBLEM2)
	$(G++) -o $(P2TARGET) $(PROBLEM2)

$(P3TARGET): $(PROBLEM3)
	$(G++) -o $(P3TARGET) $(PROBLEM3)

clean:
	rm $(P1TARGET) $(P2TARGET) $(P3TARGET)