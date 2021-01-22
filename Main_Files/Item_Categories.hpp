//Note: Using 'override' generates warning if the func isn't overridden
class Beverages final: Items{ Beverages(){}
string Unit; unsigned short Unit_Size;
void Input_Data(istream& in)override{ cout<<"	Enter Unit: "; in>>Unit; Glbl::Validate_Input(Unit_Size,65535,"	Enter Unit Size (",Unit,"): "); }
void Display_Data(ostream& out)const override{ out<<", Unit Size: "<<Unit_Size<<" ("<<Unit<<")"; }
void Read_Files(ifstream& fin)override{ fin>>Unit_Size>>Unit; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Unit_Size<<" "<<Unit<<" # "; }
Items* Clone()const override{ return new Beverages(*this); } friend class Items_List; };
class Bakery_Items final: Items{ Bakery_Items(){}
float Weight;
void Input_Data(istream& in)override{ Glbl::Validate_Input(Weight,99999,"	Enter Weight: "); }
void Display_Data(ostream& out)const override{ out<<", Weight: "<<Weight; }
void Read_Files(ifstream& fin)override{ fin>>Weight; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Weight<<" # "; }
Items* Clone()const override{ return new Bakery_Items(*this); } friend class Items_List; };
class Baking_Items final: Items{ Baking_Items(){}

void Input_Data(istream& in)override{}
void Display_Data(ostream& out)const override{}
void Read_Files(ifstream& fin)override{}
void Write_Files(ofstream& fout)const override{ fout<<" # "; }
Items* Clone()const override{ return new Baking_Items(*this); } friend class Items_List; };
class Can_Items final: Items{ Can_Items(){}
string Quality_Grade;
void Input_Data(istream& in)override{ cout<<"	Enter Quality Grade: "; in>>Quality_Grade; }
void Display_Data(ostream& out)const override{ out<<", Quality Grade: "<<Quality_Grade; }
void Read_Files(ifstream& fin)override{ fin>>Quality_Grade; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Quality_Grade<<" # "; }
Items* Clone()const override{ return new Can_Items(*this); } friend class Items_List; };
class Dairy_Items final: Items{ Dairy_Items(){}

void Input_Data(istream& in)override{}
void Display_Data(ostream& out)const override{}
void Read_Files(ifstream& fin)override{}
void Write_Files(ofstream& fout)const override{ fout<<" # ";}
Items* Clone()const override{ return new Dairy_Items(*this); } friend class Items_List; };
class Cleaning_Items final: Items{ Cleaning_Items(){}
string Product_State;
void Input_Data(istream& in)override{ cout<<"	Enter Product State: "; in>>Product_State; }
void Display_Data(ostream& out)const override{ out<<", Product State: "<<Product_State; }
void Read_Files(ifstream& fin)override{ fin>>Product_State; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Product_State<<" # "; }
Items* Clone()const override{ return new Cleaning_Items(*this); } friend class Items_List; };
class Personal_Care_Items final: Items{ Personal_Care_Items(){}

void Input_Data(istream& in)override{}
void Display_Data(ostream& out)const override{}
void Read_Files(ifstream& fin)override{}
void Write_Files(ofstream& fout)const override{ fout<<" # "; }
Items* Clone()const override{ return new Personal_Care_Items(*this); } friend class Items_List; };
class Electronic_Items final: Items{ Electronic_Items(){}
unsigned short Warranty;
void Input_Data(istream& in)override{ cout<<"	Enter Warranty: "; in>>Warranty; }
void Display_Data(ostream& out)const override{ out<<", Warranty: "<<Warranty; }
void Read_Files(ifstream& fin)override{ fin>>Warranty; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Warranty<<" # "; }
Items* Clone()const override{ return new Electronic_Items(*this); } friend class Items_List; };
class Sports_Items final: Items{ Sports_Items(){}
string Item_Type;
void Input_Data(istream& in)override{ cout<<"	Enter Item Type: "; in>>Item_Type; }
void Display_Data(ostream& out)const override{ out<<", Item Type: "<<Item_Type; }
void Read_Files(ifstream& fin)override{ fin>>Item_Type; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Item_Type<<" # "; }
Items* Clone()const override{ return new Sports_Items(*this); } friend class Items_List; };
class Paper_Goods final: Items{ Paper_Goods(){}

void Input_Data(istream& in)override{}
void Display_Data(ostream& out)const override{}
void Read_Files(ifstream& fin)override{}
void Write_Files(ofstream& fout)const override{ fout<<" # "; }
Items* Clone()const override{ return new Paper_Goods(*this); } friend class Items_List; };
class SmartPhones final: Items{ SmartPhones(){}
string Specs; short Pin_Code; 
void Input_Data(istream& in)override{ cout<<"	Enter Specs: "; in>>Specs; Glbl::Validate_Input(Pin_Code,9999,"	Enter Pin_Code: "); }
void Display_Data(ostream& out)const override{ out<<", Specs: "<<Specs; cout<<", Pin_Code: "<<Pin_Code<<"-40404-99"; }
void Read_Files(ifstream& fin)override{ fin>>Specs>>Pin_Code; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Specs<<" "<<Pin_Code<<" # "; }
Items* Clone()const override{ return new SmartPhones(*this); } friend class Items_List; };
class Medicines final: Items{ Medicines(){}
string Dosage; 
void Input_Data(istream& in)override{ cout<<"	Enter Dosage: "; in>>Dosage; }
void Display_Data(ostream& out)const override{ out<<", Dosage: "<<Dosage; }
void Read_Files(ifstream& fin)override{ fin>>Dosage; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Dosage<<" # "; }
Items* Clone()const override{ return new Medicines(*this); } friend class Items_List; };
class Apparels final: Items{ Apparels(){}
string Garment_Type; 
void Input_Data(istream& in)override{ cout<<"	Enter Garment_Type: "; in>>Garment_Type; }
void Display_Data(ostream& out)const override{ out<<", Garment_Type: "<<Garment_Type; }
void Read_Files(ifstream& fin)override{ fin>>Garment_Type; }
void Write_Files(ofstream& fout)const override{ fout<<" "<<Garment_Type<<" # "; }
Items* Clone()const override{ return new Apparels(*this); } friend class Items_List; };
