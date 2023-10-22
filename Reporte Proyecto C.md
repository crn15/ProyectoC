## Introducción 
El proyecto consiste en la implementación de un algoritmo para efectuar la rotación de una imagen 90 grados en el sentido horario, con el objetivo de desarrollar experiencia práctica en programación en C, mediante la integración de código desarrollado por terceros, en particular el uso de bibliotecas.

El programa desarrollado recibe una imagen que puede estar en formato PNG o JPEG, y guarda una nueva imagen rotada 90 grados a la derecha en el mismo formato original. Esto se logra mediante una manipulación directa de los píxeles, efectuando un barrido de las coordenadas de la imagen original y reasignando la información asociada en las nuevas coordenadas correspondientes para formar la imagen rotada.

Para lograr la manipulación de los píxeles fue necesario el uso de las bibliotecas libpng y libjpeg, las cuales poseen funciones que permiten obtener la información de las filas de píxeles de una imagen, la cual es luego utilizada por un algoritmo de rotación y finalmente reescrita en la nueva imagen rotada, nuevamente haciendo uso de las funciones facilitadas por las bibliotecas mencionadas.

## Marco Teórico 
### Libpng
Para realizar la lectura y escritura del archivo en formato png se utilizó la biblioteca Libpng. Según Randers (2010) en la documentación de la biblioteca existen dos structs importantes para modificar archivos png: `png_struct` y `png_info` la primera trata con aspectos internos de la biblioteca y la segunda se encarga de manejar la información relevante en la lectura del png. La librería también incluye otros tipos de datos predefinidos para el manejo de png como `png_byte` que es básicamente un byte de información cualquiera y `png_bytep` que define un pointer.

Ahora, según la documentación los primeros 8 bytes del header del archivo png constituyen su identificacion. La libreria provee una funcion `png_sig_cmp(header, 0 , 8)` que recibe el header y revisa si se esta tratando con un png. Si este es el caso se procede con la lectura del mismo inicializando las estructuras de png_struct y png_info.Es importante revisar que los dos punteros a dichos structs no sean nulos. . No obstante, antes se debe abrir el archivo png en modo lectura usando el comando ` FILE *fp = fopen`  este crea un puntero al archivo. La librería recibe el código de entrada por medio de la función `png_init_io( png_ptr , fp)` y guarda la información del png usando `png_read_info(png_ptr,info_ptr)`.

De acuerdo con la documentación (Randers, 2010), algunos datos relevantes que se pueden acceder en la lectura y se van a necesitar para escribir la nueva imagen después son:

| Parámetro  | Función                                 | Significado                                                                                  |
| ---------- | --------------------------------------- | -------------------------------------------------------------------------------------------- |
| width      | png_get_image_width(png_ptr, info_ptr)  | ancho de la imagen en pixels, importante para determinar las columnas de la matriz de pixels |
| height     | png_get_image_height(png_ptr, info_ptr) | altura de la imagen en pixels, importante para determinar las filas de la matriz de pixels   |
| color type | png_get_color_type(png_ptr, info_ptr)   | Describe los canales de color y alpha presentes en la imagen                                 |
| bits depth | png_get_bit_depth(png_ptr, info_ptr)    | Define el número de bits en cada pixel                                                       |                                                                                            |

Es importante mencionar como lo destaca Randers (2010) que existen los siguientes formatos para canales de color :

- Type_gray

- Type_gray_alpha

- Type_Paltette

- Type_RGB

- Type_RGB_alpha

En el presente código, se busca que la imagen tenga 3 canales de color y un canal alpha por tanto se usan la funciones `png_set_packing(png_ptr)` para expandir a una profundidad de 8 bits por pixel y `png_set_tRNS_to_alpha(png_ptr)` para agregar el canal alpha.

Luego con `png_read_update_info` se lee la nueva información.

Ahora, utilizando un ** pointer (filas_ptr) se reserva el espacio en memoria para la matriz de pixels, primero para las filas se reserva un espacio igual al tamaño del puntero `png_bytep`* height de la imagen, después por cada fila de height (recordar que es la altura en pixeles ) se le asigna la cantidad de bites por fila con la función `png_get_rowbytes`. Finalmente, la librería se encarga de posicionar la información de los bytes en el array con la función `png_read_image(png_ptr, filas_ptr)`. Luego se debe cerrar el archivo de la imagen original.

