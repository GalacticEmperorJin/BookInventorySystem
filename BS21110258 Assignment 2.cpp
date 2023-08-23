/*
	Name: Book Inventory System
	Subject: SV20303 Object Oriented Programming in C++
	Lecturer: Assoc Prof. Abdullah Bin Bade, Mdm. Miezra Midin
	Author: Katherine Grace Lang, BS21110258
	Course & Faculty: Mathematic Computer Graphics, Faculty Science and Natural Resources, Universiti Malaysia Sabah
	Description: Design a system using a C++ called books inventory with suitable member functions, array, data 
				structure and pointers. Use suitable pointers, array and data structure to allocate and handle your 
				memory space required dynamically. User can also save theirs searching process data and can be 
				opened soon by certain ID / key to index their previous searching process data.
*/

#include <cstdio>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;


struct record{
	string authorName;
	string titleName;
	string pubName;
	float price;
	int stockNum;
}list;

//global variable declarations
FILE* fp; 
FILE* ft;
FILE* searchf;
float total;
int choice,found,ch,num;
string title,author,name;

int main (){
	//menu bar
	menu:
		cout << "-PRIMER BOOKSHOP SDN BHD-"<< endl;
		cout << "---------Menu Bar--------" << endl;
		cout << "1. Entry of New Book" << endl;
		cout << "2. Display All Available Books" << endl;
		cout << "3. Buy Book" << endl;
		cout << "4. Search for Book" << endl;
		cout << "5. Edit Details Of Book" << endl;
		cout << "6. Save your Search" << endl;
		cout << "7. Open your previous Search" << endl;
		cout << "8. Help" << endl;
		cout << "9. Exit" << endl;
		cout << "Enter your choice :: ";
		cin >> choice;
	
	switch(choice){
		//Entry for books
		case 1:
			system ("cls"); //clearscreen
			cout << "----------Book Entry---------"<< endl;
			
			fp = fopen("BooksaleRecord.txt","a");
			
			do{
				cout << "=============================" << endl;

				cout << "Enter Title Name    :";
				cin.ignore();
				getline(cin,list.titleName);
				
				cout << "Enter Author Name   :";
				getline(cin,list.authorName);
					
				cout << "Enter Publisher Name:";
				getline(cin,list.pubName);
				cin.clear (); //to avoid the empty space before the output of price
					
				cout << "Enter Price in RM   :";
				cin >> setprecision(4) >> list.price;
				
				cout <<"Enter Stock Position :";
				cin >> list.stockNum;
				cin.ignore();
				
				fwrite(&list,sizeof(list),1,fp);
					
				cout << "Record Saved!" << endl;
				cout << "=============================" << endl;
				cout << "Add another? 1.Yes 2.No" << endl;
				cout << "Enter your choice :: ";
				cin >> ch;	
			}while (ch == 1);
			
			fclose(fp);
			break;
			
		//Display book records	
		case 2:
			system ("cls");
			cout << "----------Book Records---------" << endl;
			
			fp = fopen ("BooksaleRecord.txt","r");
			while(fread(&list,sizeof(list),1,fp) == 1){
				cout << "=============================" << endl;
				cout << "Title" << setw(8)<<":" << list.titleName << endl;
				cout << "Author"<< setw(7)<<":" << list.authorName << endl;
				cout << "Publisher"<<setw(4) <<":"<< list.pubName << endl;
				cout << "Price" << setw(11) << ":RM " << list.price << endl;
				cout << "Stock Number:" << list.stockNum << endl;
				cout << "=============================" << endl;
			}
			
			fclose (fp);
			
			break;
			
		//buy book
		case 3:
			system ("cls");
			cout << "----------Book Purchase---------"<<endl;
			
			fp = fopen ("BooksaleRecord.txt","r+");
			ft = fopen ("temp.txt","w");
			
			cout << "Book title:";
			cin.ignore();
			getline(cin, title);
			
			cout << "Book author:";
			getline(cin,author);
			
			while(fread(&list,sizeof(list),1,fp)==1){
				 
				if (title == list.titleName && author == list.authorName ){
					cout << "Number of book to buy:";
					cin >> num;
					
					if (num <= list.stockNum){
						total = num*list.price;
						cout << "Total: RM" << total << endl;
						list.stockNum -= num;
						cout << "Purchase Complete!";
						
						}
					
					else if (num > list.stockNum){
						cout << "Not Enough! Current Stock:" << list.stockNum << endl;
						
					}
					else {
						cout << "wrong input!";
					}
				}
				
			fwrite(&list,sizeof(list),1,ft); //rewrite record with reduced stock number
			}
			
			fclose(fp);
			fclose(ft);
			
			remove("BooksaleRecord.txt");
			rename("temp.txt","BooksaleRecord.txt");	
			
			break;
					
		//search book
		case 4:
			system("cls");
			cout << "----------Book Search----------" << endl;
			do{
				found = 0;
	 			fp=fopen("BooksaleRecord.txt","r");
	 			
	 			cout << "Enter Book Title:";
	 			cin.ignore();
				getline(cin,title);
				
				cout << "\nSearch result for " << title << endl;
				cout << "-------------------------------" << endl;
				
				while(fread(&list,sizeof(list),1,fp)==1){
					
					if (title == list.titleName){
						cout << "Title" << setw(8)<<":" << list.titleName << endl;
						cout << "Author"<< setw(7)<<":" << list.authorName << endl;
						cout << "Publisher"<<setw(4) <<":"<< list.pubName << endl;
						cout << "Price" << setw(11) << ":RM " << list.price << endl;
						cout << "Stock Number:" << list.stockNum << endl;
						cout << "-------------------------------" << endl;
						found++;
					}
					else{
						break;
					}
				}
			
			 	fclose(fp);
			 	cout << "Sorry! Title Does Not Exist!" << endl;
				cout << "Try Again? [1]Yes [0]No(Exit)" << endl;
				cout << "Choice:";
				cin >> ch;	
			}while (ch == 1);
			
			break;

		//edit book
		case 5:
			system("cls");
			cout << "-----------Edit Book-----------" <<endl;
			fp = fopen("BooksaleRecord.txt","r");
			ft = fopen("temp.txt","w");
			
			cout << "Enter Book Title to edit:";
			cin.ignore();
			getline(cin,title);
			
			cout << "Enter Book Author to edit:";
			getline(cin,author);
			
			while(fread(&list,sizeof(list),1,fp)==1){
				if(title != list.titleName && author!= list.authorName){
					fwrite(&list,sizeof(list),1,ft);
				}
			}

			cout << "Edit Book:" << title << endl;
			
			cout << "Enter Title Name    :";
			getline(cin,list.titleName);
			
			cout << "Enter Author Name   :";
			getline(cin,list.authorName);
				
			cout << "Enter Publisher Name:";
			getline(cin,list.pubName);
				
			cout << flush;
			cout << "Enter Price in RM   :";
			cin.ignore();
			cin >> setprecision (4) >> list.price;
			
			cout << flush;
			cout <<"Enter Stock Position :";
			cin >> list.stockNum;
			cin.ignore();
			
			fwrite(&list,sizeof(list),1,ft);
			fclose(fp);
			fclose(ft);
			
			remove("BooksaleRecord.txt");
			rename("temp.txt","BooksaleRecord.txt");
			
			cout << "Record Edited!";
			
			break;

		//save search
		case 6:
			system ("cls");
			cout << "----------Save Search---------" << endl;
			
			searchf = fopen ("searchRecord.txt","a");
			fp = fopen ("BooksaleRecord.txt","r");
			
			cout << "Enter your search:: " << endl;
			cout << "Enter Book Title:";
			cin.ignore();
			getline(cin,title);
			
			cout << "\nSearch result for " << title << endl;
			cout << "******************************" << endl;
		 	while(fread(&list,sizeof(list),1,fp)==1){
		 		
				if(title == list.titleName){
					cout << "Title" << setw(8)<<":" << list.titleName << endl;
					cout << "Author"<< setw(7)<<":" << list.authorName << endl;
					cout << "Publisher"<<setw(4) <<":"<< list.pubName << endl;
					cout << "Price" << setw(11) << ":RM " << list.price << endl;
					cout << "Stock Number:" << list.stockNum << endl;
					cout << "******************************" << endl;
					fwrite(&list,sizeof(list),1,searchf);
					}
			}
			
			cout << "Search Save!"<<endl;
			fclose(searchf);
			fclose(fp);
			break;
			
		//show search
		case 7:
			system ("cls");
			cout << "----------Open Previous Search---------" << endl;
			searchf = fopen ("searchRecord.txt","r");
			cout << "-------------------------------" << endl;
			while(fread(&list,sizeof(list),1,searchf) == 1){
			 	cout << "Author"<< setw(7)<<":" << list.authorName << endl;
				cout << "Title" << setw(8)<<":" << list.titleName << endl;
				cout << "Publisher"<<setw(4) <<":"<< list.pubName << endl;
				cout << "Price" << setw(11) << ":RM " << list.price << endl;
				cout << "Stock Number:" << list.stockNum << endl;
				cout << "-------------------------------" << endl;
			}
			fclose (searchf);
			break;
		//help
		case 8:
			system ("cls");
			cout << " ----------Help---------" << endl;
			cout << "1. Entry of New Book" << endl;
			cout << "Enter the each information of the new book(title,author,publisher,price,stock available)" << endl;
			cout << "2. Display All Available Books" << endl;
			cout << "Display information of all the books in the inventory system." << endl;
			cout << "3. Buy Book" << endl;
			cout << "Enter the title and author of the purchase book." << endl;
			cout << "4. Search for Book" << endl;
			cout << "Enter the title and author of the searched book" << endl;
			cout << "5. Edit Details Of Book" << endl;
			cout << "Enter the title and author of the book you want to edit and rewrite the whole information" << endl;
			cout << "of the reedited book." << endl;
			cout << "6. Save your Search" << endl;
			cout << "Enter the title and author of the book you want to save." << endl;
			cout << "7. Open your previous Search" << endl;
			cout << "Display the information of the book you save search for" << endl;
			break;

		//exit
		case 9:
			break;
		default:
			cout << "Invalid Choice!";
			return 0;	
	}
	
	//exit menu
	exit:
		cout << endl << "-------------EXIT------------" << endl;
		cout << "Are you sure? [1]Yes [0]No(Main Menu)"  << endl;
		cout << "Choice: "; 
		cin >> ch;
			
	switch (ch){
		case 1:
			return 0;
		case 0:
			system ("cls");
			goto menu;
		default:
			cout << "-------Invalid Choice!-------" << endl;
			goto exit;
	}
	return 0;
}