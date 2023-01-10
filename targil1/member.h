#pragma once
#include <iostream>
#include "date.h"
#include"status.h"
#include <vector>
#include <string>

#pragma warning(disable: 4996)

using std::vector;
using std::string;
using std::iterator;
using namespace std;

class Page;

class Member
{
	string name;
	Date birthday;
	vector<Status*> posts;
	vector<Member*> friends;
	vector<Page*> pages;
	

public:
	//cto'r
	Member(const string _name, int day, int month, int year) :name(_name), birthday(day, month, year) {}
	Member(const Member& other) = delete;

	//-------------------------------------------------------------------

	const string getName()const { return name; }//The function return the member's name
	const Date* getDate() const { return birthday.getDate(); }//The function return the member's birth day
	const vector<Member*> getFriends() const { return friends; } //The function return the members friends vector

	//-------------------------------------------------------------------

	void addFriend(Member* newMember, bool isFirst);//The function add member into friends vector
	void addPost(const string _text);//The function gets a string, allocate a new post and add it into posts vector
	void addPage(Page* newPage);//The function add page into page vector

	bool isMemberAFriend(const Member* member); //The function return true if member is a friend or false otherwise
	bool isAlreadyAFollower(const Page* page); //The function return true if page is in pages vector or false otherwise
	//-------------------------------------------------------------------

	void removeFriend(Member* member, bool isFirst);//The function remove member from friends vector 
	void removePage(Page* page);//The function remove a page from pages vector 


	//-------------------------------------------------------------------

	void printLastTenPostsOfMyFriends()const; //The function prints lasts 10 posts of my friends
	void printAllPosts()const;//The function prints all posts
	void printLastTenPosts()const;//The function prints lasts 10 posts
	void printFriends()const;//The function prints all member friends
	void printPages()const;//The function prints all member's liked pages

	//-------------------------------------------------------------------
	
	Member& operator+= (Member& newFriend) ////The function add member into friends vector
	{
		addFriend(&newFriend, true);
		return *this;
    }

	Member& operator+= (Page& newPage) //The function add page into page vector
	{
		addPage(&newPage);
		return *this;
	}

	bool operator>(const Member& other) const //The function check who has more friends
	{
		return (friends.size() > other.friends.size());
	}
	bool operator>(const Page& other) const; //The function check who has more friends/followers

	//distractor
	~Member();

private:
	//-------------------------------------------------------------------

	void deletePostsArray();//The function delete the posts array
};

class addFriendException : public exception
{
	string excep;

public:
	addFriendException(Member* member1, Member* member2);

	const char* what() const
	{
		return excep.c_str();
	}
};

class removeFriendException : public exception
{
	string excep;

public:
	removeFriendException(Member* member1, Member* member2);

	const char* what() const
	{
		return excep.c_str();
	}
};

class addPageException : public exception
{
	string excep;

public:
	addPageException(Member* _member, Page* _page);

	const char* what() const
	{
		return excep.c_str();
	}
};

class removePageException : public exception
{
	string excep;

public:
	removePageException(Member* _member, Page* _page);
	

	const char* what() const
	{
		return excep.c_str();
	}
};

class addPostToMemeberException : public exception
{
	string excep;

public:
	addPostToMemeberException()
	{
		excep = "Post allocation failed\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};
