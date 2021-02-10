#include<iostream>
#include<fstream>
#include<ctime>       //i.e. provides 'time' func
#include<cstdlib>     //i.e. provides 'rand','srand' funcs
#include<algorithm>   //i.e. provides 'reverse' func
#include<typeinfo>	  //i.e. provides 'name' func for 'typeid'
#include<conio.h>	  //i.e. provides 'getch' func
#include<windows.h>	  //i.e. provides all funcs for constructing 'gotoxy' func
using namespace std;

#define BackSpace 8
#define Tab 9
#define Enter 13
#define Escape 27
#define Up 72
#define Down 80
#define Right 77
#define Left 75

#include"Main_Files/Global.hpp"

class Ctgry final{//Note: Using 'final' keyword with class name forbids further inheritance
	static const unsigned short Category_Count;
	static const string Category_Arr[];
	Ctgry(){}//i.e. making private ctor, so that no object can be created

	static void Update_Category_Arr(const string File_Name,const string Category_Name,const unsigned short Category_Index){
		fstream File(File_Name,ios::in|ios::out|ios::ate);//i.e. opening file in multiple modes
		File.seekp(43,ios::beg);
		if (Category_Index<10)
			File<<" ";
		File<<Category_Index<<";";
		File.seekp(-4,ios::end);
		File<<",\""<<Category_Name<<"\" }; ";
		File.close();
	}
	static void Update_Item_Categories(const string File_Name,const string Category_Name){
		fstream File(File_Name,ios::in|ios::out|ios::ate);
		File<<"\nclass "<<Category_Name<<" final: Items{ "<<Category_Name<<"(){}\n";
		unsigned short choice;
		Glbl::Validate_Input(choice,2,"Add Attributes to the class?\n1) Yes\n2) No\n==> ");
		if (choice==1){
			Glbl::Validate_Input(choice,30,"How many Attributes?\n==> ");
			string Data_Type[choice],Variable_Name[choice];
			for (unsigned short i=0;i<choice;++i){
				Glbl::Validate_Input(Data_Type[i],"Enter Data_Type: ");
				Glbl::Validate_Input(Variable_Name[i],Category_Arr,Category_Count,"Enter Variable_Name: ");
				File<<Data_Type[i]<<" "<<Variable_Name[i]<<"; ";
			}
			File<<"\nvoid Input_Data(istream& in)override{ ";
			for (unsigned short i=0;i<choice;++i){
				if (Data_Type[i]=="string"||Data_Type[i]=="char"||Data_Type[i]=="char16_t"||Data_Type[i]=="char32_t"||Data_Type[i]=="wchar_t")
					File<<"cout<<\"	Enter "<<Variable_Name[i]<<": \"; in>>"<<Variable_Name[i]<<"; ";
				else{
					unsigned __int64 limit;//i.e. max datatype limit
					Glbl::Validate_Input(limit,999999999999999999,"\nEnter validating limit for ",Variable_Name[i],": ");//i.e. 18 digits
					File<<"Glbl::Validate_Input("<<Variable_Name[i]<<","<<limit<<",\"	Enter "<<Variable_Name[i]<<": \"); ";				
				}
			}
			File<<"}\nvoid Display_Data(ostream& out)const override{ ";
			for (unsigned short X,i=0;i<choice;++i){
				File<<"out<<\", "<<Variable_Name[i]<<": \"<<"<<Variable_Name[i];
				Glbl::Validate_Input(X,2,"\nWant to add additional_string for Display of ",Variable_Name[i],"?\n1) Yes\n2) No\n==> ");
				if (X==1){
					cout<<"\nEnter additional_string: ";
					string additional_string;
					cin>>additional_string;
					File<<"<<\""<<additional_string<<"\"";
				}
				File<<"; ";
			}
			File<<"}\nvoid Read_Files(ifstream& fin)override{ fin";
				for (unsigned short i=0;i<choice;++i)
					File<<">>"<<Variable_Name[i];
				File<<"; }\nvoid Write_Files(ofstream& fout)const override{ fout";
				for (unsigned short i=0;i<choice;++i)
					File<<"<<\" \"<<"<<Variable_Name[i];
				File<<"<<\" # \"; }";	
		}
		else
			File<<"\nvoid Input_Data(istream& in)override{}\nvoid Display_Data(ostream& out)const override{}"
				  "\nvoid Read_Files(ifstream& fin)override{}\nvoid Write_Files(ofstream& fout)const override{ fout<<\" # \"; }";
					
		File<<"\nItems* Clone()const override{ return new "<<Category_Name<<"(*this); } friend class Items_List; };";
		File.close();
	}
	static void Update_Category_Choice(const string File_Name,const string Category_Name,const unsigned short Category_Index){
		fstream File(File_Name,ios::in|ios::out|ios::ate);
		File.seekp(-3,ios::end);
		File<<"\ncase "<<Category_Index<<": return new "<<Category_Name<<"; }  ";//Writing to file
		File.close();
	}
	friend class Items_List;
	friend class SwiFT_Store;
};
#include"Main_Files/Category.hpp"

class Items{//i.e. Abstract/Interface Class
protected:
	unsigned __int64 ID;
	unsigned short Quantity;//i.e. 0-65535
	float Price;//i.e. 6 digits precision
	string Name,Brand,Category;
	
