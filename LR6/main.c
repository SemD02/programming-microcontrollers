typedef struct state_
{
	__UINT8_TYPE__ thisState:3;
	__UINT8_TYPE__ nextState:3;
	__UINT8_TYPE__ insert:4;
	__UINT8_TYPE__ pour_water:1;
	__UINT8_TYPE__ Change1:1;
	__UINT8_TYPE__ Change2:1;
	__UINT8_TYPE__ Change22:1;
	__UINT8_TYPE__ Change5:1;
	__UINT8_TYPE__ Change10:1;
}state;
typedef struct
{
	state * arrState;
	__UINT32_TYPE__ size;
}tableState;
void addStateToTableState(tableState * ts,state this);
state insertMoney(state thisState,tableState * ts ,__UINT8_TYPE__ X);
tableState * createTableState(__UINT8_TYPE__ X);
state setStartState(void);
state insertManyMoney(state thisSt, tableState *ts, __UINT8_TYPE__ sumX);
void getWater(void);
void getWater(void)
{
	//printf("You water, ser\n");
}

void addStateToTableState(tableState * ts,state thisState)
{
	ts->size++;
	ts->arrState=(state*)realloc(ts->arrState,sizeof(state)*ts->size);
	ts->arrState[ts->size-1].thisState=thisState.thisState;
	ts->arrState[ts->size-1].nextState=thisState.nextState;
	ts->arrState[ts->size-1].insert=thisState.insert;
	ts->arrState[ts->size-1].pour_water=thisState.pour_water;
	ts->arrState[ts->size-1].Change1=thisState.Change1;
	ts->arrState[ts->size-1].Change2=thisState.Change2;
	ts->arrState[ts->size-1].Change22=thisState.Change22;
	ts->arrState[ts->size-1].Change5=thisState.Change5;
	ts->arrState[ts->size-1].Change10=thisState.Change10;
}
state insertMoney(state thisSt,tableState * ts ,__UINT8_TYPE__ X)
{
	__UINT32_TYPE__ i;
	for(i=0;i<ts->size;i++)
	{
		if(ts->arrState[i].thisState==thisSt.thisState&&ts->arrState[i].insert==X)
		{
			state temp =ts->arrState[i];
			temp.thisState=temp.nextState;
			temp.insert=0;
			if(temp.pour_water)
				getWater();
			return temp;
		}	
	}
	return thisSt;
}
state insertManyMoney(state thisSt, tableState *ts, __UINT8_TYPE__ sumX)
{
	while(sumX>0)
	{
		if(sumX-10>=0)
		{
			sumX-=10;
			thisSt =insertMoney(thisSt,  ts , 10);
		}
		else if(sumX-5>=0)
		{
			sumX-=5;
			thisSt =insertMoney(thisSt,  ts , 5);
		}
		else if(sumX-2>=0)
		{
			sumX-=2;
			thisSt =insertMoney(thisSt,  ts , 2);
		}
		else
		{
			sumX--;
			thisSt =insertMoney(thisSt,  ts , 1);
		}
	}
	return thisSt;
}
state setStartState()
{
	state s;
	s.thisState=0;
	s.nextState=0;
	s.insert=0;
	s.pour_water=0;
	s.Change1=0;
	s.Change2=0;
	s.Change22=0;
	s.Change5=0;
	s.Change10=0;
	return s;
}
tableState * createTableState(__UINT8_TYPE__ X)
{
	tableState * ts=calloc(1,sizeof(tableState ));
	ts->arrState=(state*)0;
	ts->size=0;
	__UINT32_TYPE__ i;
	for(i=0;i<4*X;i++)
	{
		__UINT8_TYPE__ ins[4]={1,2,5,10};
		state temp=setStartState();
		temp.thisState=i/4;
		temp.insert=ins[i%4];
		temp.nextState=(temp.thisState+temp.insert)>X?0:(temp.thisState+temp.insert);
		if(temp.nextState==0)
		{	
			__INT8_TYPE__ change=(temp.thisState+temp.insert)-X;
			temp.pour_water=1;
			if(change>0&&change%10==0)
			{
				change-=10;
				temp.Change10=1;
			}
			if(change>0&&change%5==0)
			{
				change-=5;
				temp.Change5=1;
			}
			if(change>0&&change%4==0)
			{
				change-=4;
				temp.Change22=1;
			}
			if(change>0&&change%2==0)
			{
				change-=2;
				temp.Change2=1;
			}
			if(change>0)
			{
				change--;
				temp.Change1=1;
			}
		}
		addStateToTableState(ts,temp);
	}
	return ts;
}

int main()
{
	__UINT8_TYPE__ X=8,n=5;
	
	__UINT8_TYPE__ * insertingMoney=calloc(n,sizeof(__UINT8_TYPE__));
	insertingMoney[0]=1;
	insertingMoney[1]=1;
	insertingMoney[2]=5;
	insertingMoney[3]=2;
	insertingMoney[4]=10;
	tableState * ts=createTableState(X);
	state thisState=setStartState();
	while(1)
	{
		thisState=insertManyMoney(thisState,ts,17);
	}
	return 0;
}
