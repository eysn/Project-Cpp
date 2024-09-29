#include <iostream>
#include <ctime>
#include<vector>
#include <string>
#include<fstream>
using namespace std;

//Global Variable Declaration
int choice,accountCounter=0,voucherCount=0,accNumber,index1=-1,index2=-1,Amount=0;
const int hillIndex=0,numberOfRooms=10;
string givenVoucherCode;

// Structure For A Bank Account
struct bankAccount{
    int accountNumber=0,roomNum=0;
    string firstName,lastName, phoneNumber;
    double amount;
    string email;
    void createAccount(),displayAccountInformation(),createAccountHot(string fname, string lname, string mail, string phoneno,int room);
};

// Structure For Room Information
struct roomInformation{
    string voucherCode;
    float totalPrice;
    bool isPaid=false;
    int roomNumber;
};


// Vector For Storing Room Informations
vector<roomInformation> roomInfo(numberOfRooms);
// Vector to store bank accounts
vector<bankAccount> acc(1000);

// Write data from roomInfo vector to room information.csv
void exportTo_roomInfo_File(){
    ofstream roomInfoFile;
    roomInfoFile.open("room information.csv", ios::out);
    roomInfoFile<< "Voucher code,Total price,Is paid,Room number";
    for (int i = 0; i < voucherCount; i++){
        roomInfoFile<<'\n'<<roomInfo[i].voucherCode<<','<<roomInfo[i].totalPrice<< ','<<roomInfo[i].isPaid<<','<<roomInfo[i].roomNumber;        
    }
    roomInfoFile.close();
}
// Write data from acc vector to acount information.csv
void exportTo_acc_File(){
    ofstream accFile;
    accFile.open("account information.csv", ios::out);
    accFile<<"First name,Last name,Email,Phone number,Account number,Deposit amount,Room number";
    for (int i = 0; i < accountCounter; i++){
        accFile<<'\n'<<acc[i].firstName<<','<<acc[i].lastName<<','<<acc[i].email<<','<<acc[i].phoneNumber<<','<<acc[i].accountNumber<<','<<acc[i].amount<<','<<acc[i].roomNum;
    }
    accFile.close();

}
//Read from room information.csv to roomInfo vector
void update_roomInfo_Vector(){
    string temp="";
    ifstream roomInfoFile;
    roomInfoFile.open("room information.csv", ios::in);
    getline(roomInfoFile,temp,'\n');
    while(!roomInfoFile.eof()){
        bool invalidVoucher=false;
        temp="";
        getline(roomInfoFile, roomInfo[voucherCount].voucherCode,',');
        getline(roomInfoFile, temp,',');
        roomInfo[voucherCount].totalPrice = stoi(temp);
        temp="";
        getline(roomInfoFile, temp,',');
        roomInfo[voucherCount].isPaid = stoi(temp);
        getline(roomInfoFile, temp,'\n');
        roomInfo[voucherCount].roomNumber = stoi(temp);
        for (int i = 0; i < voucherCount; i++)
        {
            if(roomInfo[i].voucherCode==roomInfo[voucherCount].voucherCode ){
                roomInfo.erase(roomInfo.begin()+voucherCount);
                roomInfo.resize(numberOfRooms);
                invalidVoucher=true;
                break;
            }
        }
        if(invalidVoucher)
            continue;
        voucherCount++;
        if(voucherCount==numberOfRooms){
            cout<< "Room database is full"<< endl;
            break;
        }
    }
    roomInfoFile.close();
}
//Read from account information.csv to acc vector
void update_acc_Vector(){
    ifstream accFile;
    string temp="";
    accFile.open("account information.csv",ios::in);
    getline(accFile,temp,'\n');
    while(!accFile.eof()){
        temp="";
        bool invalidAccount=0;
        getline(accFile,acc[accountCounter].firstName,',');
        getline(accFile,acc[accountCounter].lastName,',');
        getline(accFile,acc[accountCounter].email,',');
        getline(accFile,acc[accountCounter].phoneNumber,',');
        getline(accFile,temp,',');
        acc[accountCounter].accountNumber=stoi(temp);
        temp="";
        getline(accFile,temp,',');
        acc[accountCounter].amount=stoi(temp);
        temp="";
        getline(accFile,temp,'\n');
        acc[accountCounter].roomNum=stoi(temp);
        for(int i=0;i<accountCounter;i++){
            if(acc[accountCounter].accountNumber==acc[i].accountNumber || acc[accountCounter].accountNumber<30000000 ){
                acc.erase(acc.begin()+accountCounter);
                acc.resize(acc.capacity()+1);
                invalidAccount=true;
                break;
            }
        }
        if(invalidAccount)
            continue;
        accountCounter++;
        if(accountCounter==acc.capacity())
            acc.resize(acc.capacity()*2);
    }
    accFile.close();
}
// Function For Displaying Options
void displayOptions(){
    cout<< "    Enter 1 to create an account "<<endl;
    cout<< "    Enter 2 to deposit money"<<endl;
    cout<< "    Enter 3 to transfer money"<<endl;
    cout<< "    Enter 4 to withdraw money"<<endl;
    cout<< "    Enter 5 to view account information"<<endl;
    cout<< "    Enter 6 to pay for Hill Hotel using Voucher code"<<endl;
    cout<< "    Enter 7 to go back to Hill Hotel page"<<endl;

}
// Function For Account Creation
void bankAccount::createAccount(){
    cout<< "Enter your name"<<endl;
    cin>> firstName;
    cout<< "Enter your Fathers name"<<endl;
    cin>> lastName;
    cout<< "Enter your phone number"<<endl;
    cin>> phoneNumber;
    cout << "Enter your email address"<< endl;
    cin>> email;
    while (email.find("@gmail.com") == string::npos) {
        cout << "Invalid email address. Please make sure to include '@gmail.com'." << endl;
        cin>>email;
    }
    cout<< "Enter deposite amount(Min amount is 25 ETB)"<< endl;
    cin>> amount;
    while(amount<25){
        system("cls");
        cout<< "Sorry! Min amount is 25 ETB"<< endl;
        cin>> amount;
    }
    srand(time(0));
    accountNumber = 30000000+rand();
    bool exist;
    do
    {
    exist =false;
    for(int i=0;i<accountCounter;i++){
        if(accountNumber==acc[i].accountNumber){
            accountNumber = 30000000+rand();
            exist=true;
            break;
        }
    }
    }while (exist);
    system("cls");
    cout<< "Account created successfully, your account number is = "<< accountNumber<<endl;
}
// Function that returns the index of the matching account number that the user provided
int indexOfAccount(int accNumber){
    int index=-1;
    for(int i=0;i<accountCounter;i++){
        if(acc[i].accountNumber==accNumber){
            index=i;
            break;
        }
        else
            continue;
    }
    return index;
}
// Function For Depositing Money
void deposit(){
    cout<<"Enter account number"<<endl;
    cin>> accNumber;
    index1= indexOfAccount(accNumber);
    if(index1==-1){
        system("cls");
        cout<< "Invalid bank account"<<endl;
        return;
    }
    cout<<"Enter the amount you want to deposit"<<endl;
    cin>> Amount;
    while(Amount<=0){
        system("cls");
        cout<< "Invalid deposit amount, please enter a deposit amount greater that 0 ETB"<<endl;
        cin>>Amount;
    }
    acc[index1].amount+=Amount;
    system("cls");
    cout<<"Successfully deposited, your new balance = "<< acc[index1].amount<< " ETB"<<endl;
    index1=-1;
}
// Function For Transfering Money
void transfer(){
    cout<<"Enter account number "<<endl;
    cin>> accNumber;
    index1=indexOfAccount(accNumber);
    if(index1==-1){
        system("cls");
        cout<< "Invalid bank account"<<endl;
        return;
    }
    if(acc[index1].amount==0){
        system("cls");
        cout<< "Insufficient balance for transaction"<<endl;
        return;
    }
    cout<<"Enter account number"<<endl;
    cin>> accNumber;
    index2 = indexOfAccount(accNumber);
        if(index2==-1){
            system("cls");
            cout<< "Invalid bank account"<<endl;
            return;
        }
    if(acc[index1].accountNumber==acc[index2].accountNumber){
        cout<< "Sorry, you can't transfer between the same account, Thank you!"<<endl;
        return;
    }
    cout<<"Enter the amount you want to transfer"<<endl;
    cin>> Amount;
        if(Amount<=0 || Amount>acc[index1].amount){
            system("cls");
            cout<< "Invalid withdraw amount, transaction could not be made"<<endl;
        }
    acc[index1].amount-=Amount;
    acc[index2].amount+=Amount;
    system("cls");
    cout<< "Succesfully transfered "<< Amount<< " ETB to "<< acc[index2].firstName<<endl;
    index1=-1;
    index2=-1;
}
// Function For Withdrwal Of Money
void withdraw(){
    cout<<"Enter account number"<<endl;
    cin>> accNumber;
    index1=indexOfAccount(accNumber);
    if(index1==-1){
            system("cls");
            cout<< "Invalid bank account"<<endl;
            return;
    }
    if(acc[index1].amount==0){
        system("cls");
        cout<< "Insufficient balance for withdrawal"<<endl;
        return;
    }
    cout<<"Enter the amount you want to withdraw"<<endl;
    cin>> Amount;
    if(Amount<=0 || Amount>acc[index1].amount){
        system("cls");
        cout<< "Invalid withdraw amount, transaction could not be made"<<endl;
    }
    acc[index1].amount-=Amount;
    system("cls");
    cout<<"Successfully withdrawn, your new balance = "<< acc[index1].amount<< " ETB"<<endl;
    index1=-1;
}
// Function For Displaying Informations
void bankAccount::displayAccountInformation(){
    system("cls");
    cout<< "Account number = "<< accountNumber<<endl;
    cout<< "Account Holders Name = "<< firstName<< " "<< lastName <<endl;
    cout<< "Phone number = "<< phoneNumber<<endl;
    cout<< "Email = "<< email<<endl;
    cout<< "Amount = "<< amount<< " ETB"<<endl;

}
// Function to pay for the hotel using voucher code
void  payForHotel(){
    update_roomInfo_Vector();
    cout<<"Enter account number"<<endl;
    cin>> accNumber;
    index1=indexOfAccount(accNumber);
    cout<< "Enter your voucher code"<< endl;
    cin>> givenVoucherCode;
    // Search for a matching voucher code the user provided
    for(int i=0;i<roomInfo.size();i++){
        roomInfo[i].voucherCode;
        if(givenVoucherCode==roomInfo[i].voucherCode){
            index2=i;
            break;
    }
        else
            continue;
    }
    // If the voucher code couldn't match with any existing voucher codes
    if (index2==-1 || index1==-1){
        system("cls");
        cout<< "Invalid voucher code or Invalid bank account!"<< endl;
        return;
    }
    if (!roomInfo[index2].isPaid){
    // Check if the amount in the users account is less than the total price , if so the balance is insufficent
    if(acc[index1].amount<roomInfo[index2].totalPrice){
        system("cls");
        cout<< "Insufficent balance, please try again when you have a sufficent balance Thank you!"<< endl;
        return;
    }
    // Transfer to Hill hotel acc
    acc[index1].amount-= roomInfo[index2].totalPrice ;
    acc[hillIndex].amount+=roomInfo[index2].totalPrice;
    // Make the bool 'is paid' true and return the value true so that "Succesfully booked " can be displayed
    roomInfo[index2].isPaid=true;
    index1=-1;
    exportTo_roomInfo_File();
    system("cls");
    cout<< "Payment made successfully, Your room is booked Thank you!";
    return;
    }
    else{
        system("cls");
        cout<< "Already paid with this voucher code, Thank u"<< endl;
        return;
    }

}
// If The User Cancel Their Reservation, A Function To Refund Their Money
bool refund(){
    cout<<"Enter account number"<<endl;
    cin>> accNumber;
    index1=indexOfAccount(accNumber);
    cout<< "Enter your voucher code"<< endl;
    cin>> givenVoucherCode;
    // Search for a matching voucher code the user provided
    for(int i=0;i<roomInfo.size();i++){
        if(givenVoucherCode==roomInfo[i].voucherCode){
            index2=i;
            break;
    }
        else
            continue;
    }
    // If the voucher code couldn't match with any existing voucher codes
    if (index2==-1 || index1==-1){
        system("cls");
        cout<< "Invalid voucher code or Invalid bank account!"<< endl;
        return 0;
    }
    if(roomInfo[index2].isPaid){
        // Trnsfer From Hill hotel acc to the user account
        acc[index1].amount+= roomInfo[index2].totalPrice ;
        acc[hillIndex].amount-=roomInfo[index2].totalPrice;
        // Make the bool 'is paid' false and return the value false so that "Succesfully cancelled " can be displayed
        index1=-1;
        roomInfo[index2].isPaid=false;
        exportTo_roomInfo_File();
        exportTo_acc_File();
        return 1;
    }
    else{
        system("cls");
        cout<< "Sorry no payment has been made before so refund can't be made, Thanks you !"<< endl;
        return 1;
    }

}
//Pay for hotel straight after booking
bool payForHotelin(int index){
    update_roomInfo_Vector();
    cout<< "Enter your voucher code"<< endl;
    cin>> givenVoucherCode;
    // Search for a matching voucher code the user provided
    for(int i=0;i<roomInfo.size();i++){
        roomInfo[i].voucherCode;
        if(givenVoucherCode==roomInfo[i].voucherCode){
            index2=i;
            break;
        }
        else
            continue;
    }
    // If the voucher code couldn't match with any existing voucher codes
    if (index2==-1){
        system("cls");
        cout<< "Invalid voucher code "<< endl;
        return 0;
    }
    if (!roomInfo[index2].isPaid){
        // Check if the amount in the users account is less than the total price , if so the balance is insufficent
        if(acc[index].amount<roomInfo[index2].totalPrice){
            system("cls");
            cout<< "Insufficent balance, please try again when you have a sufficent balance Thank you!"<< endl;
            return roomInfo[index2].isPaid;
        }
        // Transfer to Hill hotel acc
        acc[index].amount-= roomInfo[index2].totalPrice ;
        acc[hillIndex].amount+=roomInfo[index2].totalPrice;
        roomInfo[index2].isPaid=true;
        exportTo_roomInfo_File();
        return 1;

    }
    else
        cout<< "Already paid with this voucher code, Thank u"<< endl;
    index2=-1;
    return roomInfo[index2].isPaid;
}
//Create account for a user from the info they provided
void bankAccount::createAccountHot(string fname, string lname, string mail, string phoneno,int room){
    firstName=fname;
    lastName=lname;
    email=mail;
    phoneNumber=phoneno;
    roomNum=room;
    cout<< "Enter deposite amount(Min amount is 25 ETB)"<< endl;
    cin>> amount;
    while(amount<25){
        system("cls");
        cout<< "Sorry! Min amount is 25 ETB"<< endl;
        cin>> amount;
    }
    srand(time(0));
    accountNumber = 30000000+rand();
    bool exist;
    do
    {
    exist =false;
    for(int i=0;i<accountCounter;i++){
        if(accountNumber==acc[i].accountNumber){
            cout<< accountCounter<< endl;
            srand(time(0));
            accountNumber = 30000000+rand();
            exist=true;
            break;
        }
        else  
            continue;
    }
    }while (exist);
    system("cls");
    cout<< "Account created successfully, your account number is = "<< accountNumber<<endl;
}

int bank (){
    system("cls");
    update_roomInfo_Vector();
    update_acc_Vector();
    cout<< " Welcome to Hill microfinance : "<< endl;
    do{
    displayOptions();
    cin>>choice;
    switch (choice)
    {
    case 1:
        if(accountCounter==acc.size())
            acc.resize(acc.size()*2);
        acc[accountCounter].createAccount();
        accountCounter++;
        break;
    case 2:
        // Deposit Money
        deposit();
        break;
    case 3:
        // Transfer money
        transfer();
        break;
    case 4:
        //Withdrawal
        withdraw();
        break;
    case 5:
        //Display Account Information
        cout<<"Enter account number"<<endl;
        cin>> accNumber;
        index1= indexOfAccount(accNumber);
        if(index1==-1){
            system("cls");
            cout<< "Invalid bank account"<<endl;
            break;
        }
        acc[index1].displayAccountInformation();
        index1=-1;
        break;
    case 6:
        payForHotel();
        break;
    case 7:
        break;
    default:
        cout<< "Wrong entry, Please insert again"<<endl;
    }

    }while(choice!=7);
}