	Items():ID(ID_Generator()),Price(0),Quantity(1){} 
	//Note: generate ID Automatically, so as to search by ID, Category (optional)
	static unsigned __int64 ID_Generator(const bool Reset_Flag=false){//i.e. can produce upto 20 digit no.
		static unsigned __int64 _ID=40400;
		if(Reset_Flag){
			_ID=40400;
			return _ID;
		}
		return ++_ID;
	}
	virtual void Input_Data(istream&)=0;//i.e. pure virtual func, acts like hooker for '>>' operator func
	friend istream& operator>>(istream& in,Items &obj){//i.e. generalized code for derived classes
		cout<<"	Enter Product Name: ";
		in.sync();//i.e. neglects remaining buffer
		in>>obj.Name;//Alternate: getline(cin,Name) -> allows string with whitespaces
		cout<<"	Enter Brand Name: ";
		in.sync();
		in>>obj.Brand;
		in.sync();
		Glbl::Validate_Input(obj.Price,999999,"	Enter Price: ");
		Glbl::Validate_Input(obj.Quantity,65535,"	Enter Quantity: ");
		//Note: No need to pass 'in' obj in Validate_Input, as we've 'cin' as global input buffer
		obj.Input_Data(in);
		return in;
	}
	virtual void Display_Data(ostream&)const=0;
	friend ostream& operator<<(ostream& out,const Items &obj){//i.e. const: generates error if any class attribute is modified inside the func
		out<<") Category: "<<obj.Category<<", Name: "<<obj.Name<<", Brand: "<<obj.Brand<<", ID: "<<obj.ID<<", Price: "<<obj.Price<<", Quantity: "<<obj.Quantity;
		obj.Display_Data(out);
		return out;
	}
	virtual void Read_Files(ifstream&)=0;
	friend ifstream& operator>>(ifstream& fin,Items &obj){
		fin>>obj.Category>>obj.Name>>obj.Brand>>obj.ID>>obj.Price>>obj.Quantity;
    	obj.Read_Files(fin);
        return fin;
    }
    virtual void Write_Files(ofstream&)const=0;
	friend ofstream& operator<<(ofstream& fout,const Items &obj){
        fout<<obj.Category<<" "<<obj.Name<<" "<<obj.Brand<<" "<<obj.ID<<" "<<obj.Price<<" "<<obj.Quantity;
        obj.Write_Files(fout);
        return fout;
    }
	virtual Items* Clone()const=0;
	virtual ~Items(){}//i.e. virtual dtor -> to destruct in correct order
	friend class Items_List;
	friend class SwiFT_Store;
};
#include"Main_Files/Item_Categories.hpp"

class Items_List final{
	unsigned short Items_Counter,Items_Size;//i.e. range: 0-65535
	Items **Item;

	Items_List():Items_Counter(0),Items_Size(1),Item(new Items*[Items_Size]){}

