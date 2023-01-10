#include"page.h"
#include"member.h"
using namespace std;

bool Page::operator>(const Member& other) const
{
	return (followers.size() > other.getFriends().size());
}

void Page::addFollower(Member* newMember)
{
	followers.push_back(newMember);
}

bool Page::isMemberAFollower(const Member* member)
{
	for (int i = 0; i < followers.size(); i++)
		if (followers[i] == member)
			return false;

	return true;
}

bool Page::addPost(const string _text)
{
	Status* newStat = new Status(_text);

	if (newStat != nullptr)
		posts.push_back(newStat);

	else
		throw addPostToPageException();
}

void Page::removeFollower(Member* member)
{
	bool stop = false;
	vector<Member*>::iterator itr = followers.begin();

	for (; !stop; ++itr)
		if (*itr == member)
			stop = true;

	followers.erase(--itr);
}

void Page::printAllPosts()const
{
	if (posts.size() == 0)
		cout << "There are no posts\n";
	else
	{

		for (int i = 0; i < posts.size(); i++)
		{
			cout << name << ": " << endl;
			posts[i]->printStatus();
			cout << "\n";
		}
	}
}

void Page::printFollowers()const
{
	cout << name << "'s followers:" << endl;

	if (followers.size() == 0)
		cout << "There are no followers\n";
	else
	{

		cout << "---------------------\n";
		cout << "index | Name \n";
		cout << "------|--------------\n";

		for (int i = 0; i < followers.size(); i++)
		{
			printf("%6d", i);
			cout << "| " << followers[i]->getName() << endl;
		}
	}
}

void Page::deletePostsArray()
{
	for (int i = 0; i < posts.size(); i++)
		delete posts[i];

}

Page:: ~Page()
{
	deletePostsArray();
}