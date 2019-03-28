#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>



using namespace std;

int islogin = 0; // Set to 1 if admin login succeed;

int account = 10101; // Must be loaded only once!

int olddeposit; //
int newdeposit; // Used in deposit function. Recording account's deposit.

int objold; //
int objnew; // Used in transfer funtion. Recording recieved account's deposit.

int realaccount; //Used in data changing funciton. A vector-friendly format.
int recieveaccount; // Account which recieving transferd money, used in tranfer funciton.;

int iscancle = 0; // Initilizing to 0 after each function used.

int islegalstate = 0; // Initilizing to 0 after each function used.

int islegalaccount = 0; // Initilizing to 0 after each function used.

int oldstate; //
int newstate; // Used in state replace funtion, recording account state.

string newpass; //
string oldpass; // Used in password replace function.

string adminpath = "C:\\bank\\admin.txt";
string userinfopath = "C:\\bank\\Userinfo.txt";

char option[2];


struct User_Info{
	int account;
	string name;
	string password;
	string id;
	int balance = 0;
	int isnormal = 0;				// 0 for normal. 1 for loss. 2 for cancled.
};


string itos(int i)
{
			stringstream s;
			s << i;
			return s.str();
		};

class System_Login{

		public:
		void AdminLogin(int &islogin)
		{
			int lefttry = 3;
			int temp;
			int inputpasswordcount = 0;

			string pass;
			char password[20] = {0} ;
			char inputpassword[20] = {0};
			int ispass = 0;

			string inputuname;
			string uname;
			char username[20] = {0};
			char inputusername[20] = {0};
			int isuname = 0;

			char readusername[20] = {0};
			char readpassword[20] = {0};


			ifstream fin(adminpath, ios::in);
			ofstream fout(adminpath, ios::app);
			ifstream finu(adminpath, ios::in);

			while(lefttry && (islogin != 1))
		 {
			cout << endl << "Enter Username: ";
			getline(cin, inputuname);

			strcpy(inputusername, inputuname.c_str());
			int unamecount = 0;
			for(int i = 0; i < 20; i++)
			{
				if((inputusername[i] >= 'a' && inputusername[i] <= 'z') || (inputusername[i] >= 'A' && inputusername[i] <= 'Z') || (inputusername[i] >= '0' && inputusername[i] <= '9'))
				{
					unamecount++;
				}
				else ;
			}
			cout << endl << "Enter Password: ";
			for(int i = 0; i < 19; i++)
				{
					temp = getch();
					if (temp == '\r' || temp == EOF){
						break;
					}
					inputpassword[inputpasswordcount] = temp;
					inputpasswordcount++;
					cout << "*";
				};
				inputpassword[20] = {0};
				inputpasswordcount = 0;
				fflush(stdin);
			int passcount = 1;
			for(int i = 0; i < 20; i++)
			{
				if (inputpassword[i] >= '0' && inputpassword[i] <='9')
					{
						passcount++;
					}
					else ;
			}


			if(lefttry == 3)
			{
				while(getline(finu, uname))

				{
					strcpy(username, uname.c_str());


					if(username[0] == 'U')
					{

					 for(int i = 0; i < 19; i++)
					{
						readusername[i] = username[i];
					};

						for(int i = 9; i < 9 + unamecount; i++)
						{

							if(readusername[i] == inputusername[i-9])
							{
								isuname = 1;
							}

							else
								{
									isuname = 0;
									break;
								};
						};
					};
				};

			}
			else{
				for(int i = 0; i < 10; i++)
				{
					if(readusername[i+9] == inputusername[i])
						isuname = 1;
						else
							{
								isuname = 0;
								break;
							}
				};
			};
			if(lefttry == 3)
			{
				while(getline(fin, pass))
				{
					strcpy(password, pass.c_str());

					if(password[0] == 'P')
					{
						for(int i = 0; i < 19; i++)
						{
							readpassword[i] = password[i];
						};

					 for(int i = 9; i < 9 + passcount; i++)
						{
							if(readpassword[i] == inputpassword[i-9])
							{
								ispass = 1;
							}

							else
								{
									ispass = 0;
									break;
								};
						};
					};
				};
			}
			else{
				for(int i = 0; i < 10; i++)
				{
					if(readpassword[i+9] == inputpassword[i])
						ispass = 1;
						else
							{
								ispass = 0;
								break;
							}
				};
			};
				if((isuname == 1) && (ispass == 1))
				{
					cout << endl << "Login Successed!" << endl << endl;
					islogin = 1;
				}
				else{
					lefttry--;
					if(lefttry > 0)
					{
						cout << endl << "Incorrect Username or Password! " << endl
							<< endl << "You have " << lefttry << " time(s) to try." << endl;
						cout << "_____________________________________";
					}
					else{
						cout << "Incorrect Username or Password! " << endl
							<< "Login Failed, Programm Exit." << endl ;
					};
				};
		 };
	fout.close();
		};

};


