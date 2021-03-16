#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int getSize(char *text)
{
   int index=0;
   while (text[index]!='\0')
   {
       index++;
   }
   return index;
}

void addCaps(char *&text)
{
  
  
  const int modifier='A'-'a';
  text[0]+=modifier;
  int index=1;
  bool isNextSentence=false;
  while(text[index]!='\0')
  {
    if (text[index]==' ')
    {
        index++;
        continue;
    }
    if (text[index]=='.')
    {
      if(text[index+1]=='.') // 3x
      {
          index+=3;
          continue;
      }
      else {
         isNextSentence=true;
      }
    }
    else if (text[index]=='!' || text[index]=='?')
    {
        isNextSentence=true;
    }
    else if (text[index]>='a' && text[index]<='z' && isNextSentence )
    {
        text[index]+=modifier;
        isNextSentence=false;
    }

     index++;

  }
 return ;

}


int main()
{
    char* text=new (std::nothrow) char[1001];
    cin.getline(text,1000);
    addCaps(text);
    cout<<text;
    
    delete [] text;
    return 0;
}