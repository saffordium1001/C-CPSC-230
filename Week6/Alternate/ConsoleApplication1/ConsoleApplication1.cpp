#include <iostream>
#include <fstream>
#include <array>
using namespace std;

int main()
{
	fstream ifile;
	int numArray[100];
	int count = 0;
	int sum = 0;
	ifile.open("Lab6-7_Number_File.txt", ios::in);

	if (ifile.is_open())
	{
		std::cout << "Data File Successfully opened" << std::endl;
		//while (!ifile.eof())
		//{

		//	if (sizeof(numArray) / sizeof(numArray[0]) < 100)
		//	{

		//		ifile >> numArray[count];
		//		sum = sum + numArray[count];
		//		count++;
		//	}
		//	else
		//	{
		//		cout << "Error opening File";
		//	}

		//}

	}
	ifile.close();

	//int avg = sum / count;
	//ofstream ofile("result.txt");
	//if (ofile.is_open())
	//{
	//	ofile << "Score Above/below average" << endl;
	//	for (int j = 0; j < count; j++)
	//	{
	//		ofile << numArray[j] << " ";
	//		if (numArray[j] < avg)
	//		{
	//			ofile << "Below average" << endl;
	//		}
	//		else
	//		{
	//			ofile << "Above average" << endl;
	//		}
	//	}

	//}
	//ofile.close();
	return 0;
}