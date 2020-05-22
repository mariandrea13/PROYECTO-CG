/*---------------------------------------------------------*/
/* ----------------  PROYECTO FINAL TEORIA (CASA) --------------------------*/
/* ----------------  ALUMNO: --------------------------*/
/* ---------------- BARRON PEREZ MARIAN ANDREA--------------------------*/

#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>

#include <windows.h>
#include <mmsystem.h>
#include <mciapi.h>
#pragma comment(lib,"Winmm.lib")

#include "camera.h"
#include "Model.h"
#include "Texture.h"

// Other Libs
#include "SOIL2/SOIL2.h"

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;
GLuint skyboxVBO, skyboxVAO;

//Camera
Camera camera(glm::vec3(0.0f, 2.0f, 4.50f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;


//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(7.0f, 4.0f, 3.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

void myData(void);
void myData2(void);
void display(Shader, Shader, Model, Model);
void getResolution(void);
void animate(void);

unsigned int generateTextures(char*, bool);

//Texture


//Variables para las animaciones
float
movAuto_z = 0.0f,
movAuto_x = -5.0f,
orienta = -90.0f,
volar_z = -4.0f,
volar_y = 0.40f,
direccionBird = 0,
posicionBird = 0,
posicionPerro = 0,
correr_z = 2.0f,
correr_x = 5.0f,
rebota_x = -.80f,
rebota_y = .80f,
rotPuerta;
int st_rotPuerta;


bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,

animacionB = false,
volar_A = true,
volar_B = false,
volar_C = false,
volar_D = false,

animacionC = false,
Correr_A = true,
Correr_B = false,
Correr_C = false,
Correr_D = false,
Correr_E = false,
Correr_F = false,

animacionD = false,
bota_A = true,
bota_B = false,
bota_C = false,
bota_D = false;




















unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}



void myData()
{	
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void myData2()
{
	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	// SkyBox
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

}

void animate(void)
{
	//puerta
	//Animación por máquina de estados
	switch (st_rotPuerta) {
	case 0:
		rotPuerta += 1.0f;
		rotPuerta > 60.0f ? st_rotPuerta = 1 : st_rotPuerta = 0;
		break;
	case 1:
		rotPuerta -= 1.0f;
		rotPuerta < 1.0f ? st_rotPuerta = 0 : st_rotPuerta = 1;
		break;
	default:
		break;
	}

	//Carro 
	if (animacion) {
		if (recorrido1)
		{
			movAuto_x += 0.34f;
			
			if (movAuto_x >-3.5f)
			{
				orienta = 0.0f;
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			movAuto_z -= 0.34f;
		
			if (movAuto_z< -3.5f)
			{
				orienta = -90.0f;
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		if (recorrido3)
		{
			movAuto_x += 0.34f;
			
			if (movAuto_x > 8.0f)
			{
				orienta = 180.0f;
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4)
		{
			movAuto_z += 0.34f;
			if (movAuto_z > 4.0f)
			{
				recorrido4 = false;
				movAuto_z = 0.0f,
				movAuto_x = -5.0f;
				
			}
		}
	}

	//Pajaros 
	if (animacionB) {
		if (volar_A) {
			volar_y += 0.25;
			volar_z += 0.652;
			direccionBird = -23.005;
			posicionBird = 0;
			if (volar_y > 3.0f && volar_z > 0)
			{
				volar_A = false;
				volar_B = true;
			}
		}
		if (volar_B)
		{
			volar_y -= 0.3;
			volar_z += 0.3;
			direccionBird = 45;
			posicionBird = 0;
			if (volar_y < 0.4)
			{
				volar_B = false;
				volar_C = true;
			}
		}
		if (volar_C)
		{
			volar_y += 0.3;
			volar_z -= 0.3;
			direccionBird = -45;
			posicionBird = 180;

			if (volar_y > 3.0f)
			{
				volar_C = false;
				volar_D = true;
			}
		}
		if (volar_D)
		{
			volar_y -= 0.25;
			volar_z -= 0.652;
			posicionBird = 180;

			direccionBird = 23.005;
			if (volar_y < 0.4f && volar_z < -4.0f)
			{
				volar_D = false;
				volar_A = true;
			}
		}

	}

	//Recorrido de perro 
	if (animacionC) {
		if (Correr_A) {
			correr_x += 0.25;
			
			if (correr_x > 7.0f)
			{
				posicionPerro = 90;
				Correr_A = false;
				Correr_B = true;
			}
		}
		if (Correr_B) {
			correr_z -= 0.25;
			if (correr_z < -4.0f)
			{
				posicionPerro = 90;
				Correr_B = false;
				Correr_C = true;
			}
		}
		if (Correr_C) {
			correr_z -= 0.25;
			posicionPerro = 180;
			if (correr_z < 4.0f)
			{
				Correr_C = false;
				Correr_D = true;
			}
		}
		if (Correr_D) {
			correr_x -= 0.25;
			posicionPerro = -90;
			if (correr_x< 0.0f)
			{
				Correr_D = false;
				Correr_E = false;
			}
		}
	

	}
	if (animacionD)
	{
		if (bota_A) {
			rebota_x += 0.25;
			if (rebota_x < -.60f)
			{
				bota_A = false;
				bota_B = true;
			}
		}
		if (bota_B) {
			rebota_y -= 0.25;
			if (rebota_y < .10f)
			{
				bota_B = false;
				bota_A = true;
			}
		}
		if (bota_C) {
			rebota_y += 0.25;
			if (rebota_y > 1.0f)
			{
				bota_C = false;
				bota_D = true;
			}
		}
		if (bota_C) {

			rebota_y -= 0.25;
			rebota_x += 0.25;
			if (rebota_y < .10f)
			{
				bota_C = false;
				bota_D = false;
				rebota_x = -.80f,
				rebota_y = .80f;
			}
		}

	}



}

	



void display(	Shader shader, Shader skyboxShader, GLuint skybox, 
				Model piso,	Model arbol2, Model arbol3,
				Model lamp, Model casa, Model fuente,
				Model kiosko, Model perro,
				Model carro, Model carro2,
				Model bird, Model pelota,
				Model baulTop, Model door, Model outdoor, Model techo )
{
	shader.use();

	//Setup Advanced Lights
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("dirLight.direction", lightDirection);
	shader.setVec3("dirLight.ambient", glm::vec3(0.7, 0.7, 0.7));
	shader.setVec3("dirLight.diffuse", glm::vec3(0.8f, 0.8f, 0.4f));
	shader.setVec3("dirLight.specular", glm::vec3(0.7, 0.7, 0.7));

	shader.setVec3("pointLight[0].position", lightPosition);
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);
	shader.setFloat("pointLight[0].linear", 0.009f);
	shader.setFloat("pointLight[0].quadratic", 0.0032f);

	shader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);
	shader.setFloat("pointLight[1].linear", 0.009f);
	shader.setFloat("pointLight[1].quadratic", 0.032f);

	shader.setFloat("material_shininess", 32.0f);

	// create transformations and Projection
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 temp = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.007f));
	shader.setMat4("model", model);
	piso.Draw(shader);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.30f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	casa.Draw(shader);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.67f, .09f, -.95f));
	model = glm::scale(model, glm::vec3(.17f, .17f, .17f));
	shader.setMat4("model", model);
	baulTop.Draw(shader);

	//doors 
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.42f, 0.10f, 0.22f));
	temp=model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-rotPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(.05f, .05f, .05f));
	shader.setMat4("model", model);
	door.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.50f, 0.0f, 0.73f));
	temp = model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-rotPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(.06f, .06f, .06f));
	shader.setMat4("model", model);
	outdoor.Draw(shader);

	
	
	//pelota
	model = glm::translate(glm::mat4(1.0f), glm::vec3(rebota_x, rebota_y, -0.25f));
	model = glm::scale(model, glm::vec3(.09f, .09f, .09f));
	shader.setMat4("model", model);
	pelota.Draw(shader);

	/************************PERROS***************************************/

	model = glm::translate(glm::mat4(1.0f), glm::vec3(correr_x, -.90f, correr_z));
	model = glm::rotate(model, glm::radians(posicionPerro), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setMat4("model", model);
	perro.Draw(shader);
	/************************CARRO***************************************/
	model = glm::translate(glm::mat4(1.0f), glm::vec3(movAuto_x, 0.0f, movAuto_z));
	model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.018f, 0.018f, 0.018f));
	shader.setMat4("model", model);
	carro.Draw(shader);

	/**************************PAJAROS********************************/
	model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, volar_y, volar_z));
	model = glm::rotate(model, glm::radians(posicionBird), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(direccionBird), glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
	shader.setMat4("model", model);
	bird.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, volar_y, volar_z));
	model = glm::rotate(model, glm::radians(posicionBird), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(direccionBird), glm::vec3(1.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	bird.Draw(shader);

	/*******************LAMPARA***********/
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
	shader.setMat4("model", model);
	lamp.Draw(shader);

	/************************FUENTE***************************************/

	model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setMat4("model", model);
	fuente.Draw(shader);
	;
	/************************KIOSKO***************************************/
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, 2.5));
	model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
	shader.setMat4("model", model);
	kiosko.Draw(shader);




	

	

		//**************ARBOLES**************

		int x;
	for (x = -10; x <= 10; x = x + 2)
	{
		model = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0.0f, x));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(10, 0.0f, x + 1));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		shader.setMat4("model", model);
		arbol3.Draw(shader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0.0f, x));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0.0f, x + 1));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		shader.setMat4("model", model);
		arbol3.Draw(shader);
	}

	for (x = -10; x <= 10; x = x + 2)
	{
		model = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, .01f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(x+1, 0.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, .01f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);

		
	}

	/*********************FIN  DE ARBOL***********/

	

	
	// Draw skybox as last
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	skyboxShader.use();
	view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix

	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);

	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set depth function back to default
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
 

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "--BARRON PEREZ MARIAN ANDREA      PROYECTO FINAL--", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, my_input);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	
	myData2();
	glEnable(GL_DEPTH_TEST);
	
	//Shaders
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

	// Load models
	Model pisoModel = ((char *)"Models/plano/plano.obj");


	Model arbol2Model = ((char *)"Models/plants/arbol2.obj");
	Model arbol3Model = ((char *)"Models/plants/arbol3.obj");


	Model lampSModel = ((char *)"Models/setParque/lampS.obj");
	//Model trashModel = ((char *)"Models/setParque/trash.obj");

	Model casaModel = ((char *)"Models/casa/casa.obj");

	Model fuenteModel = ((char *)"Models/fuente/fuente1.obj");
	Model kioskoModel = ((char *)"Models/setParque/kiosko.obj");

	Model perroModel = ((char *)"Models/Perro/Perro.obj");

	Model carroModel = ((char *)"Models/Carro1/Carro1.obj");
	Model carro2Model = ((char *)"Models/Carro2/Carro2.obj");

	Model birdModel = ((char *)"Models/Bird/Bird.obj");
	Model pelotaModel = ((char *)"Models/casa/pixar.obj");
	Model baulTopModel= ((char *)"Models/casa/baulTop.obj");
	Model doorModel = ((char *)"Models/casa/puerta.obj");
	Model outdoorModel = ((char *)"Models/casa/outdoor.obj");
	Model techoModel = ((char *)"Models/casa/techo.obj");
	


	//Inicialización de KeyFrames
	

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/top.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// render loop
    // While the windows is not closed

    while (!glfwWindowShouldClose(window))
    {
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        //my_input(window);
		animate();

        // render
        // Background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(modelShader, SkyBoxshader, cubemapTexture, 
			pisoModel,  arbol2Model, arbol3Model, 
			lampSModel, casaModel, fuenteModel, 
			kioskoModel, perroModel,
			carroModel, carro2Model,
			birdModel,pelotaModel, baulTopModel, doorModel, outdoorModel,techoModel);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

	//Configuracion de teclas
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		animacion ^= true;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		animacionB ^= true;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		animacionD ^= true;

	//To play KeyFrame animation 
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		animacionC ^= true;
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
