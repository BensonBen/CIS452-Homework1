//
//  main.cpp
//  452-Homework1
//
//  Created by Benjamin J. Benson on 1/16/17.
//  Copyright © 2017 Benjamin J. Benson. All rights reserved.
//

/*
 print the user login name get login();
 print the user ID getuid(void);
 print the group ID gid_t getgid(void);
 print the hostname: int gethostname(char *name, size_t len);
 print the names of the first 5 entries in the password file:  getpwent();
 print the value of a user-specified environment variable:  getenv(string env);
 */
#include <stdlib.h>
#include <pwd.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
using namespace std;

class UserInformation{
    
private:

    /*Holds the integer value for the current login*/
    uid_t loginName;
    
    /*Holds the id of the process that runs this program*/
    uid_t idUserName;
    
    /*Holds the group id of the process that runs this program*/
    gid_t groupId;
    
    /*Holds the error type, and character array for the host process*/
    int realUserNameError;
    char nameCharacterArray[128];

    /*Holds the error type, and the character error for the login name*/
    int loginNameError;
    char loginNameHolder[128];    
public:
    UserInformation(){
        loginNameError = getlogin_r(loginNameHolder, sizeof(loginNameHolder));
        realUserNameError = gethostname(nameCharacterArray, sizeof(nameCharacterArray));
        idUserName = getuid();
        groupId = getGroupId();
    }
    unsigned int getRealUserNameError(){
        return realUserNameError;
    }
    uid_t getIduserName(){
        return idUserName;
    }
    gid_t getGroupId(){
        return groupId;
    }

    /*
    * error checks for login name, and returns the login name
    * if the login name was properly instantiated.
    */
    string getLoginNameHolder(){
         if(loginNameError >= 0){
            string result = "";
            for(int i = 0; i<128; i++){
                result += loginNameHolder[i];
            }
            return result;
         }
         return "Something went wrong getting your real user name.";
    }
    
    /*
    * Returns a string representation of the user name.
    */
    string getHostName() {
        if(realUserNameError >= 0){
        string result = "";
        for(int i = 0; i<50; i++){
            result += nameCharacterArray[i];
        }
        return result;
        }
        return "Something went wrong getting your user name.";
    }
    
    /*
    * Prints to the console
    */
    void getP(){
	   passwd *t = getpwent();
	   int index = 0;
	   while(index < 5){
	       cout << "entry " << index << ":" << t->pw_name<<endl;	
	       t = getpwent();
	       index += 1;
	   }
    }
    
    /*
    * Takes as a parameter the environment variable from the user
    * error checks their input, and prints out that variable if
    * that variable was found successfully.
    */
    void getEnvVariable(char * env){
        char * result = NULL;
        result = getenv(env);
        cout << endl;
        if(result == NULL){
            cout << "There's no variable with that name. Try again?"<<endl;
            cout << "type exit to quit"<<endl;
        }else{
            cout << "The value is: " << getenv(env);
        }
    }
};

int main(int argc, const char * argv[]) {
    //pointer to the user information object
    UserInformation * userInformation = new UserInformation();
    //used to get information from the user
    char env [128];
    
    cout << "Your login name is: "<<userInformation->getLoginNameHolder()<< endl;
    cout << "Your UserID is: " << userInformation->getIduserName() <<endl;
    cout << "Your Group ID is: "<< userInformation->getGroupId()<<endl;
    cout << "Your host name is: "<<userInformation->getHostName()<< endl; 
    userInformation->getP();   
    cout << endl;   
    cout << "Enter the environment varaible: "<<endl;
    cin >> env;

    //execute while the user doesn't type exit
    while(strcmp(env, "exit") != 0){
	   userInformation->getEnvVariable(env);
	   cout << endl<<"Enter the environment varaible: "<<endl;
	   cin >> env;
    }
    cout << "Thanks for using my program!"<<endl;
    return 0;
}