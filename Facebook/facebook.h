#pragma once
#include <iostream>
#include "member.h"
#include "page.h"
#include <vector>
#include <string>

#pragma warning(disable: 4996)

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

enum{ 
	ADD_MEMBER = 1, ADD_PAGE = 2, ADD_POST = 3, PRESENT_POST = 4,
	PRESENT_10_POST = 5, FRIENDSHIP = 6, UNFRIENDSHIP = 7, ADD_FOLLOWER = 8,
	UNFOLLOW = 9, PRESENT_ALL_FACE = 10, PRESENT_ALL_MEM = 11, POPULAR = 12,
	EXIT = 13
};

class Facebook
{
	vector<Member*> facebookMembers;
	vector<Page*> facebookPages;
	string facebookFile;
public:
	//c'tor
	Facebook(string _facebookFile);
	Facebook(const Facebook& other) = delete;

	void menu();//The function run facebook menu

	//distractor
	~Facebook();
private:
	void startFacebook();//The function put default info in facebook system

	void printMenu() const;//The function prints facebook menu

	void clearBuffer() const;//The function clear the buffer
	void CheckMemberOrPage(char& memberOrPage) const;//The function checks if the user want member or page

	void addMemberToFacebook();//The function add member to facebook
	void addPageToFacebook();//The function add page to facebook
	void addPostToPageOrMember();//The function add post to page/member
	void presentAllPostsOfMemberOrPage() const;//The function present all posts of member/page
	void presentLastTenPostsOfMemberFriends() const;//The function present last ten posts of member/page
	void makeANewFriendship();//The function make a new facebook friendship
	void unfriendship();//The function unfriend two facebook's member
	void followAFanPage();//The function make a member follow a facebook page
	void unfollowAFanPage();//The function unfollow a members to facebook page
	void presentAllFriendsOrFollowers() const;//The function present all friends of a member / followeres of a page
	void checkWhoIsMorePopular() const;//The function checks who is more popular in Facebook

	void checkIfNamesEqual(string name1, string name2) const;//The function gets two strings and checks if they are equal

	void getNameFromUser(string& name, char pageOrMember, bool isFirst = true) const;//The function gets a name from the user

	void getStatusType(char& type, string& fileName, int& color) const;

	//Prints facebook info
	void printAllArr() const;
	void printPagesArr() const;
	void printMembersArr() const;

	void saveToFile();//save data to file
	void loadFromFile();//load data from file
	void loadFriendshipsFromFile(ifstream& f_File);

	//Delete facebook info
	void deleteFacebookMembersArray();
	void deleteFacebookPagesArray();

	int findAMember(const string name, bool WantToFind = true) const;//The function try to find a facebook member according to the name
	int findAPage(const string name, bool WantToFind = true) const;//The function try to find a facebook page according to the name
};
