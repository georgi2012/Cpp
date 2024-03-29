#include <iostream>
#include <fstream>
#include <string>

using std::ios;
using std::fstream;
using std::cout;
using std::string;

int main(){

    fstream file("SourcePrint.cpp", ios::in | ios::out | ios::binary);
    if(!file.is_open()){
        cout<<"Error opening the file.\n";
        return -1;
    }
    fstream srcFile("Src_Temp_Binary.txt", ios::out | ios::binary | ios::trunc);
    if(!srcFile.is_open()){
        std::cout<<"Error creating temp file for source code.\n";
    }
    file.seekg(0,ios::end);
    std::streamsize size = file.tellg();
    std::cout<<"( File size is "<<size<<" bytes.)\n";
    std::cout<<"///Code:\n\n";
    std::string str;
    str.resize(size);
    file.read((char*)&str,size);
   // cout<<str<<str.size();
    srcFile.write((const char*)&str,sizeof(char)*str.length());
    srcFile.close();
    file.close();
    file.open("SourcePrint.cpp", ios::in | ios::out);
    if(!file.is_open()){
        cout<<"Error opening the file.\n";
        return -1;
    }
    srcFile.open("Src_Temp_Text.txt", ios::out | ios::trunc);
    if(!srcFile.is_open()){
        std::cout<<"Error creating temp file for source code.\n";
    }
    while (std::getline(file,str)){
        //std::getline(file,str);
       // if(file.eof()){
        //    break;
        //}
        srcFile<<str<<std::endl;
        cout<<str<<std::endl;
    }
    srcFile.close();
    file.close();
    return 0;
}