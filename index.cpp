#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
string arr[4];

class BackControls
{
public:
    int inncorrectAdminPassword = 0;
    int inncorrectUserPassword = 0;
    void UserLogin(string name);
    void Admin_access();
    void Admin_Login();
    void login();
    void Welcome();
};

class User
{
public:
    string username;
    string password;
};

class PolicyDetails
{
public:
    string username;
    string policyName;
    string status;

    void showPolicies()
    {
        cout << username << " " << policyName << " " << status;
    }
    void storeRecord();
    void applied_Policies();
};
class Queries
{
public:
    string username;
    string question;
    void storeQueries();
};
void Queries ::storeQueries()
{
    ofstream fout;

    string queries = "_Questions";
    string filename = this->username;

    filename.append(queries);
    filename.append(".txt");

    fout.open(filename, ios::app | ios::out | ios::binary);

    fout << this->question << endl;
    // fout.write((char*)this,sizeof(*this));

    fout.close();
}
void PolicyDetails::storeRecord()
{
    BackControls B1;
    int option;
    ofstream fout;
    fstream fin;
    int count = 0;
    string line;
    string filename = this->username;
    filename.append(".txt");

    fout.open(filename, ios::app | ios::binary);
    fin.open(filename, ios::in | ios::binary);

    while (getline(fin, line))
    {

        count++;
    }
    fout << count + 1 << " " << this->policyName << " " << this->status << endl;

    fout.close();
    cout << "1.Main Menu" << endl;
    cin >> option;

    cout << "Applied Successfully" << endl;
    if (option)
    {
        B1.UserLogin(this->username);
    }
}

//-------------------------- registration-----------------

void Admin_Reg()
{
    string admin_name, admin_pass;
    BackControls B1;
    int choice;
    cout << "Enter the username :";
    cin >> admin_name;
    cout << "\nEnter the password :";
    cin >> admin_pass;

    ofstream reg("Admin.txt", ios::app);
    reg << admin_name << ' ' << admin_pass << endl;
    system("cls");
    cout << "\nRegistration Successfull\n";
    cout << "1.login" << endl;
    cout << "2.Main menu" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        B1.Admin_Login();
        break;
    case 2:
        B1.Welcome();
        break;
    }
    // welcome();
}
void User_Reg()
{
    string user_name, user_pass;
    BackControls B1;
    int choice;
    cout << "Enter the username :";
    cin >> user_name;
    cout << "\nEnter the password :";
    cin >> user_pass;
    ofstream reg;
    ofstream reg2;
    string filename = user_name + "Credentials";

    filename.append(".txt");
    cout << filename << endl;
    reg.open(filename, ios::app);

    reg << user_name << ' ' << user_pass << endl;

    reg2.open("users.txt", ios::in);
    reg2 << user_name << endl;
    system("cls");
    cout << "\nRegistration Successfull\n";
    cout << "1.login" << endl;
    cout << "2.Main menu" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        B1.UserLogin(user_name);
        break;
    case 2:
        B1.Welcome();
        break;
    }
    reg.close();
    reg2.close();
}

void registr()
{
    int choice;

    system("cls");

    cout << "1.Admin\n";
    cout << "2.User\n";
    cout << "\nEnter your choice : ";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        Admin_Reg();
        break;
    case 2:
        User_Reg();
        break;
    }
}

//------------- Admin Reg----------------------

//------------------------login------------------------------
//----------------------------- update policy status----------------
int updatePolicyStatus(int option, string status, string str)
{
    string word = "";
    int num = 0;
    int count = 0;
    str += " ";
    for (int i = 0; i < str.length(); i++)
    {
        char x = str[i];
        // cout << "count is "<<count;
        if (x == ' ')
        {
            // 1 cout << word <<""<<name<< endl;//compres return 0 when both are string are equal
            if (!word.compare(to_string(option)))
            {
                num = 1;
                arr[count] = word;
                count++;
                word = "";
            }
            else if (count == 0)
            {
                return 0;
            }
            else
            {

                arr[count] = word;

                count++;
                word = "";
            }
        }
        else
        {
            word = word + x; //'Life_Policy'
        }
    }
    if (count)
    {
        arr[2] = status;

        return 1;
    }

    return 0;
}