class System_Menu{

public:
	int state;

	void Get_Feature(int state, char(& option)[2])
	{
		int isvalid = 0;
		if(state)
		{
			cout <<"Account state: Logged in" <<endl <<endl;
			cout <<"_______MAIN MENU________" << endl << endl ;
			cout <<"01. NEW ACCOUNT"<< endl << endl              //
				 <<"02. CANLE AN ACCOUNT"<< endl<< endl          //
				 <<"03. DEPOSIT"<< endl<< endl  				 //
				 <<"04. WITHDRAW"<< endl<< endl  				 //
				 <<"05. QUERY"<< endl<< endl  					 //
				 <<"06. TRANSFER"<< endl<< endl  				 //
				 <<"07. LOSS REGISTRATION"<< endl<< endl  		 //
				 <<"08. HANGING SOLUTION"<< endl<< endl  		 //
				 <<"09. CHANGE PASSWORD"<< endl<< endl  		 // ALL GOOD :)
				 <<"00. EXIT"<<endl  ;

			do{
			cout << endl << "Select Your Options <0-9>: ";
			cin >> option;
			if((option[0] >= '0' && option[0] <= '9') && option[1] == '\0')
				{
					isvalid = 1;

				}
				else{
					cout << endl << "Invalid Order!";
					isvalid = 0;
					}

			}while(!isvalid);

		}

	}
};


int CheackAccountLegal(int inputaccount)
{
	if(inputaccount >= 10101 && inputaccount <= account - 1)
		return 1;
		else return 0;
}


void Newaccount(vector<User_Info> (&a), int &account){

		User_Info temp;

		string temppass1 = "1";
		string temppass2 = "2";

		temp.account = account;

		cout << endl << "***CREATING NEW ACCOUNT***" << endl;

		cout <<endl << "Enter Account Name: ";
		cin >> temp.name;

		while(temppass1 != temppass2)
		{
			cout << endl << "Enter Account Password: ";
			cin >> temppass1;

			cout << endl << "Confirm Account Password: ";
			cin >> temppass2;

			if(temppass1 == temppass2)
				{
					temp.password = temppass1;
					break;
				}
				else
					{
						cout << endl << "The Password You Input Was Different!" << endl << "Please Try Again!" << endl;
						continue;
					}

		}

		cout << endl << "Enter Account IDcard Number: ";
		cin >> temp.id;

		cout << endl << "Enter How Much To Deposit: ";
		cin >> temp.balance;


		a.push_back(temp);

		ifstream finn(userinfopath, ios::in);
		ofstream foutn(userinfopath, ios::app);

		int currentaccount = account - 10101;

		foutn << a[currentaccount].account << "    " << a[currentaccount].name << "    " << a[currentaccount].password
		<< "    " << a[currentaccount].id << "    " << a[currentaccount].balance << "    " << a[currentaccount].isnormal << endl;

		account += 1;

		cout << endl << "***ACCOUNT CREATED SUCCEED!***" << endl;

		foutn.close();



	}


int BackToMenu()
{
	char LastOption ;
	while(1)
	{
		cout << endl << "Enter" << " M " << "To Back To Menu." << endl ;

	cin >> LastOption;
	  if((LastOption == 'M') || (LastOption == 'm'))
		{
			break;
			return 1;
		};
	};

}


