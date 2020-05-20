
XX = g++
TARGET = threadpool

%.o:%.cpp
	$(XX) -std=c++11 -g -c $< -o $@ 

SOURCE = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SOURCE))

$(TARGET):$(OBJS)
	$(XX) -std=c++11 -g $(OBJS) -o $(TARGET) -lpthread

clean:
	rm -rf *.o threadpool
