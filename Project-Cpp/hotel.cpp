#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include "bank.cpp"
#include<fstream>
#include<string>
using namespace std;

struct Room {
int roomNumber;
bool isBooked;
double pricePerNight;
};

struct Guest {
string firsname;
string lasName;
string email;
string phonumber;
int roomNumber;
bool hasAcc;
bool paidByMicrofinance;
};


string voucherCode;
double totalPrice=0;
vector<Room> rooms;
vector<Guest> guests;
map<int, string> voucherCodes;

void readAccountInformation(){
    //Local variable declaration
    string temp="";
    ifstream aInfo;
    Guest g;
    bool invalidEmail=false;
    //Opening and reading files
    aInfo.open("account information.csv", ios::in);
    getline(aInfo,temp,'\n');
    while(!aInfo.eof()){
        getline(aInfo,g.firsname,',');
        getline(aInfo,g.lasName,',');
        getline(aInfo,g.email,',');
        //Checks if the email has been used before to book a room
        for(auto guest:guests)
            if(guest.email==g.email){
                invalidEmail=true;
                break;
            }
        getline(aInfo,g.phonumber,',');
        getline(aInfo,temp,',');
        //If account number is '0' in account information.csv makes the bool hasAcc false
        if(temp== "0")
            g.hasAcc=false;
        else 
            g.hasAcc=true;
        //Read room number 
        getline(aInfo,temp,',');
        getline(aInfo,temp,'\n');
        g.roomNumber=stoi(temp);
        //If room number in account information.csv is '0' it skips it 
        if(g.roomNumber==0)
            continue;
        if(!g.hasAcc && voucherCodes[g.roomNumber]!="")
            g.paidByMicrofinance=true;
        //If email has been used before it skips it
        if(invalidEmail){
            invalidEmail=false;
            continue;
        }
        for (int i = 0; i < numberOfRooms; i++)
        {
            if(g.roomNumber==rooms[i].roomNumber){
                rooms[i].isBooked=true;
                break;
            }
        }
        guests.push_back(g);
    }
    aInfo.close();
}

void writeAccountInformation(){
    fstream aInfo;
    Guest g;
    aInfo.open("account information.csv", ios::app);
    //Write users who only booked a room to account information.csv
    for(auto g:guests){
        if(!g.hasAcc){
            aInfo<<'\n'<<g.firsname<<',';
            aInfo<<g.lasName<<',';
            aInfo<<g.email<<',';
            aInfo<<g.phonumber<<',';
            aInfo<< "0,0,";
            aInfo<<g.roomNumber;
        }
        else
            continue;

    }
    aInfo.close();

}

void writeRoomInformation(string vCode, double Tprice,int roomNum){
    //Write voucher code and total price in room information.csv
    ofstream rInfo;
    rInfo.open("room information.csv",ios::app);
    rInfo<<'\n'<< vCode<<',';
    rInfo<< Tprice<<',';
    rInfo<< "0,";
    rInfo<< roomNum;
    rInfo.close();
}

void readRoomInformation(){
    string temp="",vCode="";
    int roomNum;
    ifstream rInfo;
    rInfo.open("room information.csv", ios::in);
    getline(rInfo,temp,'\n');
    while(!rInfo.eof()){
        getline(rInfo,vCode,',');
        getline(rInfo,temp,',');
        getline(rInfo,temp,',');
        getline(rInfo,temp,'\n');
        roomNum=stoi(temp);
        voucherCodes[roomNum]=vCode;
    }
    rInfo.close();
}

void initializeRooms() {
rooms = {
{101, false, 1000.0},
{102, false, 1200.0},
{103, false, 1500.0},
{104, false, 1800.0},
{105, false, 2000.0}
};
}

void displayAvailableRooms() {
    int availableRooms = 0;
    int bookedRooms = 0;

    for (const auto& room : rooms) {
        if (!room.isBooked) 
            availableRooms++;
        else 
            bookedRooms++;
        
    }
    system("cls");
    cout << "Available Rooms: " << availableRooms << endl;
    cout << "Booked Rooms: " << bookedRooms << endl;
}

void displayRooms() {
    cout << "Available Rooms:" << endl;
    for (const auto& room : rooms) {
        if (!room.isBooked) {
            cout << "Room Number: " << room.roomNumber << endl;
            cout << "Price per night: ETB" << room.pricePerNight << endl << endl;
        }
    }
}

