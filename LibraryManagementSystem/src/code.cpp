#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
using namespace std;
class Library;
class Book{   
    private:
        string isbn;
        int copiesAvailable;
        int totalCopies;
    public:
        string title;
        string author;
        Book(){
            this->isbn="ISBN";
            this->title="UnknownTitle";
            this->author="UnknownAuthor";
            this->copiesAvailable=0;
            this->totalCopies=5;
        }
        Book(string title,string author,string isbn,int copies,int total){
            this->title=title;
            this->author=author;
            this->isbn=isbn;
            this->copiesAvailable=copies;
            this->totalCopies=total;
        }
        Book(Book book,string newisbn){
            this->title=book.title;
            this->author=book.author;
            this->isbn=newisbn;
            this->copiesAvailable=book.copiesAvailable;
            this->totalCopies=book.totalCopies;
        }
        string get_isbn(){
            return isbn;
        }
        int get_available_copies(){
            return copiesAvailable;
        }
        int get_total_copies(){
            return totalCopies;
        }
        bool updateCopies(int count){             
            if (copiesAvailable+count >=0){
                copiesAvailable+=count;
                totalCopies+=count;
                return true;
            }
            else{
                cout<<"Invalid request! Count becomes negative"<<endl;
                return false;
            }
        }
        bool borrowBook(){                   
            if (copiesAvailable>0){
                updateAvailableCopies(-1);
                return true;
            }
            else{
                cout<<"Invalid request! Copy of book not available"<<endl;
                return false;
            }
        }
        void updateAvailableCopies(int n){
            copiesAvailable+=n;
        }
        bool returnBook(){
            if (copiesAvailable<totalCopies){
                updateAvailableCopies(1);
                return true;
            }
            else{
                cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
                return false;
            }
        }
        void printDetails(){
            cout<<title<<" "<<author<<endl;
        }
        friend class Library;
};

class Member{
    private:
        string memberID;
        map<string,int> borrowedBooks;
        int borrowLimit;
        int numberOfBooksBorrowed;
    public:
        string name;
        Member(string memberID,string name,int borrowLimit=3){
            this->memberID=memberID;
            this->name=name;
            this->borrowLimit=borrowLimit;
            this->numberOfBooksBorrowed=0;
        }
        bool borrowBook(string isbn){
            if (numberOfBooksBorrowed<borrowLimit){
                borrowedBooks[isbn]++;
                numberOfBooksBorrowed++;
                return true;
            }
            else{
                cout<<"Invalid request! Borrow limit exceeded"<<endl;
                return false;
            }
        }
        bool returnBook(string isbn){
            if (borrowedBooks[isbn]>0){ 
                borrowedBooks[isbn]--;
                numberOfBooksBorrowed--;
                return true;
            }
            else{
                cout<<"Invalid request! Book not borrowed"<<endl;
                return false;
            }
        }
        void printDetails(){
            for (auto i:borrowedBooks){
                if (i.second>0){
                    cout<<memberID<<" "<<name<<" "<<i.first<<" "<<i.second<<endl;
                }
            }
        }
        friend class Library;
};
class Library{
    private:
        vector<Book*> books;       
        vector<Member*> members;   
    public:
    ~Library(){
        for (auto i:books){
            delete i;
        }
        for (auto j:members){
            delete j;
        }
    }
    Book* searchBook(string isbn){
            for (auto i:books){
                if (i->isbn==isbn){
                    return i;
                }
            }
            return NULL;
    }
    Member* searchMember(string memberID){
        for (auto i:members){
            if (i->memberID==memberID){
                return i;
            }
        }
        return NULL;
    }
    bool addBook(Book& book){
        if (searchBook(book.isbn)==NULL){
            books.push_back(new Book(book));
            return true;
        }
        else{
            cout<<"Invalid request! Book with same isbn already exists"<<endl;
            return false;
        }
    }
    bool registerMember(Member& member){
        if (searchMember(member.memberID)==NULL){
            members.push_back(new Member(member));
            return true;
        }
        else{
            cout<<"Invalid request! Member with same id already exists"<<endl;
            return false;
        }
    }
    bool borrowBook(string memberID, string isbn){ 
        Book* book=searchBook(isbn);
        if (book==NULL){
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
        if (book->borrowBook()){    
            Member* member=searchMember(memberID);
            if (member!=NULL && searchMember(memberID)->borrowBook(isbn)){
                return true;
            }
            else{
                book->updateAvailableCopies(1);
                return false;
            }
        }
        return false;
    }
    bool returnBook(string memberID, string isbn){
        Book* book=searchBook(isbn);
        if (book==NULL){
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
        if (book->returnBook()){
            Member* member=searchMember(memberID);
            if (member!=NULL && searchMember(memberID)->returnBook(isbn)){
                return true;
            }
            else{
                book->updateAvailableCopies(-1);
            }
        }
        return false;
    }
    void printLibraryDetails(){
        for (auto bookptr:books){
            cout<<bookptr->title<<" "<<bookptr->author<<" "<<bookptr->copiesAvailable<<endl;
        }
        for (auto memberptr:members){
            cout<<memberptr->memberID<<" "<<memberptr->name<<endl;
        }
    }
};
int main() {
    Library lib;
    while (true){
        string operation;
        cin>>operation;
        if (operation=="Book"){
            string first;
            cin>>first;
            if (first=="None"){
                Book* book=new Book();
                lib.addBook(*book);
            }
            else if (first=="ExistingBook"){
                string oldisbn,newisbn;
                cin>>oldisbn>>newisbn;
                Book* book=new Book(*(lib.searchBook(oldisbn)),newisbn);
                lib.addBook(*book);               
            }
            else{
                string author,isbn;
                int copies,total;
                cin>>author>>isbn>>copies>>total;
                Book* book=new Book(first,author,isbn,copies,total);
                lib.addBook(*book);
            }
        }
        else if (operation=="UpdateCopiesCount"){
            string isbn;
            int count;
            cin>>isbn>>count;
            Book* book=lib.searchBook(isbn);
            if (book!=NULL){ 
                lib.searchBook(isbn)->updateCopies(count);
            }
            else{
                cout<<"Invalid request! Copy of book not available"<<endl;
            }
        }
        else if (operation=="Member"){
            cin.ignore();
            string x,y,z;
            cin>>x>>y>>z;
            if (x=="NoBorrowLimit"){
                Member* m=new Member(y,z);
                lib.registerMember(*m);
            }
            else{
                Member *m=new Member(x,y,stoi(z));
                lib.registerMember(*m);
            }
        }
        else if (operation=="Borrow"){
            string id,isbn;
            cin>>id>>isbn;
            lib.borrowBook(id,isbn);
        }
        else if (operation=="Return"){
            string id,isbn;
            cin>>id>>isbn;
            lib.returnBook(id,isbn);
        }
        else if (operation=="PrintBook"){
            string isbn;
            cin>>isbn;
            lib.searchBook(isbn)->printDetails();
        }
        else if (operation=="PrintMember"){
            string id;
            cin>>id;
            lib.searchMember(id)->printDetails();
        }
        else if (operation=="PrintLibrary"){
            lib.printLibraryDetails();
        }
        else{
            break;
        }
        cin.ignore();
    }   
    return 0;
}