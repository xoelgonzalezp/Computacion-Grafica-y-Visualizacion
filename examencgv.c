
//Examen Xoel González Pereira CGV OpenGL
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLint ancho = 500;
GLint alto = 500;
GLint vel2=5;
GLint hazPerspectiva = 0;
GLint rotarFiguraCompleta = 0;
GLint alambre = 0;
GLint raton = 0;
GLint automatico_activado =0;
GLfloat angulo[3] = {0.0f, 0.0f, 0.0f};
GLfloat brazo = 0.0f;
GLfloat color[3] = {1.0f, 1.0f, 1.0f};


void reshape(int width, int height) //checked
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

    if (hazPerspectiva)
        gluPerspective(70.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f); //proyección perspecti
    else
    {
      glOrtho(-12,12, -12, 12, 1, 15);
    }
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}




void display(){ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  //Profundidad y angulo de toda la figura
  glTranslatef(0.0f,0.0f,-10);

  //Rotacion X
  glRotatef(angulo[0], 1.0f, 0.0f, 0.0f);
  //Rotacion Y
  glRotatef(angulo[1], 0.0f, 1.0f, 0.0f);
  //Rotacion Z
  glRotatef(angulo[2], 0.0f, 0.0f, 1.0f);

  //Base
  //-----
  //Cilindro
  glPushMatrix();
  glRotatef(90.0f,1.0f,0.0f,0.0f);
  glColor3f(0.2f, 0.2f, 0.2f);
  GLUquadric* qobj = gluNewQuadric();
  gluCylinder(qobj, 5, 5, 1, 32, 32);
  glPopMatrix();

  //Tapas
  float alfa;
  glColor3f(0.7f, 0.7f, 0.7f);
     
  glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++) {
        alfa = i * 3.1416 / 180;
        glVertex3f(5 * cos(alfa), 0.0f, 5 * sin(alfa));
    }
  glEnd();

  glPushMatrix();
  glTranslatef(0.,-1,0.);
  glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++) {
        alfa = i * 3.1416 / 180;
        glVertex3f(5 * cos(alfa), 0.0f, 5 * sin(alfa));
    }
  glEnd();
  glPopMatrix();


  glBegin(GL_TRIANGLES);

  //Triángulo Cara 1 
  glColor3f(0.0, 1.0, 0.5f); 
  glVertex3f(-0.5 * 9, 0.0f, 0.5 * 1);
  glVertex3f(0.0f, 5, 0.5 * 1);
  glVertex3f(0.5 * 9, 0.0f, 0.5 * 1);

  //Triángulo Cara 2
  glColor3f(0.0, 1.0, 0.5f); 
  glVertex3f(-0.5 * 9, 0.0f, -0.5 * 1);
  glVertex3f(0.0f, 5, -0.5 * 1);
  glVertex3f(0.5 * 9, 0.0f, -0.5 * 1);

  glEnd();

  glBegin(GL_QUADS);

  //Rectángulo 1 
  glColor3f(0.0, 1.0, 0.0f); 
  glVertex3f(-0.5 * 9, 0.0f, 0.5 * 1);
  glVertex3f(0.0f, 5, 0.5 * 1);
  glVertex3f(0.0f, 5, -0.5 * 1);
  glVertex3f(-0.5 * 9, 0.0f, -0.5 * 1);

  //Rectángulo 2
  glColor3f(0.0, 1.0, 0.0f); 
  glVertex3f( 0.5 * 9, 0.0f, 0.5 * 1);
  glVertex3f( 0.0, 5, 0.5 * 1);
  glVertex3f( 0.0, 5, -0.5 * 1);
  glVertex3f( 0.5 * 9, 0.0f, -0.5 * 1);

  //Rectángulo 3
  glColor3f(0.0, 1.0, 0.0f);
  glVertex3f(-0.5 * 9, 0.0f,  0.5 * 1);
  glVertex3f( 0.5 * 9, 0.0f,  0.5 * 1);
  glVertex3f( 0.5 * 9, 0.0f, -0.5 * 1);
  glVertex3f(-0.5 * 9, 0.0f, -0.5 * 1);

  glEnd();

  //Brazo
  glPushMatrix();
  //Rotacion Brazo
  glTranslatef(0,5,0);
  glRotatef(brazo,0,0,1);
  glTranslatef(0,-5,0);
    //Brazo
  glColor3f(0.7f, 0.1f, 0.7f);
  glPushMatrix();
  glTranslatef(0.0f,3.0f,0.75f);
  glScalef(1.0f,8.0f,1.0f);
  glutSolidCube(.5);
  glPopMatrix();

  //Mano
  glColor3f(0.7f, 0.1f, 0.2f);
  glPushMatrix(); //-
  glTranslatef(0.,1.,2.);
  glRotatef(-brazo,0,0,1);

  glPushMatrix();
  glScalef(1.0f,0.25f,1.0f);
  glutSolidCube(2);
  glPopMatrix();

  //Personas
  glColor3f(color[0], color[1], color[2]);

  glPushMatrix();
  glTranslatef(-0.5,0.5,0.5);
  glutSolidCube(.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5,0.5,-0.5);
  glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5,0.5,0.5);
  glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5,0.5,-0.5);
  glutSolidCube(0.5);
  glPopMatrix();

  
  glPopMatrix(); 
  glPopMatrix();

  glFlush();
  glutSwapBuffers();


}
void mouse(int boton, int estado, int x, int y){ //checked
  if (boton==GLUT_LEFT_BUTTON){
    if (glutGetModifiers() == GLUT_ACTIVE_CTRL)  
      raton=0;
    else
      raton=1; 
  }
}
void mover_con_mouse(int x, int y) {  //checked
    static int lastX = 0, lastY = 0; // Variables para almacenar la última posición del mouse
    // Calculamos la diferencia entre la posición actual y la anterior del mouse
    int deltaX = x - lastX;
    int deltaY = y - lastY;
    if (raton == 1) { 
        angulo[0]+= deltaY;
        angulo[0] += deltaX;
    } else { 
        angulo[1]+= deltaY;
        angulo[1]+= deltaX; 
    }
    // Almacena la posición actual del mouse 
    lastX = x;
    lastY = y;
    glutPostRedisplay(); 
}


