CXXFLAGS =

OBJS =	p.o s.o	

TESTOBJS= test.o p.o testrunner.o

LIBS = -lpthread  -lpqxx -llog4cpp -lpq -fpermissive


TESTLIBS =  -lcppunit  -lpthread  -lpqxx -lpq

TARGET = s

TESTTARGET = test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) 

$(TESTTARGET):	$(TESTOBJS)
	$(CXX) -o $(TESTTARGET) $(TESTOBJS) $(TESTLIBS)
	
all:	$(TARGET) $(TESTTARGET)

test: $(TESTTARGET)

app: $(TARGET)

client: 
	$(CXX) -o k k.cpp  -lpthread  -lpqxx


clean:
	rm -f $(OBJS) $(TARGET) $(TESTTARGET) $(TESTOBJS)
