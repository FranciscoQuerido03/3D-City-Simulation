#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0); // Define a cor de fundo para preto.

    ofSetFrameRate(165);
    glEnable(GL_DEPTH_TEST);

    ctrl = 0;

    cameraPosition.set(0, 0, 500);  // Posição inicial da câmera
    lensAngle = 60;
    alpha = 10;
    beta = 1000;

    view = 0;
    orbitAngle = 0;
    lookatPos.set(0, 0, 0);
    camUp.set(0, 1, 0);

    horizontalAngle = 0.0;  // Ângulo de rotação da parte horizontal


    //Parametros para o chão
    resX = 3;
    resY = 5;
    floorWidth = gw() * 0.5;
    floorHeight = gw() * 0.5;
    floorHeightPos = 0.;

    //####################### PRÉDIOS ################################

    // Loop para preencher a malha com prédios
    for (int i = 0; i < resX; i++) {

        // Pular a coluna do meio
        if (i == 1) { 
            continue;
        }

        for (int j = 0; j < resY; j++) {
            
            // Pular a linha do meio
            if (j == 2) { 
				continue;
			}

            // Gerar cores aleatórias para os prédios
            float r = ofRandom(0.5, 0.75); // base cinza
            float g = r + ofRandom(-0.1, 0); // subtrair um pouco para verde
            float b = r + ofRandom(-0.1, 0); // subtrair um pouco para azul

      
            // Calcular as coordenadas do centro do quadrado da malha
            float squareSizeX = floorWidth / resX;
            float squareSizeY = floorHeight / resY;
            float posX = -floorWidth * 0.5 + i * squareSizeX + squareSizeX * 0.5;
            float posY = -floorHeight * 0.5 + j * squareSizeY + squareSizeY * 0.5;
            float posZ = 0;

            // Gerar tamanhos aleatórios para os prédios
            float w = ofRandom(50, squareSizeX); // Largura limitada pelo tamanho do quadrado da malha
            float h = ofRandom(50, squareSizeY);
            float d = ofRandom(100,400); // Profundidade limitada pelo tamanho do quadrado da malha


            // Criar um novo prédio com as coordenadas e tamanhos calculados e adiciona ao vetor "buildings"
            buildings.push_back(Building(posX, posY, posZ, w, h, d,r,g,b));
        }
    }

    // Predio aleatorio para ficar com a estrutura em T no topo
    Building& selectedBuilding = buildings[0];

    //#######################################################


    //####################### ESTRUTURA EM FORMA T ################################

    // Posicionar a parte vertical no topo do prédio
    tVerticalPos.set(selectedBuilding.position.x, selectedBuilding.position.y, selectedBuilding.position.z + selectedBuilding.depth);

    // Posicionar a parte horizontal acima da parte vertical
    // A altura é configurada para 50 devido às configurações do tamanho da  parte horizontal
    tHorizontalPos.set(tVerticalPos.x, tVerticalPos.y, tVerticalPos.z + 50);

    //#######################################################


    //####################### CARRO ################################
 
    //Velocidade mínima e máxima do carro
    float minSpeed = 0.8;
    float maxSpeed = 1;

    //Numero de carros
    int numCars = 1;

    //Cria o numero de carros especificado
    for (int i = 0; i < numCars; i++) {
        ofVec3f position;
        ofVec3f velocity;

        //Posição inicial do carro.
        position.set(0, 0,0);

        // velocidade inicial do carro.
        velocity.set(ofRandom(minSpeed, maxSpeed), 0, 0);

        // Cria um novo carro com a posição e velocidade geradas e adiciona ao vetor "cars"
        cars.push_back(Car(position, velocity));
    }

    //#######################################################


    //####################### LUZES ################################

    controlo0 = false;
    controlo1 = false;
    controlo2 = false;
    controlo3 = false;

    controloAmb = false;
    controloDif = false;
    controloSpec = false;

    // Inicia a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // Habilita o uso de materiais coloridos
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Cria as luzes e adiciona ao vetor luzes
    luzes.push_back(Luz(GL_LIGHT0, "direcional"));
    luzes.push_back(Luz(GL_LIGHT1, "pontual"));
    luzes.push_back(Luz(GL_LIGHT2, "foco"));
    luzes.push_back(Luz(GL_LIGHT3, "direcional"));

	// Habilita as luzes    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1); 
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    //--Configurações imutaveis das luzes--
    
    // Luz Direcional -- sol    
    luzes[0].setPosition(0.0f, 0.0f, 200.0f, 0.0f);

    // Luz Pontual -- candeeiro
    luzes[1].setPosition(tHorizontalPos.x, tHorizontalPos.y, tHorizontalPos.z, 1.0f);
    luzes[1].setAttenuation(1, 0.0001, 0.00001);

    // Luz Foco -- farol do carro
    luzes[2].setDirection(1.0f, 0.0f, 0.0f);
    luzes[2].setSpotExponent(30);
    luzes[2].setSpotCutoff(50.0f);
    luzes[2].setAttenuation(1, 0, 0);

    // Luz Direcional -- por do sol
    luzes[3].setPosition(100.0f, -200.0f, 0.0f, 0);

    //#######################################################


    //####################### TEXTURAS ################################

    ofDisableArbTex();
    glShadeModel(GL_SMOOTH);

    // Carregar a texturas
    // 
    //Skybox
    sky.load("skybox.jpg");
    //Estrutura T
    texturaTVertical.load("tVertical.jpg");
    texturaTHorizontal.load("tHorizontal.jpg");
    //Chão
    texturaEstrada.load("estrada.jpg");
    //Predios e Piramide
    texturaPiramide.load("piramide.png");
    texturaPredios1.load("opt1.jpg");
    texturaPredios2.load("opt2.jpg");
    texturaPredios3.load("opt3.jpg");
    texturaPredios4.load("opt4.jpg");

    // Colocar as texturas dos predios num vetor
    texturasPredios = { texturaPredios1, texturaPredios2, texturaPredios3, texturaPredios4 };

    //#######################################################

    //####################### MATERIAIS ################################

