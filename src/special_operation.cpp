#include<iostream>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<tuple>
#include<algorithm>
#include boardFunction.h
using namespace std;

//goal: -2 meets 2, get 0; -2 meets -2, get -4(addition); others, no change



//assume there exists a negative number
void special_moveTile(gameBoard gb, vector<int>vector_)
{

	//count the number of zeros in the vector;
	int count = 0;
	for (int i = 0; i < vector_.size(); i++)
  	{
    	if (vector_[i] == 0)
      	count++;
  	}

	//erase all the zeros in the vector
	vector_.erase(remove(vector_.begin(), vector_.end(), 0), vector_.end());	

	//find the number and the position of the negative number
	vector<int>pos;
	int num = 0;
	for (int i = 0; i < vector_.size(); ++i)
	{
		if (vector_[i]<0)
		{
			pos.push_back(i);
			num ++;	
		}
	}

	// check the neighbor of each negative elements and make transformations if they are the opposite
	for (int i = 0; i < num; ++i)
	{
		int j = pos[i];
		if (j==0)
		{
			if (vector_[j] == -1*vector_[j+1])
			{
				vector_[j] = 0;
				vector_[j+1] = 0;
			}
		}
		else if (vector_[j] == -1*vector_[j-1])
		{
			vector_[j-1] = 0;
			vector_[j] = 0;
		}
		else if (vector_[j] == -1*vector_[j+1] && j != vector_.size())
		{
			vector_[j] = 0;
			vector_[j+1] = 0;
		}
	}

	//add back zeros to the vector_ and merge the tiles
	for (int i = 1; i <= count; ++i)
	{
		vector_.push_back(0);
		mergeTile(gb,vector_);
	}
}


//check if there is a negative integer in the vector and execute

void spe_check(gameBoard gb, vector<int> vec_)
{
	for (int i = 0; i < vec_.size(); ++i)
	{
		if (vec_[i]<0)
		{
			special_moveTile(gb,vec_);
			break;
		}
	}

}
