# 🎥 Plataforma de Streaming - Programación III: Proyecto Final

## Descripción
Este proyecto tiene como objetivo implementar una plataforma de streaming que permita la búsqueda y visualización de sinopsis de películas a partir de una base de datos en formato .csv. Las funcionalidades clave incluyen:

- **💾 Carga de Base de Datos:** Carga automática de una base de datos de películas desde un archivo .csv.
- **🔍 Búsqueda de Películas:** Búsqueda por palabras clave, frases y etiquetas (tags) como "cult", "horror", etc. La búsqueda muestra las cinco películas más relevantes y permite cargar las siguientes cinco.
- **🎬 Visualización de Detalles:** Muestra la sinopsis de una película seleccionada junto con opciones de "Like" y "Ver más tarde".
- **❤️ Gestión de Preferencias de Usuario:**
  - **📌 Películas Marcadas como "Ver más tarde":** Lista de películas marcadas para ver más tarde al iniciar el programa.
  - **🤖 Recomendaciones Personalizadas:** Algoritmo de recomendación de películas similares a las que el usuario ha marcado con "Like".

## Estructura del Proyecto

### Clases y Archivos Principales

- **`Movie`**: Entidad que representa una película.
- **`Database`**: Singleton que maneja la base de datos de películas.
- **`Trie`**: Estructura de datos utilizada para la búsqueda rápida de palabras.
- **`load.h`**: Contiene la función para cargar la base de datos desde un archivo .csv.
- **`utility.h`**: Funciones auxiliares para manipulación de strings.

### Archivos del Proyecto

- `database.h`
- `load.h`
- `search.h`
- `trie.h`
- `ui.h`
- `utility.h`

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

El programa carga automáticamente la base de datos de películas desde `datasets/mpst_full_data.csv`. Si el archivo no está presente, se debe descargar y colocar en la ruta indicada.

### Búsqueda de Películas

1. **Buscar por palabra clave o frase:**
   - Ingresar la palabra o frase en el campo de búsqueda.
   - Se mostrarán las cinco películas más relevantes.
   - Opción para cargar las siguientes cinco coincidencias.

2. **Buscar por etiquetas:**
   - Ingresar la etiqueta en el campo de búsqueda (por ejemplo, "cult", "horror").
   - Se mostrarán las cinco películas más relevantes.
   - Opción para cargar las siguientes cinco coincidencias.

### Visualización de Detalles

- Al seleccionar una película de la lista de resultados, se muestra la sinopsis junto con las opciones "Like" y "Ver más tarde".

### Gestión de Preferencias de Usuario

- **📌 Películas Marcadas como "Ver más tarde":**
  - Al iniciar el programa, se muestra una lista de las películas marcadas previamente.
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
