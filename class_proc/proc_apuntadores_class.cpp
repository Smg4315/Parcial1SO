#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <map>
#include <algorithm>
#include <iomanip>
#include "../medida_clases/persona.h"
#include "../medida_clases/generador.h"
#include "../medida_clases/monitor.h"

int calcularEdad(const std::string& fechaNacimiento) {
    if (fechaNacimiento.size() < 8) return 0;
    size_t pos1 = fechaNacimiento.find('/');
    if (pos1 == std::string::npos) return 0;
    int dia = std::stoi(fechaNacimiento.substr(0, pos1));
    size_t pos2 = fechaNacimiento.find('/', pos1 + 1);
    if (pos2 == std::string::npos) return 0;
    int mes = std::stoi(fechaNacimiento.substr(pos1 + 1, pos2 - pos1 - 1));
    int anio = std::stoi(fechaNacimiento.substr(pos2 + 1));
    int diaActual = 15, mesActual = 8, anioActual = 2025;
    int edad = anioActual - anio;
    if (mesActual < mes || (mesActual == mes && diaActual < dia)) edad--;
    return edad;
}

const Persona* personaMasLongeva(const std::vector<std::unique_ptr<Persona>>& personas) {
    auto it = std::max_element(personas.begin(), personas.end(),
        [](const auto& a, const auto& b) {
            return calcularEdad(a->getFechaNacimiento()) < calcularEdad(b->getFechaNacimiento());
        });
    return it != personas.end() ? it->get() : nullptr;
}

std::map<std::string, const Persona*> personaMasLongevaPorCiudad(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<std::string, const Persona*> resultado;
    std::map<std::string, int> maxEdad;
    for (const auto& p : personas) {
        int edad = calcularEdad(p->getFechaNacimiento());
        const std::string& ciudad = p->getCiudadNacimiento();
        if (maxEdad.find(ciudad) == maxEdad.end() || edad > maxEdad[ciudad]) {
            resultado[ciudad] = p.get();
            maxEdad[ciudad] = edad;
        }
    }
    return resultado;
}

const Persona* mayorPatrimonio(const std::vector<std::unique_ptr<Persona>>& personas) {
    auto it = std::max_element(personas.begin(), personas.end(),
        [](const auto& a, const auto& b) {
            return a->getPatrimonio() < b->getPatrimonio();
        });
    return it != personas.end() ? it->get() : nullptr;
}

std::map<std::string, const Persona*> mayorPatrimonioPorCiudad(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<std::string, const Persona*> resultado;
    std::map<std::string, double> maxPatrimonio;
    for (const auto& p : personas) {
        const std::string& ciudad = p->getCiudadNacimiento();
        if (maxPatrimonio.find(ciudad) == maxPatrimonio.end() || p->getPatrimonio() > maxPatrimonio[ciudad]) {
            resultado[ciudad] = p.get();
            maxPatrimonio[ciudad] = p->getPatrimonio();
        }
    }
    return resultado;
}

std::map<char, const Persona*> mayorPatrimonioPorGrupo(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<char, const Persona*> resultado;
    std::map<char, double> maxPatrimonio;
    for (const auto& p : personas) {
        char grupo = p->getCalendario();
        if (maxPatrimonio.find(grupo) == maxPatrimonio.end() || p->getPatrimonio() > maxPatrimonio[grupo]) {
            resultado[grupo] = p.get();
            maxPatrimonio[grupo] = p->getPatrimonio();
        }
    }
    return resultado;
}

std::map<char, std::vector<const Persona*>> declarantesPorCalendario(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<char, std::vector<const Persona*>> resultado;
    for (const auto& p : personas) {
        if (p->getDeclaranteRenta()) {
            resultado[p->getCalendario()].push_back(p.get());
        }
    }
    return resultado;
}

bool validarAsignacion(const std::vector<std::unique_ptr<Persona>>& personas) {
    int incorrectos = 0;
    for (const auto& p : personas) {
        int ultimos_digitos = 0;
        if (p->getId().size() >= 2) {
            ultimos_digitos = std::stoi(p->getId().substr(p->getId().size() - 2));
        }
        char grupoCorrecto = ultimos_digitos <= 39 ? 'A' : (ultimos_digitos <= 79 ? 'B' : 'C');
        if (grupoCorrecto != p->getCalendario()) {
            std::cout << "Error: Persona ID " << p->getId() << " asignada a calendario " << p->getCalendario()
                      << " incorrecto, debería ser " << grupoCorrecto << std::endl;
            incorrectos++;
        }
    }
    return incorrectos == 0;
}

