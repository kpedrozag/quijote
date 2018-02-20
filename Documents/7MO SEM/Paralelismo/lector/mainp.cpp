#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <map>
using namespace std;

int main()
{

    string texto = "", aux;
    
    char lt[84] = { 'T', 'h', 'e', ' ', 'P', 'r', 'o', 'j', 'c', 't', 'G', 'u', 'n', 'b', 'g', 'E', 'B', 'k', 'f', 'D', 'Q', 'i', 'x', ',', 'y', 'M', 'l', 'd', 'C', 'v', 'a', 's', 'w', 'm', '.', 'Y', 'p', '-', 'L', ':', 'A', 'S', 'R', 'J', '2', '7', '0', '4', '[', '#', '9', '6', ']', 'U', '1', '5', '*', 'O', 'F', 'H', 'I', 'N', 'K', 'X', 'W', 'V', '\'', 'Z', ';', '"', 'q', '8', '(', ')', 'z', '3', '?', '!', '_', '=', '/', '%', '@', '$' };
    
    int tam = sizeof(lt)/sizeof(*lt);
    
    map <char, int> mapa;
    
    //Abre archivo
    ifstream file("quijote.txt");
    
    //guarda todo en var string
    while(getline(file, aux))
    {
        texto = texto + aux + " ";
    }
    file.close();
    
    int num_hilos = 4;
    
    vector< vector<char> > letras(num_hilos);
    vector< vector<int> > contador(num_hilos);
    
    omp_set_num_threads(num_hilos);
    
    int particion = (int)(texto.length() / num_hilos);

    int id_hilo, ini, fin, it, pos;
    unsigned int jt; 
    bool bandera;
    
    #pragma omp parallel private(ini, fin, it, id_hilo, bandera, pos)
    {
        id_hilo = omp_get_thread_num();
        
        ini = particion * id_hilo;
        
        if(id_hilo == (num_hilos-1))
        {
          fin = particion * (id_hilo + 1) + texto.length() % num_hilos;
        }
        else
        {
          fin = particion * (id_hilo + 1);
        }
        for(it = ini; it < fin; it++)
        {
          bandera = false;
          for(jt = 0; jt < letras.at(id_hilo).size(); jt++)
          {
            if( texto[it] == letras.at(id_hilo).at(jt) ){
              bandera = true;
              pos = jt;
              break;
            }
          }
          
          if(bandera)
          {
            contador.at(id_hilo).at(pos) = contador.at(id_hilo).at(pos) + 1;
          }
          else
          {
            letras.at(id_hilo).push_back(texto[it]);
            contador.at(id_hilo).push_back(1);
          }
        }
    }
    
    for(int q = 0; q < tam; q++)
    {
      mapa[lt[q]] = 0;
    }
    
    for(int k = 0; k < letras.size(); k++)
    {
      for(int l = 0; l < letras.at(k).size(); l++)
      {
        mapa[letras.at(k).at(l)] += contador.at(k).at(l);
      }
    }
    
    for (map<char, int>::iterator rec = mapa.begin(); rec != mapa.end(); rec++) {
        cout<<"Caracter \'"<<rec->first<<"\' : "<<rec->second<<" veces\n"; 
    }
    
    system("pause");
    return 0;
}
