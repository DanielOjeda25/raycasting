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
 *
 * Funcionamiento línea por línea:
 * 1. glColor3f(1, 1, 0)    - Establece el color de dibujo a amarillo usando
 * valores RGB (1,1,0)
 * 2. glPointSize(8)        - Define el tamaño del punto a dibujar en 8 píxeles
 * 3. glBegin(GL_POINTS)    - Inicia el modo de dibujo de puntos en OpenGL
 * 4. glVertex2i(px, py)    - Especifica las coordenadas (px,py) donde se
 * dibujará el punto
 * 5. glEnd()               - Finaliza el modo de dibujo actual
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
 *
 * Funcionamiento línea por línea:
 * 1. Declaración de variables x, y para iterar sobre el mapa y xo, yo para las
 * coordenadas de dibujo
 * 2. Bucle exterior (y) - Recorre las filas del mapa
 * 3. Bucle interior (x) - Recorre las columnas del mapa
 * 4. Condición if      - Verifica si la celda actual es una pared (1) o espacio
 * vacío (0)
 * 5. glColor3f()      - Establece el color: blanco para paredes, negro para
 * espacios
 * 6. Cálculo de xo, yo - Convierte coordenadas de mapa a coordenadas de
 * pantalla
 * 7. glBegin(GL_QUADS) - Inicia el modo de dibujo de cuadriláteros
 * 8-11. glVertex2i()   - Define los cuatro vértices del cuadrado con offset de
 * 1 píxel
 * 12. glEnd()          - Finaliza el modo de dibujo de cuadriláteros
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
      glVertex2i(xo + 1, yo + 1);
      glVertex2i(xo + 1, yo + mapS - 1);
      glVertex2i(xo + mapS - 1, yo + mapS - 1);
      glVertex2i(xo + mapS - 1, yo + 1);
      glEnd();
    }
  }
}

/**
 * display - Función principal de renderizado
 *
 * Funcionamiento línea por línea:
 * 1. glClear()         - Limpia los buffers de color y profundidad
 * 2. drawMap2D()       - Llama a la función que dibuja el mapa 2D
 * 3. drawPlayer()      - Llama a la función que dibuja al jugador
 * 4. glutSwapBuffers() - Intercambia los buffers frontal y trasero para mostrar
 * el resultado
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
 *
 * Funcionamiento línea por línea:
 * 1. Parámetros de entrada:
 *    - key: código ASCII de la tecla presionada
 *    - x, y: coordenadas del mouse (no utilizadas)
 * 2. if (key == 'a') - Verifica si se presionó la tecla 'a' y mueve a la
 * izquierda
 * 3. if (key == 'd') - Verifica si se presionó la tecla 'd' y mueve a la
 * derecha
 * 4. if (key == 'w') - Verifica si se presionó la tecla 'w' y mueve hacia
 * arriba
 * 5. if (key == 's') - Verifica si se presionó la tecla 's' y mueve hacia abajo
 * 6. glutPostRedisplay() - Solicita a GLUT que redibuje la ventana
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
 *
 * Funcionamiento línea por línea:
 * 1. glClearColor()  - Define el color de fondo de la ventana en gris (RGB:
 * 0.3, 0.3, 0.3, 0)
 * 2. gluOrtho2D()    - Configura la proyección ortográfica 2D (0,0) a
 * (1024,512)
 * 3. px = 300        - Establece la posición inicial del jugador en X
 * 4. py = 300        - Establece la posición inicial del jugador en Y
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
 *
 * Funcionamiento línea por línea:
 * 1. glutInit()           - Inicializa la biblioteca GLUT
 * 2. glutInitDisplayMode() - Configura el modo de visualización (doble buffer y
 * RGBA)
 * 3. glutInitWindowSize() - Define el tamaño inicial de la ventana
 * 4. glutCreateWindow()   - Crea la ventana con el título especificado
 * 5. init()               - Llama a la función de inicialización personalizada
 * 6. glutDisplayFunc()    - Registra la función de callback para el dibujado
 * 7. glutKeyboardFunc()   - Registra la función de callback para el teclado
 * 8. glutMainLoop()       - Inicia el bucle principal de eventos de GLUT
 * 9. return 0            - Finaliza el programa (aunque nunca se alcanza por
 * glutMainLoop)
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
