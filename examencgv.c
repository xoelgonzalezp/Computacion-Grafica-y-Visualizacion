
//Examen Xoel González Pereira CGV OpenGL
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define PI 3.141592653
GLint ancho = 800;
GLint alto = 800;
GLfloat vel2=5.0f;
GLint vel = 90;
GLint hazPerspectiva = 0;
GLint raton = 0;
GLint automatico_activado =0;
GLint color = 0;
GLint invertir =0;
GLfloat angulo[3] = {0.0f, 0.0f, 0.0f};
GLfloat giro = 0.0f;


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

  //Base 
  glPushMatrix();
  glRotatef(90.0f,1.0f,0.0f,0.0f);
  glColor3f(0.3f, 0.3f, 0.3f);
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
  //Cara 1 
  glBegin(GL_TRIANGLES);
  glColor3f(0.0f, 1.0f, 0.5f);  //Hacemos las caras verdes
  glVertex3f(-8.0f, 0.0f, 0.5f);
  glVertex3f(0.0f, 5.0f, 0.5f);
  glVertex3f(8.0f, 0.0f,0.5f);
  glEnd();

  //Cara 2
  glBegin(GL_TRIANGLES);
  glColor3f(0.0f, 1.0f, 0.5f); 
  glVertex3f(-8.0f, 0.0f, -1.5f);
  glVertex3f(0.0f, 5.0f, -1.5f);
  glVertex3f(8.0f, 0.0f, -1.5f);
  glEnd();

  //Lados
  //Lado 1
  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f); 
  glVertex3f(-8.0f, 0.0f, 0.5f);
  glVertex3f(0.0f, 5.0f, 0.5f);
  glVertex3f(0.0f, 5.0f, -1.5f);
  glVertex3f(-8.0f, 0.0f, -1.5f);
  glEnd();
  //Lado 2
  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f); 
  glVertex3f( 8.0f, 0.0f, 0.5f);
  glVertex3f( 0.0f, 5.0f,  0.5f);
  glVertex3f( 0.0f, 5.0f, -1.5f);
  glVertex3f( 8.0f, 0.0f, -1.5f);
  glEnd();
  //Suelo
  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-8.0f, 0.0f,  0.5f);
  glVertex3f( 8.0f, 0.0f,  0.5f);
  glVertex3f( 8.0f, 0.0f, -1.5f);
  glVertex3f(-8.0f, 0.0f, -1.5f);
  glEnd();

  //Brazo
  glPushMatrix();
  glTranslatef(0.0f,5.0f,0.0f);
  glRotatef(giro,0.0f,0.0f,1.0f);
  glTranslatef(0.0f,-5.0f,0.0f);
  glColor3f(0.0f, 1.0f, 1.0f);
  glPushMatrix();
  glTranslatef(0.0f,3.0f,0.75f);
  glScalef(2.0f,8.0f,1.0f);
  glutSolidCube(0.5f);
  glPopMatrix();

  //Vagón
  glColor3f(0.0f, 0.5f, 1.0f);
  glPushMatrix();
  glTranslatef(0.0f,1.0f,2.0f);
  glRotatef(-giro,0.0f,0.0f,1.0f);
  glPushMatrix();
  glScalef(2.0f,1.0f,2.0f);
  glutSolidCube(1);
  glPopMatrix();

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

  //Cubo 1
  glPushMatrix();
  glTranslatef(-0.5f,0.75f,0.5f);
  glutSolidCube(0.5f);
  glPopMatrix();

  //Cubo 2
  glPushMatrix();
  glTranslatef(-0.5f,0.75f,-0.5f);
  glutSolidCube(0.5f);
  glPopMatrix();
  
  //Cubo 3
  glPushMatrix();
  glTranslatef(0.5f,0.75f,0.5f);
  glutSolidCube(0.5f);
  glPopMatrix();

  //Cubo 4
  glPushMatrix();
  glTranslatef(0.5f,0.75f,-0.5f);
  glutSolidCube(0.5f);
  glPopMatrix();

  
  glPopMatrix(); 
  glPopMatrix();

//glFlush();
  glutSwapBuffers();

}

