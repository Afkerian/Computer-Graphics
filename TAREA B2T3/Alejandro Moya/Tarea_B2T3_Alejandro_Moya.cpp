//Autor: Alejandro Moya
//Actividad: B2T3
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm-master/glm/glm.hpp>
#include <glm-master/glm/gtc/matrix_transform.hpp>
#include <glm-master/glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/vshaderB2T3.vs", "shaders/fshaderB2T3.fs");
    float y = 0.096;
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // texture coords
        //Trasero
    -0.5f, -0.5f, -0.5f,  0.723f, 0.230f + y,//O
     0.5f, -0.5f, -0.5f,  0.936f, 0.230f + y,//Q
     0.5f,  0.5f, -0.5f,  0.936f, 0.484f + y,//P
     0.5f,  0.5f, -0.5f,  0.936f, 0.484f + y,//P
    -0.5f,  0.5f, -0.5f,  0.723f, 0.484f + y,//N
    -0.5f, -0.5f, -0.5f,  0.723f, 0.230f + y,//O

    //Frontal
    -0.5f, -0.5f,  0.5f,  0.297f, 0.230f + y,//G
     0.5f, -0.5f,  0.5f,  0.510f, 0.230f + y,//I
     0.5f,  0.5f,  0.5f,  0.510f, 0.484f + y,//H
     0.5f,  0.5f,  0.5f,  0.510f, 0.484f + y,//H
    -0.5f,  0.5f,  0.5f,  0.297f, 0.484f + y,//F
    -0.5f, -0.5f,  0.5f,  0.297f, 0.230f + y,//G

    //Lateral Derecho
    -0.5f,  0.5f,  0.5f,  0.297f, 0.484f + y,//F
    -0.5f,  0.5f, -0.5f,  0.084f, 0.484f + y,//E
    -0.5f, -0.5f, -0.5f,  0.084f, 0.230f + y,//D
    -0.5f, -0.5f, -0.5f,  0.084f, 0.230f + y,//D
    -0.5f, -0.5f,  0.5f,  0.297f, 0.230f + y,//G
    -0.5f,  0.5f,  0.5f,  0.297f, 0.484f + y,//F

    //Lateral Izquierdo
     0.5f,  0.5f,  0.5f,  0.723f, 0.484f + y,//N
     0.5f,  0.5f, -0.5f,  0.510f, 0.484f + y,//H
     0.5f, -0.5f, -0.5f,  0.510f, 0.230f + y,//I
     0.5f, -0.5f, -0.5f,  0.510f, 0.230f + y,//I
     0.5f, -0.5f,  0.5f,  0.723f, 0.230f + y,//O
     0.5f,  0.5f,  0.5f,  0.723f, 0.484f + y,//N

     //Inferior
    -0.5f, -0.5f, -0.5f,  0.297f, 0.076f + y,//L
     0.5f, -0.5f, -0.5f,  0.510f, 0.076f + y,//M
     0.5f, -0.5f,  0.5f,  0.510f, 0.230f + y,//I
     0.5f, -0.5f,  0.5f,  0.510f, 0.230f + y,//I
    -0.5f, -0.5f,  0.5f,  0.297f, 0.230f + y,//G
    -0.5f, -0.5f, -0.5f,  0.297f, 0.076f + y,//L

    //Superior
    -0.5f,  0.5f, -0.5f,  0.297f, 0.484f + y,//F
     0.5f,  0.5f, -0.5f,  0.510f, 0.484f + y,//H
     0.5f,  0.5f,  0.5f,  0.510f, 0.728f + y,//K
     0.5f,  0.5f,  0.5f,  0.510f, 0.728f + y,//K
    -0.5f,  0.5f,  0.5f,  0.297f, 0.728f + y,//J
    -0.5f,  0.5f, -0.5f,  0.297f, 0.484f + y,//F
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  -0.5f,  0.0f),//Reference
        glm::vec3(-1.3f,  0.5f,  -1.3f),
        glm::vec3(1.3f, 0.5f, -1.3f),
        glm::vec3(-1.5f,  1.0f, 0.5f),
        glm::vec3(1.5f,  1.0f, 0.5f),
        glm::vec3(-0.0f,  2.0f, -1.5f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("textures/Grass.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/Lava.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



        //glClear(GL_COLOR_BUFFER_BIT);
        //Exercise 11 Task 3
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        ourShader.use();


        //Exercise 12 Task 3
        // pass projection matrix to shader (note that in this case it could change every frame)

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);


        for (unsigned int i = 0; i < 6; i++)//Number of Cubes
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            
            float angle = 20.0f * i;
            angle = glfwGetTime() * 50.0f; //Rote on time

            glDrawArrays(GL_TRIANGLES, 0, 36);//Draw Cubes

            //Textures

            if (i<3) {
                
                glBindTexture(GL_TEXTURE_2D, texture1);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.9f, 0.8f));
                ourShader.setMat4("model", model);
            }
            else {
                
                glBindTexture(GL_TEXTURE_2D, texture2);
                 model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.9f, 0.0f));
                ourShader.setMat4("model", model);
            }

            
            

            
        }

        



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
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

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
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