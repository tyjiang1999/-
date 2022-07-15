#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool OpenFile(string filename, ifstream & file)
{
	file.open(".\\" + filename);
	if (!file.is_open())
	{
		file.open(".\\" + filename + ".txt");
		if (!file.is_open())
			return false;
	}
	return true;
}

ofstream WriteToFile(string filename)
{
	int i = filename.find(".");
	if (filename.find(".") < 0 || i >= filename.length())
		return ofstream(".\\" + filename + ".txt");
	return ofstream(".\\" + filename);
}

string SplitFirst(string& s, const string c)
{
	string::size_type pos;
	pos = s.find(c);
	if (pos != string::npos)
	{
		string res = s.substr(0, pos);
		s = s.substr(pos + 1);
		return res;
	}
	return "";
}

void format(double x, ofstream& out)
{
	if (x > 100)
		out << x << "  ";
	else if(x > 10)
		out << x << "    ";
	else
		out << x << "      ";
}

bool user_defined_txt(string line, double* attribute, ofstream& out)
{
	bool flag = false;
	while (line.length() > 0)
	{
		string now = SplitFirst(line, ";");
		if (now.length() < 1)
		{
			if (line.length() < 1)
				return flag;
			now = line;
			line = "";
		}
		bool f = false;
		double result = 0.0;
		if (now.find("Éú") != string::npos)
		{
			f = true;
			out << "Éú";
			result += attribute[0];
		}
		if (now.find("¹¥") != string::npos)
		{
			f = true;
			out << "¹¥";
			result += attribute[1];
		}
		if (now.find("·À") != string::npos)
		{
			f = true;
			out << "·À";
			result += attribute[2];
		}
		if (now.find("¾«") != string::npos)
		{
			f = true;
			out << "¾«";
			result += attribute[3];
		}
		if (now.find("³ä") != string::npos)
		{
			f = true;
			out << "³ä";
			result += attribute[6];
		}
		if (now.find("Ë«±¬") != string::npos || now.find("Ë«±©") != string::npos)
		{
			f = true;
			out << "Ë«±¬";
			result += attribute[4] + attribute[5];
		}
		if (f)
		{
			out << ":";
			format(result, out);
			flag = true;
		}
	}
	return flag;
}

bool SaveToTxt(string name, double* attribute, ofstream & txtout)
{
	string line = "";
	if (name.find("(") != string::npos && name.find(")") != string::npos)
	{
		line = name;
		line.erase(line.find(")"));
		line.erase(0, line.find("(") + 1);
		name.erase(name.find("("), name.find(")") + 1);
	}
	else if (name.find("£¨") != string::npos && name.find("£©") != string::npos)
	{
		line = name;
		line.erase(line.find("£©"));
		line.erase(0, line.find("£¨") + 1);
		name.erase(name.find("("), name.find(")") + 1);
	}

	txtout << name + "\t";
	txtout << "Éú:";
	format(attribute[0], txtout);
	txtout << "¹¥:";
	format(attribute[1], txtout);
	txtout << "·À:";
	format(attribute[2], txtout);
	txtout << "¾«:";
	format(attribute[3], txtout);
	txtout << "±©:";
	format(attribute[4], txtout);
	txtout << "±¬:";
	format(attribute[5], txtout);
	txtout << "³ä:";
	format(attribute[6], txtout);
	txtout << "µÃ·Ö:";
	format(attribute[7], txtout);

	if (line.length() > 0 && user_defined_txt(line, attribute, txtout))
	{
		txtout << endl;
		return true;
	}

	if (name.find("¸ÊÓê") != string::npos)
	{
		txtout << "¹¥Ë«±¬:";
		format(attribute[1] + attribute[4] + attribute[5], txtout);
		txtout << "¹¥¾«Ë«±¬:";
		format(attribute[1] + attribute[3] + attribute[4] + attribute[5], txtout);
	}
	else if (name.find("ÉñÀï") != string::npos)
	{
		txtout << "¹¥Ë«±¬:";
		format(attribute[1] + attribute[4] + attribute[5], txtout);
		txtout << "¹¥³äË«±¬:";
		format(attribute[1] + attribute[4] + attribute[5] + attribute[6], txtout);
	}
	else if (name.find("ºúÌÒ") != string::npos)
	{
		txtout << "Éú¾«Ë«±¬:";
		format(attribute[0] + attribute[3] + attribute[4] + attribute[5], txtout);
	}
	else if (name.find("À×Éñ") != string::npos || name.find("À×µç½«¾ü") != string::npos)
	{
		txtout << "¹¥³äË«±¬:";
		format(attribute[1] + attribute[4] + attribute[5] + attribute[6], txtout);
	}
	else
	{
		txtout << "¹¥Ë«±¬:";
		format(attribute[1] + attribute[4] + attribute[5], txtout);
	}
	txtout << endl;
	return true;
}

