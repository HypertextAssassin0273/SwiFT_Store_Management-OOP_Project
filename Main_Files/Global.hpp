namespace Glbl{//i.e. Global
	void Gotoxy(int x,int y){//Note: x->coloumn & y->row, i.e. gotoxy(col,row)
		COORD var;//i.e. pre-defined structure
		var.X=x;
		var.Y=y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),var);
		//i.e. provides specific modes of graphical representation for console
	}
	void Cursor_Pointer(int x,int y){
		for (unsigned char i=0;!kbhit();++i){
			if (i==1)
				cout<<"<";
			else if(i==2)
				cout<<"^";
			else if (i==3)
				cout<<">";
			else
				cout<<"v";
			Gotoxy(x,y);
			Sleep(100);
			Gotoxy(x,y);
			if (i==4)
				i=0;
		}
		cout<<"\b  ";
	}
	template<typename T>//Note: class-> Independant Args, typename-> Dependant/Independant Args (i.e. nested templates)
	void Selection_Sort(T Arr[],const unsigned short Arr_Size){
    	for (unsigned short i=0,Min_Index=0;i<(Arr_Size-1);++i){
    	    T Min_Value=Arr[i];
    	    for(unsigned char j=i+1;j<Arr_Size;++j){
     	       if (Arr[j]<Min_Value){
        	        Min_Value=Arr[j];
        	        Min_Index=j;
        	    }
        	}
        	Arr[Min_Index]=Arr[i];
        	Arr[i]=Min_Value;
    	}
	}
	template<typename T1,typename T2>
	int Binary_Search(const T1 Arr[],const unsigned short Arr_Size,const T2 Key){//Note: Iterative Binary Sort is faster than Recursive 
    	int First=0,Last=Arr_Size-1,Mid,Pos=-1;  
    	bool Found=false;
    	while (!Found&&First<=Last){
        	Mid=(First+Last)/2;//i.e. avg. value = Mid value
        	if (Arr[Mid]==Key){
        	    Found=true;
        	    Pos=Mid;
        	}
        	else if (Arr[Mid]>Key)
           		Last=Mid-1;
        	else
            	First=Mid+1;
    	}
    	return Pos;
	}
	
	inline bool Check_Files(){ return true; }//i.e. base case condition func
	template<typename T,typename... Types>
	bool Check_Files(const T Arg1,const Types... Args){//Note: Parameter-Pack (...)-> takes multiple args
		ifstream File(Arg1);
		if(File){
			File.close();
			return Check_Files(Args...);
			/*Note: Func will recursively call variadic template based func until it recieves 
				    zero args & then, it calls base func (using overloading concept) */
		}
		return false;
	}
	
	inline void Print_Multiple_Args(){}
	template<typename T,typename... Types>
	void Print_Multiple_Args(const T Arg1,const Types... Args){ 
		cout<<Arg1;
		Print_Multiple_Args(Args...);
	}
	
	template<typename D,class L,typename T,typename... Types>//i.e. Additional Feature: overload cin>> for defined data-type in order to utilize here
	void Validate_Input(D& Dest,const L Limit,const T Arg1,const Types... Arg2){//Note: *Dest shouldn't be char or string
		while(true){
			Print_Multiple_Args(Arg1,Arg2...); //i.e. displays complete string
			cin>>Dest;
			if(Dest>0&&Dest<=Limit)
				break;
			cout<<"\a";//i.e. system sound
			cin.clear();
			fflush(stdin);
			//Note: Here, we have to use both cin.clear() & fflush(stdin) to clear buffer
		}
	}
	
	template<typename T,typename... Types>
	void Validate_Input(string& Str,const T Arg1,const Types... Arg2){//i.e. validates parse-time files strings for only Data-Type 
		string DataType_List[] {"bool","char","char16_t","char32_t","double","float","int","long","short","string","unsigned","wchar_t","__int64"};
		unsigned short DataType_Count=sizeof(DataType_List)/sizeof(DataType_List[0]);
		
		Selection_Sort(DataType_List,DataType_Count);
	Re_Enter_Str:
		system("cls");
		cout<<"\nNote: Only Data-Type Names are Acceptable!"<<endl;
		Print_Multiple_Args(Arg1,Arg2...);
		cin>>Str;
		cin.clear();
		fflush(stdin);
		if(Str.length()>20||Binary_Search(DataType_List,DataType_Count,Str)==-1){
			cout<<"\a";
			goto Re_Enter_Str;
		}
	}
	
	template<typename T,typename... Types>//i.e. validates parse-time files strings
	void Validate_Input(string& Str,const string Category_Arr[],const unsigned short Category_Count,const T Arg1,const Types... Arg2){
		string Keywords_List[] {"alignas","alignof","and","and_eq","asm","auto","bitand","bitor","bool","break","case","catch",
								"char","char16_t","char32_t","class","compl","const","constexpr","const_cast","continue","decltype",
								"default","delete","do","double","dynamic_cast","else","enum","explicit","export","extern","false",
								"float","for","friend","goto","if","inline","int","long","mutable","namespace","new","noexcept","not",
								"not_eq","nullptr","operator","or","or_eq","private","protected","public","register","reinterpret_cast",
								"return","short","signed","sizeof","static","static_assert","static_cast","struct","switch","string",
								"template","this","thread_local","throw","true","try","typedef","typeid","typename","union","unsigned",
								"using","virtual","void","volatile","wchar_t","while","xor","xor_eq","__int64"};
		
		char Strays_Arr[] {'#','!','\'','&','*','-','+','/','=',')','(','^','%','@','?','>','<',
						   '\\',']','[','{','}','.',',','|','`','~',':',';','\'','\0','\0'},
						   
			 Num_Arr[] {'0','1','2','3','4','5','6','7','8','9','\0'};
			 
		unsigned short Keyword_Count=sizeof(Keywords_List)/sizeof(Keywords_List[0]),
					   Stray_Count=sizeof(Strays_Arr)/sizeof(Strays_Arr[0]),
					   Num_Count=sizeof(Num_Arr)/sizeof(Num_Arr[0]);

			Selection_Sort(Keywords_List,Keyword_Count);
			Selection_Sort(Strays_Arr, Stray_Count);
	Re_Enter_Str:
		system("cls");
		cout<<"\nNote: Previous Category Names, C++ Keywords, Strays &, 1st Char as Int aren't Acceptable!"<<endl;
		Print_Multiple_Args(Arg1,Arg2...);
		cin>>Str;
		cin.clear();
		fflush(stdin);
		if (Str.length()>20||Binary_Search(Num_Arr,Num_Count,Str[0])!=-1||Binary_Search(Keywords_List,Keyword_Count,Str)!=-1){
			cout<<"\a";
			goto Re_Enter_Str;
		}
		for(unsigned short i=0;i<Category_Count;++i)
			if (Str==Category_Arr[i]){
				cout<<"\a";
				goto Re_Enter_Str;
			}
		for(int i=0;i<Str.length();++i)
			if(Binary_Search(Strays_Arr,Stray_Count,Str[i])!=-1){
				cout<<"\a";
				goto Re_Enter_Str;
			}
	}
}
