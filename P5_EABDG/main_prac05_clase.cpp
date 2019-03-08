/*---------------------------------------------------------*/
/* ----------------   Práctica 5 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computación gráfica e interacción humano computadora ---------------*/
/*--------------Díaz Gutiérrez Elvira Angela Belem---------------------*/
/*------------------ Visual Studio Versión 2017 --------------------*/
/* Instrucciones de uso:
Para poder observar, mover y rotar la imagen se debe tienen las siguientes teclas con sus respectivas acciones:
	D					Mueve la figura a la derecha
	A					Mueve la figura a la izquierda
	AvPág				Mueve la figura hacia abajo
	RePág				Mueve la figura hacia arriba
	W					Aleja la figura
	S					Acerca la figura
	Flecha abajo		Rota la figura hacia enfrente 
	Flecha arriba		Rota la figura hacia atras 
	Flecha izquierda	Rota la figura hacia la izquierda 
	Flecha derecha		Rota la figura hacia la derecha 
	T					Rota el hombro hacia abajo y si se aprieta con shift derecho hacia arriba con limites de -90° a 90°
	Y					Rota el antebrazo hacia enfrente y si se aprieta con shift derecho hacia atras con limites de -140° a 0°
	U					Rota la mano hacia enfrente	y si se aprieta con shift derecho hacia atras con limites de -40° a 20°
	I					Rota el pulgar hacia enfrente y si se aprieta con shift derecho hacia atras con limites de 0° a 80°
	O					Rota el indice hacia enfrente y si se aprieta con shift derecho hacia atras con limites de -80° a 0°
	P					Rota el medio hacia enfrente y si se aprieta con shift derecho hacia atras con limites de -80° a 0°
	L					Rota el anular hacia enfrente y si se aprieta con shift derecho hacia atras con limites de -80° a 0°
	K					Rota el meñique hacia enfrente y si se aprieta con shift derecho hacia atras con limites de -80° a 0°
 	 
*/


#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,	//Variable de traslación en X
movY = 0.0f,			//Variable de traslación en Y
movZ = -5.0f,			//Variable de traslación en Z
rotX = 0.0f,			//Ángulo de rotación en X
rotY = 0.0f;			//Ángulo de rotación en Y
float angHom = 0.0f,	//Ángulo de rotación del hombro
	angAnt=0.0f,		//Ángulo de rotación del antebrazo (codo)
	angMano=0.0f,		//Ángulo de rotación de la mano (muñeca)
	angPu = 0.0f,		//Ángulo de rotación del pulgar
	angIn=0.0f,			//Ángulo de rotación del indice
	angMed=0.0f,		//Ángulo de rotación del medio
	angAn=0.0f,			//Ángulo de rotación del anular
	angMe=0.0f			//Ángulo de rotación del meñique
	;




void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	
	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view,glm::radians(rotY),glm::vec3(0.0f,1.0f,0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);
	//Hombro
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor",glm::vec3(1,1,0));
	glDrawArrays(GL_QUADS,0,24);
	//Bicep
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 0.7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Antebrazo
	model = glm::translate(model, glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(angAnt), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(3, 1, 0.7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Mano
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(angMano), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(1, 1, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	modelTemp2 = model;
	//Pulgar Inferior
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));
	model = glm::rotate(model, glm::radians(angPu), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 0.0f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Pulgar Superior
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	model = glm::rotate(model, glm::radians(angPu*0.7f), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice inferior
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0.5, 0.38, 0));
	modelTemp2 = model;//contiene inicio de falange
	model = glm::rotate(model, glm::radians(angIn), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.168f, 0.564f, 0.933f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice medio
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angIn*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.117f, 0.835f, 0.921f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice Superior
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angIn* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.094f, 0.968f, 0.843f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio inferior
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.25, 0));
	model = glm::rotate(model, glm::radians(angMed), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.2f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio medio
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMed*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.407f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio Superior
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMed* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.580f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular inferior
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.5, 0));
	model = glm::rotate(model, glm::radians(angAn), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.8f, 0.1f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular medio
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAn*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular Superior
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAn* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.980f, 0.984f, 0.615f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique inferior
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.75, 0));
	model = glm::rotate(model, glm::radians(angMe), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.58824f, 0.0f, 0.80392f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique medio
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angMe*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.72549f, 0.29804f, 0.88235f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique Superior
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angMe* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.913f, 0.627f, 0.972f));
	glDrawArrays(GL_QUADS, 0, 24);

	glBindVertexArray(0);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 5", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();
	
	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);
    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);
        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.8f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.8f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.8f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.8f;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angHom < 90)
				angHom += 0.8f;
		}
		else {
			if (angHom > -90)
				angHom -= 0.8f;
		}
	}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angAnt <0)
					angAnt += 0.8f;
			}
			else {
				if (angAnt > -140)
					angAnt -= 0.8f;
			}
		}
	
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angMano < 20)
					angMano += 0.8f;
			}
			else {
				if (angMano > -40)
					angMano -= 0.8f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angPu > 0)
					angPu -= 0.8f;
			}
			else {
				if (angPu < 80)
					angPu += 0.8f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angIn < 0)
					angIn += 0.8f;
			}
			else {
				if (angIn > -80)
					angIn -= 0.8f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angMed < 0)
					angMed += 0.8f;
			}
			else {
				if (angMed > -80)
					angMed -= 0.8f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angAn < 0)
					angAn += 0.8f;
			}
			else {
				if (angAn > -80)
					angAn -= 0.8f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angMe < 0)
					angMe += 0.8f;
			}
			else {
				if (angMe > -80)
					angMe -= 0.8f;
			}
		}

	/*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (mode == GLFW_MOD_SHIFT) {
			hombro += 2.0f;
		}
		else {
			//lowercase
			hombro -= 2.0f;
		}
	}*/

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}