void bookRoom() {
    bool allRoomsBooked = true;
    int roomNumber;
    for (const auto& room : rooms) {
        if (!room.isBooked) {
            allRoomsBooked = false;
            break;
        }
    }
    if (allRoomsBooked) {
        system("cls");
        cout << "Sorry, no rooms are available at the moment." << endl;
        return;
    }
    system("cls");
    displayRooms();
    cout << "Enter the room number you want to book: ";
    cin >> roomNumber;
    bool roomFound = false;
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && !room.isBooked) {
            roomFound = true;
            cout<< "Do you have a microfinance account already?\n1.Yes\n2.No\n";
            cin>>choice;
            switch (choice)
            {
            case 1:
                cout<< "Enter account number"<<endl;
                cin>>accNumber;
                index1=indexOfAccount(accNumber);
                if(index1==-1 || acc[index1].roomNum!=0){
                    system("cls");
                    cout<< "Invalid bank account for room reservation"<<endl;
                    return;
                }
                for (const auto& bookedGuest : guests) {
                    if (bookedGuest.email == acc[index1].email) {
                        system("cls");
                        cout << "A room has already been booked with this email address. Please book your room with a differnt email" << endl;
                        return;
                    }
                }
                srand(time(0)); // for seeding the random number used
                voucherCode = "Hill" + to_string(rand() % 10000); // get random number up to 4 digits with 'Hill' sign in front
                voucherCodes[roomNumber] = voucherCode; // Save the voucher code tied to the room number
                acc[index1].roomNum=roomNumber;
                exportTo_acc_File();
                readAccountInformation();
                cout << "Enter the number of nights you want to spend: ";
                int numNights;
                cin >> numNights;
                while(numNights<=0){
                    cout<< "You should atleast spend one night, Please enter again"<<endl;
                    cin>>numNights;
                }
                totalPrice = room.pricePerNight * numNights;
                system("cls");
                cout<< "Your voucher code is = "<< voucherCode <<"\nSave it for payment and refunds"<< endl;
                cout << "Total Price: ETB" << totalPrice << endl;
                writeRoomInformation(voucherCode,totalPrice,room.roomNumber);
                if(payForHotelin(index1)){
                    system("cls");
                    cout << "Room booked successfully!" << endl;
                }
                else 
                    cout<< "Unable to pay, please pay with your voucher code to book your room"<<endl;
                goto write;
            default:
                break;
            }
            Guest guest;
            guest.roomNumber = roomNumber;
            cin.ignore();
            system("cls");
            cout << "Enter your first name: ";
            getline(cin, guest.firsname);
            cout << "Enter your last name: ";
            getline(cin, guest.lasName);
            cout << "Enter your email address: ";
            getline(cin, guest.email);

            // Check if email address has '@gmail.com'
            while(guest.email.find("@gmail.com") == string::npos){
                cout << "Invalid email address. Please make sure to include '@gmail.com'." << endl;
                cout << "Enter your email address: ";
                getline(cin, guest.email);
            }

            cout << "Enter your phonenumber: ";
            getline(cin, guest.phonumber);

            // Check if the same email address is already used for booking a room
            for (const auto& bookedGuest : guests) {
                if (bookedGuest.email == guest.email) {
                    system("cls");
                    cout << "A room has already been booked with this email address. Please use another email address." << endl;
                    return;
                }
            }
            cout << "Enter the number of nights you want to spend: ";
            int numNights;
            cin >> numNights;
            // Number of nights should atleast be 1
            while(numNights<=0){
                cout<< "You should atleast spend one night, Please enter again"<<endl;
                cin>>numNights;
            }
            totalPrice = room.pricePerNight * numNights;
            system("cls");
            cout << "Total Price: "<< totalPrice << " ETB" << endl;
            cout<< "Choose payment method :"<< endl<< "1. Transfer using bank"<< endl<< "2. Use our microfinance "<< endl;
            cin>>choice;
                switch (choice)
                {
                case 1:
                    system("cls");
                    cout<< "Please send us your payment recipt with our email address 'hillhotel@gmail.com' and we will comfirm your bookng. Thank you for choosing Hill Hotel!"<<endl;
                    cout << "Room reserved successfully!" << endl;
                    room.isBooked = true;
                    guest.hasAcc=false;
                    guest.paidByMicrofinance=false;
                    break;
                case 2:
                    srand(time(0)); // for seeding the random number used
                    voucherCode = "Hill" + to_string(rand() % 10000); // get random number up to 4 digits with 'Hill' sign in front
                    voucherCodes[roomNumber] = voucherCode; // Save the voucher code tied to the room number
                    system("cls");
                    cout<< "Your voucher code is = "<< voucherCode <<"\nSave it for payment and refunds"<< endl;
                    guest.hasAcc=false;
                    guest.paidByMicrofinance=true;
                    writeRoomInformation(voucherCode,totalPrice,room.roomNumber);
                    update_roomInfo_Vector();
                    cout<<"Do you want to use info from your hotel?\n1.Yes\n2.No"<<endl;
                    cin>>choice;
                    switch (choice)
                        {
                        case 1:
                            guest.hasAcc=true;
                            if(accountCounter>=acc.size())
                                acc.resize(acc.size()*2);
                            acc[accountCounter].createAccountHot(guest.firsname,guest.lasName,guest.email,guest.phonumber,guest.roomNumber);
                            if(payForHotelin(accountCounter)){
                                system("cls");
                                cout << "Room booked successfully!" << endl;
                            }
                            else{
                                system("cls");
                                cout<< "Unable to pay, Your room is reserved, Please go to bank page and pay using your voucher code to book your room Thank you!"<<endl;
                            }
                            accountCounter++;
                            break;
                        case 2:
                            acc[accountCounter].createAccount();
                            if(payForHotelin(accountCounter)){
                                system("cls");
                                cout << "Room booked successfully!" << endl;
                            }
                            else{
                                system("cls");
                                cout<< "Unable to pay, Your room is reserved, Please go to bank page and pay using your voucher code to book your room Thnak you!"<<endl;
                            }
                            accountCounter++;
                            break;
                        
                        default:
                            system("cls");
                            cout<< "Wrong entry, Room reserved successfully Please go to bank page and pay using your voucher code to book your room Thnak you!"<<endl;
                            break;
                        }
                    break;
                default:
                    system("cls");
                    cout<< "Wrong entry, unable to book your room, please try again later Thank you!"<<endl;
                    return;
                }
                room.isBooked = true;
                guests.push_back(guest);
                break;
        }
    }
    if (!roomFound) {
        system("cls");
        cout << "Incorrect room number or the room is already booked." << endl;
        return;
    }
    write:
        exportTo_acc_File();
        writeAccountInformation();
        exportTo_roomInfo_File();
        
}

