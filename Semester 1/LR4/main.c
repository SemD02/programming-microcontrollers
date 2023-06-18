typedef struct list_
{
	struct list_ *follow;
	__UINT16_TYPE__ data;
}list;
list * createList(__UINT16_TYPE__ data);
list * push(list * root,__UINT16_TYPE__ data);
void popPtr(list * root,list * this);
list * deleteRoot(list * root);
list *  sort(list * root);
__UINT8_TYPE__ pop(list * root, __UINT16_TYPE__ deletingValue);

list * createList(__UINT16_TYPE__ data)
{
	list * root=(list *)(calloc(1,sizeof(list)));
	root->follow=(list *)0;
	root->data = data;
	return root;
}
list * push(list * root,__UINT16_TYPE__ data)
{
	if(root==(list *)0)
	{
		return createList(data);
	}
	else
	{
		list *follow=(list *)(calloc(1,sizeof(list)));
		while(root->follow!=(list *)0)
				root=root->follow;
		root->follow=follow;
		follow->data=data;
		return follow;
	}
}
void popPtr(list * root,list * this)
{
	while(root->follow!=(list *)0)
			if(root->follow==this)
			{
				root->follow = this->follow;
				free(this);
				return;
			}
			else
				root=root->follow;
}
__UINT8_TYPE__ pop(list * root, __UINT16_TYPE__ deletingValue)
{
	list * previous=root;
	while(root->follow!=(list *)0)
			if(root->data==deletingValue)
			{
				previous->follow=root->follow;
				free(root);
				return 1;
			}
			else
				{
					previous=root;
					root=root->follow;	
				}
	return 0;
}


list * deleteRoot(list * root)
{
	list *follow=root->follow;
	if(root!=(list *)0)
		free(root);	
	return follow;
}

list * sort(list * root)
{
	list * newRoot=root;
	list *i=root;
	list *j;
	list *previousI=i; 
	list * previosForMaxList=(list*)0;
	while(i->follow!=(list *)0)
	{
		list *u=i;
		j=i->follow;
		__UINT16_TYPE__ max=i->data;
		while(j!=(list *)0)
		{
			if(max<j->data)
			{
				max=j->data;
				previosForMaxList=u;
			}
			u=j;
			j=j->follow;
		}
		if(max!=i->data)
		{
			list * followMax=previosForMaxList->follow->follow;
			list * followI=previousI->follow->follow;
			list * maxList=previosForMaxList->follow;	
			if(previousI==i)
			{	
				newRoot=maxList;
				if(maxList==followI)
				{							
					maxList->follow=followI;
					previosForMaxList->follow=i;
					i->follow=followMax;
				}
				else
				{
					maxList->follow=i;
					previosForMaxList->follow=followMax;
				}
			}
			else
			{
				previousI->follow=maxList;
				i->follow=followMax;
				if(maxList==followI)
				{
					maxList->follow=i;
				}
					else
				{
					maxList->follow=followI;
					previosForMaxList->follow=i;
				}
			}
			i=maxList;
		}
		previousI=i;
		i=i->follow;
		max=i->data;
		
	}
	return newRoot;
}

int main()
{
	list * root = createList(11);
	push(root,1);
	push(root,13);
	push(root,50);
	push(root,2);
	push(root,10);
	list * temp = push(root,4);
	push(root,5);
	pop(root,50);
	push(root,6);
	push(root,7);
	root=deleteRoot(root);
	popPtr(root,temp);
	root=sort(root);
	return 0;
}