int GetRealAccount(int account)   //Return a easy to identified account name, if used in vector keeps it be subtracted "1".
{
		int temp = 0;
		temp = account - 10100;
		return temp;
	}


void Query(vector<User_Info> (&a))
{
	int inputaccount;
	int realaccount;
	cout << endl << "Enter The Account You Want To Query: ";
	cin >> inputaccount;
	if(CheackAccountLegal(inputaccount))
	{
		realaccount = GetRealAccount(inputaccount);
		if(a[realaccount-1].isnormal != 2)
		{
			cout << endl << "Account: " << inputaccount
				 << endl << endl << "Name: "  << a[realaccount-1].name
				 << endl << endl << "Passward: "  << a[realaccount-1].password
				 << endl << endl << "Balance: "  << a[realaccount-1].balance
				 << endl << endl << "ID: "  << a[realaccount-1].id
				 << endl << endl << "State: ";
			if(a[realaccount-1].isnormal == 0)
			{
				cout << "Normal" << endl ;
			}
			else
			{
				cout << "Reported Lossing" << endl ;
			};

		}
		else{
			cout << endl << "Unavialuable User Data!" << endl << endl
						 << "Account Has Been Cancled!" << endl ;
		};
	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
	}


}


void ReplaceState(vector<User_Info> (&a), int &oldstate, int &newstate, int &realaccount) // Change a[i].isnormal in file.
{

		int olds = oldstate;
		int news = newstate;

		string line;
		ifstream s_myfile(userinfopath);

		vector<string> lines;

		if (s_myfile.is_open())
		{
			while (getline(s_myfile, line))
			{
				lines.push_back(line);
			}
			s_myfile.close();
		}

		else
			cout << "Unable to open file";

		//oldstate = a[realaccount - 1].isnormal;

		//a[realaccount - 1].isnormal = newstate;

		string origin;
		string after;

		string straccount = itos(a[realaccount - 1].account);
//		string strid = ltos(a[realaccount - 1].id);
		string strbalance = itos(a[realaccount - 1].balance);
		string stroldstate = itos(olds);
		string strnewstate = itos(news);
		//string strisnormal = itos(a[realaccount - 1].isnormal);

		//cout << endl << origin << endl << after << endl;


		origin = straccount + "    " + a[realaccount - 1].name + "    " + a[realaccount - 1].password
			+ "    " + a[realaccount-1].id + "    " + strbalance + "    " + stroldstate;

		after = straccount + "    " + a[realaccount - 1].name + "    " + a[realaccount - 1].password
			+ "    " + a[realaccount-1].id + "    " + strbalance + "    " + strnewstate;

		for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
			if (*it == origin)
			{
				*it = after;
			}
		}
		//cout << origin << endl <<after<<endl;


		ofstream s_myfileOut(userinfopath);

		if (s_myfileOut.is_open())
		{
			for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				s_myfileOut << *it << endl;
			}
			s_myfileOut.close();
    }

		else
			cout << "Unable to open file";
}


void LossRegistration(vector<User_Info> (&a), int &realaccount)
{
	int inputlossaccount;
	cout << endl << "Enter The Account You Want To Loss Registration: " ;
	cin >> inputlossaccount;
	if(CheackAccountLegal(inputlossaccount))
	{
		inputlossaccount = GetRealAccount(inputlossaccount);
		realaccount = inputlossaccount;
		if(a[inputlossaccount - 1].isnormal == 0)
		{
			oldstate = 0;
			newstate = 1;

			ReplaceState(a, oldstate, newstate, realaccount);

			a[inputlossaccount - 1].isnormal = 1;

			cout << endl <<  "Account Loss Registration Succeed!" << endl << endl;
		}
		else if(a[inputlossaccount - 1].isnormal == 2)
		{
			cout<< endl << endl << "Loss Registration Failed! The Account Has Been Cancled!"<< endl;
		}
		else if(a[inputlossaccount - 1].isnormal == 1)
		{
			cout << endl << endl << "Loss Registration Failed! The Account Has Been Reported Loss! " << endl;
		}
	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
		islegalaccount = 0;
	}


}


