#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	//initialite Window Manager
	glfwInit();

	//Tell GLFW what he is working with
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//coordinates of the single verticies of a triangle
	GLfloat verticies[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	};

	//The order in which it should be rendered
	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	//create a window Object
	GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);

	//If it didnt produce a window, it terminates GLFW
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Tell glfw what window it is working with
	glfwMakeContextCurrent(window);

	//initialize Glad, the thing that makes OpenGL usable
	gladLoadGL();

	//Say Opengl where it should render on the screen
	glViewport(0, 0, 800, 800);

	//gives the shader a reference (a number with whitch you can find it)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//lets opengl know, that this is a shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compiles the shader into mashine code with the given reference
	glCompileShader(vertexShader);

	//gives the shader a reference (a number with whitch you can find it)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//lets opengl know, that this is a shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compiles the shader into mashine code with the given reference
	glCompileShader(fragmentShader);

	//creates a manual for the gpu, on what to do (the whole shader thingy)
	GLuint shaderProgram = glCreateProgram();
	//gives the Vertex Shader into the programm
	glAttachShader(shaderProgram, vertexShader);
	//gives the Fragment Shader into the programm
	glAttachShader(shaderProgram, fragmentShader);

	//Links the programm, duh
	glLinkProgram(shaderProgram);

	//Deletes the shaders, cuz the gpu already has them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Creates VERTEX ARRAY OBJECT AND VERTEX BUFFER OBJECT AND INDEX BUFFER OBJECT
	GLuint VAO, VBO, EBO;

	//Generate the Buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the VAO
	glBindVertexArray(VAO);

	//Bind The Array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Idk, show him what to do
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	//same thing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//What is that abomination
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Bind everything
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//tells the back buffer how to look
	glClearColor(0.07f, .13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//main loop
	while (!glfwWindowShouldClose(window)){
		//tells the back buffer how to look
		glClearColor(0.07f, .13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//Updates the screen
		glfwSwapBuffers(window);

		//takes care of anything happening
		glfwPollEvents();
	}

	//Delete the binary crap we have loaded onto the gpu
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


	//Destroy the window
	glfwDestroyWindow(window);
	//End everything going on
	glfwTerminate();
	return 0;
}