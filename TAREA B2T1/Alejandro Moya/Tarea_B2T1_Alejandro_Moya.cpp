
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION //Add to use stb_image.h
#include "learnopengl/stb_image.h" //Add to use stb_image.h



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
    Shader ourShader("shaders/vshaderB2T1.vs", "shaders/fshaderB2T1.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        //Positions       //Colors          Textures coords
         0.3f, 0.3f, 0.0f, 1.0f, 0.8f, 0.0f, 0.65f, 0.65f,//A //0// 1.0f, 0.8f, 0.0f, Amarillo / Yellow
        0.0f, 0.6f, 0.0f, 1.0f, 0.5f, 0.0f, 0.5f, 0.8f,//B //1//
        0.0f, 0.0f, 0.0f, 1.0f, 0.4f, 0.0f, 0.5f, 0.5f,//C //2//

        -0.2f, 0.2f, 0.0f, 0.2f, 0.6f, 1.0f, 0.4f, 0.6f,//D //3// 0.2f, 0.6f, 1.0f, Azul  / Blue
        -0.2f, 0.0f, 0.0f, 0.2f, 0.4f, 1.0f, 0.4f, 0.5f,//E //4//
        0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 1.0f, 0.5f, 0.5f,//C //5//

        -0.2f, 0.2f, 0.0f, 1.0f, 0.4f, 0.4f, 0.4f, 0.6f, //D //6// 1.0f, 0.4f, 0.4f, Rojo atomatado  / Red
         -0.2f, 0.0f, 0.0f,1.0f, 0.3f, 0.3f, 0.4f, 0.5f, //E //7//
        -0.4f, 0.0f, 0.0f, 1.0f, 0.2f, 0.2f, 0.3f, 0.5f, //F //8//
        -0.4f, 0.2f, 0.0f, 1.0f, 0.1f, 0.1f, 0.3f, 0.6f,//G //9//

        -0.6f, 0.0f, 0.0f,1.0f, 0.6f, 0.2f, 0.2f, 0.5f,//H //10// 1.0f, 0.6f, 0.2f, Naranja / Orange
        -0.4f, 0.0f, 0.0f, 1.0f, 0.4f, 0.1f, 0.3f, 0.5f,//F //11//
        -0.4f, 0.2f, 0.0f,1.0f, 0.2f, 0.0f, 0.3f, 0.6f,//G //12//

        0.0f, 0.0f, 0.0f, 0.2f, 0.8f, 0.4f, 0.5f, 0.5f,//C //13// 0.2f, 0.8f, 0.4f, Verde Opaco / Dark Green
        -0.3f, -0.3f, 0.0f, 0.2f, 0.5f, 0.3f, 0.35f, 0.35f,//I //14//
        0.0f, -0.6f, 0.0f, 0.2f, 0.2f, 0.2f, 0.5f, 0.2f,//J //15//

        0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 1.0f, 0.5f, 0.5f,//C  //16// 0.2f, 0.2f, 1.0f, Verde Claro / Light Green
        0.2f, -0.2f, 0.0f, 0.2f, 0.1f, 0.6f, 0.6f, 0.4f,//K //17//
        0.4f, -0.0f, 0.0f, 0.2f, 0.0f, 0.2f, 0.7f, 0.5f,//L //18//

        0.2f, -0.2f, 0.0f, 0.4f, 0.4f, 0.8f,  0.6f, 0.4f,//K //19// 0.4f, 0.4f, 0.8f, Morado o Lila / Purpple
        0.4f, -0.0f, 0.0f, 0.4f, 0.3f, 0.6f, 0.7f, 0.5f,//L //20//
        0.4f, -0.2f, 0.0f, 0.4f, 0.2f, 0.4f, 0.7f, 0.4f,//M //21//
        0.6f, -0.0f, 0.0f, 0.4f, 0.1f, 0.2f, 0.8f, 0.5f,//N //22//

        /*// positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left */
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
        /*0, 1, 3, // first triangle
        1, 2, 3  // second triangle*/
    };
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    unsigned int texture2;

    //Textura 1
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char* data = stbi_load(FileSystem::getPath("textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load("textures/Cubes.jpg", &width, &height, &nrChannels, 0);//container.jpg

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

    //Textura 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
   // int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char* data = stbi_load(FileSystem::getPath("textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load("textures/Galaxy.jpg", &width, &height, &nrChannels, 0);//container.jpg

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

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Edito desde aqui

         // render container
        ourShader.use();
        int flag = 0;
        for (int i = 0; i < 7; i++) {
            if (i < 4) {//textura 1
                ourShader.setFloat("Val1offset", 1);
                if (i == 3 ) {
                    glBindVertexArray(VAO);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(flag * sizeof(float)));
                    flag += 6;
                }
                else {
                    glBindVertexArray(VAO);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(flag * sizeof(float)));
                    flag += 3;
                }
            }
            else{//textura 2
                ourShader.setFloat("Val1offset", 0);
                if (i == 5) {
                    glBindVertexArray(VAO);
                    glBindTexture(GL_TEXTURE_2D, texture2);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(flag * sizeof(float)));
                    flag += 6;
                }
                else {
                    glBindVertexArray(VAO);
                    glBindTexture(GL_TEXTURE_2D, texture2);
                    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(flag * sizeof(float)));
                    flag += 3;
                }
            }
        }

        float timeValue = glfwGetTime();
        float timeColor = sin(timeValue) / 2.0f+0.5f;
        ourShader.setFloat("Val2offset", timeColor);

        //Hasta aqui
        /*
        
        // bind Texture and send to the fragment shader sampler
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();

        // In this code block a random number is defined between 0 to 1 to modify the colors of the vertices. With the sine function
        float timeValue = glfwGetTime();
        float timeColor = sin(timeValue) / 2.0f;
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "timeColor"); // Time color is a variable of type uniform in the fragment shader.
        glUniform4f(vertexColorLocation, timeColor * 0.1f, timeColor * 0.3f, timeColor * 0.2f, 1.0f);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 29, GL_UNSIGNED_INT, 0);
        */
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}