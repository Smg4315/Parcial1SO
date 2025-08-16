# Parcial 1 - Sistemas Operativos  
Comparativa de uso de **Structs vs Clases** y **Paso por Valor vs Apuntadores** en C++.

Este proyecto busca analizar el rendimiento y consumo de memoria de diferentes combinaciones de estructuras de datos, usando **10 millones de registros** como caso de prueba.  

---

# 🛠️ Entorno de desarollo

- **Sistema Operativo:** EL archivo está diseñado para correr en Linux 
- **Lenguage de programación:** C++ (Compilador: Clang++ 16.00)

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

## Preguntas de pensamiento crítico

### 1. Memoria: ¿Por qué usar apuntadores reduce 75% de memoria con 10M registros?

Porque cuando se usa valor, cada objeto ocupa toda su información repetida en memoria (por ejemplo, 10 millones de nombres, direcciones, etc.).
Con apuntadores, en el arreglo solo se guarda direcciones (punteros) y los datos “pesados” se almacenan una sola vez en el heap. Esto significa que en lugar de repetir todo el bloque de información por cada registro, solo se guarda la referencia, lo que se traduce en mucho menos consumo de memoria.

 ### 2. Datos: Si el calendario depende de dígitos del documento, ¿cómo optimizar búsquedas por grupo?
Se puede agrupar por dígitos claves del documento. Por ejemplo:
Si los 2 últimos dígitos del documento indican el grupo, se puede crear un mapa/tabla hash donde la llave es ese par de dígitos.
Así, no se busca en todo el arreglo, sino solo en la lista del grupo correspondiente.

### 3. Localidad: ¿Cómo afecta el acceso a memoria al usar array de structs vs. vector de clases?
En el array de structs, los datos están contiguos en memoria, entonces el procesador aprovecha la caché mucho mejor (acceso más rápido). Mientras que en el
Vector de clases con punteros, las direcciones pueden estar regadas en memoria, lo que hace que se pierda localidad, y el acceso es un poco más lento.

### 4. Si los datos exceden la RAM, ¿cómo usar mmap o memoria virtual?
Cuando los datos son gigantes, no se pueden cargar todos a la RAM. Para eso:
Con mmap (mapear archivo a memoria): el SO carga en RAM solo las partes del archivo que se usan, no todo.
Con memoria virtual: el sistema “finge” tener más memoria usando disco (swap/paginación), aunque es más lento.
