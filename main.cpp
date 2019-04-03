#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

long byteNum(int);
struct Alumno{
  string nombre;
  string apellidos;
  int ciclo;
  float mensualidad;
  Alumno(){};
  void contar(){
    int nombre=sizeof(nombre);
    int napellidos=sizeof(apellidos);

  }
  void mostrar(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Apellidos: "<<apellidos<<endl;
    cout<<"Ciclo: "<<ciclo<<endl;
    cout<<"Mensualidad: "<<mensualidad<<endl;
  }
};

void add(Alumno *alumno){
  int lengthnombre=alumno->nombre.size();

  int lengthapellidos=alumno->apellidos.size();

  int lengthciclo=sizeof(alumno->ciclo);

  int lengthmensualidad=sizeof(alumno->mensualidad);


  int lengthtotal=sizeof(int)+lengthnombre+sizeof(int)+lengthapellidos+sizeof(int)+lengthciclo+sizeof(int)+lengthmensualidad;
  //alumno->nmensualidad=(to_string(alumno->mensualidad)).size();*/
  ofstream myfile("datos.bin", ios::out | ios::binary | ios::app );

  myfile.write((const char*)&lengthnombre,sizeof(int));
  myfile.write(alumno->nombre.c_str(),lengthnombre);
  myfile.write((const char*)&lengthapellidos,sizeof(int));
  myfile.write(alumno->apellidos.c_str(), lengthapellidos);
  myfile.write((const char*)&lengthciclo,sizeof(int));
  myfile.write((const char*)&(alumno->ciclo),lengthciclo);
  myfile.write((const char*)&lengthmensualidad,sizeof(int));
  myfile.write((const char*)&(alumno->mensualidad),lengthmensualidad);
  myfile.close();

}

void load(){
  vector<Alumno*> alumnos;
  ifstream file ("datos.bin", ios::in | ios::binary);
  int nbytes;
  int _ciclo;
  float _mensualidad;
  Alumno *alumno;
  string str="";
  char* buf;
  //file.seekg(ios::beg);
  while(!file.eof()){
    alumno=new Alumno();

    file.read((char*)&nbytes,sizeof(int));
    buf=new char[nbytes];
    file.read( buf, nbytes);
    str.append(buf, nbytes);
    alumno->nombre=str;
    str="";

    file.read((char*)&nbytes,sizeof(int));
    buf=new char[nbytes];
    file.read( buf, nbytes);
    str.append(buf, nbytes);
    alumno->apellidos=str;
    str="";

    file.read((char*)&nbytes,sizeof(int));
    file.read((char*)&_ciclo,nbytes);
    alumno->ciclo=_ciclo;

    file.read((char*)&nbytes,sizeof(float));
    file.read((char*)&_mensualidad,nbytes);
    alumno->mensualidad=_mensualidad;

    alumnos.push_back(alumno);
  }
  file.close();
  alumnos.pop_back();
  int Registo=1;
  for(auto item:alumnos){
    cout<<endl<<"Registro "<<Registo<<endl;
    item->mostrar();
    Registo++;
  }
}

int numero_alumnos(){
  int n_alumnos;
  cout<<"Ingrese # alumnos"<<endl;
  cin>>n_alumnos;
  return n_alumnos;
}

int main() {
  int cantidad=numero_alumnos();
  for(int i=0;i<cantidad;++i){
    Alumno *newAlumno=new Alumno();
    cout << "nombre: ";
    cin >> newAlumno->nombre;
    cout << "apellidos: ";
    cin.ignore();
    getline(cin, newAlumno->apellidos);
    cout << "ciclo: ";
    cin >> newAlumno->ciclo;
    cout << "mensualidad: ";
    cin >> newAlumno->mensualidad;
    add(newAlumno);
    //load();
  }
  load();

  return 0;
}
