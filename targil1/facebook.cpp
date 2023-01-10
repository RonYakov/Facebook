#include"facebook.h"
using namespace std;

Facebook:: Facebook()
{
	startFacebook();
	menu();
}

void Facebook::startFacebook()
{
	facebookMembers.push_back(new Member("Ido Hirshman", 22, 11, 1999));
	facebookMembers.push_back(new Member("Ron Yakov", 14, 3, 1999));
	facebookMembers.push_back(new Member("Ziv Cohen", 16, 5, 1995));

	facebookMembers[0]->addPost("My name is Ido");
	facebookMembers[0]->addPost("I Live in Rosh Ha'ain");
	facebookMembers[1]->addPost("My name is Ron");
	facebookMembers[1]->addPost("I Live in Ramat Gan");
	facebookMembers[2]->addPost("My name is Ziv");
	facebookMembers[2]->addPost("I Live in Tel Aviv");

	facebookPages.push_back(new Page("9GAG"));
	facebookPages.push_back(new Page("Hapshuta"));
	facebookPages.push_back(new Page("LiverpoolFC"));

	facebookPages[0]->addPost("It's 9GAG");
	facebookPages[0]->addPost("We are here to make you laugh");
	facebookPages[1]->addPost("It's Hapshuta");
	facebookPages[1]->addPost("I love Talia");
	facebookPages[2]->addPost("It's LiverpoolFC");
	facebookPages[2]->addPost("Mo Salash the egyptian king");

	facebookMembers[0]->addFriend(facebookMembers[1], true);
	facebookMembers[0]->addFriend(facebookMembers[2], true);
	facebookMembers[1]->addFriend(facebookMembers[2], true);
	facebookMembers[1]->addPage(facebookPages[2]);
}

void Facebook::menu()
{
	int currChoise;
	bool stop = false;

	while (!stop)
	{
		printMenu();

		cin >> currChoise;
		cout << "\n";

		switch (currChoise)
		{
		case 1:
			addMemberToFacebook();
			break;

		case 2:
			addPageToFacebook();
			break;

		case 3:
			addPostToPageOrMember();
			break;

		case 4:
			presentAllPostsOfMemberOrPage();
			break;
		
		case 5:
			presentLastTenPostsOfMemberFriends();
			break;

		case 6:
			makeANewFriendship();
			break;

		case 7:
			unfriendship();
			break;

		case 8:
			followAFanPage();
			break;

		case 9:
			unfollowAFanPage();
			break;

		case 10:
			printAllArr();
			break;

		case 11:
			presentAllFriendsOrFollowers();
			break;

		case 12:
			checkWhoIsMorePopular();
			break;

		case 13:
			cout << "bye bye :)\n";
			stop = true;
			break;

		default:
			cout << "Invalid input!! Please try again\n\n";
			clearBuffer();
			break;
		}

	}
}

void Facebook::clearBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Facebook::printMenu()
{
	cout << "____________________________________________________________\n";
	cout << "Please Choose the number according to the following options: \n\n";
	cout << "01 - Add a new member \n";
	cout << "02 - Add a new fan page \n";
	cout << "03 - Add a new status to a member / fan page \n";
	cout << "04 - Present all member's / fan page's posts \n";
	cout << "05 - Present the most 10 updates posts of member's friends \n";
	cout << "06 - Make new friendship between two members \n";
	cout << "07 - Unfriendship between two members\n";
	cout << "08 - Add a follower to a page \n";
	cout << "09 - Unfollow a page \n";
	cout << "10 - Present all members and pages of facebook \n";
	cout << "11 - Present all member's friends / page's followers \n";
	cout << "12 - Check who has more friends / followers \n";
	cout << "13 - Exit \n\n";
	cout << "Please put your choise here --> ";
}

