
//Examen Xoel González Pereira CGV OpenGL
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLint ancho = 800;
GLint alto = 800;
GLfloat vel2=5;
GLint vel = 90;
GLint hazPerspectiva = 0;
GLint rotarFiguraCompleta = 0;
GLint raton = 0;
GLint automatico_activado =0;
GLfloat angulo[3] = {0.0f, 0.0f, 0.0f};
GLfloat giro = 0.0f;
GLint color = 0;
GLint presionado =0;

void reshape(int width, int height) //checked
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

  if(hazPerspectiva)
    gluPerspective(120.0f, (GLfloat)width/(GLfloat)height, 1.f, 20.0f);
  else       
    glOrtho(-20,20, -20, 20, 1, 30);
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}


void display(){ 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-10.0f);
  glRotatef(angulo[0], 1.0f, 0.0f, 0.0f);
  glRotatef(angulo[1], 0.0f, 1.0f, 0.0f);
  glRotatef(angulo[2], 0.0f, 0.0f, 1.0f);

 
  //Cilindro
  glPushMatrix();
  glRotatef(90.0f,1.0f,0.0f,0.0f);
  glColor3f(0.2f, 0.2f, 0.2f);
  gluCylinder(gluNewQuadric(), 8, 8, 2, 32, 32);
  glPopMatrix();

  //Tapas
  glColor3f(0.5f, 0.5f, 0.5f);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i++) {
    glVertex3f(8 * cos(i * 3.1416 / 180), 0.0f, 8 * sin(i * 3.1416 / 180));
  }
  glEnd();

  glPushMatrix();
  glTranslatef(0.0f,-1.0f,0.0f);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i++) {
      glVertex3f(8 * cos(i * 3.1416 / 180), -1.0f, 8 * sin(i * 3.1416 / 180));
  }
  glEnd();
  glPopMatrix();


  glBegin(GL_TRIANGLES);
  //Triángulo Cara 1 
  glColor3f(0.0f, 1.0f, 0.5f); 
  glVertex3f(-8.0f, 0.0f, 0.5f);
  glVertex3f(0.0f, 5.0f, 0.5f);
  glVertex3f(8.0f, 0.0f,0.5f);

  //Triángulo Cara 2
  glColor3f(0.0f, 1.0f, 0.5f); 
  glVertex3f(-8.0f, 0.0f, -1.5f);
  glVertex3f(0.0f, 5.0f, -1.5f);
  glVertex3f(8.0f, 0.0f, -1.5f);
  glEnd();

  glBegin(GL_QUADS);
  //Rectángulo 1 
  glColor3f(0.0f, 1.0f, 0.0f); 
  glVertex3f(-8.0f, 0.0f, 0.5f);
  glVertex3f(0.0f, 5.0f, 0.5f);
  glVertex3f(0.0f, 5.0f, -1.5f);
  glVertex3f(-8.0f, 0.0f, -1.5f);

  //Rectángulo 2
  glColor3f(0.0f, 1.0f, 0.0f); 
  glVertex3f( 8.0f, 0.0f, 0.5f);
  glVertex3f( 0.0f, 5.0f,  0.5f);
  glVertex3f( 0.0f, 5.0f, -1.5f);
  glVertex3f( 8.0f, 0.0f, -1.5f);

  //Rectángulo 3
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-8.0f, 0.0f,  0.5f);
  glVertex3f( 8.0f, 0.0f,  0.5f);
  glVertex3f( 8.0f, 0.0f, -1.5f);
  glVertex3f(-8.0f, 0.0f, -1.5f);
  glEnd();

  //Brazo
  glPushMatrix();
  //Rotacion Brazo
  glTranslatef(0.0f,5.0f,0.0f);
  glRotatef(giro,0.0f,0.0f,1.0f);
  glTranslatef(0.0f,-5.0f,0.0f);
    //Brazo
  glColor3f(0.0f, 1.0f, 1.0f);
  glPushMatrix();
  glTranslatef(0.0f,3.0f,0.75f);
  glScalef(1.0f,8.0f,1.0f);
  glutSolidCube(.5);
  glPopMatrix();

  //Mano
  glColor3f(0.0f, 0.5f, 1.0f);
  glPushMatrix();
  glTranslatef(0.0f,1.0f,2.0f);
  glRotatef(-giro,0.0f,0.0f,1.0f);

  glPushMatrix();
  glScalef(1.0f,0.25f,1.0f);
  glutSolidCube(2);
  glPopMatrix();

  //Personas
  if(color == 0){
  glColor3f(1.0f, 1.0f, 1.0f);
  }else if(color == 1){
  glColor3f(1.0f, 1.0f, 0.0f);
  }else if(color == 2){
    glColor3f(1.0f, 0.5f, 0.0f);
  }else if(color == 3){
    glColor3f(0.0f, 1.0f, 0.5f);
  }
  glPushMatrix();
  glTranslatef(-0.5f,0.5f,0.5f);
  glutSolidCube(.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5f,0.5f,-0.5f);
  glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5f,0.5f,0.5f);
  glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5f,0.5f,-0.5f);
  glutSolidCube(0.5);
  glPopMatrix();

  
  glPopMatrix(); 
  glPopMatrix();