void mouse(int boton, int estado, int x, int y){ 
  if (boton==GLUT_LEFT_BUTTON){
    if (glutGetModifiers() == GLUT_ACTIVE_CTRL){  //si mantenemos CTRL 
      raton=0;
    }else{ //por defecto si mantenemos el click izquierdo la variable estará en 1
      raton=1; 
    }
  }
}
void mover_con_mouse(int x, int y) {  
    static int lastX = 0, lastY = 0; // Variables para almacenar la última posición del mouse
    // Calculamos la diferencia entre la posición actual y la anterior del mouse
    int deltaX = x - lastX;
    int deltaY = y - lastY;
    if (raton == 1) {  //si solo hacemos click izquierdo moveremos la figura en el eje X
        angulo[0] += deltaY;
        angulo[0] += deltaX;
    } else { //Si la variable del ratón está en cero movemos la figura en el eje Y 
        angulo[1]+= deltaY;
        angulo[1]+= deltaX; 
    }
    // Almacena la posición actual del mouse 
    lastX = x;
    lastY = y;
    glutPostRedisplay(); 
}


void keyboard(unsigned char key, int x, int y ){ //Función para controlar el uso de teclas

  switch(key){
  
    case 'S': //Al pulsar esta tecla la atracción empieza a girar, si la presionamos mientras
              //está en movimiento, volverá a estar parada en el inicio
    case 's':
      if (automatico_activado==0){
        automatico_activado=1;
        giro=1;
      } else
        automatico_activado=0;   
        giro=0; 
      break;

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
    
    case 'R': //Al pulsar esta tecla cambiamos el sentido del giro
    case 'r':
      vel2= -vel2;
      invertir += 1;
      if(invertir ==2){ //si el contador llega a dos, vuelve a girar en el sentido del inicio
        invertir = 0;
      }
      break;

    case 'Q': //Al pulsar esta tecla aumentamos grados en el eje X
    case 'q':
      angulo[0]+=vel2;
      break;
    
    case 'A': //Al pulsar esta tecla restamos grados en el eje X
    case 'a':
      angulo[0]-=vel2;
      break;
    
    case 'W': //Al pulsar esta tecla aumentamos grados en el eje Y
    case 'w':
      angulo[1]+=vel2;
      break;
    
    case 'E': //Al pulsar esta tecla restamos grados en el eje Y
    case 'e':    
      angulo[1]-=vel2;
      break; 

    default:
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
  if (opcion == 0){ //Si se selecciona la opción salir
    exit(-1);
  }
}


float obtenerRotacion() { 
/*Si no se ha presionado la tecla de invertir, 
cuando el giro sea de más de 180 grados, duplica la velocidad
Si se ha presionado la tecla de invertir, 
cuando el giro sea de menos de 180 grados, duplica la velocidad
Devuelve 0 si el automático no está activado*/

float increment = (automatico_activado == 1) ? 
  ((invertir == 0 && giro > 180) || (invertir == 1 && giro < 180)) ? 2 * vel2 : vel2 
    : 0.0;
  return increment;
}

void ajuste() {
  if (automatico_activado == 1) {
    giro += obtenerRotacion(); // Incrementa el ángulo

    // Ajusta el ángulo para mantenerlo en el rango [0, 360]
    giro = (giro >= 360) ? giro - 360 : (giro < 0) ? giro + 360 : giro;
  }
  glutPostRedisplay();
  glutTimerFunc(vel, ajuste, 0); // Función de timer
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

void init() 
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);//Activamos también z-buffer
}

void idle() 
{
    display();
}

int main(int argc, char** argv) 
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Activamos también z-buffer
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(alto, ancho);
    glutCreateWindow("Examen CGV"); //Crea la ventana
    init();
    glutDisplayFunc(display); //Función de control de render
    glutReshapeFunc(reshape); //Función de control de cambio  de tamaño de ventana 
    //glutIdleFunc(idle); //Función que se activa cuando no hacemos nada
    glutTimerFunc(vel, ajuste,0); //Función de timer
    glutKeyboardFunc(keyboard); //Función de control de eventos con el teclado
    glutMouseFunc(mouse);
    glutMotionFunc(mover_con_mouse);

    int f = glutCreateMenu(forma); //menú para la forma de los objetos
    glutAddMenuEntry("Color blanco", 0);
    glutAddMenuEntry("Color amarillo", 1);
    glutAddMenuEntry("Color naranja", 2);
    glutAddMenuEntry("Color verde", 3);

    int v = glutCreateMenu(velocidad);//menú para ajustar la velocidad
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
