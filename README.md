# Parcial 1 - Sistemas Operativos  
Comparativa de uso de **Structs vs Clases** y **Paso por Valor vs Apuntadores** en C++.

Este proyecto busca analizar el rendimiento y consumo de memoria de diferentes combinaciones de estructuras de datos, usando **10 millones de registros** como caso de prueba.  

---

## 📂 Estructura del Proyecto
El repositorio contiene dos carpetas principales:

- **class_proc/** → Implementación con **clases**
- **struct_proc/** → Implementación con **structs**

Cada carpeta incluye:
- `proc_valor_class` o `proc_valor_struct` → Manejo por valor
- `proc_apuntadores_class` o `proc_apuntadores_struct` → Manejo con apuntadores  

- **Las demas carpetas eran los generadores brindados por el profesor**

---

## ▶️ Ejecución

1. **Clonar el repositorio**
    ```bash
    git clone https://github.com/Smg4315/Parcial1SO.git

2. **Runnear el archivo de clases**
   ```bash
   cd class_proc
   make
   ./proc_valor_class
   ./proc_apuntadores_class

3. **Volver a la carpeta principal**
   ```bash
    cd ..

3. **Runnear el archivo de structures**
   ```bash
    cd struct_proc
    make
    ./proc_valor_struct
    ./proc_apuntadores_struct