	void Resize_Items(const string str,const unsigned short New_Items_Size){//i.e. generalized code
		cout<<"\nNote: Items List Capacity has been "<<str<<" from "<<Items_Size<<" to "<<New_Items_Size<<"\n\n\a";
		Items** new_Item=new Items*[New_Items_Size];
  		for (unsigned short i=0;i<Items_Counter;new_Item[i]=Item[i++]);//i.e. triggers default copy assignment func
		if(Items_Counter)
			delete[] Item;//i.e. deletes all sub-addresses & also the main address stored in double ptr
		else
			delete Item;//i.e. deletes only main address stored in double ptr
    	Item=new_Item;
    	Items_Size=New_Items_Size;
	}
	void Resize_Items(){
		if (Items_Counter>=Items_Size)
			Resize_Items("increased",Items_Size*2);
		else while(Items_Counter<Items_Size/2)
			Resize_Items("decreased",Items_Size/2);
	}
	Items* Category_Choice(const unsigned short Ctgry_Choice){
		#include"Main_Files/Category_Choice.hpp"
	}
	void Add_or_Insert_Item(const unsigned short Ctgry_Choice,const bool Menu_Choice_Flag){
		Item[Items_Counter]=Category_Choice(Ctgry_Choice);
		Item[Items_Counter]->Category=Ctgry::Category_Arr[Ctgry_Choice-1];
		cout<<"\nItem "<<Items_Counter+1<<" ("<<Item[Items_Counter]->Category<<"\b):-"<<endl; 
		//i.e. \b -> escape character, used to neglect last char of 'Category' str
		if (Menu_Choice_Flag&&Items_Counter>1){//i.e. Insert Item
			unsigned short Index_No;
			Glbl::Validate_Input(Index_No,Items_Counter,"\n	Enter Index No (1-",Items_Counter,"): ");
			cin>>*Item[Items_Counter];
			Items *Temp_Ptr=Item[Items_Counter];
			for (unsigned short i=Items_Counter;i>Index_No-1;Item[i]=Item[--i]);
			Item[Index_No-1]=Temp_Ptr;
		}
		else//i.e. Add Item
			cin>>*Item[Items_Counter];
		++Items_Counter;
	}
	void Delete_or_Remove_Item(const bool Menu_Choice_Flag){
		if (Items_Counter){
			if (Items_Counter>1&&Menu_Choice_Flag){
				unsigned short Index_No;
				Glbl::Validate_Input(Index_No,Items_Counter,"\nEnter Index No (1-",Items_Counter,"): ");
				for (delete Item[Index_No-1];Index_No<Items_Counter-1;Item[Index_No-1]=Item[Index_No++]);//i.e. copies item_objs	
				Item[Index_No-1]=Item[Index_No]->Clone();
				//i.e. assigns a clone copy (i.e. new address) of last item_obj by calling default copy ctor
			}
			delete Item[--Items_Counter];
		}
		else
			cout<<"\nWarning: No Item found!\n\a";
	}
	void Copy_Item(const unsigned short Ctgry_Choice){
		Item[Items_Counter]=Category_Choice(Ctgry_Choice);
		Item[Items_Counter]->Category=Ctgry::Category_Arr[Ctgry_Choice-1];
		if (Items_Counter>1){
			unsigned short Src_Index,Dest_Index;
			cout<<"(limit: 1-"<<Items_Counter<<")\n";
			Glbl::Validate_Input(Src_Index,Items_Counter,"\nEnter Item 1 (Source) Index: ");
		same_indexes:
			Glbl::Validate_Input(Dest_Index,Items_Counter,"\nEnter Item 2 (Destination) Index: ");
			if (Src_Index==Dest_Index){
				cout<<"\a";
				goto same_indexes;
			}
			delete Item[Dest_Index-1];
			Item[Dest_Index-1]=Item[Src_Index-1]->Clone();
		}
		else
			cout<<"\nWarning: Items are less than 2!\n\a";	
	}
	template<class T1,class T2>//i.e. defining different place-holders so that no error occurs for diff. types
	void Swap_Items_Ptr(T1 Index_1,T2 Index_2){
		Items *Temp_Ptr=Item[Index_1];
		Item[Index_1]=Item[Index_2];
		Item[Index_2]=Temp_Ptr;
	}
	void Move_or_Swap_Items(const bool Menu_Choice_Flag){
		if (Items_Counter>1){
			unsigned short Src_Index,Dest_Index;
			cout<<"(limit: 1-"<<Items_Counter<<")\n";
			Glbl::Validate_Input(Src_Index,Items_Counter,"\nEnter Item 1 (Source) Index: ");
		same_indexes:
			Glbl::Validate_Input(Dest_Index,Items_Counter,"\nEnter Item 2 (Destination) Index: ");
			if (Src_Index==Dest_Index){
				cout<<"\a";
				goto same_indexes;
			}
			if (Menu_Choice_Flag)//i.e. Swap Items
				Swap_Items_Ptr(Src_Index-1,Dest_Index-1);
			else{//i.e. Move Item
				if (Src_Index>Dest_Index)
					for(unsigned short i=Src_Index-1;i>Dest_Index-1;--i)
						Swap_Items_Ptr(i,i-1);
				else
					for(unsigned short i=Src_Index-1;i<Dest_Index-1;++i)
						Swap_Items_Ptr(i,i+1);
			}
		}
		else
			cout<<"\nWarning: Items are less than 2!\n\a";
	}
	void Update_Item(){
		if (Items_Counter){
			unsigned short Index_No=1;
			if (Items_Counter>1)
				Glbl::Validate_Input(Index_No,Items_Counter,"\nEnter Index No (1-",Items_Counter,"): ");
			cin>>*Item[Index_No-1];
		}
		else
		cout<<"\nWarning: No Item found!\a\n";
	}
	void Display_Data()const{
		cout<<"\nItems List:-"<<endl<<"	Total Items: "<<Items_Counter<<endl<<"	Items:"<<endl;
		for (unsigned short i=0;i<Items_Counter;i++)
			cout<<"		"<<i+1<<*Item[i]<<endl;
	}
	void Write_Data_Files(const string File_Name){
		ofstream fout(File_Name);
		for(unsigned short i=0;i<Items_Counter;fout<<*Item[i++]);
        fout.close();
	}
	static unsigned long Count_File_Items(const string File_Name,const char Delimeter='#'){
		ifstream fin(File_Name);
		if(!fin){
			cout<<"\nWarning! File not Present!\n\a";
			return false;
		}
		unsigned long Count=0;
		while(fin.good()){//i.e. gives improve results & maintains additional flags
			if(Delimeter==fin.get())
			++Count;
		}
		fin.close();
		return Count;
	}
	bool Read_Data_Files(const string File_Name){
		ifstream fin(File_Name);
		unsigned short Temp_Items_Counter=Count_File_Items(File_Name);
		if (!Temp_Items_Counter){
			cout<<"\nWarning! No Items Present in File\n\a";
			return false;
		}
		Clear_List(true);//i.e. resets Items_Counter, ID_Generator & destroys all the objs
		if(Temp_Items_Counter>Items_Size){
			if(!(Temp_Items_Counter%10))
				Resize_Items("increased",Temp_Items_Counter);
			else
				Resize_Items("increased",10*((Temp_Items_Counter/10)+1));//i.e. file_objs: 176 -> cur_ obj: 180
		}
		for(unsigned short i=0;i<Temp_Items_Counter;++i){
			string temp_str;
			fin>>temp_str;
			fin.seekg(-temp_str.length(),ios::cur);
			for (unsigned short j=0;j<Ctgry::Category_Count;++j){
					if(temp_str==Ctgry::Category_Arr[j]){
						Item[i]=Category_Choice(j+1);
						fin>>*Item[i];
						char Delimeter;
						fin>>Delimeter;
						++Items_Counter;
						break;
					}
			}
		}
        fin.close();
        return true;
	}
	void Clear_List(const bool File_Flag=false){
		if (Items_Counter){
			while(Items_Counter)
				delete Item[--Items_Counter];
			Items::ID_Generator(true);
		}
		else if(!File_Flag)
			cout<<"\nWarning: No Item found!\n\a";
	}
	~Items_List(){
		Clear_List(true);
		if (Items_Counter)
			delete[] Item;
		else
			delete Item;
	}
	friend class SwiFT_Store;
};
class SwiFT_Store final{
	SwiFT_Store(){}
	
