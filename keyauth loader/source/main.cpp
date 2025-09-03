#include "includes.h"

int main()
{
	SetConsoleTitleA("Keyauth Simple Loader ~ manuuu is here");

	KeyAuthApp.init();
	if (!KeyAuthApp.response.success)
	{
		std::cout << skCrypt("status: ") << KeyAuthApp.response.message << std::endl;
		Sleep(1200);
		exit(1);
	}

	std::string key;

	std::cout << skCrypt("\n enter your license key: ") << std::endl;
	std::cin >> key;
	KeyAuthApp.license(key, "");

	if (KeyAuthApp.response.message.empty()) exit(11);

	for (int i = 0; i < KeyAuthApp.user_data.subscriptions.size(); i++) {
		auto sub = KeyAuthApp.user_data.subscriptions.at(i);
		std::cout << skCrypt("\n name: ") << sub.name;
		std::cout << skCrypt(" : expiry: ") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
	}

	std::thread start(checkAuthenticated, ownerid); start.detach();
	std::thread check(sessionStatus); check.detach();

	std::cout << skCrypt("closing in 5 seconds.");
	Sleep(5000);

	return 0;
}