// Configurações do material da piramide
    GLfloat piramide_mat_ambient[] = { 0.25f, 0.20f, 0.07f, 1.0f };
    GLfloat piramide_mat_diffuse[] = { 0.75f, 0.61f, 0.23f, 1.0f };
    GLfloat piramide_mat_specular[] = { 0.63f, 0.56f, 0.37f, 1.0f };
    GLfloat piramide_mat_shininess = 51.21f;


    materialPiramide.setAmbient(piramide_mat_ambient);
    materialPiramide.setDiffuse(piramide_mat_diffuse);
    materialPiramide.setSpecular(piramide_mat_specular);
    materialPiramide.setShininess(piramide_mat_shininess);

    // Configurações do material dos predios
    GLfloat predios_mat_ambient[] = { 0.8f, 0.4f, 0.3f, 1.0f }; // Cor ambiente dos tijolos
    GLfloat predios_mat_diffuse[] = { 0.8f, 0.4f, 0.3f, 1.0f }; // Cor difusa dos tijolos
    GLfloat predios_mat_specular[] = { 0.8f, 0.4f, 0.3f, 1.0f }; // Cor especular dos tijolos
    GLfloat predios_mat_shininess = 1.0f; // Brilho dos tijolos

    materialPredios.setAmbient(predios_mat_ambient);
    materialPredios.setDiffuse(predios_mat_diffuse);
    materialPredios.setSpecular(predios_mat_specular);
    materialPredios.setShininess(predios_mat_shininess);

    // Configurações do material do chão
    GLfloat chao_mat_ambient[] = { 0.4f, 0.8f, 0.2f, 1.0f }; // Cor ambiente do chão
    GLfloat chao_mat_diffuse[] = { 0.4f, 0.8f, 0.2f, 1.0f }; // Cor difusa do chão
    GLfloat chao_mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // Cor especular do chão
    GLfloat chao_mat_shininess = 5.0f; // Brilho do chão

    materialChao.setAmbient(chao_mat_ambient);
    materialChao.setDiffuse(chao_mat_diffuse);
    materialChao.setSpecular(chao_mat_specular);
    materialChao.setShininess(chao_mat_shininess);

    // Configurações da estrutura T
    GLfloat estruturaT_mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Cor ambiente da estrutura T
    GLfloat estruturaT_mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Cor difusa da estrutura T
    GLfloat estruturaT_mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Cor especular da estrutura T
    GLfloat estruturaT_mat_shininess = 50.0f; // Brilho da estrutura T

    materialT.setAmbient(estruturaT_mat_ambient);
    materialT.setDiffuse(estruturaT_mat_diffuse);
    materialT.setSpecular(estruturaT_mat_specular);
    materialT.setShininess(estruturaT_mat_shininess);



    //Aplicar os materiais e texturas aos predios
    for (Building& building : buildings) {
        if (&building == &buildings[5]) {
            // Aplicar a textura à piramide
            building.textura = texturaPiramide;
            // Aplicar o material à piramide
            building.material = materialPiramide;
        }
        else {
            // Selecionar uma textura aleatória para aplicar ao prédio
            int index = (int)ofRandom(texturasPredios.size());
            building.textura = texturasPredios[index];
            // Aplicar o material ao prédio
            building.material = materialPredios;
        }
    }

    //#######################################################

}

