

//Examen Xoel González Pereira CGV OpenGL
//El cono principal no se mueve a no ser que se use el ratón, la taza y el brazo sí
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define PI 3.141592653
GLint ancho = 800;
GLint alto = 800;
GLfloat vel2=5.0f;
GLint vel = 90;
GLint hazPerspectiva = 0;
GLint color = 0;
GLint raton=0;
GLint automatico_activado =1;
GLint pos = 1;
GLfloat angulo[3] = {0.0f, 0.0f, 0.0f};
GLfloat giro_total = 0.0f;
GLfloat giro_taza_vertical = 0.0f;
GLfloat giro_taza_horizontal = 0.0f;
GLfloat constante = 45.0f;

void reshape(int width, int height) 
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

  if(hazPerspectiva)
    gluPerspective(120.0f, (GLfloat)width/(GLfloat)height, 1.f, 20.0f); //Proyección perspectiva
  else       
    glOrtho(-20,20, -20, 20, 1, 25); //Proyección ortogonal
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}


void hacer_personas() {
     //Color de los cubos del vagón
  if(color == 0){
  glColor3f(1.0f, 1.0f, 1.0f); //Blanco
  }else if(color == 1){
  glColor3f(1.0f, 1.0f, 0.0f); //Amarillo
  }else if(color == 2){
    glColor3f(1.0f, 0.5f, 0.0f); //Naranja
  }else if(color == 3){
    glColor3f(0.0f, 1.0f, 0.5f); //Verde
  }

  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    if (i == 0) {
        glTranslatef(0.5f, 0.2f, 0.5f);
    } else if (i == 1) {
        glTranslatef(0.5f, 0.2f, -0.5f);
    } else if (i == 2) {
        glTranslatef(-0.5f, 0.2f, 0.5f);
    } else if (i == 3) {
        glTranslatef(-0.5f, 0.2f, -0.5f);
    }

    glutSolidCube(0.4f);
    glPopMatrix();
    }
}


void display(){ 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); //Carga la matriz identidad
  glTranslatef(0.0f,0.0f,-15.0f);
  glRotatef(angulo[0], 1.0f, 0.0f, 0.0f); //Rotación en X
  glRotatef(angulo[1], 0.0f, 1.0f, 0.0f); //Rotación en Y
  glRotatef(angulo[2], 0.0f, 0.0f, 1.0f); //Rotación en Z

  //Base de la atracción
  glPushMatrix();
  glRotatef(90.0f,1.0f,0.0f,0.0f);
  glColor3f(1.0f, 0.5f, 0.4f);
  gluCylinder(gluNewQuadric(), 8, 8, 2, 22, 22); //Hacemos un cilindo de altura 2
  glPopMatrix();

  glColor3f(1.0f, 0.5f, 0.4f);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i++) { //Primera cubierta (mismo radio que el cilindro para cerrarlo)
    glVertex3f(8 * cos(i * PI / 180), 0.0f, 8 * sin(i * PI / 180));
  }
  glEnd();
  glPushMatrix();
  glTranslatef(0.0f,-1.0f,0.0f);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i++) { //Segunda cubierta
      glVertex3f(8 * cos(i * PI / 180), -1.0f, 8 * sin(i * PI / 180));
  }
  glEnd();
  glPopMatrix();

  //Cono de la atracción
  glColor3f(0.0f, 1.0f, 0.5f);
  glPushMatrix();
  glRotatef(-90,1.0f,0.0f,0.0f);

  glutSolidCone(7.5f,7.0f,12,12); //Hacemos un cono de altura 7
  glPopMatrix();

  //Extensión
  glPushMatrix();
  glRotatef(giro_total,0.0f,1.0f,0.0f);
  glPushMatrix();
  glColor3f(0.0f, 1.0f, 1.0f);

  glTranslatef(0.0f,7.0f,0.0f); 
  glRotatef(giro_taza_vertical,0.0f,0.0f,1.0f); //Rotamos la figura 
  glTranslatef(0.0f,-7.0f,0.0f);
  
  glPushMatrix();
  glTranslatef(2.0f,7.0f,0.0f);
  glScalef(4.0f,0.5f,0.5f);
  glutSolidCube(1.0f);
  glPopMatrix();

  //Taza
  glColor3f(0.0f, 0.5f, 1.0f);
  glPushMatrix();
  glTranslatef(4.0f,7.5f,0.0f);
  glRotatef(-giro_taza_vertical,0.0f,0.0f,1.0f);
  glRotatef(giro_taza_horizontal,0.0f,1.0f,0.0f);

  glRotatef(90,1.0f,0.0f,0.0f);
  glutSolidCone(1.0f,1.0f,12,12); //Hacemos un cono de altura 1 para darle forma a la taza
  glRotatef(-90.0f,1.0f,0.0f,0.0f); 

  glPushMatrix();
  hacer_personas();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();