void HangingSolution(vector<User_Info> (&a), int &realaccount)
{
	int inputhangingaccount;
	cout << endl << "Enter Tha Account You Want To Hanging Loss: " ;
	cin >> inputhangingaccount;

	if(CheackAccountLegal(inputhangingaccount))
	{
		inputhangingaccount = GetRealAccount(inputhangingaccount);
		realaccount = inputhangingaccount;
		if(a[inputhangingaccount - 1].isnormal == 1)
		{

			oldstate = 1;
			newstate = 0;

			ReplaceState(a, oldstate, newstate, realaccount);

			a[inputhangingaccount - 1].isnormal = 0;
			cout << endl << "Account Hnaging Loss Succeed!" << endl << endl ;
		}
		else if(a[inputhangingaccount - 1].isnormal == 2)
		{
			cout<< endl << endl << "Hanging Solution Failed! The Account Has Been Cancled!"<< endl;
		}
		else if(a[inputhangingaccount - 1].isnormal == 0)
		{
			cout<< endl << endl << "Hanging Solution Failed! The Account Has Not Been Loss Reported Yet!"<< endl;
		}

	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
	}
}


void Deposit(vector<User_Info> (&a), int &olddeposit, int &newdeposit, int &realaccount, int &islegalstate, int &islegalaccount) //Change depositamount in vector.
{
	int depositaccount;
	int depositmount;

	cout << endl << "Enter The Account You Want To Deposit: ";
	cin >> depositaccount;

	if(CheackAccountLegal(depositaccount))
	{
		islegalaccount = 1;

		depositaccount = GetRealAccount(depositaccount);

		if(a[depositaccount - 1].isnormal == 0 || a[depositaccount - 1].isnormal == 1)
		{
			islegalstate = 1;

			cout << endl;
			cout << "Account Name: " << a[depositaccount - 1].name << endl <<endl;
			cout << "Account Balance: " << a[depositaccount - 1].balance << endl;

			cout << endl << endl
				 << "Enter Deposit Mount: ";
			cin >> depositmount;

			olddeposit = a[depositaccount - 1].balance;
			a[depositaccount - 1].balance += depositmount;
			newdeposit = a[depositaccount - 1].balance;

			realaccount = depositaccount;

			cout << endl << "Deposit Succed!";
			cout << endl << "Account Balance: " << a[depositaccount - 1].balance <<endl;
		}
		else{
			islegalstate = 0;
			cout << endl << endl << "Deposit Failed! Tha Account Has Been Cancled!" << endl ;
		};

	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
		islegalaccount = 0;
	}



}


void ReplaceDeposit(vector<User_Info> (&a), int olddeposit, int newdeposit, int realaccount) //Update deposit record in files.
{




		string line;
		ifstream myfile(userinfopath);

		vector<string> lines;

		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				lines.push_back(line);
			}
			myfile.close();
		}

		else
			cout << "Unable to open file";



		string origin;
		string after;

		string straccount = itos(a[realaccount - 1].account);
		string stroldbalance = itos(olddeposit);
		string strnewbalance = itos(newdeposit);
		string strisnormal = itos(a[realaccount - 1].isnormal);


		origin = straccount + "    " + a[realaccount - 1].name + "    " + a[realaccount - 1].password
			+ "    " + a[realaccount - 1].id + "    " + stroldbalance + "    " + strisnormal;

		after = straccount + "    " + a[realaccount - 1].name + "    " + a[realaccount - 1].password
			+ "    " + a[realaccount - 1].id + "    " + strnewbalance + "    " + strisnormal;

		for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
			if (*it == origin)
			{
				*it = after;
			}
		}
		//cout << origin << endl <<after<<endl;


		ofstream myfileOut(userinfopath);

		if (myfileOut.is_open())
		{
			for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				myfileOut << *it << endl;
			}
			myfileOut.close();
    }

		else
			cout << "Unable to open file";

}


