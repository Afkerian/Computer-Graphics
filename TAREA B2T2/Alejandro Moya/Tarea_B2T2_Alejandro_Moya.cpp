//Autor: Alejandro Moya
//TAREA B2T2
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include <glm-master/glm/glm.hpp>//Add to use glm path
#include <glm-master/glm/gtc/matrix_transform.hpp>//Add to use glm path
#include <glm-master/glm/gtc/type_ptr.hpp>//Add to use glm path

#include <learnopengl/shader_s.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>//Add to use stb_image.h

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float visibilyFactor = 0.0f;
float rotation = 0.0f;
float size = 0.5f;
float position = 0.0f;
float size1 = 1.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // Conficuración de la ventana en el sistema operativo OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Alejandro Moya, 1720982493", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/vshaderB2T2.vs", "shaders/fshaderB2T2.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // posiciones          // textura
         0.3f, 0.3f, 0.0f, 0.65f, 0.65f,//A //0// 
        0.0f, 0.6f, 0.0f, 0.5f, 0.8f,//B //1//
        0.0f, 0.0f, 0.0f, 0.5f, 0.5f,//C //2//

        -0.2f, 0.2f, 0.0f, 0.4f, 0.6f,//D //3// 
        -0.2f, 0.0f, 0.0f, 0.4f, 0.5f,//E //4//
        0.0f, 0.0f, 0.0f, 0.5f, 0.5f,//C //5//

        -0.2f, 0.2f, 0.0f, 0.4f, 0.6f, //D //6// 
         -0.2f, 0.0f, 0.0f, 0.4f, 0.5f, //E //7//
        -0.4f, 0.0f, 0.0f, 0.3f, 0.5f, //F //8//
        -0.4f, 0.2f, 0.0f, 0.3f, 0.6f,//G //9//

        -0.6f, 0.0f, 0.0f, 0.2f, 0.5f,//H //10// 
        -0.4f, 0.0f, 0.0f, 0.3f, 0.5f,//F //11//
        -0.4f, 0.2f, 0.0f, 0.3f, 0.6f,//G //12//

        0.0f, 0.0f, 0.0f, 0.5f, 0.5f,//C //13// 
        -0.3f, -0.3f, 0.0f, 0.35f, 0.35f,//I //14//
        0.0f, -0.6f, 0.0f, 0.5f, 0.2f,//J //15//

        0.0f, 0.0f, 0.0f, 0.5f, 0.5f,//C  //16// 
        0.2f, -0.2f, 0.0f, 0.6f, 0.4f,//K //17//
        0.4f, -0.0f, 0.0f, 0.7f, 0.5f,//L //18//

        0.2f, -0.2f, 0.0f, 0.6f, 0.4f,//K //19// 
        0.4f, -0.0f, 0.0f, 0.7f, 0.5f,//L //20//
        0.4f, -0.2f, 0.0f, 0.7f, 0.4f,//M //21//
        0.6f, -0.0f, 0.0f, 0.8f, 0.5f,//N //22//
    };
    unsigned int indices[] = {
        0, 1, 2, // 1
        3, 4, 5, // 5
        6, 7, 8, // 6
        6, 8, 9, // 6'
        10, 11, 12, // 7
        13, 14, 15, // 2
        16, 17, 18, // 3
        19, 20, 21, // 4
        20, 21, 22 // 4'
    };

    // Creation of VBO, VAO, EBO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1;
    unsigned int texture2;

    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("textures/Cubes.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);



    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("textures/Galaxy.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);

    // Activate the shader and assign values ​​to uniform variables within it
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    // Render LOOP
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // Black
        glClear(GL_COLOR_BUFFER_BIT);

        // Active Textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Render container
        ourShader.use();

        // Timeline texture
        visibilyFactor = (sin(glfwGetTime()) / 2.0f) + 0.5f;
        ourShader.setFloat("visible", visibilyFactor);

        // Transform
        // ---------------------
        // Transform 1
        glm::mat4 transform = glm::mat4(1.0f); // Initialize the transformation matrix as the identity matrix
        transform = glm::scale(transform, glm::vec3(size, size, size));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(rotation, rotation, 1.0f));
        transform = glm::translate(transform, glm::vec3(position, 1, 0.0f));
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // Draw Elements
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);

        // Transform 2
        float scale = sin(glfwGetTime());
        float scale1 = cos(glfwGetTime());
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(position, scale, 0.0f));
        transform = glm::scale(transform, glm::vec3(scale, scale1, scale));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
        
        // Transform 3
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(position, scale1, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
       // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*
    // Sequence to control if the figure is shown full of color or only with lines. Press L (Line) to show only lines and C (Color) to show filled with color.
    if (GetKeyState('L') & 0x8000) //Check if high-order bit is set (1 << 15)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (GetKeyState('C') & 0x8000)//Check if high-order bit is set (1 << 15)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    */

    // optional: de-allocate all resources once they've outlived their purpose:
   // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        rotation = rotation + 0.1f;
        size = size + 0.1f;
        if (rotation >= 1.0f)
            rotation = 1.0f;
        if (size >= 1.0f)
            size = 1.0f;
        
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        rotation = rotation - 0.1f;
        size = size - 0.1f;
        if (rotation <= 0.0f)
            rotation = 0.0f;
        if (rotation <= 0.5f)
            size = 0.5;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position = position - (0.1f);
        if (position >= 1.0f)
            position = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position = position + (0.1f);
        if (position <= 0.0f)
            position = 0.0f;
    }
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