void Facebook::addMemberToFacebook()
{
	string name;
	int day, month, year;
	bool stop = false;

	cout << "01 - Add a new member:\n\n";

	getNameFromUser(name, '0');

	try {
		findAMember(name, false);
	}
	catch(findAMemberException& ex)
	{
		cout << ex.what();
		return;
	}

	cout << "Please enter new member's birthday (dd mm yyyy):" << endl;
	cin >> day >> month >> year;

	cout << "\n";

	try 
	{
		Date birthday(day, month, year);
	}

	catch(DateDayException& exDay)
	{
		cout << exDay.what();
		return;
	}
	catch (DateMonthException& exMonth)
	{
		cout << exMonth.what();
		return;
	}
	catch (DateYearException& exYear)
	{
		cout << exYear.what();
		return;
	}

	Member* newMember = new Member(name, day, month, year);

	if(newMember != nullptr)
		facebookMembers.push_back(newMember);

	else
	{
		cout << "Allocation failed.\n";
		clearBuffer();
	}

	cout << "\n\n";
}

void Facebook::addPageToFacebook()
{
	string name;
	bool stop = false;

	cout << "02 - Add a new fan page:\n\n";

	getNameFromUser(name, '1');

	try {
		findAPage(name, false);
	}
	catch (findAPageException& ex)
	{
		cout << ex.what();
		return;
	}

	Page* newPage = new Page(name);

	if (newPage != nullptr)
		facebookPages.push_back(newPage);

	else
	{
		cout << "Allocation failed.\n";
		clearBuffer();
	}

	cout << "\n\n";
}

void Facebook::CheckMemberOrPage(char& memberOrPage)
{
	cout << "For Member please press 0 and for Page press 1:\n";
	cin >> memberOrPage;

	while (memberOrPage != '0' && memberOrPage != '1')
	{
		cout << "Invalid choice!\n";
		clearBuffer();
		cout << "For Member please press 0 and for Page press 1:\n";
		cin >> memberOrPage;
	}
}

void Facebook::addPostToPageOrMember()
{
	char PageOrMember;
	string name, text;
	int ind;

	cout << "03 - Add a new status to a member / fan page: \n\n";
	
	CheckMemberOrPage(PageOrMember);

	getNameFromUser(name, PageOrMember);

	if (PageOrMember == '0')
	{
		try 
		{
			ind = findAMember(name);
		}
		catch(notFindAMemberException& ex)
		{
			cout << ex.what();
			return;
		}

		cout << "please enter your text here:\n";
		getline(cin, text);

		try
		{
			facebookMembers[ind]->addPost(text);
		}

		catch (addPostToMemeberException& ex)
		{
			cout << ex.what();
			return;
		}
	}

	else
	{
		try 
		{
			ind = findAPage(name);
		}
		catch (notFindAPageException& ex)
		{
			cout << ex.what();
			return;
		}

		cout << "please enter your text here:\n";
		getline(cin, text);

		try 
		{
			facebookPages[ind]->addPost(text);
		}
		catch (addPostToPageException& ex)
		{
			cout << ex.what();
			return;
		};
	}

	cout << "\n\n";
}

int Facebook::findAMember(const string name, bool WantToFind)
{
	for (int i = 0; i < facebookMembers.size(); i++)
	{
		if (facebookMembers[i]->getName() == name)
		{
			if(WantToFind)
				return i;
			else
			{
				throw findAMemberException(name);
			}
		}
	}

	if (WantToFind)
		throw notFindAMemberException(name);
}

int Facebook::findAPage(const string name, bool WantToFind)
{
	for (int i = 0; i < facebookPages.size(); i++)
	{
		if (facebookPages[i]->getName() == name)
		{ 
			if (WantToFind)
				return i;
			else
			{
				throw findAPageException(name);
			}
		}
	}

	if (WantToFind)
		throw notFindAPageException(name);
}

void Facebook::presentAllPostsOfMemberOrPage()
{
	char PageOrMember;
	int index;
	string name;


	cout << "04 - Present all member's / fan page's posts: \n\n";
	
	CheckMemberOrPage(PageOrMember);

	getNameFromUser(name, PageOrMember);
	if (PageOrMember == '0')
	{
		try
		{
			index = findAMember(name);
		}

		catch (notFindAMemberException& ex)
		{
			cout << ex.what();
			return;
		}
		facebookMembers[index]->printAllPosts();
	}
	else
	{
		try
		{
			index = findAPage(name);
		}

		catch (notFindAPageException& ex)
		{
			cout << ex.what();
			return;
		}
		facebookPages[index]->printAllPosts();
	}
	
	cout << "\n\n";
}

