
#include <GLFW/glfw3.h> /*Este encabezado proporciona todas las constantes, 
tipos y prototipos de funciones de la API GLFW.*/

int main(void)//Funcion principal
{
    GLFWwindow* window;// de declara una variable ventana

    /* Initialize the library */
    if (!glfwInit())/*Este punto inicializa las bibliotecas para poder 
	utilizar la mayoria de funciones de GLFW, es necesario finalizar*/
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);/*Esto crea una ventana de modo de ventana 
	de 640 por 480 con un contexto OpenGL. Siempre se debe comprobar el estado de la 
	ventana que se creo 1 = True y 0 = False*/
    if (!window)//Aqui es donde se comprueba
    {
        glfwTerminate();//Esta es la finalizacion de glfwInit, que permite liberar procesos
        
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);/*Esto es necesario antes de poder utilizar la 
	API de OpenGl, esto va a permitir que la ventana permaneza actualizada, hasta
	que se tenga un nuevo contexto o se cierre la ventana*/

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))/*Se crea un bucle de la ventana hasta que
    el usuario cierre la misma*/
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);/*glClear toma un solo argumento que es el bit a bit de varios valores que indican qué búfer se va a                borrar. Mientras que GL_COLOR_BUFFER_BIT indica los búferes actualmente habilitados para la escritura en color.*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);/*Todas la ventanas presentan 2 buffers, el buffer frontal
        y el buffer trasero, el frontal es el que se muestra mientras que el trasero es
		el que se procesa, cuando se renderiza el los buffers cambian entre se y viceversa. LA
		actualizacion de estos fotogramas esta definida en 0, como las odenadores se actualizan
		entre 60 y 80 veces, este proceso nunca s elogra apreciar y se transforma en ciclos
		de CPU-GPU desperdiciados*/

        /* Poll for and process events */
        glfwPollEvents();/*Esto procesa eventos pendientes. Existen dos metodos: SONDEO Y ESPERA
        en este caso en particular se esta haciendo uso del metodo de SONDEO el cual procesa los 
		eventos ya recibidos, este metodo resulta util para videojuegos, por el contrario se usa
		 glfwWaitEvents() que pone al hilo en reposo y es util para herramientas de edición. */
    }

    glfwTerminate();//Esta es la finalizacion de glfwInit, que permite liberar procesos
    return 0;//Retorna 0 a la funcion principal, indicando una ejecucion
    //o la finalizacion exitosa del programa. 
}