void keyboard(unsigned char key, int x, int y ){

  switch(key){
  
    case 'G':
    case 'g':
      if (automatico_activado==1){
        automatico_activado=0;
        brazo=0;
      } else
        automatico_activado=1;    
      break;
    
    //Perspectiva 
    case 'p':
    case 'P':
    case 'o':
    case 'O':
      if (hazPerspectiva==1)
        hazPerspectiva=0;
      else
        hazPerspectiva=1;
      reshape(ancho,alto);
      break;
    
    //Invertir 
    case 'H':
    case 'h':
      vel2=-vel2;
      break;

    //Mover 
    //X
    case 'Q':
    case 'q':
      angulo[0]=angulo[0]+vel2;
      break;
    
    case 'A':
    case 'a':
      angulo[0]=angulo[0]-vel2;
      break;
    
    //Y
    case 'W':
    case 'w':
      angulo[1]=angulo[1]+vel2;
      break;
    
    case 'S':
    case 's':    
      angulo[1]=angulo[1]-vel2;
      break; 

    default:
      break; 
  }
}


void movimiento(int opcion){ //checked
  automatico_activado=opcion;
}

void forma(int opcion) {
    switch (opcion) {
    case 0:
        color[0] = 1.0;
        color[1] = 1.0;
        color[2] = 1.0; // Blanco
        break;

    case 1:
        color[0] = 1.0;
        color[1] = 1.0;
        color[2] = 0.0; // Amarillo
        break;

    case 2:
        color[0] = 1.0;
        color[1] = 0.5;
        color[2] = 0.0; // Naranja
        break;

    case 3:
        color[0] = 0.0;
        color[1] = 1.0;
        color[2] = 0.5; // Verde
        break;
    }
}
void menu( int opcion){  //checked
  if (opcion==0)
    exit(-1);
}

float obtenerRotacion() {
  if (automatico_activado == 1) {
    float increment = vel2;
    if (fabs(brazo) > 180) {
      increment = 2 * vel2;
    }
    return increment;
  } else {
    return 0.0; // Devuelve 0 si el automático no está activado
  }
}

void ajuste() { 
  if (automatico_activado == 1) {
    brazo += obtenerRotacion(); // Incrementa el ángulo
    
    // Ajusta el ángulo para mantenerlo en el rango [0, 360]
    if (brazo >= 360) {
      brazo -= 360;
    } else if (brazo < 0) {
      brazo += 360;
    }
  }
  glutPostRedisplay();
  glutTimerFunc(50, ajuste, 0);
}


void velocidad(int opcion){ //checked
  switch (opcion){
    case 0:
      vel2=30;
      break;

    case 1:
      vel2=15;
      break;

    case 2:
      vel2=5;
      break;
  }
}

void init() //checked
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);//activamos también z-buffer
}

void idle() //checked
{
    display();
}

int main(int argc, char** argv) //checked
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //activamos también z-buffer
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(alto, ancho);
    glutCreateWindow("Ejercicio Practicas"); //Crea la ventana
    init();
    glutDisplayFunc(display); //función de control de render
    glutReshapeFunc(reshape); //función de control de cambio  de tamaño de ventana 
    //glutIdleFunc(idle); //función que se activa cuando no hacemos nada
    glutTimerFunc(50, ajuste,0); //funcion de timer
    glutKeyboardFunc(keyboard); //función de control de eventos con el teclado
    glutMouseFunc(mouse);
    glutMotionFunc(mover_con_mouse);

    int f = glutCreateMenu(forma); //menu para la forma de los objetos
    glutAddMenuEntry("Color blanco", 0);
    glutAddMenuEntry("Color amarillo", 1);
    glutAddMenuEntry("Color naranja", 2);
    glutAddMenuEntry("Color verde", 3);

    int v = glutCreateMenu(velocidad);//menu para ajustar la velocidad
    glutAddMenuEntry("Rapido", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Lento", 2);
    glutCreateMenu(menu);
    //Titulos de los menus
    glutAddSubMenu("Cambio de color",f); 
    glutAddSubMenu("Cambio Velocidad",v);
    glutAddMenuEntry("Salir", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //Abrimos el menu con el botón derecho del ratón
    glutMainLoop();
    return 0;
}