//------------------------- updateStatusApproval----------------------------

void updateStatusApproval(int option, string status, string filename, string customer_name)
{

    fstream fin;
    fstream fin2;
    string line;
    auto filename1 = filename;

    fin.open(filename, ios::in | ios::binary);
    fin2.open("temp.txt", ios::out);

    while (getline(fin, line))
    {
        int res = updatePolicyStatus(option, status, line); // "Life_Policy 5yrs"  , "Life_Policy"
        cout << "res" << res << endl;
        if (res)
        {
            fin2 << arr[0] << " " << arr[1] << " " << arr[2] << endl;
        }
        else
        {
            fin2 << line << "\n";
        }
    }

    fin.close();
    fin2.close();
    cout << (customer_name + ".txt").c_str() << endl;
    remove((customer_name + ".dat").c_str());

    rename("temp.txt", (customer_name + ".dat").c_str());
}
//-------------------- update policy status ----------------
void updateStatus(int option, string filename, string customer_name)
{
    int choice;
    int policyNumber;
    cout << "please enter the policy number" << endl;
    cin >> policyNumber;
    cout << "1.Approved" << endl;
    cout << "2.Disapproved" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        updateStatusApproval(policyNumber, "Approved", filename, customer_name);
        break;
    case 2:
        updateStatusApproval(policyNumber, "Disapproved", filename, customer_name);
        break;
    }
}
int updateString(int pos, string name, string newValue, string str) // "Life_Policy 5yrs "  , "Life_Policy"
{
    string word = "";
    int num = 0;
    int count = 0;
    str += " ";
    for (int i = 0; i < str.length(); i++)
    {
        char x = str[i];
        // cout << "count is "<<count;
        if (x == ' ')
        {
            cout << word << "" << name << endl; // compres return 0 when both are string are equal
            if (!word.compare(name))
            {
                num = 1;
                arr[count] = word;
                count++;
                word = "";
            }
            else if (count == 1)
            {
                return 0;
            }
            else
            {

                arr[count] = word;

                count++;
                word = "";
            }
        }
        else
        {
            word = word + x; //'Life_Policy'
        }
    }
    if (num)
    {
        arr[pos] = newValue;

        return 1;
    }

    return 0;
}
//------------------------------- Get substring -------------------

int getSubString(string str, string name) // "Life_Policy 5yrs "  , "Life_Policy"
{
    string word = "";
    int num = 0;
    for (auto x : str)
    {
        if (x == ' ')
        {
            // compres return 0 when both are string are equal
            if (!word.compare(name))
            {
                num = 1;
                return num;
            }
            return 0;
        }
        else
        {
            word = word + x; //'Life_Policy'
        }
    }
    return 0;
}
//----------------------- Update Policy Attribute----------------------

void update_policy_attribute(int num, string name, string newValue)
{
    ifstream fin;
    fstream fin2;
    string line;
    fin.open("policies.txt", ios::in | ios::binary);
    fin2.open("temp.txt", ios::out);

    while (getline(fin, line))
    {
        int res = updateString(num, name, newValue, line); // "Life_Policy 5yrs"  , "Life_Policy"
        cout << "res" << res << endl;
        if (res)
        {
            fin2 << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << endl;
        }
        else
        {
            fin2 << line << "\n";
        }
    }
    cout << "---Updated Successfully-----" << endl;
    fin.close();
    fin2.close();
    remove("policies.txt");
    rename("temp.txt", "policies.txt");
}

//----------------------- Policy Attribute-------------------------

