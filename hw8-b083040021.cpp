//Author:B083040021 �Y�t�P
//Date:2020/12/20
//Purpose:�HHuffman �t��k�s�@�@���ɮ����Y�P�����Y���n��
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

//�M��subtree�̳̤p��ascii��node 
int min_search(node *target){
	node *temp2;
	temp2=target;
	while(temp2->left!=NULL)//�@��������䪽��J��̤pnde 
	{
		temp2=temp2->left;
		//cout << &temp2;
	}
	int re=(int)temp2->letter;//��subtree�̳̤p�xletter��ascii
	return re;//�^��
}

//recursive function
//��recursive���覡�M�X�Ҧ�leaf node�åB���L�̽s�X+�s�_�� 
void recursive(node *huffman, vector<vector<int> > &ascii_array, vector<int> &code){
	if(huffman->left!=NULL && huffman->right!=NULL)
	{
		code.push_back(0);
		recursive(huffman->left, ascii_array, code);//������ 
		code.push_back(1);
		recursive(huffman->right, ascii_array, code);//���k�� 
		code.pop_back();
	}
	else//�p�G�J��leafnode 
	{
		int num,num1;//ascii��int�Φ� 
		num=(int)huffman->letter;
		//cout << num << "\n";
		int i;
		for(i=0;i<code.size();i++)
		{
			num1=code[i];
			ascii_array[num].push_back(num1);//�s���r���s�X 
		}
		code.pop_back();
		return;
	}
}

