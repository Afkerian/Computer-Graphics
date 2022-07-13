#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
// B1P4_Alejandro_Moya_code.cpp
#include <learnopengl/shader_s.h>
#include <iostream>
//The comments were changed, on purpose without affecting the delivery status in order to publish the code on GitHub. The original delivery of the source code, was not modified.

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

    // The shader program is created, for this the global paths of the vertex and fragment shader, respectively, are sent by argument.
    Shader ourShader("C:/Users/aleja/Desktop/Code/Computacion Grafica/C++/OpenGL/OpenGL/shaders/vshader.vert", "C:/Users/aleja/Desktop/Code/Computacion Grafica/C++/OpenGL/OpenGL/shaders/fshader.frag");

    float vertices[] = {
        // positions         // colors
        0.3f, 0.3f, 0.0f, 1.0f, 0.8f, 0.0f, //A //0// 1.0f, 0.8f, 0.0f, Amarillo / Yellow
        0.0f, 0.6f, 0.0f, 1.0f, 0.5f, 0.0f, //B //1//
        0.0f, 0.0f, 0.0f, 1.0f, 0.4f, 0.0f, //C //2//

        -0.2f, 0.2f, 0.0f, 0.2f, 0.6f, 1.0f,//D //3// 0.2f, 0.6f, 1.0f, Azul  / Blue
        -0.2f, 0.0f, 0.0f, 0.2f, 0.4f, 1.0f,//E //4//
        0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 1.0f, //C //5//

        -0.2f, 0.2f, 0.0f, 1.0f, 0.4f, 0.4f,//D //6// 1.0f, 0.4f, 0.4f, Rojo atomatado  / Red
         -0.2f, 0.0f, 0.0f,1.0f, 0.3f, 0.3f, //E //7//
        -0.4f, 0.0f, 0.0f, 1.0f, 0.2f, 0.2f, //F //8//
        -0.4f, 0.2f, 0.0f, 1.0f, 0.1f, 0.1f, //G //9//

        -0.6f, 0.0f, 0.0f,1.0f, 0.6f, 0.2f, //H //10// 1.0f, 0.6f, 0.2f, Naranja / Orange
        -0.4f, 0.0f, 0.0f, 1.0f, 0.4f, 0.1f, //F //11//
        -0.4f, 0.2f, 0.0f,1.0f, 0.2f, 0.0f, //G //12//

        0.0f, 0.0f, 0.0f, 0.2f, 0.8f, 0.4f, //C //13// 0.2f, 0.8f, 0.4f, Verde Opaco / Dark Green
        -0.3f, -0.3f, 0.0f, 0.2f, 0.5f, 0.3f, //I //14//
        0.0f, -0.6f, 0.0f, 0.2f, 0.2f, 0.2f, //J //15//

        0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 1.0f, //C  //16// 0.2f, 0.2f, 1.0f, Verde Claro / Light Green
        0.2f, -0.2f, 0.0f, 0.2f, 0.1f, 0.6f,//K //17//
        0.4f, -0.0f, 0.0f, 0.2f, 0.0f, 0.2f,//L //18//

        0.2f, -0.2f, 0.0f, 0.4f, 0.4f, 0.8f,//K //19// 0.4f, 0.4f, 0.8f, Morado o Lila / Purpple
        0.4f, -0.0f, 0.0f, 0.4f, 0.3f, 0.6f,//L //20//
        0.4f, -0.2f, 0.0f, 0.4f, 0.2f, 0.4f, //M //21//
        0.6f, -0.0f, 0.0f, 0.4f, 0.1f, 0.2f,//N //22//
    };

    unsigned int indices[] = { // Fix with the indices to plot the designated model.
        0, 1, 2, // 1
        3, 4, 5, // 5
        6, 7, 8, // 6
        6, 8, 9, // 6'
        10, 11, 12, // 7
        13, 14, 15, // 2
        16, 17, 18, // 3
        19, 20, 21, // 4
        20, 21, 22, // 4'
    };

   // Sequence to create, generate and link the VBO, VAO and EBO.
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       // Program created ourShader.
        ourShader.use();

       // In this code block a random number is defined between 0 to 1 to modify the colors of the vertices. With the sine function
        float timeValue = glfwGetTime();
        float timeColor = sin(timeValue) / 2.0f;
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "timeColor"); // Time color is a variable of type uniform in the fragment shader.
        glUniform4f(vertexColorLocation, timeColor * 0.1f, timeColor * 0.3f, timeColor * 0.2f, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 29, GL_UNSIGNED_INT, (GLvoid*)0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Sequence to control if the figure is shown full of color or only with lines. Press L (Line) to show only lines and C (Color) to show filled with color.
        if (GetKeyState('L') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if (GetKeyState('C') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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