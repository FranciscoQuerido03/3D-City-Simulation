
#include "ofMain.h"

// Função que desenha um paralelepípedo
inline void drawParallelepiped(float width, float height, float depth, float r, float g, float b) {
    // A metade das dimensões do paralelepípedo
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;



    glColor3f(r, g, b);
    // Desenha o paralelepípedo
    glBegin(GL_QUADS);

    // Face de cima
    glVertex3f(-halfWidth, -halfHeight, depth);
    glVertex3f(-halfWidth, halfHeight, depth);
    glVertex3f(halfWidth, halfHeight, depth);
    glVertex3f(halfWidth, -halfHeight, depth);

    // Face de baixo
    glVertex3f(halfWidth, -halfHeight, 0);
    glVertex3f(halfWidth, halfHeight, 0);
    glVertex3f(-halfWidth, halfHeight, 0);
    glVertex3f(-halfWidth, -halfHeight, 0);

    // Face frontal
    glVertex3f(-halfWidth, halfHeight, depth);
    glVertex3f(-halfWidth, halfHeight, 0);
    glVertex3f(halfWidth, halfHeight, 0);
    glVertex3f(halfWidth, halfHeight, depth);


    // Face traseira
    glVertex3f(halfWidth, -halfHeight, depth);
    glVertex3f(halfWidth, -halfHeight, 0);
    glVertex3f(-halfWidth, -halfHeight, 0);
    glVertex3f(-halfWidth, -halfHeight, depth);

    // Face esquerda
    glVertex3f(-halfWidth, -halfHeight, depth);
    glVertex3f(-halfWidth, -halfHeight, 0);
    glVertex3f(-halfWidth, halfHeight, 0);
    glVertex3f(-halfWidth, halfHeight, depth);

    // Face direita
    glVertex3f(halfWidth, -halfHeight, 0);
    glVertex3f(halfWidth, -halfHeight, depth);
    glVertex3f(halfWidth, halfHeight, depth);
    glVertex3f(halfWidth, halfHeight, 0);

    glEnd();
}

// Função que desenha um paralelepípedo com malha_unit()
inline void parallelepiped_malha_unit(float width_d, float height_d, float depth, float r, float g, float b, GLint m, GLint n, bool texture = false) {
    glColor3f(r, g, b);
    ofTranslate(0, 0, depth / 2);
    ofScale(width_d, height_d, depth);
    cube_malha_unit(n, m, texture);
}

//Desenha um carro
inline void draw3DCar(float x, float y, float z, float width, float height, float depth) {
    ofPushMatrix();

    ofTranslate(x, y, z);

    // Desenha o "corpo" do carro (um paralelepípedo)
    drawParallelepiped(width, height, depth, 1, 0, 0);

    // Desenha as rodas do carro (cilindros)
    float wheelRadius = width * 0.15;
    glColor3f(0, 0, 0);

    ofPushMatrix();
    ofTranslate(-width * 0.25, 0, depth * 0.2);  // Posição da roda esquerda
    ofDrawCylinder(wheelRadius, height + 5);
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(width * 0.25, 0, depth * 0.2);  // Posição da roda esquerda
    ofDrawCylinder(wheelRadius, height + 5);
    ofPopMatrix();

    ofPopMatrix();
}

//Desenha uma pirâmide
void drawPiramid(float width, float height, float depth, float red, float green, float blue) {
    // Calcular as coordenadas do quadrado da malha com base no ponto central
    float halfWidth = width * 0.5f;
    float halfDepth = depth * 0.5f;
    float halfHeight = height * 0.5f;


    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLES);

    // Triângulo frontal.
    glTexCoord2f(0, 0); glVertex3f(0, 0, depth);
    glTexCoord2f(0, 1); glVertex3f(-halfWidth, halfHeight, 0);
    glTexCoord2f(1, 1); glVertex3f(halfWidth, halfHeight, 0);

    // Triângulo direito
    glTexCoord2f(0, 0); glVertex3f(0, 0, depth);
    glTexCoord2f(0, 1); glVertex3f(halfWidth, halfHeight, 0);
    glTexCoord2f(1, 1); glVertex3f(halfWidth, -halfHeight, 0);

    // Triângulo traseiro
    glTexCoord2f(0, 0); glVertex3f(0, 0, depth);
    glTexCoord2f(0, 1); glVertex3f(halfWidth, -halfHeight, 0);
    glTexCoord2f(1, 1); glVertex3f(-halfWidth, -halfHeight, 0);

    // Triângulo esquerdo
    glTexCoord2f(0, 0); glVertex3f(0, 0, depth);
    glTexCoord2f(0, 1); glVertex3f(-halfWidth, -halfHeight, 0);
    glTexCoord2f(1, 1); glVertex3f(-halfWidth, halfHeight, 0);

    glEnd();
}



void skyBox(int res) {
    float dtheta = PI / float(res);
    float dphi = 2 * PI / float(res);



    for (int i = 0; i < res; i++) {
        for (int j = 0; j < res; j++) {
            glBegin(GL_QUADS);

            float x1 = sin(i * dtheta) * cos(j * dphi);
            float y1 = sin(i * dtheta) * sin(j * dphi);
            float z1 = cos(i * dtheta);
            float tx1 = i / float(res);
            float ty1 = j / float(res);
            ofVec3f n1 = ofVec3f(-x1, -y1, -z1);
            glTexCoord2f(ty1, tx1);
            glNormal3f(n1.x, n1.y, n1.z);
            glVertex3f(x1, y1, z1);

            float x2 = sin(i * dtheta) * cos((j + 1) * dphi);
            float y2 = sin(i * dtheta) * sin((j + 1) * dphi);
            float z2 = cos(i * dtheta);
            float tx2 = i / float(res);
            float ty2 = (j + 1) / float(res);
            ofVec3f n2 = ofVec3f(-x2, -y2, -z2);
            glTexCoord2f(ty2, tx2);
            glNormal3f(n2.x, n2.y, n2.z);
            glVertex3f(x2, y2, z2);

            float x3 = sin((i + 1) * dtheta) * cos((j + 1) * dphi);
            float y3 = sin((i + 1) * dtheta) * sin((j + 1) * dphi);
            float z3 = cos((i + 1) * dtheta);
            float tx3 = (i + 1) / float(res);
            float ty3 = (j + 1) / float(res);
            ofVec3f n3 = ofVec3f(-x3, -y3, -z3);
            glTexCoord2f(ty3, tx3);
            glNormal3f(n3.x, n3.y, n3.z);
            glVertex3f(x3, y3, z3);

            float x4 = sin((i + 1) * dtheta) * cos(j * dphi);
            float y4 = sin((i + 1) * dtheta) * sin(j * dphi);
            float z4 = cos((i + 1) * dtheta);
            float tx4 = (i + 1) / float(res);
            float ty4 = j / float(res);
            ofVec3f n4 = ofVec3f(-x4, -y4, -z4);
            glTexCoord2f(ty4, tx4);
            glNormal3f(n4.x, n4.y, n4.z);
            glVertex3f(x4, y4, z4);

            glEnd();
        }
    }
}