//glFlush();
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
        angulo[0] += deltaY;
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
  
    case 'S':
    case 's':
      if (automatico_activado==0){
        automatico_activado=1;
        giro=1;
      } else
        automatico_activado=0;   
        giro=0; 
      break;
    
   case 'P':
   case 'p':
      hazPerspectiva=1;
      reshape(ancho,alto);
      break;
 
    case 'O':
    case 'o':
      hazPerspectiva=0;
      reshape(ancho,alto);
      break;
    
    case 'R':
    case 'r':
      
      vel2= -vel2;
      presionado += 1;
      if(presionado ==2){
        presionado = 0;
      }
      break;

    case 'Q':
    case 'q':
      angulo[0]+=vel2;
      break;
    
    case 'A':
    case 'a':
      angulo[0]-=vel2;
      break;
    
    case 'W':
    case 'w':
      angulo[1]+=vel2;
      break;
    
    case 'E':
    case 'e':    
      angulo[1]-=vel2;
      break; 

    default:
      break; 
  }
}


void movimiento(int opcion){ //checked
  automatico_activado = opcion;
}

void forma(int opcion) {
    switch (opcion) {
    case 0:
        color = 0;
        break;
    case 1:
        color = 1;
        break;
    case 2:
        color = 2;
        break;
    case 3:
        color = 3;
        break;
    }
}
void menu( int opcion){  //checked
  if (opcion == 0)
    exit(-1);
}

float obtenerRotacion() {
  if (automatico_activado == 1) {
    float increment = vel2;
    if(presionado == 0){ 
    if (giro > 180) {
      increment = 2 * vel2;
    }
    }else if(presionado == 1){
      if (giro < 180) {
      increment = 2 * vel2;
    }

    }
    return increment;
  } else {
    return 0.0; // Devuelve 0 si el automático no está activado
  }
}

void ajuste() { 
  if (automatico_activado == 1) {
    giro += obtenerRotacion(); // Incrementa el ángulo
    
    // Ajusta el ángulo para mantenerlo en el rango [0, 360]
    if (giro >= 360) {
      giro -= 360;
    } else if (giro < 0) {
      giro += 360;
    }
  }
  glutPostRedisplay();
  glutTimerFunc(vel, ajuste, 0);
}


void velocidad(int opcion){ //checked
  switch (opcion){
    case 0:
   
      vel=20;
      break;

    case 1:
      vel=50;
      break;

    case 2:
      vel=90;
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
    glutCreateWindow("Examen CGV"); //Crea la ventana
    init();
    glutDisplayFunc(display); //función de control de render
    glutReshapeFunc(reshape); //función de control de cambio  de tamaño de ventana 
    //glutIdleFunc(idle); //función que se activa cuando no hacemos nada
    glutTimerFunc(vel, ajuste,0); //funcion de timer
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
