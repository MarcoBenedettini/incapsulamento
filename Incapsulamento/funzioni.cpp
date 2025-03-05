#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//dichiaro le struct sia dell'header che del frame da compilare
struct ethernetFrame{
	string preamble = "10101010101010101010101010101010101010101010101010101010";
	string sfd = "11010101";
	string destMac;
	string sourceMac;
	string type;
	string data;
};

struct ipHeader{
	string version = "0100"; //ipv4
	string headerLength;
	string tos;
	string totalLength;
	string identification;
	string flags;
	string fragmentOffset;
	string ttl;
	string protocol;
	string headerChecksum;
	string sourceIp;
	string destIp;
	ethernetFrame payload;
};

//dichiaro le variabili globali
ipHeader header;
string finalMsg;

//leggo il messaggio da file
string leggiMessaggio(){
	string line;
	ifstream fin ("msg.txt");
	if(!fin){
		cerr<<"errore apertura file in lettura.";
	}
	getline(fin, line);
	return line;
}

//scrivo il messaggio sul file frame.txt
void scriviMessaggio(){

	string text = finalMsg;

	ofstream fout ("frame.txt");
	if(!fout){
		cerr<<"errore apertura file in scrittura.";
	}

	fout<<text;
	fout.close();	
}

//conversione da char a binario per convertire i singoli caratteri in una stringa
string charToBin(char msg) {
    string bin;
    int i = 0;

    while (msg >= 1) {
        if (msg % 2) {
            bin = "1" + bin;
        }
        else {
            bin = "0" + bin;
        }
        msg /= 2;
        i++;
    }

    for (i; i < 8; i++) {
        bin = "0" + bin;
    }

    return bin;
}

//conversione da stringa a binario che converte ogni carattere della stringa in binario
string stringToBin(string msg) {
    string line;
    for (int i = 0; i < msg.size(); i++) {
        line = line + charToBin(msg[i]);
    }
    return line;
}


void frameToText(string &frameText){
	//questa funzione prende tutti i campi del frame e li mette in un unica stringa
	//prende come argomento la stringa non finita dell'header
	frameText += header.payload.preamble;
	frameText += header.payload.sfd;
	frameText += header.payload.destMac;
	frameText += header.payload.sourceMac;
	frameText += header.payload.type;
	frameText += header.payload.data;
}

string headerToText(){
	//questa funzione prende tutti i campi del datagram e li mette in una sola stringa
	string headerText;

	headerText += header.version;
	headerText += header.headerLength;
	headerText += header.tos;
	headerText += header.totalLength;
	headerText += header.identification;
	headerText += header.flags;
	headerText += header.fragmentOffset;
	headerText += header.ttl;
	headerText += header.protocol;
	headerText += header.headerChecksum;
	headerText += header.sourceIp;
	headerText += header.destIp;
	frameToText(headerText);
	
	return headerText;
}


void createFrame(string text){
	//compila i campi del frame
	header.payload.destMac = "101011111010111110101111101011111010111110101111";
	header.payload.sourceMac = "101011001010111110101101101011001010011010101110";
	header.payload.type = "1000000000000000";
	header.payload.data = stringToBin(text);
}

string createDatagram(string text){
	//compila tutti i campi dell'header per passare poi al frame ed infine metterli in una stringa

	header.headerLength = "0101"; //l'header è sempre lungo 5 words, ovvero 5 gruppi da 4 byte
	header.tos = "01100110"; //3 di precedence, reliability e monetary cost alzati
	header.totalLength = "0000000000111100";
	header.identification = "1101010011110001";
	header.flags = "010"; //flag don't fragment alzato
	header.fragmentOffset = "0000000000000";
	header.ttl = "01000000";
	header.protocol = "00000110"; //TCP
	header.headerChecksum = "0000000000000000"; //non so fare il checksum
	header.sourceIp = "11000000101010000000000100001010"; //192.168.1.10
	header.destIp = "00001000000010000000000000001000"; //192.168.4.105
	
	createFrame(text);
	
	finalMsg = headerToText();
	
	cout<<"datagram creato!"<<endl;
	return finalMsg;
}

void start(){
	finalMsg = leggiMessaggio();
	createDatagram(finalMsg);
	scriviMessaggio();
}