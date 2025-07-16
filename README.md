# 🧠 Filósofos

Este proyecto es una implementación del problema clásico de los **filósofos comensales**, desarrollado en lenguaje C como parte del programa de la escuela 42. A través de esta simulación, se pone en práctica el manejo de **hilos**, sincronización con **mutexes**, y la prevención de condiciones de carrera o bloqueos mutuos (*deadlocks*).

---

## 📚 Descripción

Cinco filósofos se sientan alrededor de una mesa circular. Cada uno alterna entre pensar, comer y dormir. Para comer, necesita tener dos tenedores (uno a cada lado). Este proyecto modela ese comportamiento usando **hilos de ejecución** y mecanismos de sincronización.

El desafío principal es asegurar que:
- No se produzcan **condiciones de carrera**
- No haya **bloqueos mutuos (deadlocks)**
- Los filósofos coman y mueran de acuerdo al tiempo dado

---

## 📁 Estructura del proyecto

```

philo/
├── .gitignore
├── LICENCIA
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
└── wiki/
├── exit.txt
├── fork.txt
├── free.txt
├── gettimeofday.txt
├── kill.txt
├── malloc.txt
├── memset.txt
├── printf.txt
├── pthread\_create.txt
├── pthread\_detach.txt
├── pthread\_join.txt
├── pthread\_mutex\_destroy.txt
├── pthread\_mutex\_init.txt
├── pthread\_mutex\_lock.txt
├── pthread\_mutex\_unlock.txt
├── sem\_close.txt
├── sem\_open.txt
├── sem\_post.txt
├── sem\_unlink.txt
├── sem\_wait.txt
├── tipos\_de\_mutex.txt
├── usleep.txt
├── waitpid.txt
└── write.txt

````

---

## 🚀 Cómo ejecutar

### 1. Clonar este repositorio
```bash
git clone [URL-del-repositorio]
cd philo
````

### 2. Compilar el proyecto

```bash
make
```

### 3. Ejecutar la simulación

```bash
./philo número_de_filósofos tiempo_para_morir tiempo_para_comer tiempo_para_dormir [número_de_veces_que_cada_filósofo_debe_comer]
```

---

## 💡 Ejemplos de uso

| Comando                   | Descripción                                                         | Resultado esperado                              |
| ------------------------- | ------------------------------------------------------------------- | ----------------------------------------------- |
| `./philo 5 800 200 200`   | 5 filósofos, mueren tras 800ms sin comer, comen y duermen por 200ms | Filósofos alternan entre comer, dormir y pensar |
| `./philo 3 400 100 100 5` | 3 filósofos, deben comer 5 veces                                    | Simulación termina al alcanzar el conteo        |
| `./philo 1 800 200 200`   | 1 filósofo, muere tras 800ms                                        | Muere al no poder tomar el segundo tenedor      |

---

## 🧪 Pruebas

### 🔎 Validación de entrada

| Caso                     | Comando                      | Resultado esperado      |
| ------------------------ | ---------------------------- | ----------------------- |
| Argumentos insuficientes | `./philo 5 800 200`          | Error: Entrada inválida |
| Números negativos        | `./philo 5 -800 200 200`     | Error: Entrada inválida |
| 0 filósofos              | `./philo 0 800 200 200`      | Error: Entrada inválida |
| Números fuera de rango   | `./philo 9999999999 800 200` | Error: Entrada inválida |

### ⚙️ Simulaciones

| Caso                         | Comando                   | Resultado esperado                       |
| ---------------------------- | ------------------------- | ---------------------------------------- |
| 1 filósofo (caso límite)     | `./philo 1 800 200 200`   | Muere al no poder comer                  |
| Filósofo muere               | `./philo 2 200 100 100`   | `"X 1 died"` (por inanición)             |
| Ningún filósofo muere        | `./philo 4 410 200 200 5` | Todos comen 5 veces y finaliza           |
| Prueba de estrés (200 filos) | `./philo 200 410 200 200` | Corre sin bloqueos ni errores de memoria |

---

## 🛠️ Verificaciones avanzadas

### ✅ Fugas de memoria (Valgrind)

```bash
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo 4 410 200 200
```

### ⚔️ Condiciones de carrera (Helgrind)

```bash
valgrind --tool=helgrind ./philo 4 410 200 200
```

### 🧵 ThreadSanitizer (Clang)

```bash
./philo_tsan 4 410 200 200  # Compilado con -fsanitize=thread
```

---

## 🧩 Consejos para pruebas

* **Colores**: Asigná un color distinto por filósofo para facilitar el seguimiento visual.
* **Precisión en el tiempo**: Implementá tu propia función `my_usleep()` en lugar de `usleep()` para más precisión.
* **Evitar *buffering***: Usá `write()` en lugar de `printf()` para tener una salida más controlada.

---

## 🎓 Qué se aprende con este proyecto

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
