CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I../medida_estructura

all: proc_apuntadores_struct proc_valores_struct

proc_apuntadores_struct: proc_apuntadores_struct.o ../medida_estructura/generador.o ../medida_estructura/monitor.o
	$(CXX) $(CXXFLAGS) $^ -o $@

proc_valores_struct: proc_valores_struct.o ../medida_estructura/generador.o ../medida_estructura/monitor.o
	$(CXX) $(CXXFLAGS) $^ -o $@

proc_apuntadores_struct.o: proc_apuntadores_struct.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

proc_valores_struct.o: proc_valores_struct.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../medida_estructura/generador.o: ../medida_estructura/generador.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../medida_estructura/monitor.o: ../medida_estructura/monitor.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o ../medida_estructura/*.o proc_apuntadores_struct proc_valores_struct
