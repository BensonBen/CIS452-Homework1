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
 print the value of a user-specified environment variable:  getenv();
 */

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

class UserInformation{
    
private:
    uid_t loginName;
    
    /*Holds the id of the process that runs this program*/
    uid_t idUserName;
    
    /*Holds the group id of the process that runs this program*/
    gid_t groupId;
    
    /*Holds the error type, and character array for the host process*/
    int realUserNameError;
    char nameCharacterArray[128];
    
    /**/
public:
    UserInformation(){
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
};
int main(int argc, const char * argv[]) {
    UserInformation * userInformation = new UserInformation();
    //fix get the real user name
    cout << "Your login name is: "<<userInformation->getHostName()<< endl;
    cout << "Your UserID is: " << userInformation->getIduserName() <<endl;
    cout << "Your Group ID is: "<< userInformation->getGroupId()<<endl;
    cout << "Your login name is: "<<userInformation->getHostName()<< endl;
    
    
    cout << "Thanks for using my program!"<<endl;
    return 0;
}
