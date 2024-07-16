# 🎥 Plataforma de Streaming - Programación III: Proyecto Final

## Descripción
Este proyecto tiene como propósito desarrollar una plataforma de streaming que facilite la búsqueda y visualización de sinopsis de películas a partir de una base de datos almacenada en un archivo .csv. Las funcionalidades principales incluyen:

- **💾 Carga de Base de Datos:** Integración automática de una base de datos de películas desde un archivo .csv.
- **🔍 Búsqueda de Películas:** Búsqueda mediante palabras clave, frases y etiquetas (tags) como "cult", "horror", entre otras. Los resultados muestran las cinco películas más relevantes, con la opción de cargar las siguientes cinco.
- **🎬 Visualización de Detalles:** Presenta la sinopsis de una película seleccionada y opciones de "Like" y "Ver más tarde".
- **❤️ Gestión de Preferencias de Usuario:**
    - **📌 Películas Marcadas como "Ver más tarde":** Lista de películas guardadas para ver posteriormente al iniciar el programa.
    - **🤖 Recomendaciones Personalizadas:** Algoritmo de recomendación que sugiere películas similares a las que el usuario ha indicado con "Like".

## Estructura del Proyecto

### Clases y Archivos Principales

- **`Movie`**: Clase que representa una película.
- **`Database`**: Singleton encargado de gestionar la base de datos de películas.
- **`Trie`**: Estructura de datos empleada para la búsqueda rápida de palabras.
- **`load.h`**: Contiene la función responsable de cargar la base de datos desde un archivo .csv.
- **`utility.h`**: Funciones auxiliares para la manipulación de strings.

### Archivos del Proyecto

- `database.h`
- `load.h`
- `search.h`
- `trie.h`
- `ui.h`
- `utility.h`
- `user.h`
- `movie.h`
- `main.cpp`

### Explicación de los headers

1. **Database.h:**
- Singleton: Database implementa el patrón Singleton para asegurar que solo haya una instancia de la base de datos en todo el programa.

- Multithreading: Se utiliza std::thread para aprovechar múltiples núcleos del procesador al generar el Trie, mejorando así la eficiencia.

- Procesamiento en Bloques: Las películas se procesan en bloques (chunks) distribuidos entre varios hilos, tanto para los títulos como para las descripciones.

- Uso de Trie: El Trie se utiliza para búsquedas rápidas de palabras y prefijos, lo que es útil para funcionalidades de búsqueda en la base de datos.

2. **Load.h:**
- El archivo load.h proporciona una función para cargar una base de datos de películas desde un archivo CSV en la clase Database. Utiliza técnicas para manejar correctamente los delimitadores dentro de comillas y distribuye la carga entre múltiples hilos para mejorar el rendimiento al procesar grandes volúmenes de datos.

3. **Search.h:**
- El archivo search.h define una interfaz SearchCommand para comandos de búsqueda y proporciona dos implementaciones concretas: MovieSearchCommand para búsquedas por palabras clave en títulos de películas y TagSearchCommand para búsquedas por etiquetas. Estos comandos utilizan la estructura de datos Trie y la base de datos de películas para realizar búsquedas eficientes y precisas.

4. **Trie.h:**
- El archivo trie.h define una estructura de datos Trie que permite búsquedas rápidas y eficientes de palabras y prefijos, útil para implementar las funcionalidades de búsqueda en una base de datos de películas. La clase Trie proporciona métodos para insertar palabras y prefijos, buscar índices de películas, y guardar/cargar el Trie desde un archivo, garantizando la seguridad en operaciones concurrentes mediante el uso de mutexes.

5. **Ui.h:**
- El archivo ui.h proporciona una interfaz de usuario basada en menús para la plataforma de streaming. Define una clase base Menu y tres clases derivadas (MovieSelectionMenu, MovieSearchMenu, MainMenu) que implementan menús específicos. Estos menús permiten al usuario buscar películas, ver detalles, marcar películas como favoritas o para ver más tarde, y navegar por las opciones del programa.
6. **Utility.h:**

