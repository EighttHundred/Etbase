CC = g++
PTHREAD = -pthread -std=c++11
VPATH = base net test
PRONAME = Etbase
OBJECTS = log.o mutex.o thread.o threadpool.o \
			epoller.o socket.o tcpclient.o tcpserver.o \
			test.o 
$(PRONAME) : $(OBJECTS)
	$(CC) -o $(PRONAME) $(OBJECTS) $(PTHREAD)
thread.o : mutex.h
threadpool.o : mutex.h thread.h
socket.o : log.h
epoller.o : threadpool.h
clean :
	rm -rf $(PRONAME) $(OBJECTS)