#include <GL/glut.h>
#include <cmath>

float angle = 0.0f;  // Sudut orbit
float orbitRadius = 2.0f;  // Radius orbit
float satelliteSize = 0.1f;  // Ukuran satelit
float planetSize = 0.5f;  // Ukuran planet
float rotationSpeed = 1.0f;  // Kecepatan rotasi

// Fungsi untuk menggambar lingkaran/bola
void drawSphere(float radius) {
    glutSolidSphere(radius, 20, 20);
}

// Fungsi untuk menggambar orbit
void drawOrbit() {
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex3f(cos(rad) * orbitRadius, sin(rad) * orbitRadius, 0.0f);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Posisi kamera
    gluLookAt(0.0f, 0.0f, 5.0f,  // Posisi kamera
              0.0f, 0.0f, 0.0f,  // Titik yang dilihat
              0.0f, 1.0f, 0.0f); // Arah atas
    
    // Gambar orbit
    glColor3f(0.5f, 0.5f, 0.5f);
    drawOrbit();
    
    // Gambar planet
    glColor3f(0.0f, 0.5f, 1.0f);
    drawSphere(planetSize);
    
    // Gambar satelit
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(orbitRadius, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawSphere(satelliteSize);
    glPopMatrix();
    
    glutSwapBuffers();
}

void update(int value) {
    angle += rotationSpeed;
    if(angle > 360) {
        angle -= 360;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // 60 FPS
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simulasi Orbit Satelit");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}
