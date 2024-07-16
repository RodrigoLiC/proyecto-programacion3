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
- Manuel Sebastian Taco Anton
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