void Withdraw(vector<User_Info> (&a), int &olddeposit, int &newdeposit, int &realaccount, int &islegalstate, int &islegalaccount)
{
	int withdrawaccount;
	int withdrawmount;

	int islegal = 0; // Check if the withdraw amount less than deposit.


	cout << endl << "Enter The Account You Want To Withdraw: ";
	cin >> withdrawaccount;

	if(CheackAccountLegal(withdrawaccount))
	{
		islegalaccount = 1;

		withdrawaccount = GetRealAccount(withdrawaccount);

		if(a[withdrawaccount - 1].isnormal == 0)
		{
			islegalstate = 1;

			cout << endl ;
			cout << "Account Name: " << a[withdrawaccount - 1].name << endl <<endl;
			cout << "Account Balance: " << a[withdrawaccount - 1].balance << endl;

			do{
			cout << endl << endl
				 << "Enter Withdraw Mount: ";
			cin >> withdrawmount;


				if(a[withdrawaccount - 1].balance >= withdrawmount)
					{
						olddeposit = a[withdrawaccount - 1].balance;
						a[withdrawaccount - 1].balance -= withdrawmount;
						newdeposit = a[withdrawaccount - 1].balance;

						realaccount = withdrawaccount;

						islegal = 1;

						cout << endl << "Withdraw Succed!";
						cout << endl << "Account Balance: " << a[withdrawaccount - 1].balance;
					}
					else{
						islegal = 0;

						cout << endl << "****Withdraw Failed!****" << endl ;
						cout << endl << "****Withdraw Amount May Not More Than The Deposit!****" << endl << endl  ;
					}
			}while(!islegal);

		}
		else if(a[withdrawaccount - 1].isnormal)
		{
			cout << endl << endl << "Withdraw Failed! The Account Has Been Reported Loss!" << endl;
			islegalstate = 0;
		}
		else{
			cout << endl << endl << "Withdraw Failed! The Account Has Been Cancled!" << endl;
			islegalstate = 0;
		}

	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
		islegalaccount = 0;
	}


}


void Transfer(vector<User_Info> (&a), int &olddeposit, int &newdeposit, int &objold, int &objnew, int &realaccount, int &recieveaccount, int &islegalstate, int &islegalaccount)
{
	int transferamount;
	int t_islegal = 0;

	int isa1legal = 0;
	int isa2legal = 0;

	cout << "Enter The Account You Want To Transfer From: ";
	cin >> realaccount;

	if(CheackAccountLegal(realaccount))
	{
		//islegalaccount = 1;

		realaccount = GetRealAccount(realaccount);

		if(!a[realaccount - 1].isnormal)
		{
			isa1legal = 1;

			cout << "Account Name: " << a[realaccount - 1].name << endl << endl;
			cout << "Account Password: " << a[realaccount - 1].password << endl << endl;
			cout << "Account Balance: " << a[realaccount - 1].balance << endl << endl;

			do
			{
				cout << "Enter Transfer Amount: ";
				cin >> transferamount;
				if(a[realaccount - 1].balance >= transferamount)
				{
					t_islegal = 1;
				}
				else{
					t_islegal = 0;
					cout << endl << endl << "Transfer Amount May Not More Than Deposit!" << endl;
				}
			}while(!t_islegal);


			cout << endl << "Enter The Account You Want To Transfer To: ";
			cin >> recieveaccount;

			if(CheackAccountLegal(recieveaccount))
			{
				islegalaccount = 1;

				recieveaccount = GetRealAccount(recieveaccount);

				if((!a[recieveaccount - 1].isnormal) || (a[recieveaccount - 1].isnormal == 1))
				{
					isa2legal = 1;

				}
				else if(a[recieveaccount - 1].isnormal == 2)
				{
					cout << endl << endl <<  "Transfer Failed! The Recieve Account Has Been Cancled!" << endl;
					isa2legal = 0;
				};

			}
			else{
				cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
				islegalaccount = 0;
			}





		}
		else if (a[realaccount - 1].isnormal == 1)
		{
			cout << endl << endl << "Can Not Transfer From This Account! The Account Has Been Reported Loss!" << endl;
			isa1legal = 0;
		}
		else
		{
			cout << endl << endl << "Can Not Transfer From This Account! The Account Has Been Cancled!" << endl;
			isa1legal = 0;
		}

	}
	else{

		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
		islegalaccount = 0;
	}



	if(isa1legal && isa2legal)
	{
		olddeposit = a[realaccount - 1].balance;
		a[realaccount - 1].balance -= transferamount;
		newdeposit = a[realaccount - 1].balance;

		cout << endl << endl << "Transfer Succed!"
			 << endl << endl << "Account Blance: " << a[realaccount - 1].balance << endl ;

		objold = a[recieveaccount - 1].balance;
		a[recieveaccount - 1].balance += transferamount;
		objnew = a[recieveaccount - 1].balance;

		islegalstate = 1;
	};


}


