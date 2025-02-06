#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
	string data;
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

string stringToBin(string msg) {
    string line;
    for (int i = 0; i < msg.size(); i++) {
        line = line + charToBin(msg[i]);
    }
    return line;
}

//chartobin ma adattato a 16 bit per total length
string calculateTotLen(char length) {
    string bin;
    int i = 0;

    while (length >= 1) {
        if (length % 2) {
            bin = "1" + bin;
        }
        else {
            bin = "0" + bin;
        }
        length /= 2;
        i++;
    }

    for (i; i < 16; i++) {
        bin = "0" + bin;
    }

    return bin;
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
	headerText += header.data;
	
	return headerText;
}

string createDatagram(string text){
	char totLen;

	header.headerLength = "0101"; //l'header è sempre lungo 5 words, ovvero 5 gruppi da 4 byte
	header.tos = "00000000";
	header.totalLength = "";
	header.identification = "0000000000000000";
	header.flags = "010"; //flag don't fragment alzato
	header.fragmentOffset = "0000000000000";
	header.ttl = "00000000";
	header.protocol = "00000110"; //TCP
	header.headerChecksum = "0000000000000000"; //non so fare il checksum
	header.sourceIp = "11000000101010000000010001101000"; //192.168.4.104
	header.destIp = "11000000101010000000010001101001"; //192.168.4.105

	header.data = stringToBin(text);

	//calcolo total length
	finalMsg = headerToText();
	//prendo la grandezza in bit del datagram e la divido per avere i byte
	totLen = finalMsg.size() / 8;
	//scrivo su totalLength la grandezza convertita in binario e aggiorno il datagram
	header.totalLength = calculateTotLen(totLen);
	finalMsg = headerToText();

	cout<<"datagram creato!"<<endl;
	return finalMsg;
}

void start(){
	finalMsg = leggiMessaggio();
	createDatagram(finalMsg);
	scriviMessaggio();
}