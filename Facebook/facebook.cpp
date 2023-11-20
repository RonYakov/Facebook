#include"facebook.h"

using std::vector;
using std::string;
using std::iterator;
using namespace std;

Facebook::Facebook(string _facebookFile):facebookFile(_facebookFile)
{
	startFacebook();
	menu();
}

void Facebook::startFacebook()
{
	loadFromFile();
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
		case ADD_MEMBER:
			addMemberToFacebook();
			break;

		case ADD_PAGE:
			addPageToFacebook();
			break;

		case ADD_POST:
			addPostToPageOrMember();
			break;

		case PRESENT_POST:
			presentAllPostsOfMemberOrPage();
			break;
		
		case PRESENT_10_POST:
			presentLastTenPostsOfMemberFriends();
			break;

		case FRIENDSHIP:
			makeANewFriendship();
			break;

		case UNFRIENDSHIP:
			unfriendship();
			break;

		case ADD_FOLLOWER:
			followAFanPage();
			break;

		case UNFOLLOW:
			unfollowAFanPage();
			break;

		case PRESENT_ALL_FACE:
			printAllArr();
			break;

		case PRESENT_ALL_MEM:
			presentAllFriendsOrFollowers();
			break;

		case POPULAR:
			checkWhoIsMorePopular();
			break;

		case EXIT:
			cout << "bye bye :)\n";
			stop = true;
			saveToFile();
			break;

		default:
			cout << "Invalid input!! Please try again\n\n";
			clearBuffer();
			break;
		}

	}
}

void Facebook::clearBuffer() const
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Facebook::printMenu() const
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
	catch(exception& ex)
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

	catch(exception& ex)
	{
		cout << ex.what();
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
	catch (exception& ex)
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

void Facebook::CheckMemberOrPage(char& memberOrPage) const
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
	char PageOrMember, statusType;
	string name, text, fileName;
	int ind, color;

	cout << "03 - Add a new status to a member / fan page: \n\n";
	
	CheckMemberOrPage(PageOrMember);

	getNameFromUser(name, PageOrMember);

	if (PageOrMember == '0')
	{
		try 
		{
			ind = findAMember(name);
		}
		catch(exception& ex)
		{
			cout << ex.what();
			return;
		}

		try {
			getStatusType(statusType, fileName, color);
		}

		catch (exception& ex)
		{
			cout << ex.what();
			return;
		}

		cout << "Please enter your text here: \n";
		getline(cin, text);

		try
		{
			facebookMembers[ind]->addPost(statusType, text, fileName, color);
		}

		catch (exception& ex)
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
		catch (exception& ex)
		{
			cout << ex.what();
			return;
		}

		try {
			getStatusType(statusType, fileName, color);
		}

		catch (exception& ex)
		{
			cout << ex.what();
			return;
		}

		cout << "please enter your text here:\n";
		getline(cin, text);

		try 
		{
			facebookPages[ind]->addPost(statusType, text, fileName, color);
		}
		catch (exception& ex)
		{
			cout << ex.what();
			return;
		};
	}

	cout << "\n\n";
}

void Facebook::getStatusType(char& type, string& fileName, int& color) const
{
	cout << "Please enter the character according to type of status: \n";
	cout << "T - text\nI - image\nV - video\n";
	cin >> type;

	if (type == 'I' || type == 'V')
	{
		cout << "Please enter the file's name: ";
		cin >> fileName;
		cout << "For Black & White color press 0, else press 1: ";
		cin >> color;

		cout << "\n\n";
	}

	else if (type != 'T')
	{
		throw typeForStatusException();
	}

	clearBuffer();
}

int Facebook::findAMember(const string name, bool WantToFind) const
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

int Facebook::findAPage(const string name, bool WantToFind) const
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

void Facebook::presentAllPostsOfMemberOrPage() const
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

		catch (exception& ex)
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

		catch (exception& ex)
		{
			cout << ex.what();
			return;
		}
		facebookPages[index]->printAllPosts();
	}
	
	cout << "\n\n";
}

