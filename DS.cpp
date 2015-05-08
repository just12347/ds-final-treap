#include "interactive/ds_finalproject.h"
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cstdio>
using namespace std;

struct Node{
	Node *left,*right;
	int priority;
	ItemList::ItemType a;
	Node() {}
	Node(string t, string _v1)
	{
		left=right=(Node*)NULL;
		a.movie_id = t;
		a.movie_information = _v1;
		priority=((rand()<<30)+(rand()<<15)+rand());
	}

};

class Treap{
	public:
		Treap();
		
		void rotateleft(Node* &T);
		void rotateright(Node* &T);
		void del(string t);
		Node* query(Node* root, string t);
		Node* find(string t);
		
		void printt();
		void add(string t, string v1);
	private:
		Node* root;
		Node* getNode(string t, string v1);
		void print(Node* root);
		void insert(Node* &root,string t, string v1);
		void remove (Node* &root,string t);
		
};

Treap::Treap()
{
	srand(time(0));
	root=NULL;
	
}


Node* Treap::getNode(string t, string v1)
{
	return new Node(t,  v1);
	
}

void Treap:: rotateleft(Node* &T)
{
	Node* T1 = T->right;
	T->right = T1->left;
	T1->left = T;
	T = T1;
}

void Treap::rotateright(Node* &T)
{
	Node* T1 = T->left;
	T->left = T1->right;
	T1->right = T;
	T = T1;
	
}

void Treap::insert(Node* &root,string t, string v1)
{

	if (root==NULL)
	{
		root = getNode(t,v1);
		return ;
		
	}
	else
	{
	
		if ( t < root->a.movie_id)
		{   
			if (root->left==NULL)
			{
				root->left= getNode(t,v1);
			}
			else
			{
				insert (root->left,  t,  v1);
				if (root->left->priority<root->priority)
					rotateright(root);
			}	
		}
	 	else if (t>root->a.movie_id)
		{   
			if (root->right==NULL)
			{
				root->right= getNode(t,v1);
			}
			else
			{
				insert (root->right,  t,  v1);
				if (root->right->priority<root->priority)
					rotateleft(root);
			}	
	
		}
	}
}
void Treap::add(string t, string v1)
{
	insert(root,t, v1);
}

void Treap::del(string t)
{
	remove(root ,t);
}

void Treap::remove(Node* &root,string t)
{
	if(root!=NULL)
	{
		if(t<root->a.movie_id )
			remove(root->left,t);
		else if (t>root->a.movie_id )
			remove(root->right,t);
		else 
		{
			if(root->left==NULL && root->right==NULL)
			{
				delete root;
				root=NULL;
				return;
			}
			else if(root->left==NULL)
			{
				
				root=root->right;
				
			}
			else if(root->right==NULL)
			{
				root=root->left;
				
			}
			else
			{
			
						
				if (root->left->priority<root->right->priority)
				{
					rotateright(root);
					remove(root->right,t);
				}
				else 
				{
					rotateleft(root);
					remove(root->left,t);			
				}
			}
		}
	}
	else return;
}  

Node* Treap::query(Node* root, string t)
{
	if (root==NULL) return root;
	else
	{
	
		if (root->a.movie_id==t)return root;
		else if (root->a.movie_id<t ) return query (root->right,t);
		else if (root->a.movie_id>t ) return query (root->left,t) ;
		else return NULL;
	
	}
}

Node* Treap::find(string t)
{
	return query(root,t);
}

void Treap::print(Node* root)
{
	if(root==NULL) 
		return;
	else
	{
		if(root->left) print(root->left);
		//cout<<root->key<<"  {  "<<root->v1<<", "<<root->v2<<", "<<root->v3<<"  }"<<endl;
		if(root->right) print(root->right);
    
	}
}

void Treap::printt()
{
	print(root);
}


Treap data;


//---------------------------ItemList-----------------------

void ItemList::insertItem(ItemType &item) throw(ItemException){
	
	if (data.find(item.movie_id)){
		throw ItemException(
	 			"ItemException: The movie is not found in the Table.");
	}
		//cout<<"This movie is already in the Table"<<endl;
	else data.add(item.movie_id,item.movie_information);
}

void ItemList::deleteItem(KeyType &item) throw(ItemException){
	
	Node* temp=data.find(item);
	if(!temp){
		throw ItemException(
	 			"ItemException: The movie is not found in the Table.");
	}
		//cout<<"This movie is not found in the Table"<<endl;
	else
	{
		//cout<<temp->key<<","<<temp->v1<<","<<temp->v2<<","<<temp->v3<<endl;
		data.del(item);
		
	}
}

ItemList::ItemType ItemList::retrieveItem(KeyType key) throw(ItemException){

	Node* temp=data.find(key);
	ItemList::ItemType newItem;
	if(!temp){
		throw ItemException(
	 			"ItemException: The movie is not found in the Table.");
	}
		//cout<<"This movie is not found in the Table"<<endl;
	else
	{
		//cout<<temp->key<<"{"<<temp->v1<<"}"<<endl;
		newItem.movie_id = temp->a.movie_id;
		newItem.movie_information = temp->a.movie_information;
		return newItem;
	}
}