void ChangePassword(vector<User_Info> (&a), string &oldpass, string &newpass, int &realaccount, int &islegalstate, int &islegalaccount)
{
	int changepassaccount;
	string inputnewpass;
	string confirmpass;

	int issame = 0;

	cout << endl << "Enter The Account You Want To Change Password: ";
	cin >> changepassaccount;

	if(CheackAccountLegal(changepassaccount))
	{
		islegalaccount = 1;

		changepassaccount = GetRealAccount(changepassaccount);
		realaccount = changepassaccount;

		if(a[realaccount - 1].isnormal == 0 || a[realaccount - 1].isnormal == 1)
			{
				cout << endl;
				cout << "Account Name: " << a[changepassaccount - 1].name << endl <<endl;
				cout << "Account Password: " << a[changepassaccount - 1].password << endl;

				while(!issame)
				{

					islegalstate = 1;

					cout << endl << endl;
					cout << "Enter New Pass: ";
					cin >> inputnewpass;

					cout << endl << endl << "Confirm Your Password: ";
					cin >> confirmpass;

					if(inputnewpass == confirmpass)
						{
							issame = 1;

							oldpass = a[changepassaccount - 1].password;
							newpass = inputnewpass;
							a[changepassaccount - 1].password = inputnewpass;

							cout << endl << endl<<  "Password Change Succeed!" << endl;

							break;
						}
					else
						{

							issame = 0;

							cout << endl << endl << "The Password You Entered Was Different! "
								 << endl << endl << "Please Try Again!";
						}
			}
		}
		else
			{
			cout << endl << endl << "Can Not Change Account Password! The Account Has Been Cancled!" << endl ;
		};

	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
		islegalaccount = 0;
	}



}


void ReplacePassword(vector<User_Info> (&a), string oldpass, string newpass, int realaccount)
{
		string line;
		ifstream p_myfile(userinfopath);

		vector<string> lines;

		if (p_myfile.is_open())
		{
			while (getline(p_myfile, line))
			{
				lines.push_back(line);
			}
			p_myfile.close();
		}

		else
			cout << "Unable to open file";



		string origin;
		string after;

		string straccount = itos(a[realaccount - 1].account);
//		string strid = ltos(a[realaccount - 1].id);
		string strbalance = itos(a[realaccount - 1].balance);
		string strnerbalance = itos(newdeposit);
		string strisnormal = itos(a[realaccount - 1].isnormal);




		origin = straccount + "    " + a[realaccount - 1].name + "    " + oldpass
			+ "    " + a[realaccount - 1].id + "    " + strbalance + "    " + strisnormal;

		after = straccount + "    " + a[realaccount - 1].name + "    " + newpass
			+ "    " + a[realaccount - 1].id + "    " + strbalance + "    " + strisnormal;

		for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
			if (*it == origin)
			{
				*it = after;
			}
		}
		//cout << origin << endl <<after<<endl;


		ofstream p_myfileOut(userinfopath);

		if (p_myfileOut.is_open())
		{
			for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				p_myfileOut << *it << endl;
			}
			p_myfileOut.close();
    }

		else
			cout << "Unable to open file";
}