bool user_defined_csv(string line, double* attribute, ofstream& out)
{
	bool flag = false;
	while (line.length() > 0)
	{
		string now = SplitFirst(line, ";");
		if (now.length() < 1)
		{
			if (line.length() < 1)
				return flag;
			now = line;
			line = "";
		}
		bool f = false;
		double result = 0.0;
		if (now.find("Éú") != string::npos)
		{
			if (!f)
			{
				f = true;
				out << ",";
			}
			out << "Éú";
			result += attribute[0];
		}
		if (now.find("¹¥") != string::npos)
		{
			if (!f)
			{
				f = true;
				out << ",";
			}
			out << "¹¥";
			result += attribute[1];
		}
		if (now.find("·À") != string::npos)
		{
			if (!f)
			{
				f = true;
				out << ",";
			}
			out << "·À";
			result += attribute[2];
		}
		if (now.find("¾«") != string::npos)
		{
			if (!f)
			{
				f = true;
				out << ",";
			}
			out << "¾«";
			result += attribute[3];
		}
		if (now.find("³ä") != string::npos)
		{
			if (!f)
			{
				f = true;
				out << ",";
			}
			out << "³ä";
			result += attribute[6];
		}
		if (now.find("Ë«±¬") != string::npos || now.find("Ë«±©") != string::npos)
		{
			if (!f)
			{
				f = true;
				out << ",";
			}
			out << "Ë«±¬";
			result += attribute[4] + attribute[5];
		}
		if (f)
		{
			out << ":" << result;
			flag = true;
		}
	}
	return flag;
}

bool SaveToCsv(string name, double* attribute, ofstream & csvout)
{
	string line = "";
	if (name.find("(") != string::npos && name.find(")") != string::npos)
	{
		line = name;
		line.erase(line.find(")"));
		line.erase(0, line.find("(") + 1);
		name.erase(name.find("("), name.find(")") + 1);
	}
	else if (name.find("£¨") != string::npos && name.find("£©") != string::npos)
	{
		line = name;
		line.erase(line.find("£©"));
		line.erase(0, line.find("£¨") + 1);
		name.erase(name.find("("), name.find(")") + 1);
	}
	
	csvout << name;
	for (int i = 0; i < 8; i++)
		csvout << ","<< attribute[i];
	
	if (line.length() > 0 && user_defined_csv(line, attribute, csvout))
	{
		csvout << endl;
		return true;
	}
	if (name.find("¸ÊÓê") != string::npos)
	{
		csvout << ",¹¥Ë«±¬:" << attribute[1] + attribute[4] + attribute[5] << ",¹¥¾«Ë«±¬:" << attribute[1] + attribute[3] + attribute[4] + attribute[5] << endl;
		return true;
	}
	if (name.find("ÉñÀï") != string::npos)
	{
		csvout << ",¹¥Ë«±¬:" << attribute[1] + attribute[4] + attribute[5] << ",¹¥³äË«±¬:" << attribute[1] + attribute[4] + attribute[5] + attribute[6] << endl;
		return true;
	}
	if (name.find("ºúÌÒ") != string::npos)
	{
		csvout << ",Éú¾«Ë«±¬:" << attribute[0] + attribute[3] + attribute[4] + attribute[5] << endl;
		return true;
	}
	if (name.find("À×Éñ") != string::npos || name.find("À×µç½«¾ü") != string::npos)
	{
		csvout << ",¹¥³äË«±¬:" << attribute[1] + attribute[4] + attribute[5] + attribute[6] << endl;
		return true;
	}
	csvout << ",¹¥Ë«±¬:" << attribute[1] + attribute[4] + attribute[5] << endl;
	return true;
}

