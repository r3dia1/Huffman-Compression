//Author:B083040021 嚴宇同
//Date:2020/12/20
//Purpose:以Huffman 演算法製作一個檔案壓縮與解壓縮之軟體
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include <iomanip>
using namespace std;

class node{
	public:
		node(){amount=0;left=NULL;right=NULL;};
		unsigned char letter;
		int amount;
		node *left;
		node *right;
};

//尋找subtree裡最小之ascii的node 
int min_search(node *target){
	node *temp2;
	temp2=target;
	while(temp2->left!=NULL)//一直往左邊找直到遇到最小nde 
	{
		temp2=temp2->left;
		//cout << &temp2;
	}
	int re=(int)temp2->letter;//此subtree裡最小ㄉletter的ascii
	return re;//回傳
}

//recursive function
//用recursive的方式尋訪所有leaf node並且為他們編碼+存起來 
void recursive(node *huffman, vector<vector<int> > &ascii_array, vector<int> &code){
	if(huffman->left!=NULL && huffman->right!=NULL)
	{
		code.push_back(0);
		recursive(huffman->left, ascii_array, code);//往左找 
		code.push_back(1);
		recursive(huffman->right, ascii_array, code);//往右找 
		code.pop_back();
	}
	else//如果遇到leafnode 
	{
		int num,num1;//ascii之int形式 
		num=(int)huffman->letter;
		//cout << num << "\n";
		int i;
		for(i=0;i<code.size();i++)
		{
			num1=code[i];
			ascii_array[num].push_back(num1);//存取字元編碼 
		}
		code.pop_back();
		return;
	}
}