void policyAttributes(int num, string name)
{
    int choice;
    string newValue;
    cout << "1.name" << endl;
    cout << "2.duration" << endl;
    cout << "3.basic plan price" << endl;
    cout << "4.premium plan price" << endl;
    cout << "please select the attribute you want to update" << endl;
    cin >> choice;
    cout << "please enter the new value" << endl;
    cin >> newValue;
    switch (choice)
    {
    case 1:
        update_policy_attribute(choice, name, newValue);
        break;
    case 2:
        update_policy_attribute(choice, name, newValue);
        break;
    case 3:
        update_policy_attribute(choice, name, newValue);
        break;
    case 4:
        update_policy_attribute(choice, name, newValue);
        break;
    }
}
//-------------------------------- Applied Policies-----------------
void applied_Policies(string name)
{

    ifstream fin;
    fstream getData;
    string line;
    string filename = name;

    filename.append(".txt");

    fin.open(filename, ios::in | ios::binary);

    while (getline(fin, line))
    {

        cout << line << endl;
    }

    getData.close();

    fin.close();
}
//------------ Apply policy ------------------------
void Apply_Policy(string policyName, string userName)
{
    PolicyDetails p1;
    p1.username = userName;
    p1.policyName = policyName;
    p1.status = "pending";
    p1.storeRecord();
    // p1.applied_Policies();
}
//---------------------------- Enter Queries ------------------------

void Enter_Queries(string name)
{
    char query[50];
    cout << "please enter ur queries" << endl;
    cin.ignore();
    cin.getline(query, 50);

    Queries q1;
    q1.username = name;
    q1.question = query;
    q1.storeQueries();
}
//------------------------- Different Policies-------------------
void life_Policy(string name)
{
    int choice;
    string policyName = "LifePolicy";
    string filename = name;
    BackControls B1;
    cout << "------------- Life Policy -------" << endl;

    fstream getData;
    string line;

    // filename.append(".dat");
    getData.open("life.dat", ios::in | ios::binary);
    cout << "PolicyName duration   basic   premium" << endl;
    while (getline(getData, line))
    {
        cout << line << endl;
    }
    getData.close();

    cout << " 1.Apply" << endl;
    cout << " 2.Main menu" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        Apply_Policy(policyName, name);
        break;
    case 2:
        B1.UserLogin(name);
    }
}
void TravelPolicy(string name)
{
    int choice;
    string policyName = "TravelPolicy";
    cout << "---- Travel Policy---------" << endl;
    string filename = name;

    fstream getData;
    string line;
    // ifstream getData;
    getData.open("travel.dat", ios::in | ios::binary);
    cout << "PolicyName Period  basic  premium" << endl;
    while (getline(getData, line))
    {
        cout << line << endl;
    }
    getData.close();

    cout << " 1.Apply" << endl;
    cout << " 2.Main menu" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        Apply_Policy(policyName, name);
        break;
    }
}
void CarPolicy(string name)
{

    int choice;
    string policyName = "CarPolicy";
    cout << "---------- Car Policy ------------" << endl;
    string filename = name;

    fstream getData;
    string line;
    // ifstream getData;
    getData.open("car.dat", ios::in | ios::binary);
    cout << "PolicyName Period  basic  premium" << endl;
    while (getline(getData, line))
    {
        cout << line << endl;
    }
    getData.close();

    cout << " 1.Apply" << endl;
    cout << " 2.Main menu" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        Apply_Policy(policyName, name);
        break;
    }
}

//--------------------------------- update policy ------------------
void update_Policy()
{

    int choice;
    string line;
    string name;
    cout << "1.life Policy" << endl;
    cout << "2.Travel Policy" << endl;
    cout << "3.Car Policy" << endl;

    cout << "please select the policy you want to update" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        policyAttributes(choice, "Life_Policy");
        break;
    case 2:
        policyAttributes(choice, "Travel_Policy");
        break;
    case 3:
        policyAttributes(choice, "Car_Policy");
        break;
    }
}
//-------------------------- Delete Policy ------------------------
void delete_Policy()
{

    ifstream fin;
    fstream fin2;
    int choice;
    string line;
    string name;
    cout << "1.life Policy" << endl;
    cout << "2.Travel Policy" << endl;
    cout << "3.Car Policy" << endl;

    cout << "please select the policy to be Deleted" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        name = "Life_Policy";
        break;
    case 2:
        name = "Travel_policy";
        break;
    case 3:
        name = "Car_policy";
        break;
    }
    fin.open("policies.txt", ios::in | ios::binary);
    fin2.open("temp.txt", ios::out);

    while (getline(fin, line))
    {

        int res = getSubString(line, name); // "Life_Policy 5yrs"  , "Life_Policy"
        // cout << "res" << res << endl;
        if (res)
        {
            cout << res << endl;
        }
        else
        {
            fin2 << line << endl;
        }
    }

    fin.close();
    fin2.close();
    remove("policies.txt");
    rename("temp.txt", "policies.txt");
}

