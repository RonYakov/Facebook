#pragma once
#include <iostream>
#include "member.h"
#include "page.h"
#include <vector>
#include <string>

#pragma warning(disable: 4996)

using std::vector;
using std::string;
using std::iterator;
using namespace std;

class notFindAMemberException : public exception
{
	string excep;
public:
	notFindAMemberException(string name)
	{
		excep = "The member ";
		excep += name;
		excep += " wasn't found.\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class findAMemberException : public exception
{
	string excep;
public:
	findAMemberException(string name)
	{
		excep = "The member ";
		excep += name;
		excep += " already exist.\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class notFindAPageException : public exception
{
	string excep;
public:
	notFindAPageException(string name)
	{
		excep = "The page ";
		excep += name;
		excep += " wasn't found.\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class findAPageException : public exception
{
	string excep;
public:
	findAPageException(string name)
	{
		excep = "The page ";
		excep += name;
		excep += " already exist.\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class IsNameTheSameException : public exception
{
	string excep;
public:
	IsNameTheSameException(string name)
	{
		excep = "The name ";
		excep += name;
		excep += " Used twice.\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class typeForStatusException : public exception
{
	string excep;

public:
	typeForStatusException()
	{
		excep = "Invalid type input\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class Facebook
{
	vector<Member*> facebookMembers;
	vector<Page*> facebookPages;

public:
	//c'tor
	Facebook();
	Facebook(const Facebook& other) = delete;

	void menu();//The function run facebook menu

	//distractor
	~Facebook();
private:
	void startFacebook();//The function put default info in facebook system

	void printMenu();//The function prints facebook menu

	void clearBuffer();//The function clear the buffer
	void CheckMemberOrPage(char& memberOrPage);//The function checks if the user want member or page

	void addMemberToFacebook();//The function add member to facebook
	void addPageToFacebook();//The function add page to facebook
	void addPostToPageOrMember();//The function add post to page/member
	void presentAllPostsOfMemberOrPage();//The function present all posts of member/page
	void presentLastTenPostsOfMemberFriends();//The function present last ten posts of member/page
	void makeANewFriendship();//The function make a new facebook friendship
	void unfriendship();//The function unfriend two facebook's member
	void followAFanPage();//The function make a member follow a facebook page
	void unfollowAFanPage();//The function unfollow a members to facebook page
	void presentAllFriendsOrFollowers();//The function present all friends of a member / followeres of a page
	void checkWhoIsMorePopular();//The function checks who is more popular in Facebook

	void checkIfNamesEqual(string name1, string name2);//The function gets two strings and checks if they are equal

	void getNameFromUser(string& name, char pageOrMember, bool isFirst = true);//The function gets a name from the user

	void getStatusType(char& type, string& fileName, int& color);

	//Prints facebook info
	void printAllArr();
	void printPagesArr();
	void printMembersArr();

	//Delete facebook info
	void deleteFacebookMembersArray();
	void deleteFacebookPagesArray();

	int findAMember(const string name, bool WantToFind = true);//The function try to find a facebook member according to the name
	int findAPage(const string name, bool WantToFind = true);//The function try to find a facebook page according to the name
};