int main(int argc, char* argv[]){
	fstream file;
	file.open(argv[3], ios::in | ios::binary);//binary開檔 
	//cout << argv[1] << endl;
	char press[2]={'-','c'};
	char unpress[2]={'-','u'};
	if(argv[1][1]=='c')
	{
		vector<node> huffman;//class node的vector用來記錄所有字母 
		node temp;
		int i,j;
		int find=0;//判斷該node是否存在 
		char input;
		unsigned char input1;
		vector<unsigned char> array;//origin檔案的字元陣列 
		//讀取一串未sorted之huffman陣列 
		while(!file.eof()){
			file.get(input);//讀取字元 
			//cout << (int)input <<endl;
			input1=input;
			//cout << (int) input1 << "\n";
			array.push_back(input1);//一個一個存進陣列 
			if(file.fail())//若讀檔失敗則停止 
				break;
			for(i=0;i<huffman.size();i++)//計算該字母出現在檔案幾次 
			{
				if(huffman[i].letter==input1)
				{
					huffman[i].amount++;
					find=1;
				}
			}
			
			if(find==0)//若 huffman vector裡還沒有該字母 
			{
				temp.amount=1;//則創造一個node並且push進huffman vector 
				temp.letter=input;
				huffman.push_back(temp);
			}
			else
			{
				find=0;//find變數歸零 
			}
		}
		file.close();
		/*for(i=0;i<huffman.size();i++)
		{
			cout << huffman[i].amount << endl;
		}*/
		//cout << huffman.size();
		
		//開始construct huffman前先按照順序sort
		//先把順序排好處理資料會比較方便 
		//1.依照amount
		//bubble sort
		for(j=0;j<huffman.size();j++)
		{
			for(i=0;i<huffman.size()-1;i++)
			{
				if(huffman[i].amount>huffman[i+1].amount)
				{
					temp=huffman[i];
					huffman[i]=huffman[i+1];
					huffman[i+1]=temp;
				}
			}
		}
		/*for(i=0;i<huffman.size();i++)
		{
			cout << " " << (int)huffman[i].letter << " " << huffman[i].amount << endl;
		}*/
		//2.依照ascii
		int first=0, end=0;//擁有相同資料量之陣列頭尾index 
		while(end<huffman.size())
		{
			//一段一段作檢查，EX:數量為1的一起檢查，接著為數量2，以此類推 
			while(huffman[end].amount==huffman[end+1].amount)
			{
				end++;
			}
			
			if(first==end)
			{
				first++;
				end++;
			}
			else
			{
				//bubble sorting
				for(j=first;j<end;j++)
				{
					for(i=first;i<end;i++)
					{
						if(huffman[i].letter>huffman[i+1].letter)
						{
							temp=huffman[i];
							huffman[i]=huffman[i+1];
							huffman[i+1]=temp;
						}
					}
				}
				
				end++;
				first=end;
			}
			//cout << endl;
		} 
		/*for(i=0;i<huffman.size();i++)
		{
			cout << " " << (int)huffman[i].letter << " " << huffman[i].amount << endl;
		}*/
		
		
		//Construct HuffmanTree
		//Rules 
		//1.製作Huffman tree時，左子樹為0、右子樹為1
		//2.每次合併兩個node時，請將字典順序較小的node設為左子樹，字典順序較大者設為右子樹(比較他們最小的符號，即可知道順序)。
		//3.若超過兩個node出現相同頻率時，則先合併字典順序上最小的兩個node。
		int sum;
		int insert;//插入位置 
		while(huffman.size()!=1)//當huffman長度>1時，代表還沒完成建構 
		{
			i=0;
			node temp1;//先設立一個等待push進huffman tree裡的node 
			temp1.amount=huffman[0].amount+huffman[1].amount;//賦予其數量(根據rule3) 
			//cout << temp1.amount << endl;
			
			//根據rule2做判斷 
			if(min_search(&huffman[0]) < min_search(&huffman[1]))//若index0擁有比較小的ascii node
			{
				node *L,*R;//宣告L R node pointer來存取index 0 index1的node
				//否則會有記憶體存取問題 
				L= new node;
				R= new node;
				L->letter=huffman[0].letter;
				R->letter=huffman[1].letter;
				L->amount=huffman[0].amount;
				R->amount=huffman[1].amount;
				L->left=huffman[0].left;
				L->right=huffman[0].right;
				R->left=huffman[1].left;
				R->right=huffman[1].right;
				temp1.left=L;//把temp的left指標存L 
				//cout << (int)temp1.left->letter << " "<< temp1.left->amount << "\n";
				//cout << &(temp1.left->left) <<"\n";		
				temp1.right=R;//把temp的right指標存R 
				/*if(temp1.amount==7)
				cout << temp1.right->left->left->amount << "\n";*/
				//cout << (int)temp1.right->letter << " "<< temp1.right->amount << endl;
			}
			else//若index0擁有比較大的ascii node
			{
				node *L,*R;
				L= new node;
				R= new node;
				L->letter=huffman[0].letter;
				R->letter=huffman[1].letter;
				L->amount=huffman[0].amount;
				R->amount=huffman[1].amount;
				L->left=huffman[0].left;
				L->right=huffman[0].right;
				R->left=huffman[1].left;
				R->right=huffman[1].right;
				temp1.right=L;//把temp的right指標存L
				//cout << (int)temp1.right->letter << " "<< temp1.right->amount << "\n";
				temp1.left=R;//把temp的left指標存R 
				//cout << (int)temp1.left->letter << " "<< temp1.left->amount << "\n";
			}
			
			huffman.erase(huffman.begin(),huffman.begin()+2);//刪除index0 index1的node 
			//cout << huffman[0].amount <<"\n";
			
			//cout << temp1.amount << endl;
			while(huffman[i].amount<temp1.amount && i<huffman.size())//尋找node temp應該要放入的位置 
			{
				i++;
			}
			//cout << temp1.amount << endl;
			huffman.insert(huffman.begin()+i,temp1);//把tnode temp放入huffman tree 
			//cout << huffman[0].left->amount << endl;
			/*for(i=0;i<huffman.size();i++)
			{
				cout << huffman[i].amount << "\n";
			}*/
		}
		//cout << huffman[0].left->amount << endl;
		
		//編碼recursive
		vector<vector<int> > ascii_array;//編碼存放陣列(二維vector) 
		vector<int> code;//用來暫存編碼 
		ascii_array.resize(260);//給予ascii_array大小 
		
		recursive(&huffman[0],ascii_array,code);//進行編碼(創造table) 
		/*for(i=0;i<260;i++)
		{
			if(ascii_array[i].size()>0)
			{
				cout << (char)i << " ";
				for(int j=0;j<ascii_array[i].size();j++)
				{
					cout << ascii_array[i][j];
				}
				cout << endl;
			}
		}*/
		
		//輸出壓縮檔
		fstream file1;
		file1.open(argv[5],ios::out|ios::binary);
		int output_bytes=0;//輸出壓縮檔大小 
		//Header內容
		//原始檔案位元組數
		file1 << "Origin:" << array.size()-1 << "bytes\n";
		int count=0;//用來推測壓縮後檔案之變數1 
		int amount=array.size();//用來推測壓縮後檔案之變數2
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		output_bytes=count+13;
		
		//計算table 輸出byte數 
		amount=0;
		count=0;
		for(i=0;i<260;i++)
		{
			if(ascii_array[i].size()>0)
			{
				count=count+3;//字母 空格 換行 
				for(j=0;j<ascii_array[i].size();j++)
				{
					count++;//編碼數 
				}
				amount++;//table數量 
			}
		}
		int table_amount=amount;
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		count++;//換行
		output_bytes=output_bytes+count;
		
		
		//編碼內容 
		vector<int> pressed_code;//壓縮檔案後之二元編碼 
		int search_index;//判斷要取哪個字母的編碼 
		for(i=0;i<array.size()-1;i++)
		{
			search_index=(int)array[i];
			for(j=0;j<ascii_array[search_index].size();j++)
			{
				pressed_code.push_back(ascii_array[search_index][j]);//把原始檔案換成編碼 
			}
		}
		
		//計算壓縮後編碼輸出bytes 
		count=0;
		amount=0;
		if(pressed_code.size()%8==0)
		{
			count=pressed_code.size()/8;
		}
		else
		{
			count=pressed_code.size()/8+1;
		}
		amount=array.size()-1;
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		output_bytes=output_bytes+count;
		
		
		//計算壓縮後文字輸出bytes
		count=0;
		amount=0;
		output_bytes=output_bytes+12;//壓縮率文字 
		output_bytes=output_bytes+12;//輸出文字
		amount=output_bytes;
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		file1 << "After:" << output_bytes+count << "bytes\n";
		
		//印出壓縮率
		float percentage=(array.size()-1)/(float)(output_bytes+count);//計算壓縮率 
		//cout << array.size()-1 << " " << (float)(output_bytes+count) << " " << setprecision(3) << percentage << endl;
		file1 << "ratio:" << setprecision(3) << percentage  << "\n";
		
		//印出table
		file1 <<  table_amount << endl;
		for(i=0;i<260;i++)
		{
			if(ascii_array[i].size()>0)
			{
				file1 << (char)i << " " ;
				for(j=0;j<ascii_array[i].size();j++)
				{
					file1 << ascii_array[i][j];
				}
				file1 <<  "\n";
			}
		}
		
		
		//輸出編碼 
		int tempc;
		int output;
		file1 << array.size()-1 << endl;
		/*for(i=0;i<pressed_code.size();i++)
		{
			cout << pressed_code[i];
		}*/
		int test=0;
		for(i=0;i<pressed_code.size();i+=8)
		{
			for(j=0;j<8;j++)//讀取到8個便輸出 
			{
				if(i+j>=pressed_code.size())
				{
					tempc=0;
				}
				else{
					if(pressed_code[i+j]==0)
					{
						tempc=0;
					}
					else
					{
						tempc=1;
					}
				}
				output+=tempc<<(7-j);//把數字0和1座左平移後相加 
			}
			test++;
			//cout << "test="<< test <<endl;
			//cout << "out="<< output << endl;
			file1.write( (char*) &output, sizeof(char));//輸出編碼字元 
			output=0;//reset output
		}
		file1.close();//關檔案 
	}
	else if(argv[1][1]=='u')//解壓縮 
	{
		string useless[3];//讀取無用header 
		vector<string> ascii;//存取table之vector 
		int i;//迴圈變數 
		for(i=0;i<3;i++)
		{
			getline(file,useless[i]);
			//cout << useless[i] <<endl;
		}
		int num,index;//num為table數量 
		char letter;
		file >> num;//table數 
		//cout << num;
		//讀取table 
		vector<char> table_letter;
		string get;
		for(i=0;i<num;i++)//一一讀取table，並放入table)letter裡 
		{
			file >> letter;
			table_letter.push_back(letter);
			//file >> letter;
			getline(file,get);
			get.erase(0,1);//空白不取用 
			ascii.push_back(get);
			//cout << get << endl;
		}
		
		int origin_data_number;//原始檔案數量 
		file >> origin_data_number;
		//cout << origin_data_number << endl;
		
		//讀取壓縮後資料
		int count=0;//計算資料是否輸出完畢
		int count8=0;//計算是否有8bit 
		string target;//最終的01型態字串 
		int num2;//(int)letter 
		int re;//餘數 
		char letter2;
		int test1=0;
		file.get(letter2);
		while(!file.eof())
		{
			count8=0;
			vector<int> transform;
			file.get(letter);//讀取字元(包括換行符) 
			if(letter==letter2)//避免file.eof()多做一次 
				break;
			letter2=letter;
			unsigned char letter1;
			letter1=letter;
			num2=(int)letter1;
			//cout << num2 <<endl;
			while(num2!=0 && num2!=1)//做二進位轉十進位
			{
				re=num2%2;
				//cout << re <<endl;
				num2=num2/2;
				transform.push_back(re);
				count8++;
			}
			//cout << "end "<< num2 <<endl;
			transform.push_back(num2);
			
			char transform1[8];
			for(i=7;i>=0;i--)//把1010等的陣列換成string型態，以便後續還原檔案需要做比較 
			{
				if(count8!=7)
				{
					transform1[7-i]='0';
					count8++;
					//cout <<"@@" << endl;
				}
				else
				{
					transform1[7-i]=(char)(transform[i]+48);//轉成01字元 
				}				
			}
			
			string temp(transform1,transform1+8);//建立讀取字元之01字串 
			test1++;
			//cout << "test1=" << test1 <<endl;
			//cout << temp << endl;
			target+=temp;//把字串做相加 
		} 
		//cout << target <<endl;
		
		//還原檔案 
		fstream refile;
		refile.open(argv[5],ios::out|ios::binary);
		int check=1;//檢查編碼為哪個letter之index 
		count=0;
		int success=0; 
		while(count<origin_data_number)//當輸出個數=原始檔案則停止 
		{
			//string test(target[0],target[0]+check);
			//cout << test << endl;
			for(i=0;i<num;i++)//跑整個table的迴圈 
			{
				//cout << target.substr(0,check) << endl;
				if(target.substr(0,check)==ascii[i])//比較字串是否相符合，若符合則輸出 
				{
					refile << table_letter[i];
					target.erase(0,check);//刪除已經輸出之編碼字串 
					//cout << target << endl;
					count++;
					success=1; 
					break;
				}
			}
			if(success==1) 
			{
				check=1; 
				success=0;
			}
			else
			{
				check++;
			}
		}
		refile.close();	 
	}
	
	
}
