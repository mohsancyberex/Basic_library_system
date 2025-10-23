#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void Borrow_books(){
    int book_id;
    int check_id;
    string book_name;
    bool found = false;
    cout<<"|====================|\n";
    cout << " Available Books \n";
	cout<<"|====================|\n";
    ifstream infile("books.txt");//if=read.of=write
    if(!infile){
        cout << " No Books found\n";
        return;
    }
    string line;
    while(getline(infile, line)){
        cout << line << endl;    
    }
    infile.close(); 

    cout << "\nEnter book Id To Borrow Book: ";
    cin >> check_id;

    ifstream books("books.txt");
    ofstream temp("temp.txt");
    ofstream borrowed("borrowed_books.txt", ios::app);

    if(!books){
        cout << " No Books found\n";
        return;
    }

    while (books >> book_id) {
        books.ignore(); 
        getline(books, book_name);
        if (book_name.empty()) continue; 

        if (check_id == book_id) {
            cout << " You Borrowed Book with Below Details:\n";
            cout << " Book Id: " << book_id << endl;
            cout << " Book Name: " << book_name << endl;
            borrowed <<book_id << " " << book_name << endl;
            found = true;
        } else {
            temp << book_id << " " << book_name << endl;
        }
    }

    books.close();
    temp.close();
    borrowed.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found) {
        cout << " Book Not Found.\n";
        cin.ignore();
        cin.get();
    } else {
        cout << "Press enter to continue...\n";
        cin.ignore();
        cin.get();
    }
}

void return_books() {
    bool found = false;
    int r_book_id, b_book_id;
    string book_name;

    cout << "|====================|\n";
    cout << "  Borrowed Books \n";
    cout << "|====================|\n";

    ifstream borrowed("borrowed_books.txt");
    if (!borrowed) {
        cout << " No borrowed books found.\n";
        return;
    }

    string line;
    while (getline(borrowed, line)) {
        cout << line << endl;
    }
    borrowed.close();

    cout << "\nEnter Book ID To Return: ";
    cin >> r_book_id;

    ifstream in_borrowed("borrowed_books.txt");
    ofstream temp("temp.txt");
    ofstream books("books.txt", ios::app);

    if (!in_borrowed) {
        cout << " No borrowed books found.\n";
        return;
    }

    while (in_borrowed >> b_book_id) {
        in_borrowed.ignore();
        getline(in_borrowed, book_name);
        if (book_name.empty()) continue;

        if (r_book_id == b_book_id) {
            cout << " You Returned Book:\n";
            cout << " Book Id: " << b_book_id << endl;
            cout << " Book Name: " << book_name << endl;
            books << b_book_id << " " << book_name << endl;
            found = true;
        } else {
            temp << b_book_id << " " << book_name << endl;
        }
    }

    in_borrowed.close();
    temp.close();
    books.close();

    remove("borrowed_books.txt");
    rename("temp.txt", "borrowed_books.txt");

    if (!found) {
        cout << " Book Not Found in Borrowed List.\n";
    } else {
        cout << " Book Returned Successfully.\n";
    }

    cout << "Press enter to continue...\n";
    cin.ignore();
    cin.get();
}


void Add_books()
{
    int how;
    cout << " Add Books \n";
    cout << " Enter how many Book you want to add:  \n\n";
    cin >> how;
    cin.ignore(); // clear newline

    string add_book[100];
    int book_id[100];

    for(int i=0;i<how;i++){
        cout<<"Enter Name of book "<<i+1<<": ";
        getline(cin,add_book[i]);
        cout<<"Enter Id of "<<add_book[i]<<": ";
        cin>>book_id[i];
        cin.ignore();
        cout<<endl;
    }

    ofstream outfile("books.txt", ios::app);
    for(int i=0;i<how;i++){
        outfile << book_id[i] << " " << add_book[i] << endl;
    }
    outfile.close();

    cout <<how<< " Books Added Successfully \n";
    cout << "Press enter to continue...\n";
    cin.get();
}

int main()
{   
    int choice;

    cout << "Welcome To CyberEX Library\n";
    cout << "================================\n";
    do {
        system("cls");
        cout << "1: Borrow Book\n2: Return Book\n3: Add Book\n4: Quit\n";
        cout << " Select Your Option: ";
        cin >> choice;
    
        switch(choice){
            case 1:
                Borrow_books();
                break;
            case 2:
                return_books();
                break;
            case 3:
                Add_books();
                break;
            case 4:
                cout << " Thank you for visiting..\n";
                break;
            default: 
                cout << "Invalid choice! Please select 1-4.\n";
                break;
        }
    } while(choice != 4);
}
