#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
38.34.028
*/
int main()
{
	// Variable que almacena la cadena 
	//de texto proveniente del archivo 'quijote.txt'
    string texto = ""; 
    string aux; 
    
    // vector que almacena los caracteres
    vector<char> letras; 
    
    // vector que almacena el numero de repeticiones de cada caracter 
    //del vector letras, relacionados con la posicion
    vector<int> contador; 
    
    // variable que almacena la posicion de un caracter en el vector letras
    int pos;
    
    // bandera para determinar si el caracter se encontró en el vector letras
    bool flag;
    
    /*
    // ****************************************************
    EL SIGUIENTE BLOQUE ES UN HOTSPOT PORQUE SE REALIZA LA LECTURA
    DEL ARCHIVO Y ALMACENAMIENTO EN LA VARIABLE texto, LO CUAL
    ES UN PROCESO DE GRAN PROCESAMIENTO

    ESTE BLOQUE NO ES PARALELIZABLE PORQUE SE CREA CONFLICTO 
    SI VARIOS HILOS INTENTAN ACCEDER A L ARCHIVO POR EL TIPO 
    DE OPERACION QUE IMPLICA ESTO
    */
    //Abre archivo guardado en el mismo directorio del ejecutable
    ifstream file("quijote.txt"); //TAREA: ABRIR EL ARCHIVO

    // ciclo while que guarda todo lo que esta en el archivo txt
    // hasta que no encuentre mas lineas
    while(getline(file, aux)) // TAREA: ALMACENAR EL ARCHIVO
    {
    	// se concatena para guardar el contenido en la variable 'texto'
        texto = texto + aux + " ";
    }
    file.close(); // TAREA: CERRAR EL ARCHIVO
    // ****************************************************


    /*
    // ****************************************************
    EL SIGUIENTE BLOQUE ES UN HOTSPOT PORQUE SE REALIZA
    MUCHO PROCEDIMIENTO DEBIDO AL NUMERO DE VECES QUE DEBE
    EJECUTARSE EL BLOQUE INTERNO. EN PRIMER LUGAR, EL FOR EXTERNO SE EJECUTA 
    LA CANTIDAD DE VECES COMO LONGITUD TENGA LA VARIABLE texto,
    Y EN SEGUNDO LUGAR, EL FOR INTERNO SE EJECUTA TANTAS VECES 
    COMO POSICIONES TENGA EL VECTOR.

    ESTE BLOQUE DEL CODIGO SI ES PARALELIZABLE PORQUE
    VARIOS HILOS PUEDEN LEER EL STRING TEXTO Y CADA UNO
    // PUEDE IR CONTANDO CARACTERES EN UNA PORCION DEL STRING
    */

    for(unsigned int i = 0; i < texto.length(); i++)
    {
    	// para cada letra en la variable TEXTO se ejecuta el primer for


        //bandera para avisar si caracter existe en el vector letras
        flag = false;

        for(unsigned int j = 0; j < letras.size(); j++)
        {
        	// se compara el caracter de la iteracion i 
        	// con cada posicion j del vector letras

            //si el caracter esta en el vector
            if(texto[i] == letras.at(j)) // TAREA: COMPARAR CARACTER CON CARACTER
            {
                //lo encontro y pone la bandera en true
                flag = true;

                //almacena en la variable 'pos' del caracter en vector letras
                pos = j;
                // apenas se encontro el caracter no es necesario 
                // seguir en el ciclo for interno
                break;
            }
        }

        // Si existe (flag = true), sumele una unidad al vector 
        // contador en la posicion 'pos'
        if(flag)
        {
            contador.at(pos) = contador.at(pos) + 1; // TAREA: AUMENTAR EL CONTADOR
        }
        // si no existe, agregue el caracter de la iteracion i 
        // en el vector letras en la ultima posicion y en 
        // contador ponga 1

        else
        {
        	// TAREA: AGREGAR UN NUEVO CARACTER
            letras.push_back(texto[i]);
            contador.push_back(1);
        }
    }
    // ****************************************************

    /*
    // ****************************************************
    EL SIGUIENTE BLOQUE DE CODIGO IMPRIME AMBOS VECTORES.

    ES POSIBLE PARALELIZAR, SIN EMBARGO, SI NO SE TIENE UN MECANISMO
    DE SINCRONIZACION PUEDE NO REALIZARSE LA TAREA DE FORMA EFICICIENTE
    */
    for(unsigned int k = 0; k < letras.size(); k++)
    {
        cout<<"Caracter \""<<letras.at(k)<<"\" : "<<contador.at(k)<<" veces\n";
        //cout<<"\'"<<letras.at(k)<<"\', ";
        cc++;
    }
    // ****************************************************
    system("pause");
    return 0;
}