struct ipHeader{
	string version= "0100";
	string headerLength;
	struct typeOfService{
		string precedence;
		string delay;
		string throughput;
		string realiability;
		string monetaryCost;
		string unused = "0";
	};
	string totalLength;
	string identification;
	string flags;
	string fragmentOffset;
	string ttl;
	string protocol;
	string headerChecksum;
	string sourceip;
	string destip;
	string options;
	string padding;
	string data;
};



void leggiMessaggio(){
	string line;
	ifstream fin ("msg.txt");
	if(!fin){
		cerr<<"errore apertura file in lettura.";
	}
	getline(fin, line);
    cout<<line;
}

void scriviMessaggio(){
	
	ofstream fout ("frame.txt");
	if(!fout){
		cerr<<"errore apertura file in scrittura.";
	}
	fout<<headerIp;
}

string chartobin(char c){
	string s;
	char a[8];
	for(int i=0; i<8; i++)	{
		a[i]=c%2;
		if(c%2){
			c-=(c-1)/2;	
		}else{
			c-=c/2;
		}	
	}
	s=a;
	cout<<s;
	return s;
}

string stringtobin(string c){
	
}