std::pair<std::string, int> ciudadMayorMenoresDe18(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<std::string, int> conteoMenores;
    for (const auto& p : personas) {
        int edad = calcularEdad(p->getFechaNacimiento());
        if (edad < 18) {
            conteoMenores[p->getCiudadResidencia()]++;
        }
    }
    int maxConteo = -1;
    std::string ciudadMax;
    for (const auto& [ciudad, count] : conteoMenores) {
        if (count > maxConteo) {
            maxConteo = count;
            ciudadMax = ciudad;
        }
    }
    return { ciudadMax, maxConteo };
}

std::map<char, double> promedioIngresosPorGrupo(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<char, double> sumaIngresos;
    std::map<char, int> conteo;
    for (const auto& p : personas) {
        sumaIngresos[p->getCalendario()] += p->getIngresosAnuales();
        conteo[p->getCalendario()]++;
    }
    std::map<char, double> promedios;
    for (const auto& [grupo, suma] : sumaIngresos) {
        promedios[grupo] = suma / conteo[grupo];
    }
    return promedios;
}

std::map<char, double> porcentajeMayores50PorCalendario(const std::vector<std::unique_ptr<Persona>>& personas) {
    std::map<char, int> totalPorGrupo;
    std::map<char, int> mayoresPorGrupo;
    for (const auto& p : personas) {
        char grupo = p->getCalendario();
        int edad = calcularEdad(p->getFechaNacimiento());
        totalPorGrupo[grupo]++;
        if (edad > 50) mayoresPorGrupo[grupo]++;
    }
    std::map<char, double> porcentaje;
    for (const auto& [grupo, total] : totalPorGrupo) {
        int mayores = mayoresPorGrupo[grupo];
        porcentaje[grupo] = (total > 0) ? (100.0 * mayores / total) : 0.0;
    }
    return porcentaje;
}

