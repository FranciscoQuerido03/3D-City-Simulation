#pragma once
//Funções auxiliares disponibilizadas para uso nos exercícios de CG
// Arquivos originais:
// -cg_extras.h
// -cg_cam_extras_solution.h
//Autor: Professor André Perrota & Evgheni Polisciuc

#ifndef CG_CAM_EXTRAS
#define CG_CAM_EXTRAS

#include "ofMain.h"


//short named function to get screen width
inline float gw() {
	return ofGetWidth();
}

//short named function to get screen height
inline float gh() {
	return ofGetHeight();
}


inline ofVec3f cross(ofVec3f A, ofVec3f B) {
	ofVec3f aux;
	aux.x = A.y * B.z - A.z * B.y;
	aux.y = A.z * B.x - A.x * B.z;
	aux.z = A.x * B.y - A.y * B.x;

	return aux;
}

//calcula o frustum com base em theta, alpha e beta
inline void perspective(GLfloat theta, GLfloat alpha, GLfloat beta, bool invertX = false, bool invertY = false) {
	// Define a matriz atual como matriz de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Inicializa a matriz de projeção

	// Calcula a tangente do ângulo theta dividido por 2 (em radianos)
	GLfloat tan = tanf(theta * 0.5 * PI / 180.0);

	// Calcula a distância d (a partir do centro da projeção)
	GLfloat d = (gh() / 2.0) / tan;

	// Calcula os planos de recorte próximos e distantes
	GLfloat nearClip = d / alpha;
	GLfloat farClip = d * beta;

	// Calcula as coordenadas ymax e xmax na projeção
	GLfloat ymax = nearClip * tan;
	GLfloat xmax = (gw() / gh()) * ymax;

	// Inverte xmax e ymax, se especificado
	if (invertX) {
		xmax = -xmax;
	}
	if (invertY) {
		ymax = -ymax;
	}

	// Configura a matriz de projeção usando glFrustum
	glFrustum(-xmax, xmax, -ymax, ymax, nearClip, farClip);
}



//implementa o algoritmo de lookAt
inline void lookat(
	GLfloat camX,
	GLfloat camY,
	GLfloat camZ,
	GLfloat targetX,
	GLfloat targetY,
	GLfloat targetZ,
	GLfloat upX,
	GLfloat upY,
	GLfloat upZ)
{
	ofVec3f cam = ofVec3f(camX, camY, camZ);
	ofVec3f target = ofVec3f(targetX, targetY, targetZ);
	ofVec3f up = ofVec3f(upX, upY, upZ);


	ofVec3f N = cam - target;
	N = N.normalized();
	ofVec3f U = cross(up, N);
	U = U.normalized();
	ofVec3f V = cross(N, U);
	V = V.normalized();

	GLfloat camTransformMatrix[4][4] = {
		{U.x, V.x, N.x, 0},
		{U.y, V.y, N.y, 0},
		{U.z, V.z, N.z, 0},
		{-U.dot(cam), -V.dot(cam), -N.dot(cam), 1}
	};


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(&camTransformMatrix[0][0]);
	
}

inline void lookat(ofVec3f cam, ofVec3f look, ofVec3f up) {
	lookat(cam.x, cam.y, cam.z, look.x, look.y, look.z, up.x, up.y, up.z);
}






//função que desenha malha unitária com resolução mxn
void malha_unit(GLint m, GLint n, bool texture = false) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			if (texture) {
				glTexCoord2f(i * 1 / float(m), j * 1 / float(n));
			}
			glVertex2d(i * x_step + x_start, j * y_step + y_start);

			if (texture) {
				glTexCoord2f(i * 1 / float(m), (j + 1) * 1 / float(n));
			}
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);

			if (texture) {
				glTexCoord2f((i + 1) * 1 / float(m), (j + 1) * 1 / float(n));
			}
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);

			if (texture) {
				glTexCoord2f((i + 1) * 1 / float(m), (j) * 1 / float(n));
			}
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();
}




//funcao que desenha cubo unit?rio com malha_unit()
inline void cube_malha_unit(GLint m, GLint n, bool texture = false) {


	//baixo
	glPushMatrix();
	glTranslated(0., 0., -0.5);
	glRotated(180, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//tras
	glPushMatrix();
	glTranslated(0., -0.5, 0.);
	glRotated(90, 1, 0, 0);
	malha_unit(m, n, texture);
	glPopMatrix();

	//frente
	glPushMatrix();
	glTranslated(0., 0.5, 0.);
	glRotated(-90, 1, 0, 0);
	malha_unit(m, n, texture );
	glPopMatrix();

	//direita
	glPushMatrix();
	glTranslated(-0.5, 0., 0.);
	glRotated(-90, 0, 1, 0);
	malha_unit(m, n, texture);
	glPopMatrix();

	//esquerda
	glPushMatrix();
	glTranslated(0.5, 0., 0.);
	glRotated(90, 0, 1, 0);
	malha_unit(m, n, texture);
	glPopMatrix();

	//cima
	glPushMatrix();
	glTranslated(0., 0., 0.5);
	malha_unit(m, n, texture);
	glPopMatrix();


}

#endif