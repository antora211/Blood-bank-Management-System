#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

using namespace std;

class Donor{

    private:
        int ID_No;
        char name [30];
        char address [30];
        char age[30];
        char phn_no[30];
        char DOB[30];
        char blood_group [10];
        char sex[30];

    public:

        Donor (){

            strcpy (name,"No Title");
            strcpy (address,"No Title");
            strcpy (age,"No Title");
            strcpy (phn_no,"No Title");
            strcpy (DOB,"No Title");
            strcpy (blood_group,"No Title");
            strcpy (sex,"No Title");
        }

    void NewDoner (){

        int a, flag;
        ofstream fout("Donor.txt",ios::app);
        cout << "\n\n\tPlease Enter";

        cout<<"\n\n  Enter ID number: ";
        cin>>a;

        flag=check(a);
        if(flag)
            cout<<"\n\tSorry..... Not available";

        else {
            ID_No=a;

            cin.ignore();

            cout << "\n  Name : ";
            gets(name);

            cout << "  Blood Group : ";
            gets(blood_group);

            cout << "  Address : ";
            gets(address);

            cout << "  Age : ";
            gets(age);

            cout << "  Phone Number : ";
            gets(phn_no);

            cout << "  Date of Birth : ";
            gets(DOB);

            cout << "  Sex : ";
            gets(sex);

            fout.write((char*)this, sizeof(*this));
            fout.close();

        }
    }

    int check (int a) {

        int flag=0;

        ifstream fin("Donor.txt",ios::in);

        while(!fin.eof()) {

            fin.read((char*)this,sizeof(*this));

            if(ID_No==a){

                flag=1;
                break;
            }
        }
        fin.close();
        return(flag);
    }


    void showDonorDetail(){

        cout<<"\n\n";
        cout<<"  ID number     : " << ID_No << endl;
        cout<<"  Name          : " << name << endl;
        cout<<"  Blood Group   : " << blood_group <<endl;
        cout<<"  Address       : " << address << endl;
        cout<<"  Age           : " << age << endl;
        cout<<"  Mobile Number : " << phn_no << endl;
        cout<<"  Date of Birth : " << DOB << endl;
        cout<<"  Sex           : " << sex << endl;

    }


    int showAllDonor (){

        ifstream fin;
        fin.open("Donor.txt", ios::app | ios::binary);

        if (!fin){

            cout << "Donor Not Found\n";
        }

        else{

            fin.read((char*)this, sizeof(*this));

            while(!fin.eof()){
                showDonorDetail();

                fin.read((char*)this, sizeof(*this));
            }
            fin.close();
        }
    }

    int searchDonor (char *b){

        int counter = 0;

        ifstream fin;

        fin.open("Donor.txt", ios::in | ios::binary);

        if (!fin){

            cout << "File Not Found.\n";
        }

        else{

            fin.read((char*)this, sizeof(*this));

            while(!fin.eof()){

                if (!strcmp(b,blood_group)){

                    showDonorDetail();
                    counter++;
                }
                fin.read((char*)this, sizeof(*this));
            }
            if(counter == 0)
                cout << "\nDonor Record not found\n";

            fin.close();
        }
    }


    int deleteDonor (int d) {

        ifstream fin;
        ofstream fout;

        fin.open("Donor.txt", ios::in| ios::binary);

        if (!fin) {
            cout << "File Not Found\n";
        }
        else{

            fout.open("temp.txt", ios::out| ios::binary);
            fin.read((char*)this, sizeof(*this));

            while(!fin.eof()) {

                if(ID_No != d)

                    fout.write((char*)this, sizeof(*this));

                    fin.read((char*)this, sizeof(*this));
                }

                cout<<"Record deleted...";
            fin.close();
            fout.close();
            remove("Donor.txt");
            rename("temp.txt","Donor.txt");

        }

    }

    void editDetail(int d){

        long pos,flag=0;
        fstream file("Donor.txt",ios::in|ios::out|ios::binary);

        while(!file.eof()) {

            pos=file.tellg();

            file.read((char*)this,sizeof(*this));

            if(ID_No==d) {

                cout<<"\n\t Enter New Details";
                cin.ignore();

            cout << "\nName : ";
            gets(name);

            cout << "Blood Group : ";
            gets(blood_group);

            cout << "Address : ";
            gets(address);

            cout << "Age : ";
            gets(age);

            cout << "Phone Number : ";
            gets(phn_no);

            cout << "Date of Birth : ";
            gets(DOB);

            cout << "Sex : ";
            gets(sex);


                file.seekg(pos);
                file.write((char*)this,sizeof(*this));
                cout<<"\n Record is Edited";
                flag=1;
                break;
            }
        }

        if(flag==0)
            cout<<"\n Sorry not found ...."<<endl;

        file.close();
    }


};


int menu(){

        int choice;
        cout<<"\n\n"<<endl;
        cout<<"\t\t\t\t\t\t****************************"<<endl;
        cout<<"\t\t\t\t\t\t**                        **\n"<<endl;
        cout<<"\t\t\t\t\t\t   Blood bank Management    \n"<<endl;
        cout<<"\t\t\t\t\t\t**                        **"<<endl;
        cout<<"\t\t\t\t\t\t****************************\n"<<endl;

        cout <<"\n\t\t\t1. Register New Donor";
        cout <<"\n\t\t\t2. View All Donor";
        cout <<"\n\t\t\t3. Search Blood";
        cout <<"\n\t\t\t4. Delete Donor";
        cout <<"\n\t\t\t5. Edit Donor Detail";
        cout <<"\n\t\t\t6. Exit";

        cout <<"\n\n\t\t\t Enter your choice : ";
        cin >> choice ;

        return (choice);
}


int main(){

    Donor d1;

    char blood[10];
    int d;

    while(1){

        system ("cls");

        switch (menu()){

            case 1:
                d1.NewDoner();
                cout <<"\n Record Inserted";
                break;

            case 2:
                d1.showAllDonor();
                break;

            case 3:
                cout << "\n Enter Blood Group to Search : ";
                cin.ignore();
                cin.getline(blood,20);
                d1.searchDonor(blood);
                break;

            case 4:
                cout << "\n Enter Donor ID to Delete : ";
                cin.ignore();
                cin>>d;
                d1.deleteDonor(d);
                break;

            case 5:
                cout << "\n Enter Donor ID to Edit : ";
                cin.ignore();
                cin>>d;
                d1.editDetail(d);
                break;

            case 6:
                cout << "\n Thank you for using this application";
                cout << "\n Press any key to exit";
                getch();
                exit(0);

            default :
                cout <<"\n Invalid Choice";
                getch();

            }

            getch();

    }

    return 0;
}
