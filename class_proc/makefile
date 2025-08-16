CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I../medida_clases

all: proc_apuntadores_class proc_valores_class


proc_apuntadores_class: proc_apuntadores_class.o ../medida_clases/generador.o ../medida_clases/monitor.o ../medida_clases/persona.o
	$(CXX) $(CXXFLAGS) $^ -o $@

proc_valores_class: proc_valores_class.o ../medida_clases/generador.o ../medida_clases/monitor.o ../medida_clases/persona.o
	$(CXX) $(CXXFLAGS) $^ -o $@
../medida_clases/persona.o: ../medida_clases/persona.cpp ../medida_clases/persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

proc_apuntadores_class.o: proc_apuntadores_class.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

proc_valores_class.o: proc_valores_class.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../medida_clases/generador.o: ../medida_clases/generador.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../medida_clases/monitor.o: ../medida_clases/monitor.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o ../medida_clases/*.o proc_apuntadores_class proc_valores_class
