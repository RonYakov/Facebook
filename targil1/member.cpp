#include"member.h"
#include"page.h"

using namespace std;

bool Member::operator>(const Page& other) const
{
	return (friends.size() > other.getNumOfFollowers());
}

void Member::addFriend(Member* newMember, bool isFirst)
{
	if (isFirst)
	{
		if (!isMemberAFriend(newMember))
		{
			friends.push_back(newMember);
			newMember->addFriend(this, false);
		}

		else
			throw addFriendException(newMember, this);
	}
	else
		friends.push_back(newMember);
}

void Member::addPage(Page* newPage)
{
	if (!isAlreadyAFollower(newPage))
	{
		pages.push_back(newPage);
		newPage->addFollower(this);
	}

	else
		throw addPageException(this, newPage);
}

bool Member::isMemberAFriend(const Member* member)
{
	for (int i = 0; i < friends.size(); i++)
		if (friends[i] == member)
			return true;

	return false;
}

bool Member::isAlreadyAFollower(const Page* page)
{
	for (int i = 0; i < pages.size(); i++)
		if (pages[i] == page)
			return true;

	return false;
}

void Member::addPost(char type, string text, string nameOfFile, int color)
{
	Status* newStat = StatusFactory::createNewStatus(type, text, nameOfFile, color);

	if (newStat != nullptr)
		posts.push_back(newStat);

	else
		throw addPostToMemeberException();
}

void Member::removeFriend(Member* member, bool isFirst)
{
	bool stop = false;

		vector<Member*>::iterator itr = friends.begin();
		vector<Member*>::iterator itrEnd = friends.end();

		for (; itr != itrEnd && !stop; ++itr)
			if (*itr == member)
				stop = true;


		if (stop)
		{
			friends.erase(--itr);
			if(isFirst)
				member->removeFriend(this, false);
		}

		else
		{
			throw removeFriendException(member, this);
		}
}

void Member::removePage(Page* page)
{
	bool stop = false;
	vector<Page*>::iterator itr = pages.begin();
	vector<Page*>::iterator itrEnd = pages.end();

	for (; itr != itrEnd && !stop; ++itr)
		if (*itr == page)
			stop = true;


	if (stop)
	{
		pages.erase(--itr);
		page->removeFollower(this);
	}

	else
	{
		throw removePageException(this, page);
	}
}

void Member::printAllPosts()const
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

void Member::printLastTenPostsOfMyFriends()const
{
	for (int i = 0; i < friends.size(); i++)
	{
		friends[i]->printLastTenPosts();
	}
}

void Member::printLastTenPosts()const
{
	if (posts.size() == 0)
		cout << "There are no posts\n";
	else
	{

		for (int i = 0; i < 10 && i < posts.size(); i++)
		{
			cout << name << ": " << endl;
			posts[i]->printStatus();
			cout << "\n";
		}
	}
}

void Member::printFriends()const
{
	cout << name << "'s friends:" << endl;

	if (friends.size() == 0)
		cout << "There are no Friends\n";
	else
	{

		cout << "---------------------\n";
		cout << "index | Name \n";
		cout << "------|--------------\n";

		for (int i = 0; i < friends.size(); i++)
		{
			printf("%6d", i);
			cout << "| " << friends[i]->getName() << endl;
		}
	}
}

void Member::printPages()const
{
	cout << name << "'s pages" << endl;

	if (pages.size() == 0)
		cout << "There are no pages\n";
	else
	{
		cout << "---------------------\n";
		cout << "index | Name \n";
		cout << "------|--------------\n";

		for (int i = 0; i < pages.size(); i++)
		{
			printf("%6d", i);
			cout << "| " << pages[i]->getName() << endl;
		}
	}
}

void Member::deletePostsArray()
{
	for (int i = 0; i < posts.size(); i++)
		delete posts[i];
}

Member:: ~Member()
{
	deletePostsArray();
}

addFriendException::addFriendException(Member* member1, Member* member2)
{
	excep = "The member ";
	excep += member1->getName();
	excep += " is already a friend of ";
	excep += member2->getName();
	excep += "\n\n";
}

removePageException::removePageException(Member* _member, Page* _page)
{
	excep = "The member ";
	excep += _member->getName();
	excep += " wasn't a follower of ";
	excep += _page->getName();
	excep += "\n\n";
}

addPageException::addPageException(Member* _member, Page* _page)
{
	excep = "The member ";
	excep += _member->getName();
	excep += " is already a follower of ";
	excep += _page->getName();
	excep += "\n\n";
}

removeFriendException::removeFriendException(Member* member1, Member* member2)
{
	excep = "The member ";
	excep += member1->getName();
	excep += " wasn't a friend of ";
	excep += member2->getName();
	excep += "\n\n";
}