void CancleAccount(vector<User_Info> (&a), int &olddeposit, int &newdeposit, int &realaccount, int &iscancle, int &islegalaccount)
{

	char cancleconfirm[2];

	int inputcancleaccount;
	cout << endl << "Enter The Account You Want To Cancle: " ;
	cin >> inputcancleaccount;

	if(CheackAccountLegal(inputcancleaccount))
	{
		islegalaccount = 1;
		inputcancleaccount = GetRealAccount(inputcancleaccount);
		realaccount = inputcancleaccount;
		if(a[realaccount - 1].isnormal == 0 || a[realaccount - 1].isnormal == 1 )
		{
				cout << endl << endl << "Account Name: " << a[inputcancleaccount - 1].name
				 << endl << endl << "Account Passworsd: " << a[inputcancleaccount - 1].password
				 << endl << endl << "Account Balance: " << a[inputcancleaccount - 1].balance;

			cout << endl << endl << " Are You Sure To Cancle This Account? (y/n)";

			cin >> cancleconfirm;

			if(cancleconfirm[0] == 'y' || cancleconfirm[0] == 'Y')
			{
				a[inputcancleaccount - 1].isnormal = 2;
				cout << endl <<  "Account Cancle Succeed!" << endl << endl;

				iscancle = 1;

				olddeposit = a[inputcancleaccount - 1].balance;
				newdeposit = 0;

				oldstate = 0;
				newstate = 2;

				ReplaceState(a, oldstate, newstate, realaccount);

				a[inputcancleaccount - 1].balance = 0;


				cout << "Withdrawed Account Balance: " << olddeposit;
			}
			else{

				iscancle = 0;

				cout << "Account Cancle Suspand, Now Return To Main Menu."<< endl << endl;
			};

		}
		else
		{
			cout << endl << endl << "Account Cancle Failed! The Account Has Been Cancled Already!"<< endl ;
		};

	}
	else{
		cout << endl << endl << "The Account You Entered Does Not Exist! " << endl;
		islegalaccount = 0;
	}




}


int main()
{
    cout << "+----------------------------+" << endl;
    cout << "+    Welcome to SnTz's bank   " << endl;
    cout << "+----------------------------+" << endl;

	System_Login AA;
	AA.AdminLogin(islogin);

	vector<User_Info> a;


	System_Menu A;
	A.state = islogin;
	menu:
	A.Get_Feature(A.state, option);
	//Option save in option[0] by a number from 0 to 9;



	system("cls");

	if(option[0] == '1')
		{
			Newaccount(a, account);
		}
		else if (option[0] == '5')
		{
			Query(a);
		}
		else if (option[0] == '2')
		{
			CancleAccount(a, olddeposit, newdeposit, realaccount, iscancle, islegalaccount);
			if(iscancle && islegalaccount)
			{
				ReplaceDeposit(a, olddeposit, newdeposit, realaccount);
				iscancle = 0;
				islegalaccount = 0;
			};
		}
		else if (option[0] == '7')
		{
			LossRegistration(a, realaccount);
		}
		else if (option[0] == '8')
		{
			HangingSolution(a, realaccount);
		}
		else if (option[0] == '3')
		{
			Deposit(a, olddeposit, newdeposit, realaccount, islegalstate, islegalaccount);
			if(islegalstate && islegalaccount)
			{
				ReplaceDeposit(a, olddeposit, newdeposit, realaccount);
				islegalstate = 0;
				islegalaccount = 0;
			}
		}
		else if (option[0] == '4')
		{
			Withdraw(a, olddeposit, newdeposit, realaccount, islegalstate, islegalaccount);
			if(islegalstate && islegalaccount)
			{
				ReplaceDeposit(a, olddeposit, newdeposit, realaccount);
				islegalstate = 0;
				islegalaccount = 0;
			}

		}
		else if (option[0] == '6')
		{
			Transfer(a, olddeposit, newdeposit, objold, objnew, realaccount, recieveaccount, islegalstate, islegalaccount);
			if(islegalstate && islegalaccount)
			{
				ReplaceDeposit(a, olddeposit, newdeposit, realaccount);
				ReplaceDeposit(a, objold, objnew, recieveaccount);
				islegalstate = 0;
				islegalaccount = 0;
			}

		}
		else if (option[0] == '9')
		{
			ChangePassword(a, oldpass, newpass, realaccount, islegalstate, islegalaccount);
			if(islegalstate && islegalaccount)
			{
				ReplacePassword(a, oldpass, newpass, realaccount);
				islegalstate = 0;
				islegalaccount = 0;
			}

		}
		else exit(0);

		if(BackToMenu())
		{
			system("cls");
			goto menu;
		}


}