Una vez efectuada la transformación se debe escribir la imagen en el path del archivo especificado por el usuario. Para eso se abre el archivo, sino existe se crea en el momento. Luego nuevamente dos structs para manejar la información de la nueva imagen `pngw_ptr` y `winfo_ptr`. Es importante resaltar el uso de la función `png_set_IHDR(pngw_ptr , winfo_ptr , width, height , bits_d , PNG_COLOR_TYPE_RGBA , PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT` ya que como se menciono anteriormente es el header quien contiene la información que especifica el formato del png. La nueva imagen debe tener el mismo formato que su antecesora y por eso era importante obtener esta información de la lectura inicial. Además, es por esta función que es importante especificar un formato del tipo RGBA.

`png_write_info` actualiza el header y `png_write_image(pngw_ptr, newarray)` toma el array transformado y lo escribe en el file. Por último, se limpian todos los structs y se libera la memoria usada para los arrays.

**Nota**: Además de la documentación se consulto el siguiente ejemplo para hacer uso de la biblioteca . [https://gist.github.com/niw/5963798](https://gist.github.com/niw/5963798)
### Libjpeg
Según Free Standards Group (s.f), libjpeg es una biblioteca utilizada para leer y escribir archivos en formato JPEG y las siguientes son las herramientas de esta librería utilizadas en este proyecto:

- jpeg_CreateCompress: Crea e inicia el archivo de compresión.

 - jpeg_CreateDecompress: Crea e inicia el archivo de descompresión.

- jpeg_destroy_compress: Libera el archivo de compresión.

- jpeg_destroy_decompress: Libera el archivo de descompresión.

- jpeg_finish_compress: termina compresión.

- jpeg_finish_decompress: termina descompresión.

- jpeg_read_header: Lee el inicio de la secuencia de datos JPEG.

- jpeg_read_scanlines: Lee las líneas de escaneo de datos desde un descompresor JPEG.

- jpeg_set_defaults: Establece los parámetros de compresión en los valores establecidos.

- jpeg_set_quality: Construye las tablas de cuantizació G para la calidad del archivo.

- jpeg_start_compress: Inicia compresión.

- jpeg_start_decompress: Inicia descompresión.

- jpeg_std_error: Actualiza el manejo de errores.

- jpeg_stdio_dest: Inicia el estado para la salida a una secuencia de stdio.

- jpeg_write_scanlines: Escribe las líneas de escaneo de datos en un compresor.

  

#### Archivo JPEG_CHECK.C

Este archivo contiene la función llamada “ItsJPEG”, la cual es utilizada para comprobar si el archivo ingresado por el usuario se trata de una imagen en tipo JPEG, mediante la revisión de los primeros tres bytes de la imagen para comprobar que estos coincidan con el formato JPEG.

  

#### Archivo JPEG_Reader.C

Este archivo contiene la función llamada “loadJPEGImage”, la cual es llamada después de comprobar que el archivo ingresado es una imagen JPEG. Esta función se encarga de leer y cargar la imagen recibida para guardar líneas de pixeles de la imagen en un arreglo bidimensional, esto utilizando una estructura llamada JSAMPARRAY incluida en la librería libjpeg. La imagen se abre en modo lectura binaria y se descomprime, para así guardar las características de la imagen en una variable y temporalmente se posicionar memoria para las líneas de pixeles, las cuales se utilizan para crear una el arreglo bidimensional que será utilizado en la función utilizada para rotar imágenes JPEG. Al final se debe finalizar la descompresión y liberar los recursos de la memoria.

  

### Archivo JPEG_writer.c

Este archivo contiene la función llamada “writeJPEGImage”, la cual recibe como argumentos el nombre del archivo JPEG de salida y una matriz que contiene las líneas de pixeles de la imagen ya rotada. El archivo de salida se abre en modo lectura binaria y se vuelve a utilizar JSAMPARRAY y, en este caso se inicia una compresión dela imagen, además de guardar sus características para así iniciar un nuevo arreglo que contenga cada línea de pixeles, esto para finalizar escribiendo estas líneas de pixeles.

### Algoritmo de rotación 90 grados en sentido horario

Se utiliza un algoritmo de manipulación directa de píxeles. Para este caso, se puede entender una imagen como una matriz bidimensional de píxeles, con sus diferentes filas y columnas en los ejes _x_ y _y_. La manipulación directa de los píxeles para su respectiva rotación consiste en asignar las nuevas coordenadas de la matriz en las que se reubicará la información de cada píxel para formar la nueva imagen rotada resultante, determinadas a partir de las coordenadas del píxel en la matriz de información original.

Para el cálculo de las "coordenadas rotadas", conviene observar que para rotar una matriz 90 grados a la derecha el proceso se puede dividir en dos pasos: primero, efectuar la transposición de la matriz (es decir, colocar las filas como columnas) y segundo, invertir el orden de las columnas (la primera de última y así sucesivamente).

![matriz](https://raw.githubusercontent.com/crn15/ProyectoC/algoritmo/rotate-matrix-90-degrees-clockwise.png)
## Implementación
### Función de validación de entrada
Esta función se encarga de validar las entradas desde la línea de comandos y se encuentra en el archivo Entrada_Linea_comandos.c . Como se denota en el siguiente diagrama la lógica se basa en comprobar el número de argumentos ingresados. Solo hay 3 casos posibles: 1 argumento, 4 o 5. Recordar que el nombre del archivo se cuenta como el primer argumento del array argv. Si se ingresan menos o más argumentos es un error y debe pararse la ejecución del programa. Luego, hay que revisar los argumentos dependiendo del caso. 
- Si es 1 la única posibilidad es que sea -h o -help, de lo contrario es un error. Si es cualquiera de los dos se despliega el archivo de ayuda y se termina la ejecución del programa. 
- Si son 4 argumentos significa que se omitió el argumento de -r que es innecesario ya que solo hay una transformación. Si alguno de los argumentos del array es -r significa que faltó un argumento mandatorio y se debe parar la ejecución. De lo contrario, se guardan los path de salida y entrada en los punteros respectivos. 
- Si son 5 argumentos, se debe comprobar que el de entrada es válido (no es necesario para el de salida, más adelante en la escritura con las respectivas bibliotecas se lidia con fallos en el archivo de salida) y guardar la información de los paths. 
Hay que destacar, que siempre que se evalué una posibilidad invalida se retorna False y se detiene el programa.

![alt image](https://github.com/Msolis314/Clases/blob/main/Drawing%202023-10-14%2023.01.09.excalidraw.png)

### Lógica general del programa
La lógica del flujo del programa se resume en el diagrama a continuación:

![alt image](https://github.com/Msolis314/Clases/blob/main/Drawing%202023-10-15%2020.08.31.excalidraw.png)

Primero, se tiene la ya mencionada entrada desde la línea de comandos, si en esta etapa existe un error por parte de la entrada de usuario acaba el programa. De lo contrario, se continua con la evaluación de un condicional `if` para evaluar si se trata de un jpeg o un png, en caso de no ser ninguno de los dos se acaba el programa. Dependiendo del caso se procede con la lectura de la imagen utilizando las funciones de la biblioteca respectiva para lograr obtener una estructura de datos tipo array con la información de los pixels. Luego, se aplica el algoritmo de rotación y finalmente se guarda la imagen en el path especificado por el usuario al inicio del programa.
### Rotación 

Para implementar en código la manipulación de los píxeles mediante la reasignación de coordenadas de forma tal que efectúe la rotación, la transformación equivalente a transponer la matriz e invertir el orden se sus columnas se puede hacer en un único paso mediante operaciones aritmética a partir de las dimensiones y coordenadas de la matriz original.

Así, para calcular las nuevas coordenadas y rotar los píxeles simplemente se sigue el siguiente algoritmo:

- Se determinan las dimensiones `height` y `width` de la matriz de píxeles de la imagen original

- Se hace un barrido por cada una de las filas de la matriz, desde `y = 0` hasta `y = height - 1`

- Dentro de cada una de las filas en el barrido anterior, se efectúa a su vez un barrido por cada una de las entradas de la fila, es decir, en la posición correspondiente cada columna de la matriz, i.e. desde `x = 0` hasta `x = width - 1`

- Para cada valor de coordenada `x` de la matriz de la imagen original, este corresponderá a la coordenada `rotaded_y` de las ordenadas en la matriz rotada

- Se carga en punteros las direcciones de las coordenadas en el espacio de memoria asignado para el almacenamiento tanto para leer la matriz de información de píxeles de la imagen original, como para escribir la nueva matriz de píxeles rotada; estos punteros apuntan a la posición fuente y destino, respectivamente

- Utilizando los punteros a las coordenadas correspondientes, se copia la información del píxel original a la nueva posición en la matriz de la imagen rotada, teniendo en cuenta la cantidad de canales que en el caso de RGB son 3 y para RGBA son 4

Este algoritmo recibe un puntero a las filas de la imagen original y genera un puntero a donde estarán las filas de la imagen rotada. A continuación se presenta un diagrama de flujo del algoritmo utilizado.

![algoritmo](https://raw.githubusercontent.com/crn15/ProyectoC/algoritmo/diagrama_algoritmo2.png)

## Resultados

Como se denota a continuación pasando la siguiente imagen en png: 

![Pngsinrotar](https://github.com/crn15/ProyectoC/blob/main/bin/dog.png)
Se obtiene el siguiente resultado al realizar la transformación: 

![alt image](https://github.com/crn15/ProyectoC/blob/main/bin/pruebafinal.png)

Por igual, al pasar la siguiente imagen en formato jpeg:

![alt image](https://github.com/crn15/ProyectoC/blob/main/bin/pruebajpeg.jpeg)

Se obtiene:

![alt image](https://github.com/crn15/ProyectoC/blob/main/bin/pruebafinal.jpeg)

Mostrando que se cumplió con el objetivo del proyecto.
Además, para monitorear el consumo de  %memoria y %cpu del programa se utilizó el siguiente script en bash. 
```bash 
#!/bin/bash
n = 0 
echo " #%CPU #MEM #Time" > log.txt
while ( $n -lt 50 );
do 
	id=$1
	var1=$( ps -p $id -o %cpu= )
	var2=$( ps -p $id -o %mem= )
	time=$( date "+ %s" )
	echo "$var1 $var2 $time" >> log.txt
	n=$(( n+1))
done
```
Utilizando la función `sleep()` contenida en la biblioteca estándar `<unistd.h>` se prolongo la duración del programa para lograr obtener su id usando el comando `pidof ` y luego pasarlo al script. Los resultados se escribieron en un archivo de log como se denota a continuación: 

![alt image](https://github.com/Msolis314/Clases/blob/main/%25CPUC.png)

El porcentaje de consumo de CPU promedia en 0.2 y de memoria en 0. Luego para obtener el tiempo de duración se utilizo la biblioteca `<time.h>` iniciando el relog al comienzo de la función main con `clock_t begin = clock()` y finalizando la toma de tiempo al cerrarse la ejecución con `clock_t end = clock()`. Para calcular el tiempo se utilizo:


```C
double time = (double)(end - begin)/ CLOCKS_PER_SEC;
```
Finalmente, al imprimir la variable time se obtiene: 

![alt image](https://github.com/Msolis314/Clases/blob/main/WhatsApp%20Image%202023-10-22%20at%2013.15.10.jpeg)


El cual sería el tiempo de ejecución del programa.
## Conclusión
- El uso de bibliotecas para la programación en C es una tarea fundamental para optimizar el desarrollo de código mediante el uso de herramientas altamente probadas y depuradas que facilitan la implementación de algoritmos más complejos a partir de ellas, y así, la solución de problemas de mayor tamaño.

- Para aprovechar al máximo el uso de las bibliotecas en el desarrollo de soluciones complejas de programación, es crucial como personas programadoras desarrollar la habilidad de entender y utilizar código escrito por terceras personas e integrarlo a la aplicación propia. Esto conlleva el estudio y comprensión de la documentación de las bibliotecas y herramientas de éstas que se requieren en la construcción de un proyecto de programación en particular; en este caso para el manejo de información de imágenes.

- Un aspecto esencial para el desarrollo de habilidades de programación robustas, consiste en adquirir destrezas en debugging, aplicando buenas prácticas de programación, así como mediante el uso de herramientas de debug como por ejemplo GDB, que ayudan a determinar el origen de los problemas y sus posibles soluciones.

- El lenguaje de programación C permite el control de la memoria a un relativo bajo nivel, lo cual es relevante en aplicaciones que requieran optimizar la gestión de recursos y la ejecución del programa en general. Para aprovechar esta característica al máximo, es importante contar con fundamentos sólidos en cuanto al funcionamiento de punteros, los tipos de datos y el manejo de la memoria dinámica y el heap.

- Un enfoque incremental es conveniente para llevar a cabo el desarrollo de un problema complejo en programación, por medio del cual se divide el problema en tareas de menor complejidad y estas se van desarrollando poco a poco mediante prototipos más sencillos a los que se les van agregando funcionalidades y probando el correcto funcionamiento en cada pequeño avance.

- Git es una herramienta muy poderosa que ayuda en el desarrollo de programas, en particular para un ordenado control de versiones y respaldo, así como para el trabajo colaborativo en equipos de desarrollo. Aprender en detalle su funcionamiento es de gran valor en la formación en programación.
## Referencias
Randers, G.  (2010).*libpng.txt - A description on how to use and modify libpng*. (Version 1.6.39). [Source code](https://libpng.sourceforge.io/)


Free Standards Group. (s.f). *V. JPEG library. Linux Standard Base.*[Source code](https://refspecs.linuxbase.org/LSB_3.1.0/LSB-Desktop-generic/LSB-Desktop-generic/toclibjpeg.html) 

