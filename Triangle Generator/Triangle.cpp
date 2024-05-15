#include <iostream>
using namespace std;

int main()
{
	int n; // resource reference idea from Youtube channel: Simply Coding
	cout << "Please enter a number between 3 and 25; any other number to terminate: ";
	cin >> n;
	while ((n >= 3) && (n <= 25))
	{

		for (int x = 1; x <= n; x++) //rows
		{
			for (int y = 1; y <= x; y++) //columns
			{
				cout << " ";
			}
			for (int y = x; y < n; y++)
			{
				cout << "*"; // left side upper triangle
			}
			for (int y = x; y <= n; y++)
			{
				cout << "*"; // right side upper triangle
			}
			cout << "\n";
		}

		for (int x = 1; x <= n; x++)
		{
			for (int y = x; y <= n; y++)
			{
				cout << " ";
			}
			for (int y = 1; y < x; y++)
			{
				cout << "*"; // left side bottom triangle
			}
			for (int y = 1; y <= x; y++)
			{
				cout << "*"; // right side bottom triangle
			}
			cout << "\n"; // finish hourglass triangle
		}
		cout << "\n";

		for (int x = 1; x <= n; x++) // resource reference of this code from Youtube channel: Mazen Labs
		{
			for (int y = 1; y <= x; y++)
			{
				cout << "*"; // left side
			}
			for (int k = 1; k <= (n - x) * 2; k++)
			{
				cout << " "; // space in between
			}
			for (int y = 1; y <= x; y++)
			{
				cout << "*"; // right side
			}
			cout << "\n"; // upper side of the triangle ^^
		}
		for (int x = n - 1; x >= 1; x--)
		{
			for (int y = 1; y <= x; y++)
			{
				cout << "*"; // left side
			}
			for (int k = 1; k <= (n - x) * 2; k++)
			{
				cout << " ";  // space in between
			}
			for (int y = 1; y <= x; y++)
			{
				cout << "*"; // right side
			}
			cout << "\n"; // bottom triangle

		} // finished butterfly triangle 

		cout << "Please enter a number between 3 and 25; any other number to terminate: ";
		cin >> n;
	}
	return 0;
}
