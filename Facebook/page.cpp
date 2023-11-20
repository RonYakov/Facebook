#include"page.h"
#include"member.h"


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

void Page::addPost(char type, string text, string nameOfFile, int color)
{
	Status* newStat = StatusFactory::createNewStatus(type, text,0, nameOfFile, color);

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

void Page::saveToFile(ofstream& facebookFile)
{
	facebookFile << name << endl;
	facebookFile << posts.size() << endl;
	for (int i = 0; i < posts.size(); i++)
	{
		posts[i]->saveToFile(facebookFile);
	}

	//The facebook members will save which page they follow
}

void Page::loadFromFile(ifstream& facebookFile)
{
	int postSize;
	string getEnter;
	
	getline(facebookFile, getEnter);
	getline(facebookFile, name);
	facebookFile >> postSize;

	for (int i = 0; i < postSize; i++)
	{
		posts.push_back(StatusFactory::loadFromFile(facebookFile));
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