void Facebook::presentLastTenPostsOfMemberFriends()
{
	char PageOrMember;
	int ind;
	string name;


	cout << "05 - Present the most 10 updates posts of member's friends: \n\n";

	getNameFromUser(name, '0');

	try
	{
		ind = findAMember(name);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}

	facebookMembers[ind]->printLastTenPostsOfMyFriends();


	cout << "\n\n";
}

void Facebook::makeANewFriendship()
{
	int  index1, index2;
	string name1, name2;

	cout << "06 - Make new friendship between two members: \n\n";
	cout << "First member:\n";
	getNameFromUser(name1, '0');

	try
	{
		index1 = findAMember(name1);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}

	cout << "Second member:\n";
	getNameFromUser(name2, '0', false);

	try
	{
		index2 = findAMember(name2);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		checkIfNamesEqual(name1, name2);
	}
	catch (IsNameTheSameException& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		*facebookMembers[index1] += *facebookMembers[index2];
	}
	catch (addFriendException& ex)
	{
		cout << ex.what();
		return;
	}

	cout << "\n\n";
}

void Facebook::unfriendship()
{
	int  index1, index2;
	string name1, name2;

	cout << "07 - Unfriendship between two members: \n\n";
	cout << "First member:\n";
	getNameFromUser(name1, '0');

	try
	{
		index1 = findAMember(name1);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}

	cout << "Second member:\n";
	getNameFromUser(name2, '0', false);

	try
	{
		index2 = findAMember(name2);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		checkIfNamesEqual(name1, name2);
	}
	catch (IsNameTheSameException& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		facebookMembers[index1]->removeFriend(facebookMembers[index2], true);
	}
	catch (removeFriendException& ex)
	{
		cout << ex.what();
		return;
	}

	cout << "\n\n";
}

void Facebook::checkIfNamesEqual(string name1, string name2)
{
	if (name1 == name2)
		throw IsNameTheSameException(name1);
}

void Facebook::followAFanPage()
{
	int  index1, index2;
	string name1, name2;

	cout << "08 - Add a follower to a page: \n\n";
	getNameFromUser(name1, '0');

	try
	{
		index1 = findAMember(name1);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}
	
	getNameFromUser(name2, '1', false);

	try
	{
		index2 = findAPage(name2);
	}
	catch (notFindAPageException& ex)
	{
		cout << ex.what();
		return;
	}
	try
	{
		*facebookMembers[index1] += *facebookPages[index2];
	}

	catch (addPageException& ex)
	{
		cout << ex.what();
	}

	cout << "\n\n";
}

void Facebook::unfollowAFanPage()
{
	int  index1, index2;
	string name1, name2;

	cout << "09 - Unfollow a page: \n\n";
	
	getNameFromUser(name1, '0');

	try
	{
		index1 = findAMember(name1);
	}
	catch (notFindAMemberException& ex)
	{
		cout << ex.what();
		return;
	}
	
	getNameFromUser(name2, '1', false);

	try
	{
		index2 = findAPage(name2);
	}
	catch (notFindAPageException& ex)
	{
		cout << ex.what();
		return;
	}
	try
	{
		facebookMembers[index1]->removePage(facebookPages[index2]);
	}

	catch (removePageException& ex)
	{
		cout << ex.what();
	}

	cout << "\n\n";
}

void Facebook::presentAllFriendsOrFollowers()
{
	char PageOrMember;
	int index;
	string name;


	cout << "11 - Present all member's friends / page's followers: \n\n";
	
	CheckMemberOrPage(PageOrMember);

	getNameFromUser(name, PageOrMember);

	if (PageOrMember == '0')
	{
		try
		{
			index = findAMember(name);
		}

		catch (notFindAMemberException& ex)
		{
			cout << ex.what();
			return;
		}
		facebookMembers[index]->printFriends();
	}
	else
	{
		try
		{
			index = findAPage(name);
		}

		catch (notFindAPageException& ex)
		{
			cout << ex.what();
			return;
		}
		facebookPages[index]->printFollowers();
	}

	cout << "\n\n";
}

void Facebook::getNameFromUser(string& name,char pageOrMember, bool isFirst)
{
	if (pageOrMember == '0')
	{
		cout << "Please enter the member's name :\n";
		if(isFirst)
			clearBuffer();
		getline(cin, name);
	}

	else
	{
		cout << "Please enter the page's name :\n";
		if (isFirst)
			clearBuffer();
		getline(cin, name);
	}

	cout << "\n" <<endl;
}