//---------------- add new policy -----------------------------
void add_New_Policy()
{
    string policyName, duration;
    int count = 0;
    string line;
    fstream filein;
    int Basic_Plan_Price, Premium_Price_Plan;
    cout << "enter the Policy Name" << endl;
    cin >> policyName;
    cout << "enter the Duration in Years" << endl;
    cin >> duration;
    cout << "enter the Basic plan price " << endl;
    cin >> Basic_Plan_Price;
    cout << "enter the Premium plan price " << endl;
    cin >> Premium_Price_Plan;

    ofstream file;
    filein.open("policies.txt", ios::in);
    while (getline(filein, line))
    {

        count++;
    }

    file.open("policies.txt", ios::app);

    file << count + 1 << " " << policyName << "   " << duration + "yrs"
         << "   " << Basic_Plan_Price << "   " << Premium_Price_Plan << endl;
    cout << "Policy Added Successfully" << endl;
    file.close();
}
//------------------------ view policy ---------------------
void View_Policies()
{
    ifstream fin;
    int choice;
    string line;
    BackControls B1;
    fin.open("policies.txt", ios::in | ios::binary);
    cout << "Policy_Name "
         << " "
         << "duration"
         << " "
         << "basic"
         << " "
         << "premium " << endl;
    while (getline(fin, line))
    {

        cout << line << endl;
    }

    fin.close();
    cout << "----- please select -----" << endl;
    cout << "1.Add new policy" << endl;
    cout << "2.Delete Policy" << endl;
    cout << "3.Update Policy" << endl;
    cout << "4.Back Menu" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        add_New_Policy();
        break;
    case 2:
        delete_Policy();
        break;
    case 3:
        update_Policy();
    case 4:
        B1.Admin_access();
    }
}
//--------------------- show Queries  to admin -------------
void showQueries(string customer_name)
{
    BackControls B1;
    int choice;
    ifstream fin;
    string line;
    string file = customer_name.append("_Questions.txt");
    cout << file << endl;
    fin.open(file, ios::in | ios::binary);
    if (fin.is_open())
        while (getline(fin, line))
        {

            cout << line << endl;
        }
    cout << "1.main menu" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        B1.Admin_access();
        break;

    default:
        break;
    }
}
//----------------------------- show Customers---------------------
void Customers()
{
    ifstream fin;
    int option;
    string line;
    BackControls B1;

    fin.open("users.txt", ios::in | ios::binary);

    while (getline(fin, line))
    {

        cout << line << endl;
    }

    string customer_name;
    fin.close();
    cout << "please enter customer name" << endl;
    cin >> customer_name;
    ifstream fin2;
    string filename = customer_name;
    filename.append(".dat");
    string line2;

    fin2.open(filename, ios::in | ios::binary);

    while (getline(fin2, line2))
    {

        cout << line2 << endl;
    }
    cout << "---- please select below option ---------" << endl;
    cout << "1.Update Status" << endl;
    cout << "2.Show Queries" << endl;
    cout << "3.main menu" << endl;
    cin >> option;
    switch (option)
    {
    case 1:
        updateStatus(option, filename, customer_name);
        break;

    case 2:
        showQueries(customer_name);
        break;
    case 3:
        B1.Admin_access();
        break;

    default:
        break;
    }
}
//------------------------------- user login-----------------------
void BackControls::UserLogin(string name)
{
    int choice;
    BackControls B1;
    cout << "Hey, Here are few policies we offer" << endl;
    cout << "1.Life Policy" << endl;
    cout << "2.Travel Policy" << endl;
    cout << "3.Car Policy" << endl;
    // cout << "4.applied_Policies" << endl;
    cout << "4.show Applied Polices" << endl;
    cout << "5.Ask Question" << endl;
    cout << "6.Logout" << endl;
    cout << "please enter a Policy number " << endl;

    cin >> choice;
    switch (choice)
    {
    case 1:
        life_Policy(name);
        break;
    case 2:
        TravelPolicy(name);
        break;
    case 3:
        CarPolicy(name);
        break;
    case 4:
        applied_Policies(name);
        break;
    case 5:
        Enter_Queries(name);
        break;
    case 6:
        B1.login();
        break;
    }
}
//---------------------------- Admin Access-------------------
void BackControls::Admin_access()
{
    int choice;
    BackControls B1;
    cout << "Hello Admin" << endl;

    cout << "1.Customers\n";
    cout << "2.View Policies\n";
    cout << "3.TotalView Policy Holders\n";
    cout << "4.Logout\n";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        Customers();
        break;
    case 2:
        View_Policies();
        break;
    // case 3:
    //     View_Policy_Holders();
    //     break;
    case 4:
        B1.login();
    }

    // }
}
//----------------------------------Admin Login ----------------
void BackControls::Admin_Login()
{
    int count = 0;
    BackControls B1;
    string user, pass, u, p;
    system("cls");
    if (inncorrectAdminPassword)
    {
        cout << "Please check your username and password and login again\n"
             << endl;
    }
    else
    {
        cout << "please enter the following details" << endl;
    }

    cout << "USERNAME :";
    cin >> user;
    cout << "PASSWORD :";
    cin >> pass;
    ifstream input("Admin.txt");
    while (input >> u >> p)
    {
        if (u == user && p == pass)

        {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if (count == 1)
    {
        cout << "\nHello" << user << "\nLOGIN SUCCESS\nWe're glad that you're here.\nThanks for logging in\n";

        Admin_access();
    }
    else
    {
        cout << "\nLOGIN ERROR\n";

        inncorrectAdminPassword = 1;
        cout << inncorrectAdminPassword << endl;
        Admin_Login();
    }
}

void User_Login()
{
    BackControls B1;
    int count = 0;

    string user, pass, u, p;
    system("cls");
    cout << "please enter the following details" << endl;
    cout << "USERNAME :";
    cin >> user;
    cout << "PASSWORD :";
    cin >> pass;
    User user1;
    user1.username = user;
    user1.password = pass;
    ifstream input;
    string filename = user + "Credentials";
    filename.append(".txt");
    input.open(filename, ios::in);
    while (input >> u >> p)
    {
        if (u == user && p == pass)

        {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if (count == 1)
    {
        cout << "\nHello" << user << "\nLOGIN SUCCESS\n";

        B1.UserLogin(user1.username);
    }
    else
    {
        cout << "\nLOGIN ERROR\nPlease check your username and password\n";

        sleep_for(50ns);
        sleep_until(system_clock::now() + 1s);
        User_Login();
    }
}
void BackControls::login()
{

    int choice;

    cout << "1.Admin Login\n";
    cout << "2.User Login\n";
    cout << "\nEnter your choice : ";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        Admin_Login();
        break;
    case 2:
        User_Login();
        break;
    }
}

//------------------------login   completed ------------------------------

void BackControls::Welcome()
{
    int choice;
    BackControls B1;
    cout << "***********************************************************************\n\n";

    cout << "1.LOGIN\n";
    cout << "2.REGISTER\n";
    cout << "3.Exit\n";
    cout << "\nEnter your choice : ";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        B1.login();
        break;
    case 2:
        registr();
        break;
    case 3:
        cout << "Thanks for using this program\n";
        break;
    default:
        cout << "Wrong Choice Entered\n"
             << endl;
    }
}
//-------------- welocme done --------------
// file system (crud )
//
int main()
{
    int choice;
    BackControls B1;
    cout << "                      Welcome to Mphasis Policy services                               \n\n";
    cout << "*******************        MENU        ********************************\n\n";
    B1.Welcome();
}
