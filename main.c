/**
 * Programa de ejemplo de Raycasting usando OpenGL
 * Este programa crea una ventana donde se puede mover un jugador en un mapa 2D
 */

#include <GL/glut.h> // Librería para gráficos OpenGL con GLUT
#include <stdio.h>   // Librería estándar de entrada/salida
#include <stdlib.h>  // Librería estándar para funciones generales

// Variables globales para la posición del jugador
float px, py;

/**
 * drawPlayer - Dibuja la representación del jugador en la pantalla
 * Crea un punto amarillo en la posición actual del jugador (px, py)
 * El punto tiene un tamaño de 8 píxeles y color amarillo brillante
 */
void drawPlayer() {

  glColor3f(1, 1, 0); // Color amarillo (RGB)
  glPointSize(8);     // Tamaño del punto
  glBegin(GL_POINTS); // Comienza a dibujar puntos
  glVertex2i(px, py); // Dibuja el punto en la posición del jugador
  glEnd();            // Finaliza el dibujo
}

// Definición del mapa: dimensiones y tamaño de cada celda
int mapX = 8, mapY = 8, mapS = 64;
// Array que define el mapa: 1 representa paredes, 0 representa espacios vacíos
int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0,
    0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

/**
 * drawMap2D - Dibuja el mapa 2D en la pantalla
 * Recorre el array del mapa y dibuja cuadrados blancos para las paredes (1)
 * y cuadrados negros para los espacios vacíos (0)
 * Cada celda del mapa tiene un tamaño de mapS x mapS píxeles
 */
void drawMap2D() {
  int x, y, xo, yo;
  for (y = 0; y < mapY; y++) {
    for (x = 0; x < mapX; x++) {
      if (map[y * mapX + x] == 1) {
        glColor3f(1, 1, 1); // Color blanco para paredes
      } else {
        glColor3f(0, 0, 0); // Color negro para espacios vacíos
      }
      xo = x * mapS;
      yo = y * mapS;
      glBegin(GL_QUADS);
      glVertex2i(xo, yo);
      glVertex2i(xo, yo + mapS);
      glVertex2i(xo + mapS, yo + mapS);
      glVertex2i(xo + mapS, yo);
      glEnd();
    }
  }
}

/**
 * display - Función principal de renderizado
 * Se llama automáticamente cuando se necesita redibujar la pantalla
 * Limpia la pantalla, dibuja el mapa 2D y luego dibuja al jugador
 */
void display() {
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT); // Limpia la pantalla y el buffer de profundidad
  drawMap2D();                  // Dibuja el mapa
  drawPlayer();                 // Dibuja al jugador
  glutSwapBuffers();            // Intercambia los buffers (doble buffer)
}

/**
 * buttons - Maneja las entradas del teclado para mover al jugador
 * @param key: tecla presionada
 * @param x: posición x del mouse (no utilizado)
 * @param y: posición y del mouse (no utilizado)
 *
 * Controles:
 * - 'w': mueve hacia arriba
 * - 's': mueve hacia abajo
 * - 'a': mueve hacia la izquierda
 * - 'd': mueve hacia la derecha
 */
void buttons(unsigned char key, int x, int y) {
  if (key == 'a') {
    px -= 5; // Mueve al jugador a la izquierda
  }
  if (key == 'd') {
    px += 5; // Mueve al jugador a la derecha
  }
  if (key == 'w') {
    py -= 5; // Mueve al jugador hacia arriba (en coordenadas invertidas)
  }
  if (key == 's') {
    py += 5; // Mueve al jugador hacia abajo
  }
  glutPostRedisplay(); // Solicita redibujar la pantalla
}

/**
 * init - Inicializa la configuración gráfica
 * Establece el color de fondo, el sistema de coordenadas 2D
 * y la posición inicial del jugador
 */
void init() {
  glClearColor(0.3, 0.3, 0.3, 0); // Color de fondo gris
  gluOrtho2D(
      0, 1024, 512,
      0);   // Define un sistema de coordenadas 2D: (izq, der, abajo, arriba)
  px = 300; // Posición inicial del jugador en X
  py = 300; // Posición inicial del jugador en Y
}

/**
 * main - Función principal del programa
 * @param argc: número de argumentos de línea de comandos
 * @param argv: array de argumentos de línea de comandos
 *
 * Inicializa GLUT, crea la ventana y establece las funciones de callback
 * para el renderizado y la entrada del teclado
 */
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);                        // Inicializa GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Usa doble buffer y modo RGBA
  glutInitWindowSize(1024, 512);                // Tamaño de la ventana
  glutCreateWindow("Raycasting");               // Crea la ventana con título
  init();                    // Llama a la función de inicialización
  glutDisplayFunc(display);  // Establece la función de dibujo
  glutKeyboardFunc(buttons); // Establece la función para manejo de teclado
  glutMainLoop();            // Inicia el bucle principal de eventos
  return 0;                  // Fin del programa
}