void Facebook::printAllArr()
{
	printMembersArr();
	printPagesArr();
}

void Facebook::printPagesArr()
{
	cout << "---Facebook Pages List---\n\n";
	cout << "index | Name \n";
	cout << "------|-------------\n";

	for (int i = 0; i < facebookPages.size(); i++)
	{
		printf("%6d", i);
		cout << "| " << facebookPages[i]->getName() << endl;
	}
	cout << "\n\n";
}

void Facebook::printMembersArr()
{
	cout << "---Facebook Members List---\n\n";
	cout << "index | Name \n";
	cout << "------|---------------\n";

	for (int i = 0; i < facebookMembers.size(); i++)
	{
		printf("%6d", i);
		cout << "| " << facebookMembers[i]->getName() << endl;
	}
	cout << "\n\n";
}

void Facebook::checkWhoIsMorePopular()
{
	char PageOrMember1, PageOrMember2;
	string name1, name2;
	int ind1, ind2;


	cout << "12 - Check who has more friends / followers: \n\n";

	CheckMemberOrPage(PageOrMember1);
    getNameFromUser(name1, PageOrMember1);

	if (PageOrMember1 == '0')
	{
		try
		{
			ind1 = findAMember(name1);
		}
		catch (notFindAMemberException& ex)
		{
			cout << ex.what();
			return;
		}
	}
	else
	{
		try
		{
			ind1 = findAPage(name1);
		}
		catch (notFindAPageException& ex)
		{
			cout << ex.what();
			return;
		}
	}


	CheckMemberOrPage(PageOrMember2);
	getNameFromUser(name2, PageOrMember2);


	if (PageOrMember2 == '0')
	{
		try
		{
			ind2 = findAMember(name2);
		}
		catch (notFindAMemberException& ex)
		{
			cout << ex.what();
			return;
		}
	}
	else
	{
		try
		{
			ind2 = findAPage(name2);
		}
		catch (notFindAPageException& ex)
		{
			cout << ex.what();
			return;
		}
	}
	
	if (PageOrMember1 == '0' && PageOrMember2 == '0')
	{
		if (*facebookMembers[ind1] > *facebookMembers[ind2])
			cout << facebookMembers[ind1]->getName() << " is more popular than " << facebookMembers[ind2]->getName() << "\n\n";
		else
			cout << facebookMembers[ind1]->getName() << " is not more popular than " << facebookMembers[ind2]->getName() << "\n\n";
	}
	
	else if (PageOrMember1 == '1' && PageOrMember2 == '1')
	{
		if (*facebookPages[ind1] > *facebookPages[ind2])
			cout << facebookPages[ind1]->getName() << " is more popular than " << facebookPages[ind2]->getName() << "\n\n";
		else
			cout << facebookPages[ind1]->getName() << " is not more popular than " << facebookPages[ind2]->getName() << "\n\n";
	}

	else if (PageOrMember1 == '1' && PageOrMember2 == '0')
	{
		if (*facebookPages[ind1] > (*facebookMembers[ind2]))
			cout << facebookPages[ind1]->getName() << " is more popular than " << facebookMembers[ind2]->getName() << "\n\n";
		else
			cout << facebookPages[ind1]->getName() << " is not more popular than " << facebookMembers[ind2]->getName() << "\n\n";
	}

	else if (PageOrMember1 == '0' && PageOrMember2 == '1')
	{
		if (*facebookMembers[ind1] > (*facebookPages[ind2]))
			cout << facebookMembers[ind1]->getName() << " is more popular than " << facebookPages[ind2]->getName() << "\n\n";
		else
			cout << facebookMembers[ind1]->getName() << " is not more popular than " << facebookPages[ind2]->getName() << "\n\n";
	}
}

Facebook::~Facebook()
{
	deleteFacebookMembersArray();
	deleteFacebookPagesArray();
}

void Facebook::deleteFacebookMembersArray()
{
	int i;
	for (i = 0; i < facebookMembers.size(); i++)
		delete facebookMembers[i];

}

void Facebook::deleteFacebookPagesArray()
{
	int i;
	for (i = 0; i < facebookPages.size(); i++)
		delete facebookPages[i];

}