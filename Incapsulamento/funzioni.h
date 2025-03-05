#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//input e output del file
string leggiMessaggio();
void scriviMessaggio();

//conversioni
string charToBin(char msg);
string stringToBin(string msg);
void frameToText(string &frameText);
string headerToText();

//compilazione campi struct
void createFrame(string text);
string createDatagram(string text);

//inizio
void start();