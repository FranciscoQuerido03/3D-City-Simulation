#pragma once

#include "ofMain.h"
#include "aux_func_extras.h"
#include "aux_func.h"



class Luz {
public:
    GLfloat position[4];
    GLfloat direction[3];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat attenuation[3];
    GLfloat spotExponent;
    GLfloat spotCutoff;
    bool enabled;
    GLenum lightId;
    string lightType;

    Luz(GLenum lightId, string lightType) {
        this->lightId = lightId;
        this->lightType = lightType;
        enabled = false;
    }

    void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        position[3] = w;
    }

    void setDirection(GLfloat x, GLfloat y, GLfloat z) {
        direction[0] = x;
        direction[1] = y;
        direction[2] = z;
    }

    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) {
        ambient[0] = r;
        ambient[1] = g;
        ambient[2] = b;
        ambient[3] = a;
    }

    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) {
        diffuse[0] = r;
        diffuse[1] = g;
        diffuse[2] = b;
        diffuse[3] = a;
    }

    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) {
        specular[0] = r;
        specular[1] = g;
        specular[2] = b;
        specular[3] = a;
    }

    void setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadratic) {
        attenuation[0] = constant;
        attenuation[1] = linear;
        attenuation[2] = quadratic;
    }

    void setSpotExponent(GLfloat exponent) {
        spotExponent = exponent;
    }

    void setSpotCutoff(GLfloat cutoff) {
        spotCutoff = cutoff;
    }

    void enable() {
        enabled = true;
    }

    void disable() {
        enabled = false;
    }

    void draw() {
        if (enabled) {
            // Define as propriedades da luz
            glLightfv(lightId, GL_POSITION, position);

            // Define as propriedades da luz
            glLightfv(lightId, GL_AMBIENT, ambient);
            glLightfv(lightId, GL_DIFFUSE, diffuse);
            glLightfv(lightId, GL_SPECULAR, specular);

            // Define as propriedades de atenuação
            glLightf(lightId, GL_CONSTANT_ATTENUATION, attenuation[0]);
            glLightf(lightId, GL_LINEAR_ATTENUATION, attenuation[1]);
            glLightf(lightId, GL_QUADRATIC_ATTENUATION, attenuation[2]);

            // Define as propriedades especificas da luz foco
            if (lightType == "foco") {
                glLightfv(lightId, GL_SPOT_DIRECTION, direction);
                glLightf(lightId, GL_SPOT_EXPONENT, spotExponent);
                glLightf(lightId, GL_SPOT_CUTOFF, spotCutoff);
            }
            // Define as propriedades especificas da luz direcional
            else if (lightType == "direcional") {
                glLightfv(lightId, GL_SPOT_DIRECTION, direction);
            }

            glEnable(lightId);
        }
        else {
            glDisable(lightId);
        }
    }
};


class Textura {
public:
    ofImage image;

    void load(const string& path) {
        image.load(path);
        image.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
        image.getTexture().setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
    }

    void bind() {
        glEnable(GL_TEXTURE);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        image.bind();
    }

    void unbind() {
        image.unbind();
        glDisable(GL_TEXTURE);
    }

    void clear() {
		image.clear();
	}
};


class Material {
public:
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

    void innerSetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        ambient[0] = r;
        ambient[1] = g;
        ambient[2] = b;
        ambient[3] = a;
    }

    void innerSetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        diffuse[0] = r;
        diffuse[1] = g;
        diffuse[2] = b;
        diffuse[3] = a;
    }

    void innerSetSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
        specular[0] = r;
        specular[1] = g;
        specular[2] = b;
        specular[3] = a;
    }

    void setSpecular(const GLfloat* values) {
        innerSetSpecular(values[0], values[1], values[2], values[3]);
    }

    void setAmbient(const GLfloat* values) {
        innerSetAmbient(values[0], values[1], values[2], values[3]);
    }
    void setDiffuse(const GLfloat* values) {
        innerSetDiffuse(values[0], values[1], values[2], values[3]);
    }

    void setShininess(GLfloat value) {
        shininess = value;
    }


    void setMaterial() {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
    }
};



class Building {
public:
    ofVec3f position;
    float width;
    float height;
    float depth;
    float red, green, blue;
    Textura textura;
    Material material;

    Building(float x, float y, float z, float w, float h, float d, float r, float g, float b) {
        position.set(x, y, z);
        width = w;
        height = h;
        depth = d;
        red = r;
        green = g;
        blue = b;
        material = material;
        textura = textura;
    }
};


class Car {
public:
    ofVec3f position;  // Posição do carro no espaço 3D
    ofVec3f velocity;  // Velocidade do carro

    // Construtor para inicializar um carro com posição, velocidade e cor
    Car(ofVec3f startPos, ofVec3f startVelocity) {
        position = startPos;
        velocity = startVelocity;
    };

    void  update() {
        // Atualize a posição com base na velocidade.
        position += velocity;
    }
};


class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void drawGeometry();

    void keyPressed(int key);
    void exit();

    //floor
    GLint resX, resY;
    GLfloat floorWidth, floorHeight, floorHeightPos;


    //Vetor para guardar a posição da câmera
    ofVec3f cameraPosition;

    //Variavel de controle para o modo de desenho
    int ctrl;

    //Vista atual
    int view;
    
    //Parametros para perpective
    GLfloat lensAngle;
    GLfloat alpha, beta;

    //Parametros para lookat
    ofVec3f camPos;
    ofVec3f lookatPos;
    ofVec3f camUp;
    GLfloat orbitAngle;

    //matriz com valores para diferentes lookat
    #define W 1500
    #define H 600
    GLfloat cp[3][9] = {
        {0, 0, W, 0, 0, 0, 0, -1, 0},  // Vista de topo
        {0, W, 1, 0, 0, 0, 0, -1, 0}, // Vista frontal
        {H, 0, W, 0, 0, 0, -1, 0, 0}  // Vista à escolha
    };

    ofVec3f tVerticalPos;  // Posição da parte vertical da estrutura T
    ofVec3f tHorizontalPos;  // Posição da parte horizontal da estrutura T
    float horizontalAngle;  // Ângulo de rotação da parte horizontal



    //Vetor de prédios.
    vector<Building> buildings;
    ofEasyCam camera;
    int viewMode;
    bool isPerspective;


    //Vetor de carros.
    vector<Car> cars;


    //Luzes

    //Vetor de Luzes
    vector<Luz> luzes;

    //Variaveis de controlo
    bool controlo0;
    bool controlo1;
    bool controlo2;
    bool controlo3;
    bool controloAmb;
    bool controloDif;
    bool controloSpec;

    //Texturas
    Textura texturaPredios1, texturaPredios2, texturaPredios3, texturaPredios4, texturaPiramide, texturaEstrada, texturaCeu, texturaTVertical, texturaTHorizontal;
    vector<Textura> texturasPredios;

    //Materiais
    Material materialPredios, materialPiramide, materialEstrada, materialChao, materialT;

    //Skybox
    ofImage sky;
};