int main() {
    Monitor monitor;
    int n;
    std::cout << "Ingrese número de personas a generar: ";
    std::cin >> n;

    monitor.iniciar_tiempo();
    std::vector<std::unique_ptr<Persona>> personas;
    personas.reserve(n);
    for (int i = 0; i < n; ++i) {
        auto p = generarPersona();
        personas.push_back(std::make_unique<Persona>(std::move(p)));
    }
    double tiempoGeneracion = monitor.detener_tiempo();
    long memoriaGeneracion = monitor.obtener_memoria();

    std::cout << "Generación de datos:\n";
    std::cout << "Tiempo = " << tiempoGeneracion << " ms,\n";
    std::cout << "Memoria = " << memoriaGeneracion << " KB\n";

    char opcionVer;
    std::cout << "\n¿Desea ver el listado completo de personas generadas? (s/n): ";
    std::cin >> opcionVer;
    if (opcionVer == 's' || opcionVer == 'S') {
        std::cout << "\nResumen de personas generadas:\n";
        for (size_t i = 0; i < personas.size(); ++i) {
            std::cout << i << ". ";
            personas[i]->mostrarResumen();
            std::cout << '\n';
        }
    }

    monitor.iniciar_tiempo();

    std::cout << "\n== Persona más longeva en todo el país ==\n";
    const Persona* longeva = personaMasLongeva(personas);
    if (longeva) {
        std::cout << "[" << longeva->getId() << "] " << longeva->getNombre() << " " << longeva->getApellido()
                  << ", Edad: " << calcularEdad(longeva->getFechaNacimiento()) << " años"
                  << ", " << longeva->getFechaNacimiento()
                  << ", Ciudad de nacimiento: " << longeva->getCiudadNacimiento()
                  << ", Ciudad de residencia: " << longeva->getCiudadResidencia() << "\n";
    }

    std::cout << "\n== Persona más longeva por ciudad ==\n";
    auto longevasCiudad = personaMasLongevaPorCiudad(personas);
    for (const auto& [ciudad, persona] : longevasCiudad) {
        std::cout << "--> " << ciudad << ": [" << persona->getId() << "] " << persona->getNombre() << " " << persona->getApellido()
                  << ", Edad: " << calcularEdad(persona->getFechaNacimiento())
                  << ", Fecha de nacimiento: " << persona->getFechaNacimiento() << "\n";
    }

    std::cout << "\n== Persona con mayor patrimonio en todo el país ==\n";
    const Persona* mayorPat = mayorPatrimonio(personas);
    if (mayorPat) {
        std::cout << "[" << mayorPat->getId() << "] " << mayorPat->getNombre() << " " << mayorPat->getApellido()
                  << ", Edad: " << calcularEdad(mayorPat->getFechaNacimiento())
                  << ", Patrimonio: $" << std::fixed << std::setprecision(2) << mayorPat->getPatrimonio()
                  << ", Ingresos anuales: $" << mayorPat->getIngresosAnuales()
                  << ", Ciudad de residencia: " << mayorPat->getCiudadResidencia() << "\n";
    }

    std::cout << "\n== Persona con mayor patrimonio por ciudad ==\n";
    auto patroCiudad = mayorPatrimonioPorCiudad(personas);
    for (const auto& [ciudad, persona] : patroCiudad) {
        std::cout << "--> " << ciudad << ": [" << persona->getId() << "] " << persona->getNombre() << " " << persona->getApellido()
                  << ", Edad: " << calcularEdad(persona->getFechaNacimiento())
                  << ", Patrimonio: $" << std::fixed << std::setprecision(2) << persona->getPatrimonio() << "\n";
    }

    std::cout << "\n== Persona con mayor patrimonio por grupo de declaración ==\n";
    auto patroGrupo = mayorPatrimonioPorGrupo(personas);
    for (const auto& [grupo, persona] : patroGrupo) {
        std::cout << "--> Grupo " << grupo << ": [" << persona->getId() << "] " << persona->getNombre() << " " << persona->getApellido()
                  << ", Ingresos anuales: $" << std::fixed << std::setprecision(2) << persona->getIngresosAnuales()
                  << ", Patrimonio: $" << persona->getPatrimonio() << "\n";
    }

    std::cout << "\n== Contar declarantes por calendario ==\n";
    auto declarantes = declarantesPorCalendario(personas);
    for (const auto& [grupo, lista] : declarantes) {
        std::cout << "--> Grupo " << grupo << ": " << lista.size() << " declarantes\n";
        for (const Persona* persona : lista) {
            std::cout << "[" << persona->getId() << "]: " << persona->getNombre() << " " << persona->getApellido() << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "== Validación de asignación de calendario ==\n";
    if (validarAsignacion(personas)) {
        std::cout << "Todas las personas están correctamente asignadas según el calendario de DIAN 2025.\n";
    }

    std::cout << "\n== Ciudad con mayor cantidad de personas menores de 18 años ==\n";
    auto ciudadMenores18 = ciudadMayorMenoresDe18(personas);
    std::cout << "Ciudad: " << ciudadMenores18.first << ", Cantidad de menores: " << ciudadMenores18.second << "\n";

    std::cout << "\n== Promedio de ingresos anuales por grupo de calendario ==\n";
    auto ingresosPromedio = promedioIngresosPorGrupo(personas);
    for (const auto& [grupo, promedio] : ingresosPromedio) {
        std::cout << "Grupo " << grupo << ": $" << std::fixed << std::setprecision(2) << promedio << "\n";
    }

    std::cout << "\n== Porcentaje de personas mayores de 50 años por calendario ==\n";
    auto porcentajeMayores = porcentajeMayores50PorCalendario(personas);
    for (const auto& [grupo, porcentaje] : porcentajeMayores) {
        std::cout << "Grupo " << grupo << ": " << std::fixed << std::setprecision(2) << porcentaje << "%\n";
    }

    double tiempoProcesamiento = monitor.detener_tiempo();
    long memoriaProcesamiento = monitor.obtener_memoria();

    std::cout << "\nProcesamiento:\n";
    std::cout << "Tiempo = " << tiempoProcesamiento << " ms\n";
    std::cout << "Memoria usada después de procesar los datos = " << memoriaProcesamiento << " KB\n";

    return 0;
}