int main(int argc, char* argv[]){
	fstream file;
	file.open(argv[3], ios::in | ios::binary);//binary�}�� 
	//cout << argv[1] << endl;
	char press[2]={'-','c'};
	char unpress[2]={'-','u'};
	if(argv[1][1]=='c')
	{
		vector<node> huffman;//class node��vector�ΨӰO���Ҧ��r�� 
		node temp;
		int i,j;
		int find=0;//�P�_��node�O�_�s�b 
		char input;
		unsigned char input1;
		vector<unsigned char> array;//origin�ɮת��r���}�C 
		//Ū���@�ꥼsorted��huffman�}�C 
		while(!file.eof()){
			file.get(input);//Ū���r�� 
			//cout << (int)input <<endl;
			input1=input;
			//cout << (int) input1 << "\n";
			array.push_back(input1);//�@�Ӥ@�Ӧs�i�}�C 
			if(file.fail())//�YŪ�ɥ��ѫh���� 
				break;
			for(i=0;i<huffman.size();i++)//�p��Ӧr���X�{�b�ɮ״X�� 
			{
				if(huffman[i].letter==input1)
				{
					huffman[i].amount++;
					find=1;
				}
			}
			
			if(find==0)//�Y huffman vector���٨S���Ӧr�� 
			{
				temp.amount=1;//�h�гy�@��node�åBpush�ihuffman vector 
				temp.letter=input;
				huffman.push_back(temp);
			}
			else
			{
				find=0;//find�ܼ��k�s 
			}
		}
		file.close();
		/*for(i=0;i<huffman.size();i++)
		{
			cout << huffman[i].amount << endl;
		}*/
		//cout << huffman.size();
		
		//�}�lconstruct huffman�e�����Ӷ���sort
		//���ⶶ�ǱƦn�B�z��Ʒ|�����K 
		//1.�̷�amount
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
		//2.�̷�ascii
		int first=0, end=0;//�֦��ۦP��ƶq���}�C�Y��index 
		while(end<huffman.size())
		{
			//�@�q�@�q�@�ˬd�AEX:�ƶq��1���@�_�ˬd�A���۬��ƶq2�A�H������ 
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
		//1.�s�@Huffman tree�ɡA���l��0�B�k�l��1
		//2.�C���X�֨��node�ɡA�бN�r�嶶�Ǹ��p��node�]�����l��A�r�嶶�Ǹ��j�̳]���k�l��(����L�̳̤p���Ÿ��A�Y�i���D����)�C
		//3.�Y�W�L���node�X�{�ۦP�W�v�ɡA�h���X�֦r�嶶�ǤW�̤p�����node�C
		int sum;
		int insert;//���J��m 
		while(huffman.size()!=1)//��huffman����>1�ɡA�N���٨S�����غc 
		{
			i=0;
			node temp1;//���]�ߤ@�ӵ���push�ihuffman tree�̪�node 
			temp1.amount=huffman[0].amount+huffman[1].amount;//�ᤩ��ƶq(�ھ�rule3) 
			//cout << temp1.amount << endl;
			
			//�ھ�rule2���P�_ 
			if(min_search(&huffman[0]) < min_search(&huffman[1]))//�Yindex0�֦�����p��ascii node
			{
				node *L,*R;//�ŧiL R node pointer�Ӧs��index 0 index1��node
				//�_�h�|���O����s�����D 
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
				temp1.left=L;//��temp��left���ЦsL 
				//cout << (int)temp1.left->letter << " "<< temp1.left->amount << "\n";
				//cout << &(temp1.left->left) <<"\n";		
				temp1.right=R;//��temp��right���ЦsR 
				/*if(temp1.amount==7)
				cout << temp1.right->left->left->amount << "\n";*/
				//cout << (int)temp1.right->letter << " "<< temp1.right->amount << endl;
			}
			else//�Yindex0�֦�����j��ascii node
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
				temp1.right=L;//��temp��right���ЦsL
				//cout << (int)temp1.right->letter << " "<< temp1.right->amount << "\n";
				temp1.left=R;//��temp��left���ЦsR 
				//cout << (int)temp1.left->letter << " "<< temp1.left->amount << "\n";
			}
			
			huffman.erase(huffman.begin(),huffman.begin()+2);//�R��index0 index1��node 
			//cout << huffman[0].amount <<"\n";
			
			//cout << temp1.amount << endl;
			while(huffman[i].amount<temp1.amount && i<huffman.size())//�M��node temp���ӭn��J����m 
			{
				i++;
			}
			//cout << temp1.amount << endl;
			huffman.insert(huffman.begin()+i,temp1);//��tnode temp��Jhuffman tree 
			//cout << huffman[0].left->amount << endl;
			/*for(i=0;i<huffman.size();i++)
			{
				cout << huffman[i].amount << "\n";
			}*/
		}
		//cout << huffman[0].left->amount << endl;
		
		//�s�Xrecursive
		vector<vector<int> > ascii_array;//�s�X�s��}�C(�G��vector) 
		vector<int> code;//�ΨӼȦs�s�X 
		ascii_array.resize(260);//����ascii_array�j�p 
		
		recursive(&huffman[0],ascii_array,code);//�i��s�X(�гytable) 
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
		
		//��X���Y��
		fstream file1;
		file1.open(argv[5],ios::out|ios::binary);
		int output_bytes=0;//��X���Y�ɤj�p 
		//Header���e
		//��l�ɮצ줸�ռ�
		file1 << "Origin:" << array.size()-1 << "bytes\n";
		int count=0;//�Ψӱ������Y���ɮפ��ܼ�1 
		int amount=array.size();//�Ψӱ������Y���ɮפ��ܼ�2
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		output_bytes=count+13;
		
		//�p��table ��Xbyte�� 
		amount=0;
		count=0;
		for(i=0;i<260;i++)
		{
			if(ascii_array[i].size()>0)
			{
				count=count+3;//�r�� �Ů� ���� 
				for(j=0;j<ascii_array[i].size();j++)
				{
					count++;//�s�X�� 
				}
				amount++;//table�ƶq 
			}
		}
		int table_amount=amount;
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		count++;//����
		output_bytes=output_bytes+count;
		
		
		//�s�X���e 
		vector<int> pressed_code;//���Y�ɮ׫ᤧ�G���s�X 
		int search_index;//�P�_�n�����Ӧr�����s�X 
		for(i=0;i<array.size()-1;i++)
		{
			search_index=(int)array[i];
			for(j=0;j<ascii_array[search_index].size();j++)
			{
				pressed_code.push_back(ascii_array[search_index][j]);//���l�ɮ״����s�X 
			}
		}
		
		//�p�����Y��s�X��Xbytes 
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
		
		
		//�p�����Y���r��Xbytes
		count=0;
		amount=0;
		output_bytes=output_bytes+12;//���Y�v��r 
		output_bytes=output_bytes+12;//��X��r
		amount=output_bytes;
		while(amount!=0)
		{
			amount=amount/10;
			count++;
		}
		file1 << "After:" << output_bytes+count << "bytes\n";
		
		//�L�X���Y�v
		float percentage=(array.size()-1)/(float)(output_bytes+count);//�p�����Y�v 
		//cout << array.size()-1 << " " << (float)(output_bytes+count) << " " << setprecision(3) << percentage << endl;
		file1 << "ratio:" << setprecision(3) << percentage  << "\n";
		
		//�L�Xtable
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
		
		
		//��X�s�X 
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
			for(j=0;j<8;j++)//Ū����8�ӫK��X 
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
				output+=tempc<<(7-j);//��Ʀr0�M1�y��������ۥ[ 
			}
			test++;
			//cout << "test="<< test <<endl;
			//cout << "out="<< output << endl;
			file1.write( (char*) &output, sizeof(char));//��X�s�X�r�� 
			output=0;//reset output
		}
		file1.close();//���ɮ� 
	}
	else if(argv[1][1]=='u')//�����Y 
	{
		string useless[3];//Ū���L��header 
		vector<string> ascii;//�s��table��vector 
		int i;//�j���ܼ� 
		for(i=0;i<3;i++)
		{
			getline(file,useless[i]);
			//cout << useless[i] <<endl;
		}
		int num,index;//num��table�ƶq 
		char letter;
		file >> num;//table�� 
		//cout << num;
		//Ū��table 
		vector<char> table_letter;
		string get;
		for(i=0;i<num;i++)//�@�@Ū��table�A�é�Jtable)letter�� 
		{
			file >> letter;
			table_letter.push_back(letter);
			//file >> letter;
			getline(file,get);
			get.erase(0,1);//�ťդ����� 
			ascii.push_back(get);
			//cout << get << endl;
		}
		
		int origin_data_number;//��l�ɮ׼ƶq 
		file >> origin_data_number;
		//cout << origin_data_number << endl;
		
		//Ū�����Y����
		int count=0;//�p���ƬO�_��X����
		int count8=0;//�p��O�_��8bit 
		string target;//�̲ת�01���A�r�� 
		int num2;//(int)letter 
		int re;//�l�� 
		char letter2;
		int test1=0;
		file.get(letter2);
		while(!file.eof())
		{
			count8=0;
			vector<int> transform;
			file.get(letter);//Ū���r��(�]�A�����) 
			if(letter==letter2)//�קKfile.eof()�h���@�� 
				break;
			letter2=letter;
			unsigned char letter1;
			letter1=letter;
			num2=(int)letter1;
			//cout << num2 <<endl;
			while(num2!=0 && num2!=1)//���G�i����Q�i��
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
			for(i=7;i>=0;i--)//��1010�����}�C����string���A�A�H�K�����٭��ɮ׻ݭn����� 
			{
				if(count8!=7)
				{
					transform1[7-i]='0';
					count8++;
					//cout <<"@@" << endl;
				}
				else
				{
					transform1[7-i]=(char)(transform[i]+48);//�ন01�r�� 
				}				
			}
			
			string temp(transform1,transform1+8);//�إ�Ū���r����01�r�� 
			test1++;
			//cout << "test1=" << test1 <<endl;
			//cout << temp << endl;
			target+=temp;//��r�갵�ۥ[ 
		} 
		//cout << target <<endl;
		
		//�٭��ɮ� 
		fstream refile;
		refile.open(argv[5],ios::out|ios::binary);
		int check=1;//�ˬd�s�X������letter��index 
		count=0;
		int success=0; 
		while(count<origin_data_number)//���X�Ӽ�=��l�ɮ׫h���� 
		{
			//string test(target[0],target[0]+check);
			//cout << test << endl;
			for(i=0;i<num;i++)//�]���table���j�� 
			{
				//cout << target.substr(0,check) << endl;
				if(target.substr(0,check)==ascii[i])//����r��O�_�۲ŦX�A�Y�ŦX�h��X 
				{
					refile << table_letter[i];
					target.erase(0,check);//�R���w�g��X���s�X�r�� 
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
