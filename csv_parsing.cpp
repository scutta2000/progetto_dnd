#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ifstream ip("bestiario_golarion.csv");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string clima;
  string fonte;
  string gs;
  string nome;
  string sottotipo;
  string terreno;
  string tipo;

  while(ip.good()){

    getline(ip,clima,',');
    getline(ip,fonte,',');
    getline(ip,gs,',');
    getline(ip,nome,',');
    getline(ip,sottotipo,',');
    getline(ip,terreno,',');
    getline(ip,tipo,'\n');

    std::cout << "cilma: "<<clima << '\n';
    std::cout << "fonte: "<<fonte << '\n';
    std::cout << "gs: "<<gs << '\n';
    std::cout << "sottotipo: "<<sottotipo << '\n';
    std::cout << "terreno: "<<terreno << '\n';
    std::cout << "tipo: "<<tipo << '\n';
    std::cout << "-------------------" << '\n';
  }

  //TODO in vece che stampare salvare in un array i valori letti


  ip.close();
}
