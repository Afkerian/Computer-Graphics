#include <glad/glad.h>
#include <GLFW/glfw3.h>
// B1P3_Alejandro_Moya_code.cpp
#include <iostream>
//The comments were changed, on purpose without affecting the delivery status in order to publish the code on GitHub. The original delivery of the source code, was not modified.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 480;
const unsigned int SCR_HEIGHT = 480;

const char* vertexShaderSource = "#version 330 core\n" // The vertex shader is written in GLSL (OpenGL Shader Language) and is stored in a variable of type char.
"layout (location = 0) in vec3 aPos;\n" // Location allows you to identify the VBO from which the coordinates will be extracted. The apos data correspond to the data in VBO and this consideration is made.
"void main () \ n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // Se especifica que las coordenadas son de posición y se usaran para generar las primitivas. El ultimo arguemento representa la perspectiva, de momento solo tendrá el valor de uno. gl_Position es una palabra reservada.
"}\0";

const char* fragmentShaderSource1 = "#version 330 core\n" // El fragment shader es escrito en GLSL(OpenGL Shader Language) y se almacena en una variable de tipo char.
"out vec4 FragColor;\n" // Definimos variable de salida de cuatro componentes.
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.8f, 0.0f, 0.0f);\n" // Amarillo/Yellow.
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.8f, 0.4f, 0.0f);\n"//Verde Opaco/Dark Green
"}\n\0";

const char* fragmentShaderSource3 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.6f, 0.8f, 0.2f, 0.0f);\n" //Verde Claro/ Light Green
"}\n\0";

const char* fragmentShaderSource4 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.4f, 0.4f, 0.8f, 0.0f);\n" //Morado o Lila/ Purpple
"}\n\0";

const char* fragmentShaderSource5 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.6f, 1.0f, 0.0f);\n"//Azul/Blue
"}\n\0";

const char* fragmentShaderSource6 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.4f, 0.4f, 0.0f);\n"// Rojo atomatado/Red
"}\n\0";

const char* fragmentShaderSource7 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.6f, 0.2f, 0.0f);\n"//Naranja/Orange
"}\n\0";

const char* fragmentShadersSources[] = { fragmentShaderSource1, fragmentShaderSource2, fragmentShaderSource3, fragmentShaderSource4, fragmentShaderSource5, fragmentShaderSource6, fragmentShaderSource7 };

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Alejandro Moya", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    int vertexShader = glCreateShader(GL_VERTEX_SHADER); //A shader object type VERTEX and its ID is saved in the variable vertexShader.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // The source code of the shader object is specified. 
    glCompileShader(vertexShader); // Compile VERTEX shader.

    //In this case, the creation of the vertex shader.
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShaders[7];

    for (int i = 0; i < 7; i++) {
        fragmentShaders[i] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaders[i], 1, &fragmentShadersSources[i], NULL);
        glCompileShader(fragmentShaders[i]);

        glGetShaderiv(fragmentShaders[i], GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShaders[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    int shaderPrograms[7];

    for (int i = 0; i < 7; i++) {
        shaderPrograms[i] = glCreateProgram();
        glAttachShader(shaderPrograms[i], vertexShader);
        glAttachShader(shaderPrograms[i], fragmentShaders[i]);
        glLinkProgram(shaderPrograms[i]);

        glGetProgramiv(shaderPrograms[i], GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderPrograms[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    glDeleteShader(vertexShader); 
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (int i = 0; i < 7; i++) {
        glDeleteShader(fragmentShaders[i]); 
    }

    float vertices[] = { // Arrangement with the coordinates of the vertices.
        0.3f, 0.3f, 0.0f, //A
        0.0f, 0.6f, 0.0f, //B
        0.0f, 0.0f, 0.0f, //C
        -0.2f, 0.2f, 0.0f, //D
        -0.2f, 0.0f, 0.0f, //E
        -0.4f, 0.0f, 0.0f, //F
        -0.4f, 0.2f, 0.0f, //G
        -0.6f, 0.0f, 0.0f, //H
        -0.3f, -0.3f, 0.0f, //I
        0.0f, -0.6f, 0.0f, //J
        0.2f, -0.2f, 0.0f, //K
        0.4f, -0.0f, 0.0f, //L
        0.4f, -0.2f, 0.0f, //M
        0.6f, -0.0f, 0.0f, //N
    
    };

    unsigned int indices[] = {
        0, 1, 2, // 1
        2, 8, 9, // 2
        11, 2, 10, // 3
        12, 11, 10, // 4
        13, 11, 12, // 4'
        2, 3, 4, // 5
        4, 3, 5, // 6
        3, 6, 5, // 6'
        5, 6, 7, // 7
        
    };


    unsigned int VBO, VAO, EBO; // Allocation of memory space for the variables Vertex Buffer Object (VBO), Vertex Array Object (VAO) and Element Buffer Object (EBO). The latter allows you to save the configuration data of a scene, of all the objects in it.
    glGenVertexArrays(1, &VAO); // Generates a VAO space in the GPU memory, the first corresponds to the identifier and the second establishes in which variable the VAO is stored, in this case in the VAO variable itself.
    glGenBuffers(1, &VBO); // Generates a VBO space in the GPU memory, the first corresponds to the identifier and the second establishes in which variable the VBO is stored, in this case in the VBO variable itself.
    glGenBuffers(1, &EBO); // Generates an EBO space in the GPU memory, the first corresponds to the identifier and the second establishes in which variable the EBO is stored, in this case in the EBO variable itself.

    glBindVertexArray(VAO);// Bind and activate the vertex array object. Which implies that the following commands are saved in the activated VAO.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer that is passed in the 2nd argument with the type of buffer object that is specified in the 1st. In this case, the VBO will store an array. It also enables VBO and therefore the following commands apply to the specified VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy the vertices stored in the memory of the CPU in the memory of the GPU, that is, the vertices are passed to the VBO previously activated in the glBindBuffer function.
    // The first argument receives the type of buffer object (array in this case), the 2nd the size in bits of the buffer, the 3rd the variable in the CPU with the vertices to pass and the 4th specifies how to use the card graphics data. In this case they remain constant and are not modified

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0); // Set the criteria to OpenGL for the interpretation of the vertex buffer when a draw call is made. The 1st argument is the index of the vertex attribute. The 2nd argument receives the
    // the number of components per attribute (It can be 1, 2, 3 or 4). 
    //glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (void*)4);
    glEnableVertexAttribArray(0);// Enables the attribute in the vertex shader, that is, it executes the reading of data that can already be used.
    // These last three steps can be done more efficiently when you have a large number of objects, making use of the VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
   
   // Render Loop

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int flag = 0;
        for (int i = 0; i < 7; i++) {
            glUseProgram(shaderPrograms[i]); // Run the shader program. It is the application itself. 
            glBindVertexArray(VAO); // Link the vertex Array Object with all the information of the vertices and their attributes.
            if (i == 3 || i == 5 ) {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(flag * sizeof(float)));
                flag += 6;
            }
            else {
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(flag * sizeof(float)));
                flag += 3;
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}