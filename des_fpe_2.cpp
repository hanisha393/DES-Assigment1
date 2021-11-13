#include<iostream>
#include <bits/stdc++.h>
using namespace std;
int check_CCN_validity(string CCN)
{
	if (CCN.length() == 16)
	{
		long long int a=0;char ch[1];
		for(int i=0;i<CCN.length();i++)
		{
			ch[0]=CCN[i];
			if (ch[0]-'0'>9 || ch[0]-'0'<0)
			{
				cout<<"\n-------------------------------------CCN cannot have alphanumerics---------------------------------\n";
				return -1;
			}
			else
			{
		        a=a*10+atoi(ch);
			}
		}
		if (a==0) 
		{
			cout<<"\n----------------------------------------CCN cannot be all zeros----------------------------------\n";
			return -1;
		}
	}
	else
	{
		cout<<"\n---------------------------Lenght is greate than 16--------------------------------------\n";
		return -1;
	}
	return 1;
}
int convert_string_to_int(string s, int n,int m,int a)
{
	char ch[1];
	for(int i=n;i<m;i++)
	{
		ch[0]=s[i];
		a=a*10+atoi(ch);
	}
	return a;
}
string convert_int_to_string(int a)
{
	string s="";
	char ch[20];
    itoa(a,ch,10);
    s+=ch;
	return s;
}
string convert_int_to_bit_string(int a)
{
	string s="";
	char ch[100];
	itoa(a,ch,2);
	s+=ch;
	return s;
}
string shift_left(string k, int shifts)
{
    string s = "";
    for (int i = 0; i < shifts; i++) 
	{
        for (int j = 1; j < 28; j++) 
		{
            s += k[j];
        }
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}
string xor_(string a, string b)
{
    string ans = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            ans += "0";
        }
        else {
            ans += "1";
        }
    }
    return ans;
}
string permute(string k, int* arr, int n)
{
    string per = "";
    for (int i = 0; i < n; i++) {
        per += k[arr[i] - 1];
    }
    return per;
}
int convert_bit_string_to_int(string s)
{
	int a=0,count=0;
	for(int i=s.length()-1;i>=0;i--)
	{   //cout<<"\n s[i]"<<s[i];
		if (s[i] == '1')
		{
			a=a+pow(2,count);//cout<<"\t a:"<<a;
		}
		count++;
	}
	return a;
}
int function_Fk(string enc_num, vector<string> keys_list)
{
    int exp_d[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                      6, 7, 8, 9, 8, 9, 10, 11,
                      12, 13, 12, 13, 14, 15, 16, 17,
                      16, 17, 18, 19, 20, 21, 20, 21,
                      22, 23, 24, 25, 24, 25, 26, 27,
                      28, 29, 28, 29, 30, 31, 32, 1 };

    // S-box Table
    int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
                          
    int rounds=0;
    //Running loop till we get encrypted data <1000000
    while (1)
    {
    	rounds++;
	    //splitting
	    string left = enc_num.substr(0,10);
	    string right = enc_num.substr(10,10);
        string temp_str="";
	    cout<<"\n--------------------------------------------------Round0-------------------------------------------------";
	    cout<<"\n left:"<<left<<"\t right"<<right;
	    for (int i=0;i<16;i++)
	    {
		    string temp_right=right;string temp_left=left;
		
		    //appending zeros
		    temp_right+="0000000000000000000000";
		
		    //expanding 32 to 48
		    string right_exp = permute(temp_right, exp_d, 48);
		
		    //xoring right and key
		    string x = xor_(keys_list[i], right_exp);
		
		    //compressing 48 to 10
	        string op = x;string temp_storage;int temp_a=0;int temp_index=0;
	        while (op.length()>=6)
	        {
	    	    string temp_op="";temp_index=0;
                for (int i4 = 0; i4 < op.length(); i4=i4+6) 
			    {
                    int row = 2 * int(op[i4] - '0') + int(op[i4 + 5] - '0');
                    int col = 8 * int(op[i4 + 1] - '0') + 4 * int(op[i4 + 2] - '0') + 2 * int(op[i4 + 3] - '0') + int(op[i4 + 4] - '0');
                    int val = s[temp_index++][row][col];
                    temp_op += char(val / 8 + '0');
                    val = val % 8;
                    temp_op += char(val / 4 + '0');
                    val = val % 4;
                    temp_op += char(val / 2 + '0');
                    val = val % 2;
                    temp_op += char(val + '0');
                }
                if ( (temp_op.length()>6) && ((temp_op.length())%6 != 0))
                {
            	    op="";
            	    op=temp_op.substr(0,temp_op.length()-2);
            	    temp_storage+=temp_op.substr(temp_op.length()-2,2);
			    }
			    else
			    {
				    op="";op=temp_op;
			    }
            }
		    op+=temp_storage;

            //xoring with left half
            x = xor_(op, left);
            left = x;
 
            // Swapper
            if (i != 15) 
			{
                swap(left, right);
            }
            cout<<"\n---------------------------------------------Round"<<i+1<<"---------------------------------------------";
            cout<<"\nkey:"<<keys_list[i];
            cout<<"\n left:"<<left<<"\t right:"<<right;
             cout<<"\n------------------------------------------------------------------------------------------------------------";
	    }

	    string combine=left+right;
	    cout<<"\n combined string:"<<combine;
	    int final_number=convert_bit_string_to_int(combine);
	    cout<<"\n final number:"<<final_number;
	    if (final_number<1000000)
	    {
	    	cout<<"\nNo.of 16-rounded DES rounds taken to get data in range:"<<rounds;
		    return convert_bit_string_to_int(combine);
		}
    }
}
vector<string> key_generation(string key_bit_string, int keyp[], int shift_table[],int key_comp[])
{
	vector<string> keys_gen;
	cout<<"\n Main key:"<<key_bit_string;
	string key_bit_p1 = permute(key_bit_string, keyp, 56);
	// Splitting
    string left = key_bit_p1.substr(0, 28);
    string right = key_bit_p1.substr(28, 28);
    for (int i = 0; i < 16; i++) 
	{
        // Shifting
        left = shift_left(left, shift_table[i]);
        right = shift_left(right, shift_table[i]);
 
        // Combining
        string combine = left + right;
 
        // Key Compression
        string RoundKey = permute(combine, key_comp, 48);
        keys_gen.push_back(RoundKey);
    }
    return keys_gen;
}
void decryption( string CCN, vector<string> keys_list)
{
	string dec_str="";
	int dec_num=0,tweak=0;
	dec_num=convert_string_to_int(CCN,6,12,dec_num);
	tweak=convert_string_to_int(CCN,0,2,tweak);
	tweak=convert_string_to_int(CCN,3,4,tweak);
	tweak=convert_string_to_int(CCN,13,16,tweak);
	cout<<"\n number to be decrypted:"<<dec_num<<"\n tweak:"<<tweak;
	dec_str=convert_int_to_bit_string(dec_num);
    if (dec_str.length()<20)
    {
        string temp_str="";
        for(int i=0;i<20-dec_str.length();i++)
        {
        	temp_str+="0";
		}
		temp_str+=dec_str;dec_str="";
		dec_str=temp_str;
	}
	cout<<"\n number to be decrypted in bit format:"<<dec_str;
    //function_Fk
    int num=function_Fk(dec_str,keys_list);
	cout<<"\n decrypted number:"<<num;
	if(num<tweak)
	{
		num=num+1000000;
	}
	dec_str=CCN.substr(0,6);
	num=num-tweak;
	char ch[10];itoa(num,ch,10);
	for(int i=0;i<6-strlen(ch);i++) dec_str+="0";
	dec_str+=ch;dec_str+=CCN.substr(12,4);
	cout<<"\n-----------------------------------DECRYPTED CCN:"<<dec_str<<"---------------------------------------";
}
void encryption( string CCN, vector<string> keys_list)
{
	string enc_str="";
	int enc_num=0,tweak=0;
	enc_num=convert_string_to_int(CCN,6,12,enc_num);
	tweak=convert_string_to_int(CCN,0,2,tweak);
	tweak=convert_string_to_int(CCN,3,4,tweak);
	tweak=convert_string_to_int(CCN,13,16,tweak);
	cout<<"\n number to be encrypted:"<<enc_num<<"\n tweak:"<<tweak;
    enc_num+=tweak;
    if (enc_num>1000000)
    {
        enc_num=enc_num%1000000;
	}
	cout<<"\nnumber to be encrypted after adding tweak:"<<enc_num;
	enc_str=convert_int_to_bit_string(enc_num);
    if (enc_str.length()<20)
    {
        string temp_str="";
        for(int i=0;i<20-enc_str.length();i++)
        {
        	temp_str+="0";
		}
		temp_str+=enc_str;enc_str="";
		enc_str=temp_str;
	}
	cout<<"\n number to be encrypted in bit format:"<<enc_str;
    //function_Fk
    int num=function_Fk(enc_str,keys_list);
    enc_str="";
    enc_str+=CCN.substr(0,6);
    char ch[10];
    itoa(num,ch,10);
    for(int i=0;i<6-strlen(ch);i++) enc_str+="0";
    enc_str+=ch;
    enc_str+=CCN.substr(12,4);
    cout<<"\n-----------------------------------ENCRYPTED CCN:"<<enc_str<<"----------------------------------------";
}
int main()
{
	string key_bit_string= "0110011001010100011010100101011101101110010110100111001000110100",CCN="";
    int option=0;
    vector<string> keys_list;

    int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };

    int shift_table[16] = { 1, 1, 2, 2,
                            2, 2, 2, 2,
                            1, 2, 2, 2,
                            2, 2, 2, 1 };

    // Key- Compression Table
    int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };

    cout <<"Select an option \n 1.Encrypt CCN 2.Decrypt CCN";cin>>option;
    if (option ==1)
    {
    	cout<<"enter CCN to encrypt";
	}
	else if (option ==2)
	{
		cout<<"enter CCN to decrypt";
	}
	else
	{
		cout<<"invalid option";return -1;
	}
	cin>>CCN;
    if (check_CCN_validity(CCN) == -1)
    {
    	cout<<"\n------------------------------Invalid CCN number------------------------------";
    	return -1;
	}
    //Key_generation
    keys_list= key_generation(key_bit_string,keyp,shift_table,key_comp);

    cout<<"\n Entered CCN:"<<CCN;
    if (option ==1)
    {
        encryption(CCN,keys_list);
	}
	else
	{
		reverse(keys_list.begin(), keys_list.end());
		decryption(CCN,keys_list);
	}
}