	static unsigned char Key_Generator(){
		srand(time(NULL));
		return rand()%127+1;//i.e. range: 1-128
	}//Note: max: 127 possible (i.e.signed char +ve range)
	static void Encrypt_Data(string& File_Str,const char Public_Key){
		string Private_Str_Key="~`!@#$%^&*()_+=-\\|/*-+><.,;:\"?[]{}"//Note: Private_Str_Key is resizable
							   	"abcdefghijklmnopqrstuvwxyz"
					    		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					    		"0123456789";
		for (unsigned short i=0;i<Private_Str_Key.size();++i)
			for(short j=0;j<File_Str.size();++j)
				File_Str[j]^=Private_Str_Key[i];
		for (unsigned short i=0;i<File_Str.size();++i)
			File_Str[i]=(File_Str[i]-Public_Key)%255;
	}
	static void Decrypt_Data(string& Encrypted_Str,const char Public_Key){
		string Private_Str_Key="~`!@#$%^&*()_+=-\\|/*-+><.,;:\"?[]{}"//Note: Should be same as above Private_Str_Key
							   "abcdefghijklmnopqrstuvwxyz"
							   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							   "0123456789";
		for (unsigned short i=0;i<Encrypted_Str.size();++i){
			Encrypted_Str[i]=(Encrypted_Str[i]+Public_Key)%255;
			for(short j=Private_Str_Key.size()-1;j>=0;--j)
				Encrypted_Str[i]^=Private_Str_Key[j];
		}
	}
	static string File_Str_Reader(const string File_Name){
		string File_Str;
		ifstream fin(File_Name);
		if(!fin){
			cout<<"\nWarning! File not Present!\n\a";
			return "N-U-L-L";
		}
		while(fin.good())//i.e. provides improved performance than eof()
			File_Str+=fin.get();
		fin.close();
		File_Str.pop_back();//i.e. eliminates last null/eof char
		return File_Str;
	}
	static void File_Str_Writer(const string File_Name,const string File_Str){
		ofstream fout(File_Name);
			fout<<File_Str;
		fout.close();
	}
	static void Delete_Public_Key(string& File_Str,const unsigned short Line_Index){
		for (unsigned int Line_Counter=0,i=0;i<File_Str.length();++i)
			if(File_Str[i]=='\n'){
				++Line_Counter;
				if (Line_Counter==Line_Index){
					File_Str.erase(i-7,7);//i.e. deletes the specific part from string
					break;
				}
			}
	}
	static void Insert_Public_Key(string& File_Str,const unsigned short Line_Index,const unsigned short Key){
		string String_Part;
		if(Line_Index<10){
			if(Key<10)
				String_Part="  "+to_string(Line_Index)+")  "+to_string(Key);
			else if(Key<100)
				String_Part="  "+to_string(Line_Index)+") "+to_string(Key);
			else
				String_Part="  "+to_string(Line_Index)+")"+to_string(Key);						
		}
		else if(Line_Index<100){
			if(Key<10)
				String_Part=" "+to_string(Line_Index)+")  "+to_string(Key);
			else if(Key<100)
				String_Part=" "+to_string(Line_Index)+") "+to_string(Key);
			else
				String_Part=" "+to_string(Line_Index)+")"+to_string(Key);
		}
		else{
			if(Key<10)
				String_Part=to_string(Line_Index)+")  "+to_string(Key);
			else if(Key<100)
				String_Part=to_string(Line_Index)+") "+to_string(Key);
			else
				String_Part=to_string(Line_Index)+")"+to_string(Key);
		}
		
		for (unsigned int Line_Counter=0,i=0;i<File_Str.length();++i)
			if(File_Str[i]=='\n'){
				++Line_Counter;
				if(Line_Counter==Line_Index){
					File_Str.insert(i,String_Part);//i.e. inserts the specific part in string
					break;
				}
			}
	}
	static void Display_Boxes(unsigned char Boxes,unsigned char x,unsigned char y){
		for (unsigned char z=0,i=0;i<Boxes;++i){//i.e. z->skips 2 lines after 1 box
			for (unsigned char j=1;j<=3;++j){
				Glbl::Gotoxy(x,y+z);
				for (unsigned char k=1;k<=17;++k){
					if (j==1||j==3||k==1||k==17)
						cout<<"?";
					else
						cout<<" ";
				}
				cout<<"\n";
				++y;
			}
			++z;
		}
	}
	static void Password(string& Pass){
		char i=0,Temp_Pass[10];
		do{
			Temp_Pass[i]=getch();
			if (i>=10){//i.e. restricts users to type more than 10 characters
				if (Temp_Pass[i]==BackSpace){
					cout<<"\b \b";
					i--;
				}
				continue;
			}
			if (isprint(Temp_Pass[i])){//Note: isprint() returns '+ve value' for printable characters & '0' for non-printable
				cout<<"*";
				i++;
			}
			else if(Temp_Pass[i]==BackSpace&&i!=0){// i.e. allow users to re-write their Password
				cout<<"\b \b";
				i--;
			}
		}while (Temp_Pass[i]!=Enter);
		Temp_Pass[i]='\0';//i.e. neglecting the re-written characters after 'NULL'
		Pass=Temp_Pass;
	}
	static void Add_New_Category(){
		const char* File_Names[] {"Main_Files/Category.hpp","Main_Files/Item_Categories.hpp","Main_Files/Category_Choice.hpp"};//Note: const char* = string
		//Note: Insert all included Main_File names in above string arr
		if(!Glbl::Check_Files(File_Names[0],File_Names[1],File_Names[2])){//i.e. checks Main_Files are present
			cout<<"\nError! All Main Files are not Found!\n\a";
			return;
		}
		string Category_Name;
		Glbl::Validate_Input(Category_Name,Ctgry::Category_Arr,Ctgry::Category_Count,"\n!!! RETAILER-MENU / ADD-NEW-CATEGORY !!!"
																					 "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
																					 "Enter New Category Name: ");		
		Ctgry::Update_Category_Arr(File_Names[0],Category_Name,Ctgry::Category_Count+1);
		Ctgry::Update_Item_Categories(File_Names[1],Category_Name);
		Ctgry::Update_Category_Choice(File_Names[2],Category_Name,Ctgry::Category_Count+1);
		system("g++ SwiFT_Store_Management.cpp -o New_SwiFT_Store_Management.exe -std=gnu++11"); 
		//i.e. recompiles the program & generates a new .exe using cmd-prompt instructions
		cout<<"Source Files Updated Successfully!\nNote: Use the New Version of App to See Changes!\n";
		system("pause");
	}
	static void Update_Current_DataBase(Items_List& List,const unsigned short DB_Index){
		unsigned short Ctgry_Choice;
		bool X_Flag=true;
		while(true){
			unsigned short Menu_Choice;
			Glbl::Validate_Input(Menu_Choice,13,"\n !!! RETAILER-MENU / UPDATE-DATABASE-",DB_Index,
												" !!!\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
									 	   		" 1)  Add Item\n"
									 	   		" 2)  Delete Item\n"
									 	   		" 3)  Insert Item (Randomly)\n"
									 	   		" 4)  Remove Item (Randomly)\n"
									 	   		" 5)  Copy Item\n"
									 	   		" 6)  Move Item\n"
									 	   		" 7)  Swap Items\n"
									 	   		" 8)  Update Item Details\n"
									 	   		" 9)  View Items List\n"
									 	   		"10)  Change Category\n"
									 	   		"11)  Clear Screen\n"
									 	   		"12)  Return Back\n"
									 	   		"13)  Clear List\n"
									 	   		"==>  ");
			string Ctgry_str="\nWhich Category?\n";
			switch (Menu_Choice){
				case 1:
					if (X_Flag)
						goto Change_Category;
					List.Add_or_Insert_Item(Ctgry_Choice,0);
					break;
				case 2:
					List.Delete_or_Remove_Item(0);
					break;
				case 3:
					if (X_Flag)
						goto Change_Category;
					List.Add_or_Insert_Item(Ctgry_Choice,1);//i.e. Insert_Item-> randomly inserts item
					break;	
				case 4:
					List.Delete_or_Remove_Item(1);//i.e. Remove_Item-> randomly removes item
					break;
				case 5:
					List.Copy_Item(Ctgry_Choice);
				break;
				case 6:
					List.Move_or_Swap_Items(0);
					break;
				case 7:
					List.Move_or_Swap_Items(1);
					break;
				case 8:
					List.Update_Item();
					break;
				case 9:
					List.Display_Data();	
					break;
				case 10:
					Change_Category:
					for (unsigned short i=1;i<=Ctgry::Category_Count;++i)//i.e. creating category menu string
						Ctgry_str+=(to_string(i)+")  "+Ctgry::Category_Arr[i-1]+"\n");
					Ctgry_str+="==> ";
					Glbl::Validate_Input(Ctgry_Choice,Ctgry::Category_Count,Ctgry_str);
					if (X_Flag){
						if (Menu_Choice==1)
							List.Add_or_Insert_Item(Ctgry_Choice,0);
						else if (Menu_Choice==3)
							List.Add_or_Insert_Item(Ctgry_Choice,1);
						X_Flag=false;
					}
					break;
				case 11:
					system("cls");
					break;
				case 12:
					system("cls");
					return;
				case 13:
					List.Clear_List();
					break;
			}//i.e. no need for default case, as value is already restriced through Validate_Input func
			List.Resize_Items();//Note: Automatically resizes the Items_ptr array (i.e.vector class approach)
			cout<<endl;
		}
	}
	static void Change_App_Name(string Path){//i.e. Path: "bla-bla-bla/New_SwiFT_Store_Management.exe"
		reverse(Path.begin(),Path.end());//i.e. Reversed Path: "exe.tnemeganaM_erotS_TFwiS_weN/bla-bla-bla"
		string App_Name;
		for (unsigned short i=0;Path[i]!='\\';App_Name+=Path[i++]);//i.e. Reversed App_Name: "exe.tnemeganaM_erotS_TFwiS_weN"
		reverse(App_Name.begin(),App_Name.end());//i.e. Original App_Name: "New_SwiFT_Store_Management.exe"
		if(App_Name=="New_SwiFT_Store_Management.exe"){
			remove("SwiFT_Store_Management.exe");
			rename(App_Name.c_str(),"SwiFT_Store_Management.exe");
		}
	}// Note: It can change App_Name from any Destination
	static bool Retailer_Menu(unsigned short& Data_Base_Counter,unsigned short& Customer_Data_Base_Index){
		bool Encryption_Flag,Menu_Flag=true;
		unsigned short Cur_DB_Index=0,Choice=0;//i.e. extra 'choice' variable for other inputs
		string Cur_DB_Nme_Str,Temp_DB_Nme_Str;
		Items_List List;
		while(true){
			system("cls");
			unsigned short Cursor_Pos=1;//i.e. defaults to 1st choice
			if(Menu_Flag){
				cout<<"\n   !!! RETAILER-MENU !!!\t\t(Data_Bases: "<<Data_Base_Counter<<", Current DB_Index: "<<Cur_DB_Index
					<<")\n  ^^^^^^^^^^^^^^^^^^^^^^^\n"
					  " 1)    Update Data_Base\n"
					  " 2)    Save Data to Files\n"
		 			  " 3)    Retrieve Data From Files\n"
		 			  " 4)    Encrypt Data_Base\n"
		  			  " 5)    Decrypt Data_Base\n"
		  			  " 6)    Delete Data_Base\n"
		  			  " 7)    Add New Category\n"
		  			  " 8)    Change Account Password\n"
					  " 9)    Set Customer Data_Base\n"
					  "10)    Change Menu Outlook\n"
					  "11)    Log off Account\n";
				do {
					Glbl::Gotoxy(4,Cursor_Pos+2);
					Glbl::Cursor_Pointer(4,Cursor_Pos+2);
					char Hit=getch();
					if (Hit==Down||Hit==Right)
						++Cursor_Pos;
					else if(Hit==Up||Hit==Left)
						--Cursor_Pos;
					else if(Hit==Enter)
						break;
					else if(Hit==Escape){
						Cursor_Pos=11;
						break;
					}
					else if(Hit==Tab){
						Cursor_Pos=10;
						break;
					}
					if (Cursor_Pos==12)
						Cursor_Pos=1;
					else if(!Cursor_Pos)
						Cursor_Pos=11;
				}while(true);
			}
			else{
				Cursor_Pos=0;//i.e. to avoid proceeding to next menu on invalid 'ctrl+any' inputs 
				Glbl::Validate_Input(Cursor_Pos,11,"\n   !!! RETAILER-MENU !!!\t\t(Data_Bases: ",Data_Base_Counter,", Current DB_Index: ",Cur_DB_Index,
													")\n   ^^^^^^^^^^^^^^^^^^^^^\n"
													" 1)   Update Data_Base\n"
											  		" 2)   Save Data to Files\n"
										 	  		" 3)   Retrieve Data From Files\n"
										 	  		" 4)   Encrypt Data_Base\n"
										 	   		" 5)   Decrypt Data_Base\n"
										   			" 6)   Delete Data_Base\n"
										   			" 7)   Add New Category\n"
										  			" 8)   Change Account Password\n"
										 			" 9)   Set Customer Data_Base\n"
										  			"10)   Change Menu Outlook\n"
										  			"11)   Log off Account\n"
													"==>   ");
			}
			system("cls");
			switch (Cursor_Pos){
				case 1:
					Update_Current_DataBase(List,Cur_DB_Index);
					break;
				case 2:
					cout<<"\n !!! RETAILER-MENU / SAVE DATA !!!"
						  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					if(!List.Items_Counter){
						cout<<"Warning: No Items Present in List!\n\a";
						system("pause");
						break;
					}
					Glbl::Validate_Input(Choice,2,"Want to apply changes on:\n1) New Data_Base\n2) Existing Data_Bases\n==>  ");
					if (Choice==1){
						Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(++Data_Base_Counter)+".txt";
						fstream File("Data_Files/Data_Bases/Data_Base_Counter.txt",ios::in|ios::out|ios::ate);
						File.seekp(0,ios::beg);
						File<<Data_Base_Counter;
						File.close();
						goto Save_Data_to_New_DB;
					}
				case 3:
					if (Cursor_Pos==3)
						cout<<"\n !!! RETAILER-MENU / RETRIEVE DATA !!!"
							  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";						
					if(!Data_Base_Counter){
						cout<<"\nWarning: No Data_Base Found!\n\a";
						system("pause");
						break;
					}
					Glbl::Validate_Input(Choice,Data_Base_Counter,"Enter Data_Base Index No (1-",Data_Base_Counter,"): ");
					Cur_DB_Index=Choice;
					Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(Choice)+".txt";
					Temp_DB_Nme_Str="Data_Files/Hidden_Files/Temp_Data_Bases/Temp_DB_"+to_string(Choice)+".txt";
					Encryption_Flag=Glbl::Check_Files(Temp_DB_Nme_Str);
					if(Cursor_Pos==2){
						if(Encryption_Flag){
							remove(Temp_DB_Nme_Str.c_str());
							string File_Str=File_Str_Reader("Data_Files/Hidden_Files/Public_Keys.txt");
							Delete_Public_Key(File_Str,Choice);
							File_Str_Writer("Data_Files/Hidden_Files/Public_Keys.txt",File_Str);
						}
	Save_Data_to_New_DB:
						List.Write_Data_Files(Cur_DB_Nme_Str);
						cout<<"\nFiles Successfully uploaded to Data_Base!\n\a";
					}
					else{
						if(Encryption_Flag){
							if(List.Read_Data_Files(Temp_DB_Nme_Str))
								cout<<"\nFiles Successfully Retrieve from Temp. DataBase "<<Choice<<"!\n\a";
						}
						else if(List.Read_Data_Files(Cur_DB_Nme_Str))
							cout<<"\nFiles Successfully Retrieve from DataBase "<<Choice<<"!\n\a";
					}
					system("pause");
					break;
				case 6:{//i.e. defined local scope in order to skip cross initialization for 'case' labels
					cout<<"\n !!! RETAILER-MENU / DELETE DATABASE !!!"
						  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					if(!Data_Base_Counter){
						cout<<"\nWarning: No Data_Base Found!\n\a";
						system("pause");
						break;
					}
					cout<<"Warning: All Encrypted Data will be Decrypted!\n\n";
					Glbl::Validate_Input(Choice,Data_Base_Counter,"Enter Data_Base Index No (1-",Data_Base_Counter,"): ");
				
					for(unsigned short i=1;i<=Data_Base_Counter;++i){//i.e. deletes all temp_DBs
						Temp_DB_Nme_Str="Data_Files/Hidden_Files/Temp_Data_Bases/Temp_DB_"+to_string(i)+".txt";
						Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(i)+".txt";
						if(Glbl::Check_Files(Temp_DB_Nme_Str)){
							File_Str_Writer(Cur_DB_Nme_Str,File_Str_Reader(Temp_DB_Nme_Str));
							remove(Temp_DB_Nme_Str.c_str());
						}
					}
					fstream File("Data_Files/Hidden_Files/Public_Keys.txt",ios::out);
					File<<endl;
					File.close();//i.e. erases all public_keys
				
					Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(Choice)+".txt";
					remove(Cur_DB_Nme_Str.c_str());//i.e. deletes specified DB
					for (unsigned short i=Choice;i<Data_Base_Counter;++i){//i.e. renames all remaining DBs
						Temp_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(i+1)+".txt";
						Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(i)+".txt";
						rename(Temp_DB_Nme_Str.c_str(),Cur_DB_Nme_Str.c_str());
					}
					File.open("Data_Files/Data_Bases/Data_Base_Counter.txt",ios::in|ios::out|ios::ate);
					File.seekp(0,ios::beg);
					File<<--Data_Base_Counter;
					File.close();
					cout<<"\nData_Base deleted Successfully!\n\a";
					system("pause");
				 	break;
				}
				case 7:
					Add_New_Category();
					return true;
				case 8:{
					cout<<"\n !!! RETAILER-MENU / CHANGE PASSWORD !!!"
						  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					string Pass,Temp_Pass;
					ifstream fin("Data_Files/Hidden_Files/Retailer_Pass.txt");
				Re_Enter:
					cout<<"\nEnter New Password (max limit: 10): ";
					Password(Pass);
					cout<<"\nRe-Enter New Password (max limit: 10): ";
					Password(Temp_Pass);
					if(Pass==Temp_Pass){
						ofstream fout("Data_Files/Hidden_Files/Retailer_Pass.txt");
						Encrypt_Data(Pass,100);//i.e. 100->fixed
						fout<<Pass;
						fout.close();
						cout<<"\n\nPassword Changed!\n";
					}
					else{
						cout<<"\nError! Password Mismatched!\n\a";
						goto Re_Enter;
					}
					system("pause");
					break;
				}
				case 9:{
					cout<<"\n !!! RETAILER-MENU / SET CUSTOMER DATABASE !!!		(Current Customer_Data_Base: "<<Customer_Data_Base_Index<<")"
						  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					if(!Data_Base_Counter){
						cout<<"\nWarning: No Data_Base Found!\n\a";
						system("pause");
						break;
					}
					Glbl::Validate_Input(Customer_Data_Base_Index,Data_Base_Counter,"Set Data_Base Index No (1-",Data_Base_Counter,"): ");
					ofstream fout("Data_Files/Customer_Data/Customer_Data_Base_Index.txt");
					fout<<Customer_Data_Base_Index;
					fout.close();
					cout<<"\nCustomer Data_Base Updated!\n";
					system("pause");
					break;
				}
				case 10:
					if(Menu_Flag)
						Menu_Flag=false;
					else
						Menu_Flag=true;
					break;
				case 11:
					return false;
				case 4:
				case 5:
					if(Cursor_Pos==4)
						cout<<"\n !!! RETAILER-MENU / ENCRYPT DATABASE !!!"
							  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					else
						cout<<"\n !!! RETAILER-MENU / DECRYPT DATABASE !!!"
							  "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					if(!Data_Base_Counter){
						cout<<"\nWarning: No Data_Base Found!\n\a";
						system("pause");
						break;
					}
					Glbl::Validate_Input(Choice,Data_Base_Counter,"Enter Data_Base Index No (1-",Data_Base_Counter,"): ");
					Temp_DB_Nme_Str="Data_Files/Hidden_Files/Temp_Data_Bases/Temp_DB_"+to_string(Choice)+".txt";
					Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(Choice)+".txt";
					string File_Str=File_Str_Reader(Cur_DB_Nme_Str);
					if(File_Str=="N-U-L-L")
						break;
					Encryption_Flag=Glbl::Check_Files(Temp_DB_Nme_Str);
					if (Cursor_Pos==4){
						if(Encryption_Flag){
							cout<<"\nWarning: File Already Encrypted!\n\a";
							system("pause");
							break;
						}
						File_Str_Writer(Temp_DB_Nme_Str,File_Str);
						unsigned short Key=Key_Generator();
						Encrypt_Data(File_Str,Key);
						cout<<"\nENCRYPTED DATA:-\n"<<File_Str<<"\n\nPublic Key: "<<Key;
					
						unsigned short Line_Counter=Items_List::Count_File_Items("Data_Files/Hidden_Files/Public_Keys.txt",'\n');
						if (Choice>Line_Counter){
							ofstream fout("Data_Files/Hidden_Files/Public_Keys.txt",ios::app);
							for(unsigned short i=Line_Counter;i<Choice;++i)
								fout<<endl;
							fout.close();
						}
						string File_Str=File_Str_Reader("Data_Files/Hidden_Files/Public_Keys.txt");
						Insert_Public_Key(File_Str,Choice,Key);
						File_Str_Writer("Data_Files/Hidden_Files/Public_Keys.txt",File_Str);
					}
					else{
						if(!Encryption_Flag){
							cout<<"\nWarning: File Not Encrypted!\n\a";
							system("pause");
							break;
						}
						Glbl::Validate_Input(Cursor_Pos,128,"\nEnter Public Key: ");
						Decrypt_Data(File_Str,Cursor_Pos);
						cout<<"DECRYPTED DATA:-\n"<<File_Str;
						remove(Temp_DB_Nme_Str.c_str());//i.e. deletes temp. data file
						
						string File_Str=File_Str_Reader("Data_Files/Hidden_Files/Public_Keys.txt");
						Delete_Public_Key(File_Str,Choice);
						File_Str_Writer("Data_Files/Hidden_Files/Public_Keys.txt",File_Str);
					}
					File_Str_Writer(Cur_DB_Nme_Str,File_Str);
					cout<<endl<<endl;
					system("pause");
			 		break;
			}
			fflush(stdin);
		}
	}
	static void Customer_Menu(const unsigned short Data_Base_Index){
		string Cur_DB_Nme_Str="Data_Files/Data_Bases/Data_Base_"+to_string(Data_Base_Index)+".txt";
		if(!Glbl::Check_Files(Cur_DB_Nme_Str)){
			cout<<"\nWarning: No Data_Base Found!\n\a";
			system("pause");
			return;
		}
		string Temp_DB_Nme_Str="Data_Files/Hidden_Files/Temp_Data_Bases/Temp_DB_"+to_string(Data_Base_Index)+".txt";
		Items_List List;
		if(Glbl::Check_Files(Temp_DB_Nme_Str))
			List.Read_Data_Files(Temp_DB_Nme_Str);
		else
			List.Read_Data_Files(Cur_DB_Nme_Str);
		unsigned short Choice,Quantity=0;
		float Total_Price=0;
		while(true){
			Glbl::Validate_Input(Choice,5,"\n   !!! CUSTOMER-MENU !!!"
										  "\n   ^^^^^^^^^^^^^^^^^^^^^\n"
										  " 1)   View Items List\n"
										  " 2)   Select Item\n"
										  " 3)   Proceed to Checkout\n"
										  " 4)   Clear Screen\n"
										  " 5)   Return Back\n"
										  "==>   ");
			switch(Choice){
				case 1:
					List.Display_Data();
					break;
				case 2:
					Glbl::Validate_Input(Choice,List.Items_Counter,"Enter Item Index: ");
					cout<<endl<<Choice<<*List.Item[Choice-1]<<endl;
					if(List.Item[Choice-1]->Quantity>0){
						Glbl::Validate_Input(Quantity,List.Item[Choice-1]->Quantity,"Enter Quantity: ");
						List.Item[Choice-1]->Quantity-=Quantity;
						Total_Price+=(List.Item[Choice-1]->Price*Quantity);
					}
					else
						cout<<"Warning: Insufficient Stock!\n\a";
					break;
				case 3:
					if(Quantity){
						cout<<"\nTotal Price: "<<Total_Price<<endl;
						if(Glbl::Check_Files(Temp_DB_Nme_Str))
							List.Write_Data_Files(Temp_DB_Nme_Str);
						else
							List.Write_Data_Files(Cur_DB_Nme_Str);
						system("pause");
						return;
					}
					cout<<"Warning: No Item Selected!\n\a";
					break;
				case 4:
					system("cls");
					break;
				case 5:
					return;
			}
		}
	}
