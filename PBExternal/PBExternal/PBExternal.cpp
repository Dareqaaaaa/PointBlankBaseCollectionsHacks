#include <Windows.h>
#include "Header.h"
using namespace std;



int main() {
	
	HANDLE test = get_handle_to_process(L"PointBlank.exe");

	printf("0x%X", test);

	system("pause");

	return EXIT_SUCCESS;
}