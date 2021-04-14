#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>


//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define WRONG_ARG 3
#define WRONG_FILE 3

using namespace std; 

string read_file(string path){
	ifstream t(path.c_str());
	stringstream buffer;
	buffer << t.rdbuf();
	string s = buffer.str(); 
	return s;
}

bool check(string path){
	ifstream t(path.c_str());
	return !t.is_open();
}

void smx(int & a, const int & b){	if(a < b)	a = b;	}

int main(int argc, char *argv[]){
	if(argc != 3){
		cerr<<("You need to pass exactly 2 files to compare")<<endl;
		return WRONG_ARG;
	}
	for(int i=1;i<=2;i++)
		if( check(argv[i]) ){
			cerr<<"File \""<< RED<< argv[i] << RESET <<"\" does not exist"<<endl;
			return WRONG_FILE;
		}
	string file1 = read_file(argv[1]); 
	string file2 = read_file(argv[2]);
	file1=file1+'\n';
	file2=file2+'\n';
	int n=file1.size(); 
	int m=file2.size();
	int dp[n+2][m+2]; 
	memset(dp, 0, sizeof dp); 

	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)	{
		smx(dp[i][j], dp[i-1][j]);
		smx(dp[i][j], dp[i][j-1]);
		if(file1[i-1] == file2[j-1])	smx(dp[i][j], dp[i-1][j-1]+1);
	}


	int other1[n+2], other2[m+2];

	int i1=n, i2=m;
	while(i1+i2)
		if(i1 > 0 && dp[i1-1][i2] == dp[i1][i2]){
			other1[i1-1] = -1; 
			i1 -- ; 
		} else if(i2 > 0 && dp[i1][i2 - 1] == dp[i1][i2]){
			other2[i2-1] = -1; 
			i2 -- ;
		} else {
			other1[i1-1] = i2-1; 
			other2[i2-1] = i1-1; 
			i1 -- ; 
			i2 -- ;
		}

	int mx = 0;
	string s1, s2;
	i2=0;

	for(i1=0;i1<n;i1++){
		smx(mx, other1[i1]);
		if( other1[i1]  == -1)	s1 = s1 + BOLDGREEN ; 
		else	s1 = s1 + RESET ; 
		s1 = s1 + file1[i1]; 
		for(;i2<=mx;i2++){
			if(other2[i2] == -1)	s2 = s2 + BOLDRED ; 
			else s2 = s2 + RESET ; 
			s2 = s2 + file2[i2];
		}
		if(s1[s1.size() - 1] == '\n' && s2[s2.size() -1] == '\n'){
			if(s1 != s2) cout<<">: "<<s1<<"<: "<<s2<<endl;
			s1 = "";
			s2 = "";
		}
	}
	return 0;
}