//--------------------------------------------------------------
void ofApp::update() {

    //Vista que roda em torno da cena
    if (view == 3) {
        camPos.x = W * cos(orbitAngle);
        camPos.z = W * sin(orbitAngle);
        camPos.y = H * cos(orbitAngle * 0.5);
        orbitAngle += PI * 0.005;
    }

    // Aumenta o ângulo de rotação da parte horizontal da estrutura T
    horizontalAngle += 1.0;

    // Atualize a posição dos carros
    for (Car& car : cars) {
        car.update();

        // Verifique se o carro ultrapassa os limites do chão.
        if (car.position.x + 25 > floorWidth * 0.5) {
            car.position.x = -floorWidth * 0.5 + 25;
        }
    }


}

//--------------------------------------------------------------
void ofApp::draw() {

    //viewport principal
    glViewport(0, 0, gw(), gh());

    // matriz projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(lensAngle, alpha, beta);
    ofTranslate(cameraPosition);


    //posiciona a câmera com lookat
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    if (view < 3) {
        lookat(
            cp[view][0], cp[view][1], cp[view][2],
            cp[view][3], cp[view][4], cp[view][5],
            cp[view][6], cp[view][7], cp[view][8]
        );
    }
    else {
        lookat(camPos, lookatPos, camUp);
    }

    drawGeometry();
    glPopMatrix();


    //mini-view - vista ortogfica
    glViewport(0, 0, gw() * 0.35, gh() * 0.35);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //projeção ortográfica
    glOrtho(-gw() * 0.5, gw() * 0.5, -gh() * 0.5, gh() * 0.5, -10000, 10000);

    if (view < 3) {
        lookat(
            cp[view][0], cp[view][1], cp[view][2],
            cp[view][3], cp[view][4], cp[view][5],
            cp[view][6], cp[view][7], cp[view][8]
        );
    }
    else {
        lookat(camPos, lookatPos, camUp);
    }

    drawGeometry();

}
void ofApp::drawGeometry() {

    // Luz Direcional -- sol
    luzes[0].setAmbient(controloAmb ? 1.0f : 0.0f, controloAmb ? 1.0f : 0.0f, controloAmb ? 0.8f : 0.0f);
    luzes[0].setDiffuse(controloDif ? 1.0f : 0.0f, controloDif ? 1.0f : 0.0f, controloDif ? 0.8f : 0.0f);
    luzes[0].setSpecular(controloSpec ? 1.0f : 0.0f, controloSpec ? 1.0f : 0.0f, controloSpec ? 0.8f : 0.0f);

    if (controlo0) luzes[0].enable();
    else luzes[0].disable();

    // Luz Pontual -- candeeiro?
    luzes[1].setAmbient(controloAmb ? 0.5f : 0.0f, controloAmb ? 0.5f : 0.0f, controloAmb ? 0.5f : 0.0f);
    luzes[1].setDiffuse(controloDif ? 0.1f : 0.0f, controloDif ? 0.1f : 0.0f, controloDif ? 0.1f : 0.0f);
    luzes[1].setSpecular(controloSpec ? 0.5f : 0.0f, controloSpec ? 0.5f : 0.0f, controloSpec ? 0.5f : 0.0f);

    if (controlo1) luzes[1].enable();
    else luzes[1].disable();

    // Luz Foco -- farol do carro
    luzes[2].setPosition(cars[0].position.x, cars[0].position.y, cars[0].position.z);

    luzes[2].setAmbient(controloAmb ? 0.3f : 0.0f, controloAmb ? 0.3f : 0.0f, controloAmb ? 0.3f : 0.0f); // cor branca suave
    luzes[2].setDiffuse(controloDif ? 1.0f : 0.0f, controloDif ? 1.0f : 0.0f, controloDif ? 1.0f : 0.0f); // cor branca brilhante
    luzes[2].setSpecular(controloSpec ? 1.0f : 0.0f, controloSpec ? 1.0f : 0.0f, controloSpec ? 1.0f : 0.0f); // cor branca brilhante

    if (controlo2) luzes[2].enable();
    else luzes[2].disable();

    // Luz Direcional -- por do sol
    luzes[3].setAmbient(controloAmb ? 0.8f : 0.0f, controloAmb ? 0.4f : 0.0f, controloAmb ? 0.0f : 0.0f); // cor laranja
    luzes[3].setDiffuse(controloDif ? 0.8f : 0.0f, controloDif ? 0.1f : 0.0f, controloDif ? 0.1f : 0.0f); // cor vermelha
    luzes[3].setSpecular(controloSpec ? 0.8f : 0.0f, controloSpec ? 0.4f : 0.0f, controloSpec ? 0.4f : 0.0f); // cor rosa

    if (controlo3) luzes[3].enable();
    else luzes[3].disable();


    // Desenha as luzes
    for (int i = 0; i < luzes.size(); ++i) {
        luzes[i].draw();
    }


    // Chão
    glColor3f(1, 1, 1);
    glPushMatrix();//floor push
    glScalef(floorWidth, floorHeight, 1.);

    materialChao.setMaterial();

    texturaEstrada.bind();
    malha_unit(resX, resY, true);
    texturaEstrada.unbind();

    glPopMatrix();//floor pop


    // Desenhar todos os predios criados  e colocados no vetor "buildings"
    for (Building& building : buildings) {
        ofPushMatrix(); // Salva a matriz de transformação atual

        //Desenha uma piramide como predio com a posição 5 no vetor de predios
        if (&building == &buildings[5]) {
            // Salva o estado atual do OpenGL
            glPushAttrib(GL_ALL_ATTRIB_BITS);

            //Material da piramide
            building.material.setMaterial();

            ofTranslate(building.position);
            building.textura.bind();
            drawPiramid(building.width, building.height, building.depth, building.red, building.green, building.blue);
            building.textura.unbind();


            // Restaura o estado do OpenGL
            glPopAttrib();
        }
        else {
            // Salva o estado atual do OpenGL
            glPushAttrib(GL_ALL_ATTRIB_BITS);

            //Material dos predios
            building.material.setMaterial();

            ofTranslate(building.position);
            building.textura.bind();
            parallelepiped_malha_unit(building.width, building.height, building.depth, building.red, building.green, building.blue, 3, 5, true);
            building.textura.unbind();

            // Restaura o estado do OpenGL
            glPopAttrib();

        }
        ofPopMatrix();
    }

    // Desenhar a parte vertical da estrutura T
    ofPushMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    materialT.setMaterial();

    ofTranslate(tVerticalPos);
    texturaTVertical.bind();
    parallelepiped_malha_unit(20, 20, 50, 0.5, 0.5, 0.5, 3, 5, true);
    texturaTVertical.unbind();

    ofPopMatrix();

    // Aplicar a rotação na parte horizontal em torno da parte vertical
    ofPushMatrix();

    ofTranslate(tHorizontalPos);
    ofRotateDeg(horizontalAngle, 0, 0, 1);

    // Desenhar a parte horizontal da estrutura em forma de T (em relação à parte vertical)
    ofPushMatrix();

    texturaTHorizontal.bind();
    parallelepiped_malha_unit(20, 50, 20, 0.5, 0.5, 0.5, 3, 5, true);
    texturaTHorizontal.unbind();

    glPopAttrib();

    ofPopMatrix();

    ofPopMatrix();

    //Desenhar todos os carros criados e colocados no vetor "cars"
    for (Car& car : cars) {
        draw3DCar(car.position.x, car.position.y, car.position.z, 50, 25, 40);
    }

    // Desenhar a skybox
    glEnable(GL_TEXTURE);
    sky.bind();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glColor3f(1, 1, 1);
    glPushMatrix();
    glRotatef(0, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 0, 0, 1);
    glScalef(50 * gw(), 50 * gw(), 50 * gw());
    skyBox(70);
    glPopMatrix();

    sky.unbind();
    glDisable(GL_TEXTURE);



    //Aplicação da variavel ctrl para mudar o modo de desenho
    if (ctrl == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {

        case '1':
            controlo0 = !controlo0;
            break;

        case '2':
            controlo1 = !controlo1;
            break;

        case '3':
            controlo2 = !controlo2;
            break;

        case '4':
            controlo3 = !controlo3;
            break;

        case 'a':
            controloAmb = !controloAmb;
            break;

        case 'd':
            controloDif = !controloDif;
            break;

        case 's':
            controloSpec = !controloSpec;
            break;


        case 'g':
            // Variavel de controlo para alternar o modo de desenho
            ctrl = 1;
            break;

        case 'f':
            // Variavel de controlo para alternar o modo de desenho
            ctrl = 0;
            break;

        case 'v':
            view++;
            if (view > 3) {
                view = 0;
            }
            break;

        case OF_KEY_SHIFT:
            lensAngle++;
            cout << endl << lensAngle;
            break;

        case OF_KEY_CONTROL:
            lensAngle--;
            cout << endl << lensAngle;
            break;

        case OF_KEY_RIGHT:
            cameraPosition.x -= 5;
            break;

        case OF_KEY_LEFT:
            cameraPosition.x += 5;
            break;

        case OF_KEY_UP:
            cameraPosition.y -= 5;
            break;

        case OF_KEY_DOWN:
		    cameraPosition.y += 5;
		    break;

        case 'r':
            // Redefine a posição da câmera
		    cameraPosition.set(0, 0, 500);
            lensAngle = 60;
		    break;
    }

}

void ofApp::exit() {
    // Limpa recuros
    texturaPredios1.clear();
    texturaPredios2.clear();
    texturaPredios3.clear();
    texturaPredios4.clear();
    texturaPiramide.clear();
    texturaEstrada.clear();
    texturaTVertical.clear();
    texturaTHorizontal.clear();
    sky.clear();
}


