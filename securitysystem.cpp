#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

int main(){
    int a, i=0;
    string text, old, password1, password2, pass, password0, name, age,user,word, word1;
    string creds[2], cp[2];

    cout<<"     Southern-Just Security"<<endl;

    cout<<"__________________"<<endl<<endl;
    cout<<"|              1.Register            |"<<endl;
    cout<<"|              2.Login               |"<<endl;
    cout<<"|              3.Change password     |"<<endl;
    cout<<"|              4.End program         |"<<endl<<endl;

    do{
        cout<<endl<<endl;
        cout<<"Enter your choice:- ";
        cin>>a;
        switch(a)
        {
            case 1:{
                cout<<"________________"<<endl<<endl;
                cout<<"-------Register-------"<<endl;
                cout<<"|___________________|"<<endl<<endl;
                cout<<"Please Enter username:- ";
                cin>>name;
                cout<<"Please enter password:- ";
                cin>>password0;
                cout<<"Please enter your age:- ";
                cin>>age;

                ofstream of1;
                of1.open("file.txt");
                if(of1.is_open()){
                    of1<<name<<"\n";
                    of1<<password0;
                    cout<<"Registration successful"<<endl;

                }

                break;
            }

            case 2:{
                i=0;

                cout<<" ____________________"<<endl<<endl;
                cout<<"|--------Login------|"<<endl;
                cout<<"|___________________|"<<endl<<endl;

                ifstream of2;
                of2.open("file.txt");
                cout<<"Please enter the username:-";
                cin>>user;
                cout<<"please enter passsword:-";
                cin>>pass;

                if(of2.is_open()){
                    while(!of2.eof()){
                        while(getline(of2, text)){
                            istringstream iss(text);
                            iss>>word;
                            creds[1]=word;
                            i++;
                        }

                        if(user==creds[0] && pass==creds[1]){
                            cout<<"----Log in successful----";
                            cout<<endl<<endl;

                            cout<<"Details"<<endl;

                            cout<<"username: "+ name<<endl;
                            cout<<"password: "+ pass<<endl;
                            cout<<"age: "+ age<<endl;
                        }

                        else{
                            cout<<endl<<endl;
                            cout<<"Incorrect credentials"<<endl;
                            cout<<"|    1. press 2 to login     |"<<endl;
                            cout<<"|    2. press 3 to change password    |"<<endl;

                            break;
                        }

                    }
                }

                break;
            }
            case 3:{
                i=0;

                cout<<"-------Change password------"<<endl;

                ifstream of0;
                of0.open("file.txt");
                cout<<"Enter Old password:- ";
                cin>>old;
                if(of0.is_open()){
                    while(of0.eof()){
                        while(getline(of0, text)){
                            istringstream is(text);
                            is>>word1;
                            cp[1]=word1;
                            i++;

                        }
                        if(old==cp[1]){
                            of0.close();

                            ofstream of1;
                            if(of1.is_open()){
                                cout<<"Enter new password:- ";
                                cin>>password1;
                                cout<<"Enter password again:- ";
                                cin>>password2;

                                if(password1 == password2){
                                    of1<<cp[0]<<"\n";
                                    of1<<password1;
                                    cout<<"Password changed successfully"<<endl;

                                }
                                else{
                                    of1<<cp[0]<<"\n";
                                    of1<<old;
                                    cout<<"Password do not match"<< endl;
                                }

                            }
                        }
                        else{
                            cout<<"please enter a valid password"<<endl;
                            break;

                        }
                    }
                }
                break;
            }
            case 4:
            {
                cout<<"________Thank you!________";
                break;
            }
            default:
            cout<<"Enter a valid choice";
        
        }

    }
    while(a!=4);
    return 0;


}