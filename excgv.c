
//Examen Xoel González Pereira CGV OpenGL
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
GLfloat giro = 0.0f;
GLfloat giroV = 0.0f;
GLfloat giroH = 0.0f;
GLfloat constante = 30.0f;

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

void display(){ 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); //Carga la matriz identidad
  glTranslatef(0.0f,0.0f,-15.0f);
  glRotatef(angulo[0], 1.0f, 0.0f, 0.0f); //Rotación en X
  glRotatef(angulo[1], 0.0f, 1.0f, 0.0f); //Rotación en Y
  glRotatef(angulo[2], 0.0f, 0.0f, 1.0f); //Rotación en Z


  //Base de la noria
  glPushMatrix();
  glRotatef(90.0f,1.0f,0.0f,0.0f);
  glColor3f(0.2f, 0.2f, 0.2f);
  gluCylinder(gluNewQuadric(), 8, 8, 2, 22, 22); //Hacemos un cilindo de altura 2
  glPopMatrix();


  glColor3f(0.5f, 0.5f, 0.5f);
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

  //Noria
  glColor3f(0.0f, 1.0f, 0.5f);
  glPushMatrix();
  glRotatef(-90,1.0f,0.0f,0.0f);
  glutSolidCone(7.5f,6.0f,16,16); //Hacemos un cono de altura 6
  glPopMatrix();

  //Brazo
  glPushMatrix();
  glRotatef(giro,0.0f,1.0f,0.0f);
  glPushMatrix();
  glColor3f(0.0f, 1.0f, 1.0f);

  glTranslatef(0.0f,6.0f,0.0f);
  glRotatef(giroV,0.0f,0.0f,1.0f); //Rotamos la figura 
  glTranslatef(0.0f,-6.0f,0.0f);
  
  glPushMatrix();
  glTranslatef(2.0f,6.0f,0.0f);
  glScalef(4.0f,0.5f,0.5f);
  glutSolidCube(1.0f);
  glPopMatrix();

  //Vagón
  glColor3f(0.0f, 0.5f, 1.0f);
  glPushMatrix();
  glTranslatef(4.0f,6.5f,0.0f);
  glRotatef(-giroV,0.0f,0.0f,1.0f);
  glRotatef(giroH,0.0f,1.0f,0.0f);

  glRotatef(90,1.0f,0.0f,0.0f);
  glutSolidCone(1.0f,1.0f,16,16); //Hacemos un cono de altura 1 para darle forma al vagón
  glRotatef(-90.0f,1.0f,0.0f,0.0f); //Rotamos en el eje X 

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i++) { //Cubierta del vagón
      glVertex3f(1 * cos(i * PI / 180), 0.0f, 1 * sin(i * PI / 180));
  }
  glEnd();

  glColor3f(1.0f,0.0f,0.0f); //Color de los cubos del vagón
  //Cubo 1
  glPushMatrix();
  glTranslatef(0.5f,0.2f,0.5f);
  glutSolidCube(0.4f); 
  glPopMatrix();
  //Cubo 2
  glPushMatrix();
  glTranslatef(0.5f,0.2f,-0.5f);
  glutSolidCube(0.4f);
  glPopMatrix();
  //Cubo 3
  glPushMatrix();
  glTranslatef(-0.5f,0.2f,0.5f);
  glutSolidCube(0.4f);
  glPopMatrix();
  //Cubo 4
  glPushMatrix();
  glTranslatef(-0.5f,0.2f,-0.5f);
  glutSolidCube(0.4f);
  glPopMatrix();

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
        giroV=-constante;
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
    if (glutGetModifiers() == GLUT_ACTIVE_CTRL){ //si mantenemos CTRL 
      raton=1;
    }else{ //por defecto si mantenemos el click izquierdo la variable estará en 0
      raton=0; 
    }
  }
}
void mover_con_mouse(int x, int y) {  
    static int lastX = 0, lastY = 0; // Variables para almacenar la última posición del mouse
    // Calculamos la diferencia entre la posición actual y la anterior del mouse
    int deltaX = x - lastX;
    int deltaY = y - lastY;
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
    giro = giro + vel2;  
    giroH = giroH + vel2;  
    
    if (giroV > constante || giroV < -constante) { //Si el giro llega a alguno de los límites
     pos = (pos == 1) ? 0 : 1; //Si está arriba baja, si está abajo sube
    }
    
    giroV = (pos == 1) ? giroV + vel2 : giroV - vel2; 
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
    glutCreateWindow("Examen CGV"); //Crea la ventana
    init();
    glutDisplayFunc(display); //Función de control de render
    glutReshapeFunc(reshape); //Función de control de cambio  de tamaño de ventana 
    //glutIdleFunc(idle); //Función que se activa cuando no hacemos nada
    glutTimerFunc(vel, obtenerRotacion,0); //Función de timer
    glutKeyboardFunc(keyboard); //Función de control de eventos con el teclado
    glutMouseFunc(mouse);
    glutMotionFunc(mover_con_mouse);


    int v = glutCreateMenu(velocidad);//Menú para ajustar la velocidad
    glutAddMenuEntry("Rapido", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Lento", 2);
    glutCreateMenu(menu);

    //Títulos de los menús
    glutAddSubMenu("Cambio Velocidad",v);
    glutAddMenuEntry("Salir", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //Abrimos el menú con el botón derecho del ratón
    glutMainLoop();
    return 0;
}
