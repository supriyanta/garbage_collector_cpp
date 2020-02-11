gc: Iter.o GCInfo.o GCPtr.o
	g++ Iter.o GCInfo.o GCPtr.o main3.cpp -o gc

GCPtr.o: GCPtr.cpp
	g++ -c GCPtr.cpp

GCInfo.o: GCInfo.cpp
	g++ -c GCInfo.cpp

Iter.o: Iter.cpp
	g++ -c Iter.cpp

clean:
	rm *.o