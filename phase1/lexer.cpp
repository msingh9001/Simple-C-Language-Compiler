//
//  lexer.cpp
//  Phase 1
//
//  Created by Mandeep Singh on 1/5/21.
//  All rights reserved.
//
//  Phase 1 is creatinng the lexical analysis module. We read in some code provided by the user and classify it as either an integer, string, identifier, keyword, or operator. Whitespace, comments, and illegal constructs produce no output
//  Example: int x; is the input. The program will output:
//  keyword:int
//  identifier:x
//  operator:;
//

/* The following points summarize the lexical rules for Simple C:
 •  spaces,  tabs,  newlines,  and other whitespace are ignored;  it is formally defined by the regular expression(|\t|\n|\f|\v|\r)+
 •  an integer consists of one or more digits; it is formally defined by the regular expression [0–9]+
 •  a string is enclosed in double quotes (". . .") and may not contain a newline or a double quote unless theyare preceded by a backslash
 •  an identifier consists of a letter or underscore followed by optional letters, underscores, and digits; it is de-fined by the regular expression [_a–zA–Z][_a–zA–Z0–9]*
 •  keywords are auto,break,case,char,const,continue,default,do,double,else,enum,extern,float,for,goto,if,int,long,register,return,short,signed,sizeof,static,struct,switch,typedef,union,unsigned,void,volatile, and while; keywords may not be used as identifiers
 •  operators are =,|,||,&&,==,!=,<,>,<=,>=,+,-,*,/,%,&,!,++,--,.,->,(,),[,],{,},;,:, and ,
 •  comments may not include a */
/*
 •  any other character is illegal*/

# include <iostream>

using namespace std;

int main(){
    //Define set of keywords
    const char* keywords[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    //Define set of operators
    char operators[] = {'=','|','<','>','+','-','*','/','%','&','!','.','(',')','[',']','{','}',';',':',','};
    
    string token;
    bool flag1 = 0;
    bool flag2 = 0;
    bool flag3 = 0;
    bool flag4 = 0;
    int c = cin.get();
    
    while (!cin.eof()) {
        //Clear token for good measure
        token.clear();
        
        //blankspace character
        if(isspace(c)){
            c = cin.get();
            continue;
        }
        
        //since '/' and '*' are operators and '/*' and '*/' are comment delimeters, we need an exception to make sure they are ignored
        if(c == '/' && cin.peek() == '*'){
            flag4 = 1;
            while(flag4 == 1){
                c = cin.get();
                if(c == '*' && cin.peek() == '/'){
                    c = cin.get();
                    flag4 = 0;
                }
            }
            c = cin.get();
            continue;
        }
        //identifiers or keywords
        if(isalpha(c) || c == '_'){
            //we know if starts with _ then has to be identifier
            if(c == '_')
                flag1 = 1;
            token += c;
            c = cin.get();
            
            //the rest of the characters of an identifier can be alphanumeric or _
            while(isalnum(c) || c == '_'){
                token += c;
                c = cin.get();
            }
            if(token == "_"){
                flag1 = 0;
                continue;
            }
            //If flag is set, we save time by not going through for loop since we know its identifier
            if(flag1 == 1)
                cout << "identifier:" << token << endl;
            else{
                //Trying to match token with keyword
                for(int i = 0; i < 32; i++){
                    if(token == keywords[i]){
                        cout << "keyword:" << token << endl;
                        flag2 = 1;
                    }
                }
            }
            
            //If not a keyword, then identifier
            if(flag2 == 0 && flag1 == 0)
                cout << "identifier:" << token << endl;
            
            token.clear();
            flag1 = 0;
            flag2 = 0;
            continue;
        }
        
        //integer (single or multiple characters long)
        if(isdigit(c)) {
            while (isdigit(c)){
                token += c;
                c = cin.get();
            }
            cout << "int:" << token << endl;
            token.clear();
            continue;
        }
        
        //strings
        if(c == '"'){
            //If open quote, we flag to check for close quote later
            token += c;
            c = cin.get();
            while(c != '"'){
                //We want quotation marks to be allowed in strings so we make an exception for it
                if(c == '\\'){
                   token += c;
                   c = cin.get();
                }
                token += c;
                if(cin.peek() == cin.eof())
                    cout << "Error, no close quotation mark for string" << endl;
                c = cin.get();
            }
            token += '"';
            cout << "string:" << token << endl;
            token.clear();
            c = cin.get();
            continue;
        }
        
        //Set a flag if character is an operator
        for(int i = 0; i < 21; i++)
            if(c == operators[i])
                flag3 = 1;
        
        //operators
        if(flag3 == 1){
            token += c;
            
            // | & = + - > are only options for second operator character
            if(cin.peek() == '|' || cin.peek() == '&' || cin.peek() == '=' || cin.peek() == '+' || cin.peek() == '-' || cin.peek() == '>'){
                switch(c){
                    case '|':
                        if(cin.peek() == '|'){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '&':
                        if(cin.peek() == '&'){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '=':
                        if(cin.peek() == '='){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '+':
                        if(cin.peek() == '+'){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '-':
                        if(cin.peek() == '-' || cin.peek() == '>'){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '!':
                        if(cin.peek() == '='){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '<':
                        if(cin.peek() == '='){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    case '>':
                        if(cin.peek() == '='){
                            c = cin.get();
                            token += c;
                        }
                        break;
                    default:
                        break;
               }
            }
            cout << "operator:" << token << endl;
            token.clear();
            c = cin.get();
            flag3 = 0;
            continue;
        }
        
        //All other characters should be skipped
       // cout << "illegal character" << endl;
        c = cin.get();
        continue;
    }
}