public:
	static void Main_Menu(string Path="NULL"){//i.e. defaults to no change in App Name
		Change_App_Name(Path);
		unsigned short Data_Base_Counter,Customer_Data_Base_Index;
		{//i.e. defined local scope in order to destroy file_obj after its working
			ifstream fin("Data_Files/Data_Bases/Data_Base_Counter.txt");
			if(fin){
				fin>>Data_Base_Counter;//i.e. reads Data_Base_Counter from file
				fin.close();
				/*NOTE: Update the counter manually if you add/delete a database manually, 
						otherwise the program might malfunction */
			}
			else{
				ofstream fout("Data_Files/Data_Bases/Data_Base_Counter.txt");
				fout<<0;
				fout.close();
			}
			fin.open("Data_Files/Customer_Data/Customer_Data_Base_Index.txt");
			if(fin){
				fin>>Customer_Data_Base_Index;//i.e. reads Customer_Data_Base_Index from file
				fin.close();
			}
			else{
				ofstream fout("Data_Files/Customer_Data/Customer_Data_Base_Index.txt");
				fout<<0;
				fout.close();
			}
		}
		while(true){
			Glbl::Gotoxy(47,3);
			cout<<"vvvvvvvvvvvvvvvvvvvvvvv";
			Glbl::Gotoxy(47,4);
			cout<<"!!!!   MAIN-MENU   !!!!";
			Glbl::Gotoxy(47,5);
			cout<<"^^^^^^^^^^^^^^^^^^^^^^^";
			Display_Boxes(3,50,8);
			Glbl::Gotoxy(52,9);
			cout<<"Retailer Menu";
			Glbl::Gotoxy(52,13);
			cout<<"Customer Menu";
			Glbl::Gotoxy(52,17);
			cout<<"    Close    ";
			Glbl::Gotoxy(52,22);
			unsigned short Cursor_Pos=1;//i.e. defaults to 1st choice
			do {
				Glbl::Gotoxy(47,4*Cursor_Pos+5);
				Glbl::Cursor_Pointer(47,4*Cursor_Pos+5);
				char Hit=getch();
				if (Hit==Down||Hit==Right)
					++Cursor_Pos;
				else if(Hit==Up||Hit==Left)
					--Cursor_Pos;
				else if(Hit==Enter)
					break;
				else if(Hit==Escape){
					Cursor_Pos=3;
					break;
				}
				if (Cursor_Pos==4)
					Cursor_Pos=1;
				else if(!Cursor_Pos)
					Cursor_Pos=3;
			}while(true);
			system("cls");
			switch (Cursor_Pos){
					case 1:{
						cout<<"Note: Authorized Personnel Only!\n";
						string Pass,Temp_Pass;
						ifstream fin("Data_Files/Hidden_Files/Retailer_Pass.txt");
						if(!fin){
						Re_Enter:
							cout<<"\nEnter New Password (max limit: 10): ";
							Password(Pass);
							cout<<"\nRe-Enter New Password (max limit: 10): ";
							Password(Temp_Pass);
							if(Pass==Temp_Pass){
								ofstream fout("Data_Files/Hidden_Files/Retailer_Pass.txt");
								Encrypt_Data(Pass,100);//i.e. 100-> fixed
								fout<<Pass;
								fout.close();
								cout<<"\n\nPassword Saved!\n";
							}
							else{
								cout<<"\nError: Password Mismatched!\n\a";
								goto Re_Enter;
							}
						}
						else{
							fin>>Temp_Pass;
							fin.close();
							if(!Temp_Pass.length())
								goto Re_Enter;
							Decrypt_Data(Temp_Pass,100);//i.e. 100-> fixed
							cout<<"\nEnter Password: ";
							Password(Pass);
							if(Pass!=Temp_Pass){
								cout<<"\n\nError: Password Mismatched!\a\n";
								system("pause");
								break;
							}
							cout<<"\n\nPassword Matched!\n";
						}
						system("pause");
						if(Retailer_Menu(Data_Base_Counter,Customer_Data_Base_Index))
							return;
						break;
					}
					case 2:
						cout<<"Current_Data_Base_Index: "<<Customer_Data_Base_Index<<endl;
						if(Data_Base_Counter&&Customer_Data_Base_Index)
							Customer_Menu(Customer_Data_Base_Index);
						else{
							cout<<"Warning! No Customer Data_Base Found!\n\a";
							system("pause");
						}
						break;
					case 3:
						system("cls");
						Glbl::Validate_Input(Cursor_Pos,2,"\nDo you Want to Quit the App?\n1) Yes\n2) No\n==> ");
						if (Cursor_Pos==1)
							return;
			}
			system("cls");
			fflush(stdin);
		}
	}
};
int main(int argc,const char *argv[]){
	try{//i.e. in order to handle any type of exception
		SwiFT_Store::Main_Menu(argv[0]);
	}
	catch(const exception& e){
		cout<<"\aError: "<<e.what()<<endl
			<<"Type: "<<typeid(e).name()<<endl;
	}
	catch(...){
		cout<<"\aError: Exception Occurred!"<<endl;
	}
	return false;
}