- El archivo utility.h proporciona funciones auxiliares para el procesamiento de cadenas:
- toAlphabet: Convierte una cadena a minúsculas y reemplaza caracteres no alfabéticos por espacios.
- splitString: Divide una cadena en subcadenas utilizando un delimitador específico.
- trimLeadingSpaces: Elimina los espacios en blanco iniciales de cada cadena en un vector de cadenas.
7. **User.h:**
- La clase User en el archivo user.h gestiona las preferencias del usuario en la plataforma de streaming. Permite al usuario:
- Marcar películas como "liked" o "watch later".
- Mostrar las listas de películas gustadas y las películas para ver más tarde.
- Esta clase interactúa con la base de datos de películas para recuperar y mostrar la información relevante de las películas guardadas por el usuario.
8. **Movie.h:**
- El archivo movie.h define la estructura de una película (Movie) y las clases necesarias para visualizar las películas de diferentes maneras.
9. **Main.cpp:**
- Archivo en dónde se ejecuta todo el código. Se hace llamado a los headers.
## Instalación

1. **Clonar el repositorio:**

    ```bash
    git clone https://github.com/usuario/repositorio.git
    ```

2. **Compilar el proyecto:**

    ```bash
    cd repositorio
    make
    ```

3. **Ejecutar el programa:**

    ```bash
    ./programa
    ```

## Uso

### Carga de Base de Datos

El programa carga automáticamente la base de datos de películas desde `datasets/mpst_full_data.csv`. En caso de que el archivo no esté disponible, se debe descargar y colocar en la ruta especificada.

### Búsqueda de Películas

1. **Buscar por palabra clave o frase:**
    - Introducir la palabra o frase en el campo de búsqueda.
    - Se mostrarán las cinco películas más relevantes.
    - Existe una opción para cargar las siguientes cinco coincidencias.

2. **Buscar por etiquetas:**
    - Introducir la etiqueta en el campo de búsqueda (por ejemplo, "cult", "horror").
    - Se mostrarán las cinco películas más relevantes.
    - Existe una opción para cargar las siguientes cinco coincidencias.

### Visualización de Detalles

- Al seleccionar una película de la lista de resultados, se muestra la sinopsis junto con las opciones "Like" y "Ver más tarde".

### Gestión de Preferencias de Usuario

- **📌 Películas Marcadas como "Ver más tarde":**
    - Al iniciar el programa, se presenta una lista de las películas guardadas previamente.
- **🤖 Recomendaciones Personalizadas:**
    - Algoritmo que recomienda películas similares a las que el usuario ha marcado con "Like".

## Integrantes

- Rodrigo Li Chumpitaz
- Jorge Alexander Leon Villareyes
- Diva Stewart Maquera Bobadilla

Para contribuir al proyecto:
1. **Clonar el repositorio:**

    ```bash
    git clone https://github.com/usuario/repositorio.git
    ```

2. **Crear una nueva rama:**

    ```bash
    git checkout -b nombre-rama
    ```

3. **Realizar cambios y hacer commit:**

    ```bash
    git add .
    git commit -m "Descripción de los cambios"
    ```

4. **Subir los cambios:**

    ```bash
    git push origin nombre-rama
    ```

5. **Crear un Pull Request en GitHub.**

## Fuentes Utilizadas

1. Gonzales Gonzales, C. E. (2020). Trabajo de investigación una revisión de los patrones de diseño de software aplicado a las aplicaciones web. Recuperado de https://repositorio.uss.edu.pe/handle/20.500.12802/6783

2. Ruano, D., & Herrera, N. E. (2014). Representación secuencial de un trie de sufijos. In XX Congreso Argentino de Ciencias de la Computación (Buenos Aires, 2014). Recuperado de: https://sedici.unlp.edu.ar/handle/10915/42291

3. Fuente 3

4. Fuente 4
