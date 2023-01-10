#pragma once
#include <iostream>
#include"status.h"
#include <vector>
#include <string>

#pragma warning(disable: 4996)

using std::vector;
using std::string;
using std::iterator;
using namespace std;

class Member;


class Page
{
	string name;
	vector<Member*> followers;
	vector<Status*> posts;

public:
	//cto'r
	Page(const string _name) : name(_name) {}
	Page(const Page& other) = delete;

	//-------------------------------------------------------------------

	const string getName() const { return name; }//The function return the page's name
	int getNumOfFollowers() const { return followers.size(); }//The function return the number of followers of the page
	int getNumOfPosts() const { return posts.size(); }//The function return the number of posts of the page

	//-------------------------------------------------------------------
	
	void addFollower(Member* newFollower);//The function add follower into followers vector
	bool addPost(const string _text);//The function gets a string, allocate a new post and add it to posts vector

	bool isMemberAFollower(const Member* member); //The function return true if member is a follower or false otherwise

	//-------------------------------------------------------------------

	void removeFollower(Member* member);//The function remove member from followers vector

	//-------------------------------------------------------------------

	void printAllPosts()const;//The function prints all posts
	void printFollowers()const;	//The function prints all page's followers

	//-------------------------------------------------------------------

	bool operator>(const Page& other) const //The function check who has more followers
	{
		return (followers.size() > other.followers.size());
	}
	bool operator>(const Member& other) const; //The function check who has more friends/followers

	//distractor
	~Page();
private:

	//-------------------------------------------------------------------

	void deletePostsArray();//The function deletes the posts array
};

class addPostToPageException : public exception
{
	string excep;

public:
	addPostToPageException()
	{
		excep = "Post allocation failed\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};