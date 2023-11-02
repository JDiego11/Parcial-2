#include "data.h"

Data::Data(string FileName)         //Constructor de la clase, el contenido del archivo será el atributo principal
{
    bool OpenFile = false;
    while (!OpenFile) {
        Name = FileName;
        try {
            ifstream data(FileName);
            if (!data.is_open()) {
                throw runtime_error("\nNo se encontro el archivo: " + FileName);}
            stringstream buffer;
            buffer << data.rdbuf();
            File = buffer.str();
            data.close();
            DeleteLast();
            OpenFile = true;
        } catch (const exception& ReadFile) {         //Manejo de excepciones con el fallo de lectura de archivo de partidas
            cerr << "Error al abrir el archivo " << ReadFile.what() << endl;
            int option;
            while (true){ cerr << "\n1. Crear un archivo con el nombre ingresado \n2. Ingresar el nombre nuevamente \nSeleccione una opcion: ";
                cin >> option;
                if (option == 1){ofstream NewFile(FileName);break;}             //Validacion de opciones adecuadas
                else if(option == 2) {cerr << "\nVerifique correctamente el nombre: "; cin >> FileName; break;}
                else{cerr << "\nOpcion invalida, seleccione entre 1 y 2";}
            }}}
}

void Data::DeleteLast()
{
    if (!File.empty()) {  // Verificar si File tiene contenido para guardar ordenadamente
        size_t lastNewline = File.find_last_of('\n');
        if (lastNewline != string::npos) {
            File = File.substr(0, lastNewline);
        }
    }
}

void Data::NewData(string Player1, string Player2, int Case, int Num){
    time_t now = time(0);
    string Winner;
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    string Players = "Jugadores: " + Player1 + ", " + Player2;
    string Records = "Fichas: " + to_string(Num);
    string Date = "Fecha: " +to_string(timeinfo.tm_mday) +"/"+ to_string(timeinfo.tm_mon +1)+ "/"+ to_string(timeinfo.tm_year+1900);
    string Time = "Hora: " + to_string(timeinfo.tm_hour) + ":" + to_string(timeinfo.tm_min);
    if (Case == 1) Winner = "Ganador: " + Player1;
    else if(Case == 2) Winner = "Ganador: " + Player2;
    else if(Case == 3) Winner = "Ganador: Empate";
    File += Players + '\n' + Date + '\n' + Time + '\n' + Winner + '\n' + Records + "\n\n";
}

void Data::WriteData(){
    try {
        ofstream OutFile(Name);
        if (!OutFile.is_open()) {
            throw runtime_error("No se pudo guardar la informacion");
        }
        OutFile << File << endl;
        OutFile.close();
    } catch (const exception& e){
        string New;
        cerr << "Error: " << e.what() << endl;
        cerr <<"\n Ingrese un el nombre del archivo de respaldo: "<< endl;
        cin >> New;
        ofstream OutFile(New);
        OutFile << File << endl;
        OutFile.close();
    }
}

string Data::GetField(string fieldName, string data) {
    size_t pos = data.find(fieldName);
    if (pos != string::npos) {
        pos += fieldName.length();
        size_t endPos = data.find('\n', pos);
        if (endPos != string::npos) {
            return data.substr(pos, endPos - pos);
        }
    }
    return "No encontrado";
}


void Data::Winner_Historial() {
    string Historial =
        "+------------------+---------------------------+-----------------+--------------------+\n"
        "|     Fecha        |        Jugadores          |     Ganador     |     Puntuacion     |\n"
        "+------------------+---------------------------+-----------------+--------------------+\n";
    size_t pos = 0;
    while ((pos = File.find("Jugadores: ", pos)) != string::npos) {
        string Players = GetField("Jugadores: ", File.substr(pos));
        string Date = GetField("Fecha: ", File.substr(pos));
        string Winner = GetField("Ganador: ", File.substr(pos));
        string Record = GetField("Fichas: ", File.substr(pos));
        Players.resize(20, ' ');
        Date.resize(12, ' ');
        Winner.resize(16, ' ');
        Record.resize(19, ' ');
        Historial += "|   " + Date + "   |   " + Players +   "    | " + Winner + "| " + Record + "|\n";

        pos = File.find("Jugadores: ", pos)+1;
        Historial += "+------------------+---------------------------+-----------------+--------------------+\n";
    }
    cout << Historial;
}

Data::~Data(){

}
