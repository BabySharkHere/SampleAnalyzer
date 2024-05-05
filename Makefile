SRCPREFIX = src/
install: 
	g++ $(SRCPREFIX)main.cpp $(SRCPREFIX)empiricFunction.cpp $(SRCPREFIX)histogram.cpp $(SRCPREFIX)calculating.cpp -o main.exe
