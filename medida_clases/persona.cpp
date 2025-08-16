#include "persona.h"
#include <iomanip> // Para std::setprecision

/**
 * Implementación del constructor de Persona.
 * 
 * POR QUÉ: Inicializar los miembros de la clase.
 * CÓMO: Usando la lista de inicialización y moviendo los strings para evitar copias.
 * PARA QUÉ: Eficiencia y correcta construcción del objeto.
 */
Persona::Persona(std::string nom, std::string ape, std::string id, 
                 std::string ciudad, std::string residencia, std::string fecha, double ingresos, 
                 double patri, double deud, bool declara, char calendario)
    : nombre(std::move(nom)), 
      apellido(std::move(ape)), 
      id(std::move(id)), 
      ciudadNacimiento(std::move(ciudad)),
      ciudadResidencia(std::move(residencia)),
      fechaNacimiento(std::move(fecha)), 
      ingresosAnuales(ingresos), 
      patrimonio(patri),
      deudas(deud), 
      declaranteRenta(declara),
      calendario(calendario) {}

/**
 * Implementación de mostrar.
 * 
 * POR QUÉ: Mostrar todos los datos de la persona de forma estructurada.
 * CÓMO: Usando flujos de salida y formateadores.
 * PARA QUÉ: Facilitar la lectura de los datos completos de una persona.
 */
void Persona::mostrar() const {
    std::cout << "-------------------------------------\n";
    std::cout << "[" << id << "] Nombre: " << nombre << " " << apellido << "\n";
    std::cout << "   - Ciudad de nacimiento: " << ciudadNacimiento << "\n";
    std::cout << "   - Ciudad de residencia: " << ciudadResidencia << "\n";
    std::cout << "   - Fecha de nacimiento: " << fechaNacimiento << "\n\n";
    std::cout << std::fixed << std::setprecision(2); // Formato de números
    std::cout << "   - Ingresos anuales: $" << ingresosAnuales << "\n";
    std::cout << "   - Patrimonio: $" << patrimonio << "\n";
    std::cout << "   - Deudas: $" << deudas << "\n";
    std::cout << "   - Declarante de renta: " << (declaranteRenta ? "Sí" : "No") << "\n";
    std::cout << "   - Calendario: " << calendario << "\n";
}

/**
 * Implementación de mostrarResumen.
 * 
 * POR QUÉ: Mostrar información esencial de la persona en una sola línea.
 * CÓMO: Imprime ID, nombre completo, ciudad e ingresos.
 * PARA QUÉ: Listados rápidos y eficientes.
 */
void Persona::mostrarResumen() const {
    std::cout << nombre << " " << apellido
              << " | " << fechaNacimiento
              << " | " << ciudadResidencia
              << " | Patrimonio: $" << std::fixed << std::setprecision(2) << patrimonio
              << " | Deudas: $" << std::fixed << std::setprecision(2) << deudas
              << " | ID: [" << id << "]"
              << " | Calendario: " << calendario;
}
