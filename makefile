# All Targets
all: cyber

# Tool invocations
cyber: bin/Run.o bin/cyberpc.o bin/cyberworm.o bin/cyberexpert.o bin/cyberdns.o
	g++ -o bin/cyber bin/Run.o bin/cyberpc.o bin/cyberworm.o bin/cyberexpert.o bin/cyberdns.o
	
# Depends on the source and header files
bin/cyberpc.o: src/cyberpc.cpp
	g++ -g -Wall -c -Linclude -o bin/cyberpc.o src/cyberpc.cpp
	
	# Depends on the source and header files
bin/cyberworm.o: src/cyberworm.cpp
	g++ -g -Wall -c -Linclude -o bin/cyberworm.o src/cyberworm.cpp
	
	# Depends on the source and header files
bin/cyberexpert.o: src/cyberexpert.cpp
	g++ -g -Wall -c -Linclude -o bin/cyberexpert.o src/cyberexpert.cpp

		# Depends on the source and header files
bin/cyberdns.o: src/cyberdns.cpp
	g++ -g -Wall -c -Linclude -o bin/cyberdns.o src/cyberdns.cpp
	
# Depends on the source and header files 
bin/Run.o: src/Run.cpp
	g++ -g -Wall -c -Linclude -I/usr/local/boost/1.57.0/include/boost -o bin/Run.o src/Run.cpp
	
#Clean the build directory
clean: 
	rm -f bin/*