# PI_Final 
## Integrantes: Arce Julian Francisco, Catalan Roberto Jose y Pecile Gian Luca.

### Instalación
En consola ingresar comando `make all`.

El ejecutable será guardado bajo el nombre `TPFinal` en el mismo directorio.

### Modo de uso
Para ejecutar el programa, se deben pasar como argumentos por linea de comando los archivos CSV deseados.
Por ejemplo si ambos archivos se encuentran en el mismo directorio que el ejecutable, el programa se puede invocar cómo:
`./TPFinal provincias.csv nacimientos.csv`

Si desea eliminar los archivos generados en consola ingresar el comando `make clean`.

### Salida de errores
La salida de errores predeterminada es salida estándar. 

Para redireccionar la salida de errores añadir `2>fichero`. Esto envía la salida de error a _fichero_.

Por ejemplo:
`./TPFinal provincias.csv nacimientos.csv 2>error.txt`