void cancelReservation() {
    bool noBookedRoom=true;
    for (auto room: rooms){
        if(room.isBooked==true){
            noBookedRoom=false;
            break;
        }
    }
    if(noBookedRoom){
        system("cls");
        cout<< "No rooms have been booked yet"<<endl;
        return;
    }

    int roomNumber=0;
    bool reservationFound = false;
    string email;
    Guest it;
    cout << "Enter the room number of the reservation you want to cancel: "<<endl;
    cin >> roomNumber;
    cout<< "Enter the email that you reserved the room"<<endl;
    cin>>email;
    for(auto it:guests){
        if(email==it.email && it.roomNumber==roomNumber){
            reservationFound = true;
            if(it.hasAcc){
                if(refund()){  
                    for (int i = 1; i < accountCounter; i++){
                        if(acc[i].roomNum==roomNumber){
                            acc[i].roomNum=0;
                            break;
                        }
                    }            
                    break;
                }
                else{
                    system("cls");
                    cout<< "Unable to cancel Please try again later Thank you!"<<endl;
                    return;
                }
            }
            else if (it.paidByMicrofinance){
                if(refund())
                    break;
                else{
                    system("cls");
                    cout<< "Unable to cancel Please try again later Thank you!"<<endl;
                    return;
                }
            }
            else
                break;
        }
        else
            continue;
    }        
    if (!reservationFound) {
        system("cls");
        cout << "Unable to find your reservation wiht provided information please try again later" << endl;
        return;
    }
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && room.isBooked) {
            room.isBooked = false;
            //Removes user information from guests vector
            for (auto i = guests.begin(); i != guests.end(); i++) {
                if (i->roomNumber == roomNumber) {
                    guests.erase(i);
                    break;
                }
            }
        }
    }
    
    //Removes voucher code from roomInfo vector of bank
    for (auto i = roomInfo.begin(); i != roomInfo.end(); i++) {
        if (i->voucherCode == givenVoucherCode) {
            roomInfo.erase(i);
            voucherCount--;
            roomInfo.resize(numberOfRooms);
            break;
        }
    }
    voucherCodes.erase(roomNumber); // Remove the voucher code tied to the room number
    system("cls");
    cout << "Reservation for room number " << roomNumber << " has been canceled." << endl;
    exportTo_acc_File();
    writeAccountInformation();
    exportTo_roomInfo_File();
}

void displayBookedRooms() {
    system("cls");
    if (guests.empty()) {
        cout << "Sorry, You have not booked any room yet." << endl;
    } 
    else {
        cout << "Booked Rooms:" << endl;
        for (const auto& guest : guests) {
            cout << guest.firsname<<" "<<guest.lasName << " has booked room : " << guest.roomNumber <<endl;
        }
    }
}

int main() {
    initializeRooms();
    update_acc_Vector();
    update_roomInfo_Vector();
    readRoomInformation();
    readAccountInformation();
    system("cls");
    cout << "Welcome to Hill Hotel!" <<endl;
    int choice;
    do{
        cout << "   1. Book a room" << endl;
        cout << "   2. Display available rooms" << endl;
        cout << "   3. Display booked rooms" << endl;
        cout << "   4. Cancel reservation" << endl;
        cout << "   5. HillMicrofinance"<<endl;
        cout << "   6. Exit" << endl;
        cin >> choice;
        switch (choice){
            case 1:
                bookRoom();
                break;
            case 2:
                displayAvailableRooms();
                break;
            case 3:
                displayBookedRooms();
                break;
            case 4:
                cancelReservation();
                break;
            case 5:
                bank();
                system("cls");
                exportTo_acc_File();
                writeAccountInformation();
                exportTo_roomInfo_File();
                break;
            case 6:
                exportTo_acc_File();
                writeAccountInformation();
                exportTo_roomInfo_File();
                cout << "Thank you for using Hill Hotel. Goodbye!" << endl;
                break;
            default: 
                system("cls");
                cout << "Incorrect choice. Please try again." << endl;
                break;
            }
    }while (choice!=6);

}