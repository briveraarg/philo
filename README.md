# 🧠 Philosophers

Este proyecto es una implementación del problema clásico de los **filósofos comensales**, desarrollado en lenguaje C como parte del programa de la escuela 42. A través de esta simulación, se pone en práctica el manejo de **hilos**, sincronización con **mutexes**, y la prevención de condiciones de carrera o bloqueos mutuos (*deadlocks*).


## Descripción

Cinco filósofos se sientan alrededor de una mesa circular. Cada uno alterna entre pensar, comer y dormir. Para comer, necesita tener dos tenedores (uno a cada lado). Este proyecto modela ese comportamiento usando **hilos de ejecución** y mecanismos de sincronización.

El desafío principal es asegurar que:
- No se produzcan **condiciones de carrera**
- No haya **bloqueos mutuos (deadlocks)**
- Los filósofos coman y mueran de acuerdo al tiempo dado


## Estructura del proyecto

```bash

philo/
├── Makefile
├── include/
│   └── philosophers.h
├── src/
│   ├── init\_struct.c
│   ├── input\_check.c
│   ├── main.c
│   ├── print\_msj.c
│   ├── pthread\_00.c
│   ├── pthread\_01.c
│   ├── pthread\_02.c
│   ├── pthread\_03.c
│   ├── pthread\_free.c
│   ├── pthread\_utils.c
│   └── utils.c
└── wiki/ #documentación de las funciones autorizadas

```

## A filosofar!

#### 1. Clonar repositorio y compilar

```bash
   git clone https://github.com/yourusername/philo.git
   cd philo
   make
```

#### 2. Ejecutar la simulación

```bash

./philo [número_de_filósofos] [tiempo_para_morir] [tiempo_para_comer] [tiempo_para_dormir]

./philo ./philo [número_de_filósofos] [tiempo_para_morir] [tiempo_para_comer] [tiempo_para_dormir][número_de_comidas]

```

| Comando                   | Descripción                                                         | Resultado esperado                              |
| ------------------------- | ------------------------------------------------------------------- | ----------------------------------------------- |
| `./philo 3 400 100 100 5` | 3 filósofos, deben comer 5 veces                                    | Simulación termina al alcanzar el conteo        |
| `./philo 2 210 100 100`   | 2 filósofos, mueren tras 2100ms                                     | Nadie muere, entre comer y dormir tienen tiempo |
| `./philo 1 800 200`.      | Falta un argumento                                                  | Error: entrada invalida                         |
| `./philo 2 210 100 100`   | 2 filósofos, mueren tras 2100ms                                     | `"X 1 died"` (por inanición)                    |



## 🛠️ Más controles

```bash

#Fugas de memoria
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo 5 410 200 200

### Condiciones de carrera (Helgrind)
valgrind --tool=helgrind ./philo 5 410 200 200

### hreadSanitizer

./philo_tsan 5 410 200 200  # Compilado con -fsanitize=thread

```

---

## Qué se aprende con este proyecto

* Uso de **hilos de ejecución** (`pthread_create`, `pthread_join`, etc.)
* Uso correcto de **mutexes** para proteger recursos compartidos
* Detección y prevención de **condiciones de carrera**, **deadlocks** y **starvation**
* Uso de funciones de tiempo como `gettimeofday()` y `usleep()`
* Buenas prácticas para proyectos concurrentes
* Depuración de memoria y sincronización con herramientas como **Valgrind** y **ThreadSanitizer**
* Organización de código modular y trabajo en C puro

Este proyecto es una excelente introducción a la **programación concurrente** y a la lógica de **sistemas operativos**.

---



## 📜 Licencia

Este proyecto está bajo la licencia especificada en el archivo `LICENCIA`.




## 💬 Contacto

Creado por **Brenda Rivera**  
📧 brennriveraa@gmail.com
🇦🇷 Estudiandante de 42 Madrid 
