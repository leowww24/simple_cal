#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;

//异常函数
void error(const string& s)
{
	cerr<<s<<endl;
	throw runtime_error(s);
}

//存储运算符和操作数的单词类
class Token
{
public:
	Token(char ch):type(ch){}
	Token(char ch,double val):type(ch),value(val){}
	char type;
	double value;
};

//输入流和单词类Token的媒介
//对输入流进行分词，根据输入类型返回一个运算符或运算数的单词
class Token_Stream
{
private:
	Token buffer;
	bool null;
public:
	Token_Stream():buffer(0),null(true){}
	void push_back(Token t);
	Token get();
};

void Token_Stream::push_back(Token t)
{
	if (!null)
	{
		error("Buffer not null,cannot push_back.");
	}
	buffer=t;
	null=false;
}

Token Token_Stream::get()
{
	if (!null)
	{
		null=true;
		return buffer;
	}
	char ch;
	cin>>ch;
	switch (ch)
	{
	case 'q':case '=':
		return Token(ch);
	case '+':case '-':case '*':case '/':case '(':case ')':
	 	return Token(ch);
	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9':
		cin.putback(ch);  
		double val;
		cin>>val;
		return Token('0',val);
	default:
		return Token(ch);
	}
}

//全局对象
Token_Stream ts;

//文法实现
double term();
double primary();

double expression()
{
	double lef=term();
	while (true)
	{
		Token token=ts.get();
		switch (token.type)
		{
		case '+':
			lef+=term();
			break;
		case '-':
			lef-=term();
			break;
		default:
			ts.push_back(token);
			return lef;
		}
	}
}

double term()
{
	double lef=primary();

	while (true)
	{
		Token token=ts.get();
		switch (token.type)
		{
		case '*':
			lef*=primary();
			break;
		case '/':
			lef/=primary();
			break;
		default:
			ts.push_back(token);
			return lef;
		}
	}
}

double primary()
{
	double val;
	Token token=ts.get();

	switch (token.type)
	{
	case '0':
		val=token.value;
		break;
	case '(':
		val=expression();
		token=ts.get();
		if (token.type!=')')
		{
			error("Missing ).");
		}
		break;
	default:
		char invalid=token.type;
		string wrong_msg=" is not defined.";
		error(invalid+wrong_msg);
	}
	return val;
}

//主函数
int main()
{
	double val=0;
	cout<<"WELCOME TO LEO'S SIMPLE CALCULATOR!"<<endl
		<<"Please enter expressions using float-point numbers."<<endl
		<<"Enter '=' to show the result."<<endl
		<<"Enter 'q' to quit the program."<<endl
		<<"**************************************"<<endl;
	while (cin)
	{
		try
		{
			Token token=ts.get();
			if (token.type=='q')
			{
				break;
			}
			else if (token.type=='=')
			{
				cout<<"Result:"<<val<<endl;
			}
			else
			{
				ts.push_back(token);
				val=expression();
			}
		}
		catch(exception &e)
		{
			cerr<<"Error:"<<e.what()<<endl;
		}
		catch(...)
		{
			cerr<<"Unkwon error."<<endl;
		}
	}
}