bool caculate(string line, ofstream & txtout, ofstream & csvout)
{
	line.erase(line.find_last_not_of(" ") + 1);
	line.erase(0,line.find_first_not_of(" "));
	if (line.length() == 0)
	{
		txtout << endl;
		return false;
	}
	if (line[0] == '#')
		return false;

	istringstream str(line);
	string name;
	double base[3], attribute[8];
	int type[3];

	if (!(str >> name))
		return false;
	for (int i = 0; i < 3; i++)
	{
		if (!(str >> base[i]))
			return false;
	}
	for (int i = 0; i < 3; i++)
	{
		if (!(str >> type[i]))
			return false;
	}
	for (int i = 0; i < 7; i++)
	{
		if (!(str >> attribute[i]))
			return false;
	}

	attribute[7] = attribute[4] * 2 + attribute[5];

	attribute[0] -= 4780;
	attribute[1] -= 311;
	attribute[0] = attribute[0] * 100.0 / base[0];
	attribute[1] = attribute[1] * 100.0 / base[1];
	attribute[2] = attribute[2] * 100.0 / base[2];

	if (type[0] == 4)
		type[0] = 6;
	else if (type[0] == 5)
		type[0] = 7;
	if (type[1] == 4)
		type[1] = 7;
	if (type[2] == 6)
		type[2] = 7;
	for (int i = 0; i < 3; i++)
	{
		switch (type[i])
		{
		case 0:
			attribute[0] -= 46.6;
			break;
		case 1:
			attribute[1] -= 46.6;
			break;
		case 2:
			attribute[2] -= 58.3;
			break;
		case 3:
			attribute[3] -= 183;
			break;
		case 4:
			attribute[4] -= 31.1;
			break;
		case 5:
			attribute[5] -= 62.2;
			break;
		case 6:
			attribute[6] -= 51.8;
			break;
		default:
			break;
		}
	}

	attribute[0] /= 4.975;
	attribute[1] /= 4.975;
	attribute[2] /= 6.2;
	attribute[3] /= 19.75;
	attribute[4] /= 3.3;
	attribute[5] /= 6.6;
	attribute[6] /= 5.5;

	SaveToTxt(name, attribute, txtout);
	SaveToCsv(name, attribute, csvout);
	return true;
}

bool partition(string input,string txtout, string csvout)
{
	ifstream input_file;
	if (!OpenFile(input, input_file))
	{
		cout << "Error, parameter file not find!" << endl;
		system("pause");
		return false;
	}

	ofstream txtout_file,csvout_file;
	txtout_file = WriteToFile(txtout);
	csvout_file = WriteToFile(csvout);
	bool flag = false;
	string line;

	txtout_file << setiosflags(ios::fixed) << setprecision(1);
	csvout_file << "½ÇÉ«Ãû³Æ,ÉúÃü,¹¥»÷,·ÀÓù,¾«Í¨,±©»÷,±¬ÉË,³äÄÜ,Ë«±¬µÃ·Ö,ÓÐÐ§´ÊÌõ" << endl << setiosflags(ios::fixed) << setprecision(1);
	while (getline(input_file, line))
	{
		flag |= caculate(line, txtout_file, csvout_file);
	}

	input_file.close();
	txtout_file.close(); 
	csvout_file.close();
	return flag;
}

int main()
{
	if (partition("parameter.txt", "result.txt", "result.csv"))
	{
		system("start result.txt");
	}
	return 0;
}