void Facebook::presentLastTenPostsOfMemberFriends() const
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
	catch (exception& ex)
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
	catch (exception& ex)
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
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		checkIfNamesEqual(name1, name2);
	}
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		*facebookMembers[index1] += *facebookMembers[index2];
	}
	catch (exception& ex)
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
	catch (exception& ex)
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
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		checkIfNamesEqual(name1, name2);
	}
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}

	try
	{
		facebookMembers[index1]->removeFriend(facebookMembers[index2], true);
	}
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}

	cout << "\n\n";
}

void Facebook::checkIfNamesEqual(string name1, string name2) const
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
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}
	
	getNameFromUser(name2, '1', false);

	try
	{
		index2 = findAPage(name2);
	}
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}
	try
	{
		*facebookMembers[index1] += *facebookPages[index2];
	}

	catch (exception& ex)
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
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}
	
	getNameFromUser(name2, '1', false);

	try
	{
		index2 = findAPage(name2);
	}
	catch (exception& ex)
	{
		cout << ex.what();
		return;
	}
	try
	{
		facebookMembers[index1]->removePage(facebookPages[index2]);
	}

	catch (exception& ex)
	{
		cout << ex.what();
	}

	cout << "\n\n";
}

void Facebook::presentAllFriendsOrFollowers() const
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

		catch (exception& ex)
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

		catch (exception& ex)
		{
			cout << ex.what();
			return;
		}
		facebookPages[index]->printFollowers();
	}

	cout << "\n\n";
}

void Facebook::getNameFromUser(string& name,char pageOrMember, bool isFirst) const
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

void Facebook::printAllArr() const
{
	printMembersArr();
	printPagesArr();
}

void Facebook::printPagesArr() const
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

void Facebook::printMembersArr() const
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

void Facebook::checkWhoIsMorePopular() const
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
		catch (exception& ex)
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
		catch (exception& ex)
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
		catch (exception& ex)
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
		catch (exception& ex)
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

void Facebook::saveToFile()
{
	ofstream f_File(facebookFile, ios_base::trunc);

	f_File << facebookPages.size() << endl;
	for (int i = 0; i < facebookPages.size(); i++)
	{
		facebookPages[i]->saveToFile(f_File);
	}
	

	f_File << facebookMembers.size() << endl;
	for (int i = 0; i < facebookMembers.size(); i++)
	{
		facebookMembers[i]->saveDataToFile(f_File);
	}

	for (int i = 0; i < facebookMembers.size(); i++)
	{
		facebookMembers[i]->saveFriendsAndFollowersToFile(f_File);
	}
	
	f_File.close();
}

void Facebook::loadFromFile()
{
	int pagesSize, membersSize;
	char readEnter;
	ifstream f_File(facebookFile, ios_base::in);

	f_File >> pagesSize;
	for (int i = 0; i < pagesSize; i++)
	{
		facebookPages.push_back(new Page(f_File));
	}

	f_File >> membersSize;
	for (int i = 0; i < membersSize; i++)
	{
		facebookMembers.push_back(new Member(f_File));
	}

	loadFriendshipsFromFile(f_File);

	f_File.close();
}

void Facebook::loadFriendshipsFromFile(ifstream& f_File)
{
	int currPageSize, currFriendSize;
	string currName;
	string readEnter;

	for (int i = 0; i < facebookMembers.size(); i++)
	{
		f_File >> currPageSize;

		getline(f_File, readEnter);

		for (int j = 0; j < currPageSize; j++)
		{
			getline(f_File, currName);
			*facebookMembers[i] += *facebookPages[findAPage(currName)]; // There is no need to check exception
		}

		f_File >> currFriendSize;

		getline(f_File, readEnter);

		for (int j = 0; j < currFriendSize; j++)
		{
			getline(f_File, currName);
			*facebookMembers[i] += *facebookMembers[findAMember(currName)]; // There is no need to check exception
		}

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