//glFlush();
  glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y ){ //Función para controlar el uso de teclas

  switch(key){
    
   case 'P': //Al pulsar esta tecla cambiamos la proyección a perspectiva
   case 'p':
      hazPerspectiva=1;
      reshape(ancho,alto);
      break;
 
    case 'O': //Al pulsar esta tecla cambiamos la proyección a ortogonal
    case 'o':
      hazPerspectiva=0;
      reshape(ancho,alto);
      break;
    
    case 's': //Al pulsar esta tecla la atracción empieza a girar, si la presionamos mientras
              //está en movimiento, se parará y se quedará posicionada en el ángulo negativo del giro vertical
    case 'S':
      if (automatico_activado==0){ //si está parada y pulsamos la tecla se pone a uno
        automatico_activado=1;
      } else{ // si está en movimiento se para y se queda posicionada en el ángulo negativo
        automatico_activado=0;
        giro_taza_vertical=-constante;
      }
      break;

    case 'r': //Al pulsar esta tecla cambiamos el sentido del giro
    case 'R':
      vel2= -vel2;
      break;
  }
}

void mouse(int boton, int estado, int x, int y){ 
  if (boton==GLUT_LEFT_BUTTON){
    if (glutGetModifiers() == GLUT_ACTIVE_ALT){ //si mantenemos ALT 
      raton=0;
    }else{ //por defecto si mantenemos el click izquierdo la variable estará en 0
      raton=1; 
    }
  }
}
void mover_con_mouse(int x, int y) {  
    static int lastX = 0, lastY = 0; // Variables para almacenar la última posición del mouse
    // Calculamos la diferencia entre la posición actual y la anterior del mouse
    int deltaX = x - lastX;
    int deltaY = y - lastY;

    giro_taza_horizontal +=5; //Podemos mover con el ratón la taza en cualquier dirección
    giro_taza_vertical +=5;



    if (raton == 0) {  //si solo hacemos click izquierdo moveremos la figura en el eje X
        angulo[0] += deltaY;
        angulo[0] += deltaX;
      
    } else {  //Si la variable del ratón está en uno movemos la figura en el eje Y 
        angulo[1]+= deltaY;
        angulo[1]+= deltaX; 

    }
    // Almacena la posición actual del mouse 
    lastX = x;
    lastY = y;
    glutPostRedisplay(); 
}


void obtenerRotacion(int x) {
 
  if (automatico_activado == 1) { //Si la atracción está en movimiento
    giro_total = giro_total + vel2;  
    giro_taza_horizontal = giro_taza_horizontal + vel2;  
    if (giro_taza_vertical > constante || giro_taza_vertical < -constante) { //Si el giro llega a alguno de los límites
     pos = (pos == 1) ? 0 : 1; //Si está arriba baja, si está abajo sube
    }
    
    giro_taza_vertical = (pos == 1) ? giro_taza_vertical + vel2 : giro_taza_vertical - vel2; 
  }
  glutPostRedisplay();
  glutTimerFunc(vel, obtenerRotacion, 0); //Función de timer
}


void velocidad(int opcion){ //Selección de velocidades
  switch (opcion){
    case 0: //Rápido
      vel=20;
      break;
    case 1: //Medio
      vel=50;
      break;
    case 2: //Lento
      vel=90;
      break;
  }
}



void forma(int opcion) { 
    switch (opcion) { //Dependiendo de la opción seleccionada se asignará un valor a la variable color
    case 0:   
        color = 0; //Blanco
        break;
    case 1:
        color = 1; //Amarillo
        break;
    case 2:
        color = 2; //Naranja
        break;
    case 3:
        color = 3; //Verde
        break;
    }
}

void menu( int opcion){  
  if (opcion == 0) //Si se selecciona la opción salir
    exit(-1);
}

void init() 
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);//activamos también z-buffer
}

void idle() 
{
    display();
}

int main(int argc, char** argv) 
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //activamos también z-buffer
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(alto, ancho);
    glutCreateWindow("Examen Tazas CGV"); //Crea la ventana
    init();
    glutDisplayFunc(display); //Función de control de render
    glutReshapeFunc(reshape); //Función de control de cambio  de tamaño de ventana 
    //glutIdleFunc(idle); //Función que se activa cuando no hacemos nada
    glutTimerFunc(vel, obtenerRotacion,0); //Función de timer
    glutKeyboardFunc(keyboard); //Función de control de eventos con el teclado
    glutMouseFunc(mouse);
    glutMotionFunc(mover_con_mouse);


    int f = glutCreateMenu(forma); //menú para la forma de los objetos
    glutAddMenuEntry("Color blanco", 0);
    glutAddMenuEntry("Color amarillo", 1);
    glutAddMenuEntry("Color naranja", 2);
    glutAddMenuEntry("Color verde", 3);


    int v = glutCreateMenu(velocidad);//Menú para ajustar la velocidad
    glutAddMenuEntry("Rapido", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Lento", 2);
    glutCreateMenu(menu);

    //Títulos de los menus
    glutAddSubMenu("Cambio de color",f); 
    glutAddSubMenu("Cambio Velocidad",v);
    glutAddMenuEntry("Salir", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //Abrimos el menú con el botón derecho del ratón
    glutMainLoop();
    return 0;
}
